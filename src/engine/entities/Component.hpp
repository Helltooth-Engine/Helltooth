﻿/*
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

#include <string>

#include "core/Internal.hpp"

#define HT_RTTI(Child, Parent)                                 \
	public:                                                    \
		static u32 TypeIdClass() {                             \
			static int id = 0;                                 \
			return (u32)&id;                                   \
		}                                                      \
		                                                       \
		virtual u32 TypeIdInstance() const {                   \
			return TypeIdClass();                              \
		}                                                      \
		                                                       \
		virtual bool IsInstance(u32 id) const {                \
			if(TypeIdClass() == id)                            \
				return true;                                   \
			else                                               \
				return Parent::IsInstance(id);                 \
		}


namespace ht { namespace entities {

	class Component {
	public:
		virtual u32 TypeIdInstance() const = 0;

		virtual bool IsInstance(u32 id) const {
			return false;
		}

		template<typename T>
		T* As() {
			if (IsInstance(T::TypeIdClass()))
				return static_cast<T*>(this);
			else 
				return nullptr;
		}

		template<typename T>
		const T* As() const {
			if (IsInstance(T::TypeIdClass()))
				return static_cast<T*>(this);
			else 
				return nullptr;
		}
	};

} }