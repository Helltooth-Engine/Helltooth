#ifdef HT_OPENGL

#include "graphics/shaders/Shader.hpp"

namespace ht { namespace graphics {
	using namespace utils;

#define Stringify(type) #type

	int CompileShader(const char* source, ShaderType type) {
		u32 id = GL(glCreateShader((GLenum)type));
		GL(glShaderSource(id, 1, &source, 0));
		GL(glCompileShader(id));

		s32 result;
		GL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) {
			s32 length;
			GL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char* data = new char[length];
			GL(glGetShaderInfoLog(id, length, &length, data));
			HT_WARN("%s", source);
			HT_FATAL("Failed to compile %s shader!\n %s", Stringify(type), data);
			GL(glDeleteShader(id));
			return -1;
		}
		return id;
	}

	Shader::Shader(BufferLayout layout, utils::String vertexPath, utils::String fragmentPath, bool path) : m_Layout(layout) {
		m_Program = GL(glCreateProgram());
		u32 vertexID, fragmentID;

		if (!path) {
			vertexID = CompileShader(vertexPath.GetData(), ShaderType::VERTEX);
			fragmentID = CompileShader(fragmentPath.GetData(), ShaderType::FRAGMENT);
		}
		else {
			String vertData, fragData;
			
			vertData = FileUtils::ReadFile(VFS::Resolve(vertexPath));
			fragData = FileUtils::ReadFile(VFS::Resolve(fragmentPath));

			vertexID = CompileShader(vertData.GetData(), ShaderType::VERTEX);
			fragmentID = CompileShader(fragData.GetData(), ShaderType::FRAGMENT);
		}

		GL(glAttachShader(m_Program, vertexID));
		GL(glAttachShader(m_Program, fragmentID));

		GL(glLinkProgram(m_Program));

		GLint isLinked;
		glGetProgramiv(m_Program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE) {
		
			GLint maxLength = 0;
			glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &maxLength);
		
			char* data = new char[maxLength];
			GL(glGetProgramInfoLog(m_Program, maxLength, &maxLength, data));
		
			HT_FATAL("Failed to link program!\n %s", data);
			GL(glDeleteProgram(m_Program));
			delete[] data;
		}

		GL(glDetachShader(m_Program, vertexID));
		GL(glDetachShader(m_Program, fragmentID)); 

		GL(glDeleteShader(vertexID));
		GL(glDeleteShader(fragmentID));

		HT_ASSERT(layout.attributes.size() > 10, "[VertexBuffer] Layout attributes can not be bigger than 10!");
		GL(glGenVertexArrays(1, &m_VertexArray));
		GL(glBindVertexArray(m_VertexArray));
		GL(glBindVertexArray(0));

	}

	Shader::~Shader() {
		GL(glDeleteProgram(m_Program));
	}


	void Shader::SetUniformBuffer(UniformBuffer* buffer) {

	}

	void Shader::Start() {
		GL(glBindVertexArray(m_VertexArray));
		u32 offset = 0; 
		for (u32 i = 0; i < m_Layout.attributes.size(); i++) {
			u8 dataSize = DataTypeSize(m_Layout.attributes[i].type);
			GL(glEnableVertexAttribArray(i));
			GL(glVertexAttribPointer(i, m_Layout.attributes[i].count, (GLenum)m_Layout.attributes[i].type,
				(GLboolean)m_Layout.attributes[i].normalized, m_Layout.attributes[i].stride * dataSize, (GLvoid*)offset));
			offset += m_Layout.attributes[i].count * dataSize;
		}
		GL(glUseProgram(m_Program));
	}

} }


#endif
