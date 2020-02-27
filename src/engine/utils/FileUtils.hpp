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

#include <fstream>

#include "utils/String.hpp"
#include "utils/Log.hpp"

namespace ht { namespace utils {

	class FileUtils {
	public:
		inline static String ReadFile(String path) {
			std::fstream file;
			file.open(path.GetData(), std::fstream::in);
			if (!file.good())
				HT_ERROR("[FileUtils] File \"%s\" does not exist", path.GetData());

			u32 length;
			file.seekg(0, std::ios::end);
			length = static_cast<u32>(file.tellg());
			file.seekg(0, std::ios::beg);

			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			file.read(data, length);
			file.close();

			String a = data;
			delete[] data;

			return a;
		}

	};

} }