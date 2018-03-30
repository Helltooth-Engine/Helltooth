#pragma once

#include "maths/Vector3.hpp"
#include "maths/Matrix4.hpp"

namespace ht { namespace core {

	class Entity {
	private:
		bool m_Modified;

	protected:
		maths::Vector3 m_Position;
		maths::Vector3 m_Rotation;
		mutable maths::Matrix4 m_ModelMatrix;

	public:
		Entity() : m_ModelMatrix(1.0f) {}
		Entity(f32 x, f32 y, f32 z);
		Entity(const maths::Vector3& position);

		void Move(f32 x, f32 y, f32 z);
		void Move(const maths::Vector3& position);
		
		void SetPosition(f32 x, f32 y, f32 z);
		void SetPosition(const maths::Vector3& position);

		void Rotate(f32 x, f32 y, f32 z);
		void Rotate(const maths::Vector3& rotation);

		void SetRotation(f32 x, f32 y, f32 z);
		void SetRotation(const maths::Vector3& rotation);

		inline virtual void Update(f32 delta) { if (m_Modified) CalculateModelMatrix(); }

		inline maths::Matrix4 GetModelMatrix() { return m_ModelMatrix; }
		inline maths::Vector3 GetRotation() { return m_Rotation; }
		inline maths::Vector3 GetPosition() { return m_Position; }

	private:
		inline void CalculateModelMatrix() { m_ModelMatrix = maths::Matrix4(1.0f).Rotate(m_Rotation).Translate(m_Position); }

	};

} }