#include "Enums.hpp"

namespace ht { namespace graphics {

	inline u32 DataTypeSize(DataType type) {
		switch (type) {
		case DataType::FLOAT: return sizeof(f32);
		case DataType::UNSIGNED_SHORT: return sizeof(u16);
		case DataType::UNSIGNED_INT: return sizeof(u32);
		case DataType::UNSIGNED_BYTE: return sizeof(u8);
		}
	}

} }