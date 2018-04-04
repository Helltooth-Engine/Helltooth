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