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

#include "Vfs.hpp"

namespace ht { namespace utils {

	std::unordered_map<String, std::vector<String>> VFS::mounts;

	void VFS::Mount(const String &virtualPath, const String &physicalPath) {
		String path = physicalPath;
		if (!path.EndsWith('/')) {
			HT_WARN("[VFS] Path \"%s\"does not end in forward slash.", physicalPath.GetData());
			path += '/';
		}
		mounts[virtualPath].push_back(path);
	}

	void VFS::Unmount(const String &path) {
		mounts[path].clear();
	}

	String VFS::Resolve(const String& path) {
		if (!path.StartsWith('/')) {
			HT_ASSERT(Exists(path), "[VFS] File does not exist!");
			return path;
		}

		String subPath = path.Substring(1);

		std::vector<String> dividedPath = subPath.Split('/');
		HT_ASSERT(!mounts[dividedPath[0]].empty() || mounts.find(dividedPath[0]) != mounts.end(), "[VFS] Mount point not found");

		String physicalPart;
		for (u32 i = 1; i < dividedPath.size(); i++) {
			if (i > 1)
				physicalPart += '/';
			physicalPart += dividedPath[i];
		}

		for (u32 i = 0; i < mounts[dividedPath[0]].size(); i++) {
			String physicalPath = mounts[dividedPath[0]][i];
			String path = physicalPath + physicalPart;
			if (Exists(path))
				return path;
		}

		HT_WARN("[VFS] Path \"%s\" could not be parsed", path.GetData());
		return String();
	}

} }