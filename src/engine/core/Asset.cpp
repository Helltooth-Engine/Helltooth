#include "Asset.hpp"

namespace ht { namespace core {
	using namespace Cereal;

	graphics::Texture* Asset::LoadTexture(utils::String path) {
		Buffer buffer(1);
		buffer.readFile(utils::VFS::Resolve(path).GetData());

		Database* database = new Database();
		database->read(buffer);

		graphics::Texture* result = nullptr;

		Object* object = database->getObject("texture2D");
		if (object != nullptr) {
			u32 width = static_cast<u32>(object->getField("width")->getValue<s32>());
			u32 height = static_cast<u32>(object->getField("height")->getValue<s32>());
			u32 bpp = static_cast<u32>(object->getField("bpp")->getValue<s32>());
			
			Array* pArray = object->getArray("pixels");

			byte* pixels = pArray->getRawArray<byte>(new byte[pArray->getCount()]);

			result = new graphics::Texture2D(pixels, width, height, graphics::GetFormat(bpp));
			
			delete[] pixels;
		}

		delete database;

		if (result == nullptr) {
			HT_FATAL("[Asset] Texture format not supported!");
		}

		return result;
	}

} }