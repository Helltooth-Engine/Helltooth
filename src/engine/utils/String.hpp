#pragma once

#include <string>
#include <vector>

#include "core/Internal.hpp"

namespace ht { namespace utils {

	class String {
	private:
		char* m_Data = nullptr;
		u32 m_Size;

		mutable u32 m_HashValue = 0;

	public:
		String();
		String(const String& other);
		String(const char* string);
		String(const std::string& string);
		String(char c, u32 rep = 1);

		~String();

		void Append(char c);
		void Append(const char* string);
		void Append(const String& string);
		void Append(const std::string& string);

		String Substring(u32 left, u32 right = (u32)-1) const;

		std::vector<String> Split(char delimiter);

		void Clear();

		u32 Hash() const;

		inline u32 GetSize() const { return m_Size; }
		inline const char* GetData() const { return m_Data; }

		inline bool EndsWith(char c) const { return m_Data[m_Size - 2] == c; }
		inline bool StartsWith(char c) const { return m_Data[0] == c; }

	public: // operator block

		inline friend String operator+(String left, char right) { left.Append(right); return left; }
		inline friend String operator+(String left, const char* right) { left.Append(right); return left; }
		inline friend String operator+(String left, const String& right) { left.Append(right); return left; }
		inline friend String operator+(String left, const std::string& right) { left.Append(right); return left; }

		inline void operator+=(char other) { Append(other); }
		inline void operator+=(const char* other) { Append(other); }
		inline void operator+=(const String& other) { Append(other); }
		inline void operator+=(const std::string& other) { Append(other); }

		inline bool operator==(const String& other) const { return (Hash() == other.Hash()); }
		inline bool operator!=(const String& other) const { return (Hash() != other.Hash()); }

		inline char operator[](u32 index) const { return m_Data[index]; }
	};

} }

namespace std {
	template <>
	struct hash<ht::utils::String> {
		std::size_t operator()(const ht::utils::String& k) const {
			return k.Hash();
		}
	};
}