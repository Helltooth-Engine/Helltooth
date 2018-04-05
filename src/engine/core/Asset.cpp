#include "Asset.hpp"
#include "cereal/Cereal.hpp"

namespace ht { namespace core {
	using namespace Cereal;
	using namespace entities;
	using namespace graphics;
	using namespace utils;

	Texture* Asset::LoadTexture(String path) {
		Buffer buffer(1);
		buffer.readFile(VFS::Resolve(path).GetData());

		Database* database = new Database();
		database->read(buffer);

		Texture* result = nullptr;

		Object* object = database->getObject("texture2D");
		if (object != nullptr) {
			u32 width = static_cast<u32>(object->getField("width")->getValue<s32>());
			u32 height = static_cast<u32>(object->getField("height")->getValue<s32>());
			u32 bpp = static_cast<u32>(object->getField("bpp")->getValue<s32>());
			
			Array* pArray = object->getArray("pixels");

			byte* pixels = pArray->getRawArray<byte>(new byte[pArray->getCount()]);

			result = new Texture2D(pixels, width, height, graphics::GetFormat(bpp));
			
			delete[] pixels;
		}

		delete database;

		if (result == nullptr) {
			HT_FATAL("%s", "[Asset] Texture format not supported!");
		}

		return result;
	}

	ModelComponent* Asset::LoadModel(String path) {
		Buffer buffer(1);
		buffer.readFile(VFS::Resolve(path).GetData());

		Database* database = new Database();
		database->read(buffer);

		ModelComponent* result = nullptr;

		Object* object = database->getObject("model");
		if (object != nullptr) {
			bool hasBones = object->getField("hasBones")->getValue<bool>();
			HT_ASSERT(!hasBones, "[Asset] Model with bones are not supported yet.");
			// TODO: Support bones

			Array* verticesData = object->getArray("verticesData");
			f32* vertexData = new f32[verticesData->getCount()];
			verticesData->getRawArray(vertexData);
			
			Array* indicesData = object->getArray("indicesData");
			u32* indexData = new u32[indicesData->getCount()];
			indicesData->getRawArray(reinterpret_cast<s32*>(indexData));

			result = new ModelComponent(vertexData, verticesData->getCount() * sizeof(f32));
			result->SetIndices(indexData, indicesData->getCount() * sizeof(u32));
		}

		delete database;

		if (result == nullptr) {
			HT_FATAL("%s", "[Asset] Model format not supported!");
		}
		
		return result;
	}

} }