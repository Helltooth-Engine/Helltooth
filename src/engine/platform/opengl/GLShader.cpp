#ifdef HT_OPENGL
#include "graphics/shaders/Shader.hpp"

namespace ht { namespace graphics {
	using namespace utils;

#define Stringify(type) #type

	int CompileShader(const char* source, ShaderType type) {
		u32 id = GL(glCreateShader(static_cast<GLenum>(type)));
		GL(glShaderSource(id, 1, &source, 0));
		GL(glCompileShader(id));

#if defined(HT_DEBUG)
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
#endif // HT_DEBUG
		return id;
	}

	Shader::Shader(BufferLayout* layout, const String& vertexPath, const String& fragmentPath, int path) : m_Layout(layout) {
		m_Program = GL(glCreateProgram());
		u32 vertexID, fragmentID;

		if ((path & ShaderLocationType::FROM_MEMORY) != 0) {
			vertexID = CompileShader(vertexPath.GetData(), ShaderType::VERTEX);
			fragmentID = CompileShader(fragmentPath.GetData(), ShaderType::FRAGMENT);
		}
		else if((path & ShaderLocationType::FROM_PATH) != 0) {
			String vertData, fragData;
			
			vertData = FileUtils::ReadFile(VFS::Resolve(vertexPath));
			fragData = FileUtils::ReadFile(VFS::Resolve(fragmentPath));
			
			if ((path & ShaderLocationType::FROM_HTSL) != 0) {
				htsl::Parser::Init();
				std::vector<std::string> result;
				result = htsl::Parser::Get()->Parse(vertData.GetData());
				m_Layout->SetSemanticNames(htsl::Parser::Get()->GetVertexInputLayout());
				modelLayout = true;
				vertData = result[0];

				result = htsl::Parser::Get()->Parse(fragData.GetData());
				fragData = result[0];

				htsl::Parser::End();
			}

			vertexID = CompileShader(vertData.GetData(), ShaderType::VERTEX);
			fragmentID = CompileShader(fragData.GetData(), ShaderType::FRAGMENT);
		}

		GL(glAttachShader(m_Program, vertexID));
		GL(glAttachShader(m_Program, fragmentID));

		GL(glLinkProgram(m_Program));

#ifdef HT_DEBUG
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
#endif // HT_DEBUG

		GL(glDetachShader(m_Program, vertexID));
		GL(glDetachShader(m_Program, fragmentID)); 

		GL(glDeleteShader(vertexID));
		GL(glDeleteShader(fragmentID));

		u32 vIndex = glGetUniformBlockIndex(m_Program, "Vertex");
		if (vIndex == (u32)-1) {
			HT_WARN("%s", "[Shader] No uniform block found called \"Vertex\", skipping it.");
		}
		else GL(glUniformBlockBinding(m_Program, vIndex, 0));

		u32 fIndex = glGetUniformBlockIndex(m_Program, "Fragment");
		if (fIndex == (u32)-1) {
			HT_WARN("%s", "[Shader] No uniform block found called \"Fragment\", skipping it.");
		}
		else GL(glUniformBlockBinding(m_Program, fIndex, 1));

	}

	Shader::~Shader() {
		GL(glDeleteProgram(m_Program));
		if (modelLayout) 
			delete m_Layout;
	}

	void Shader::Start() {
		GL(glUseProgram(m_Program));
	}

} }

#endif // HT_OPENGL