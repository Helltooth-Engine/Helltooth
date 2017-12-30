#include "Enums.hpp"

namespace ht { namespace graphics {

	inline u32 DataTypeSize(DataType type) {
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
		HT_ASSERT("[Enums] DataType not recognized!");
	}

	extern u32 GetSemanticIndex(DataType type) {
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
		HT_ASSERT("[Enums] DataType not recognized!");
	}


} }