#pragma once

#include <fstream>

#include "String.hpp"
#include "Log.hpp"

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
			length = (u32)file.tellg();
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