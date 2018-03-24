#include "Enums.hpp"

namespace ht { namespace graphics {

	u32 DataTypeSize(DataType type) {
		switch (type) {
		case DataType::FLOAT: return sizeof(f32);
		case DataType::UNSIGNED_SHORT: return sizeof(u16);
		case DataType::UNSIGNED_INT: return sizeof(u32);
		case DataType::UNSIGNED_BYTE: return sizeof(u8);
		case DataType::VECTOR2: return sizeof(f32) * 2;
		case DataType::VECTOR3: return sizeof(f32) * 3;
		case DataType::VECTOR4: return sizeof(f32) * 4;
		case DataType::MATRIX4: return sizeof(f32) * 16;
		}
		HT_ASSERT(true, "[Enums] DataType not recognized!");
		return -1;
	}

	u32 TextureFormatSize(TextureFormat type) {
		switch (type) {
		case TextureFormat::RGB: return 3;
		case TextureFormat::RGBA: return 4;
		}
		HT_ASSERT(true, "[Enums] TextureFormat not recognized!");
		return -1;
	}

	u32 GetSemanticIndex(DataType type) {
		switch (type) {
		case DataType::FLOAT:
		case DataType::UNSIGNED_SHORT:
		case DataType::UNSIGNED_INT:
		case DataType::UNSIGNED_BYTE:
		case DataType::VECTOR2:
		case DataType::VECTOR3:
		case DataType::VECTOR4:
			return 0;
		case DataType::MATRIX4:
			return 4;
		}
		HT_ASSERT(true, "[Enums] Semantic Index not recognized!");
		return -1;
	}

	TextureFormat GetFormat(u32 bpp) {
		switch (bpp) {
		case 24: return TextureFormat::RGB;
		case 32: return TextureFormat::RGBA;
		}
		HT_ASSERT(true, "[Enums] Texture Format not recognized!");
		return TextureFormat::UNKNOWN;
	}

	TextureFormat GetBaseFormat(TextureFormat format) {
		switch (format) {
		case TextureFormat::RGBA: return TextureFormat::BGRA;
		}
		HT_ASSERT(true, "[Enums] Texture Format not recognized!");
		return TextureFormat::UNKNOWN;
	}

} }