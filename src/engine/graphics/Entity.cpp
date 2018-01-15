#include "Entity.hpp"


namespace ht { namespace graphics {
	using namespace maths;

	Entity::Entity(f32 x, f32 y, f32 z) 
		: m_Position(x, y, z), m_ModelMatrix(1.0f), m_Modified(false) { }

	Entity::Entity(const Vector3& position)
		: m_Position(position), m_ModelMatrix(1.0f), m_Modified(false) { }

	void Entity::Move(f32 x, f32 y, f32 z) {
		m_Position += Vector3(x, y, z);
		m_Modified = true;
	}

	void Entity::Move(const Vector3& position) {
		m_Position += position;
		m_Modified = true;
	}

	void Entity::SetPosition(f32 x, f32 y, f32 z) {
		m_Position = Vector3(x, y, z);
		m_Modified = true;
	}

	void Entity::SetPosition(const Vector3& position) {
		m_Position = position;
		m_Modified = true;
	}

	void Entity::Rotate(f32 x, f32 y, f32 z) {
		m_Rotation += Vector3(x, y, z);
		m_Modified = true;
	}

	void Entity::Rotate(const Vector3& rotation) {
		m_Rotation += rotation;
		m_Modified = true;
	}

	void Entity::SetRotation(f32 x, f32 y, f32 z) {
		m_Rotation = Vector3(x, y, z);
		m_Modified = true;
	}

	void Entity::SetRotation(const Vector3& rotation) {
		m_Rotation = rotation;
		m_Modified = true;
	}

} }