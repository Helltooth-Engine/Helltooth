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

#include "Enums.hpp"

namespace ht { namespace graphics {

	u32 DataTypeSize(DataType type) {
		switch (type) {
		case DataType::FLOAT:          return sizeof(f32);
		case DataType::UNSIGNED_SHORT: return sizeof(u16);
		case DataType::UNSIGNED_INT:   return sizeof(u32);
		case DataType::UNSIGNED_BYTE:  return sizeof(u8);
		case DataType::VECTOR2:        return sizeof(f32) * 2;
		case DataType::VECTOR3:        return sizeof(f32) * 3;
		case DataType::VECTOR4:        return sizeof(f32) * 4;
		case DataType::MATRIX4:        return sizeof(f32) * 16;
		}
		HT_ASSERT(false, "[Enums] DataType not recognized!");
		return -1;
	}

	u32 TextureFormatSize(TextureFormat type) {
		switch (type) {
		case TextureFormat::RGB:       return 3;
		case TextureFormat::RGBA:      return 4;
		}
		HT_ASSERT(false, "[Enums] TextureFormat not recognized!");
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
		HT_ASSERT(false, "[Enums] Semantic Index not recognized!");
		return -1;
	}

	TextureFormat GetFormat(u32 bpp) {
		switch (bpp) {
		case 24: return TextureFormat::RGB;
		case 32: return TextureFormat::RGBA;
		}
		HT_ASSERT(false, "[Enums] Texture Format not recognized!");
		return TextureFormat::UNKNOWN;
	}

	TextureFormat GetBaseFormat(TextureFormat format) {
		switch (format) {
		case TextureFormat::RGBA: return TextureFormat::BGRA;
		}
		HT_ASSERT(false, "[Enums] Texture Format not recognized!");
		return TextureFormat::UNKNOWN;
	}

} }