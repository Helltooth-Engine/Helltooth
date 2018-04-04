#pragma once

#include <vector>

#include "Component.hpp"

namespace ht { namespace entities {

	class Entity {
	protected:
		std::vector<Component*> m_Components;

	public:
		inline void AddComponent(Component* component) {
			m_Components.push_back(component);
		}

		inline void RemoveComponent(Component* component) {
			for (u32 i = 0; i <= m_Components.size(); i++)
				if (m_Components[i] == component)
					m_Components.erase(m_Components.begin() + i);
		}

		template<typename T>
		inline T* GetComponent() {
			for (Component* component : m_Components)
				if (component->IsInstance<T>())
					return static_cast<T*>(component);
			return nullptr;
		}

		template<typename T>
		inline const T* GetComponent() const {
			for (const Component* component : m_Components)
				if (component->IsInstance<T>())
					return static_cast<T*>(component);
			return nullptr;
		}
	};

} }