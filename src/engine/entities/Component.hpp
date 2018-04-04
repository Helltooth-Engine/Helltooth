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