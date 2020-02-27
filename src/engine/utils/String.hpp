/*
 * Copyright (c) 2020 Rareș-Nicolaie Ciorbă
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#pragma once

#include <string>
#include <vector>
#include <memory.h>

#include "core/Internal.hpp"

namespace ht { namespace utils {

	class String {
	private:
		char* m_Data = nullptr;
		uptr m_Size;

		mutable u32 m_HashValue = 0;

	public:
		String();
		String(const char* string);
		String(const String& string);
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

		inline uptr GetSize() const { return m_Size; }
		inline const char* GetData() const { return m_Data; }

		inline bool EndsWith(char c) const { return m_Data[m_Size - 1] == c; }
		inline bool StartsWith(char c) const { return m_Data[0] == c; }
		inline bool StartsWith(utils::String other) const { return memcmp(m_Data, other.m_Data, other.m_Size); }

	public:

		void operator=(const char* string);
		void operator=(const String& string);
		void operator=(const std::string& string);

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