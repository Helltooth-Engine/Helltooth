#pragma once

#include "Component.hpp"

#include "maths/Matrix4.hpp"
#include "maths/Vector3.hpp"

namespace ht { namespace entities {
	
	class TransformComponent : public Component {
		HT_RTTI(TransformComponent, Component)

	protected:
		bool m_Modified;

		mutable maths::Matrix4 m_ModelMatrix;
		
		maths::Vector3 m_Position;
		maths::Vector3 m_Rotation;
		maths::Vector3 m_Scale;

	public:
		TransformComponent() : m_ModelMatrix(1.0f), m_Scale(1.f, 1.f, 1.f) {}
		TransformComponent(const maths::Vector3& position) : m_Modified(true), m_Position(position), m_Scale(1.f, 1.f, 1.f) {}
		
		void Move(f32 x, f32 y, f32 z)                    { m_Position += maths::Vector3(x, y, z);  m_Modified = true; }
		void Move(const maths::Vector3& position)         { m_Position += position;                 m_Modified = true; }

		void SetPosition(f32 x, f32 y, f32 z)             { m_Position = maths::Vector3(x, y, z);  m_Modified = true; }
		void SetPosition(const maths::Vector3& position)  { m_Position = position;                 m_Modified = true; }

		void Rotate(f32 x, f32 y, f32 z)                  { m_Rotation += maths::Vector3(x, y, z);  m_Modified = true; }
		void Rotate(const maths::Vector3& rotation)       { m_Rotation += rotation;                 m_Modified = true; }

		void SetRotate(f32 x, f32 y, f32 z)               { m_Rotation = maths::Vector3(x, y, z);  m_Modified = true; }
		void SetRotate(const maths::Vector3& rotation)    { m_Rotation = rotation;                 m_Modified = true; }
	
		void Scale(f32 x, f32 y, f32 z)                   { m_Scale += maths::Vector3(x, y, z);  m_Modified = true; }
		void Scale(const maths::Vector3& scale)           { m_Scale += scale;                    m_Modified = true; }

		void SetScale(f32 x, f32 y, f32 z)                { m_Scale = maths::Vector3(x, y, z);   m_Modified = true; }
		void SetScale(const maths::Vector3& scale)        { m_Scale = scale;                     m_Modified = true; }
	
		virtual void Update(f32 delta)                    { if (m_Modified) CalculateModelMatrix(); }

		maths::Matrix4 GetModelMatrix()                   { return m_ModelMatrix; }
		maths::Vector3 GetPosition()                      { return m_Position; }
		maths::Vector3 GetRotation()                      { return m_Rotation; }
		maths::Vector3 GetScale()                         { return m_Scale; }
	
	protected:
		void CalculateModelMatrix() { m_ModelMatrix = maths::Matrix4(1.0f).Scale(m_Scale).Rotate(m_Rotation).Translate(m_Position); m_Modified = false; }
	};

} }