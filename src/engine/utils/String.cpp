#include "String.hpp"


namespace ht { namespace utils {
	String::String()
		: m_Size(0) {
		m_Data = new char;
		m_Data[0] = 0;
	}

	String::String(const String& other) {
		m_Size = other.m_Size;
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, other.m_Data, m_Size + 1);
	}

	String::String(const char* string) {
		m_Size = strlen(string);
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, string, m_Size + 1);
	}

	String::String(const std::string& string) {
		m_Size = string.size();
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, string.c_str(), m_Size + 1);
	}

	String::String(char c, int rep) {
		m_Size = rep;
		m_Data = new char[m_Size + 1];
		for (unsigned int i; i < m_Size; i++)
			m_Data[i] = c;
	}
	
	String::~String() {
		if (m_Data)
			delete[] m_Data;
	}


	void String::Append(char c) {
		char* temp = new char[m_Size + 2]; // 1 for null terminated, 1 for the char to be added
		memcpy(temp, m_Data, m_Size);
		temp[m_Size + 1] = 0;
		temp[m_Size] = c;
		delete[] m_Data;
		m_Data = temp;
		m_Size++;
		m_HashValue = 0;
	}

	void String::Append(const char* string) {
		unsigned int stringSize = strlen(string);
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


	String String::Substring(unsigned int left, unsigned int right) {
		String result = String();
		if (right == (unsigned int)-1) { // 'till the end
			result.m_Size = m_Size - left;
			result.m_Data = new char[result.m_Size + 1];
			memcpy(result.m_Data, m_Data + left, result.m_Size);
			result.m_Data[result.m_Size + 1] = 0;
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


	void String::Clear() {
		if (m_Data) delete[] m_Data;
		m_Data = new char[1];
		m_Data[0] = 0;
		m_Size = 1;
		m_HashValue = 0;
	}


#define STRING_HASH_A 54059
#define STRING_HASH_B 76963
#define STRING_HASH_C 86969
#define STRING_HASH_FIRSTH 37

	unsigned int String::Hash() const {
		if (m_HashValue == 0) {
			unsigned h = STRING_HASH_FIRSTH;
			for (unsigned int i = 0; i < m_Size; i++) {
				h = (h * STRING_HASH_A) ^ (m_Data[i] * STRING_HASH_B);
			}

			m_HashValue = h % STRING_HASH_C;
		}
		return m_HashValue; // or return h % C;
	}


} }