#include "String.hpp"


namespace ht { namespace utils {
	String::String()
		: m_Size(0) {
		m_Data = new char[1];
		m_Data[0] = 0;
	}

	String::String(const char* string) {
		m_Size = strlen(string);
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, string, m_Size + 1);
	}

	String::String(const String& string) {
		m_Size = string.m_Size;
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, string.m_Data, m_Size + 1);
	}

	String::String(const std::string& string) {
		m_Size = string.size();
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, string.c_str(), m_Size + 1);
	}

	String::String(char c, u32 rep) {
		m_Size = rep;
		m_Data = new char[m_Size + 1];
		for (u32 i = 0; i < m_Size; i++)
			m_Data[i] = c;
	}
	
	String::~String() {
		delete[] m_Data;
	}


	void String::Append(char c) {
		char* temp = new char[m_Size + 2];
		memcpy(temp, m_Data, m_Size);
		temp[m_Size + 1] = 0;
		temp[m_Size] = c;
		delete[] m_Data;
		m_Data = temp;
		m_Size++;
		m_HashValue = 0;
	}

	void String::Append(const char* string) {
		u32 stringSize = strlen(string);
		char* temp = new char[m_Size + stringSize + 1];
		memcpy(temp, m_Data, m_Size);
		memcpy(temp + m_Size, string, stringSize + 1);
		delete[] m_Data;
		m_Data = temp;
		m_Size += stringSize;
		m_HashValue = 0;
	}

	void String::Append(const String& string) {
		char* temp = new char[m_Size + string.m_Size + 1];
		memcpy(temp, m_Data, m_Size);
		memcpy(temp + m_Size, string.m_Data, string.m_Size + 1);
		delete[] m_Data;
		m_Data = temp;
		m_Size += string.m_Size;
		m_HashValue = 0;
	}

	void String::Append(const std::string& string) {
		char* temp = new char[m_Size + string.size() + 1];
		memcpy(temp, m_Data, m_Size);
		memcpy(temp + m_Size, string.c_str(), string.size() + 1);
		delete[] m_Data;
		m_Data = temp;
		m_Size += string.size();
		m_HashValue = 0;
	}


	String String::Substring(u32 left, u32 right) const{
		String result = String();
		if (right == (u32)-1) { // 'till the end
			result.m_Size = m_Size - left;
			result.m_Data = new char[result.m_Size + 1];
			memcpy(result.m_Data, m_Data + left, result.m_Size);
			result.m_Data[result.m_Size] = 0;
		}
		else {
			result.m_Size = right - left;
			result.m_Data = new char[result.m_Size + 1];
			memcpy(result.m_Data, m_Data + left, result.m_Size);
			result.m_Data[result.m_Size] = 0;
		}
		result.m_HashValue = 0;
		return result;
	}

	std::vector<String> String::Split(char delimiter) {
		std::vector<String> result;
		String split = "";
		for (u32 i = 0; i < m_Size; i++) {
			if (m_Data[i] == delimiter) {
				result.push_back(split);
				split = "";
				continue;
			}
			split += m_Data[i];
		}
		result.push_back(split);
		return result;
	}


	void String::Clear() {
		if (m_Data) delete[] m_Data;
		m_Data = new char[1];
		m_Data[0] = 0;
		m_Size = 1;
		m_HashValue = 0;
	}


	void String::operator=(const char* string) {
		m_Size = strlen(string);
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, string, m_Size + 1);
	}

	void String::operator=(const String& string) {
		m_Size = string.m_Size;
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, string.m_Data, m_Size + 1);
	}

	void String::operator=(const std::string& string) {
		m_Size = string.size();
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, string.c_str(), m_Size + 1);
	}

#define STRING_HASH_A 54059
#define STRING_HASH_B 76963
#define STRING_HASH_C 86969
#define STRING_HASH_FIRSTH 37

	u32 String::Hash() const {
		if (m_HashValue == 0) {
			u32 h = STRING_HASH_FIRSTH;
			for (u32 i = 0; i < m_Size; i++) {
				h = (h * STRING_HASH_A) ^ (m_Data[i] * STRING_HASH_B);
			}

			m_HashValue = h % STRING_HASH_C;
		}
		return m_HashValue; // or return h % C;
	}


} }