#include "Transform.h"

namespace KEngine
{
	namespace Math
	{
		namespace D2
		{
			Transform::Transform() : m_position(), m_rotation()
			{
			}
			Transform::Transform(const Coordinate::NormalizedVector<2>& p_localXAxis, const Coordinate::Vector<2>& p_position)
				: m_position(p_position), m_rotation()
			{
				SetXAxis(p_localXAxis);
			}
			Transform::Transform(float p_rotation, const Coordinate::Vector<2>& p_position)
				: m_position(p_position), m_rotation(p_rotation)
			{
			}

			Transform::~Transform()
			{
			}

			const Coordinate::Vector<2>& Transform::GetPosition() const
			{
				return m_position;
			}
			Coordinate::NormalizedVector<2> Transform::GetXAxis() const
			{
				auto rotMat = DirectX::XMMatrixRotationZ(m_rotation);
				Coordinate::Vector<2> localXAxis = DirectX::XMVector2TransformNormal(Coordinate::Vector<2>::UnitX, rotMat);
				return Coordinate::NormalizedVector<2>(localXAxis);
			}
			Coordinate::NormalizedVector<2> Transform::GetYAxis() const
			{
				auto rotMat = DirectX::XMMatrixRotationZ(m_rotation);
				Coordinate::Vector<2> localYAxis = DirectX::XMVector2TransformNormal(Coordinate::Vector<2>::UnitY, rotMat);
				return Coordinate::NormalizedVector<2>(localYAxis);
			}
			float Transform::GetRotation() const
			{
				return m_rotation;
			}

			void Transform::SetPosition(const Coordinate::Vector<2>& p_newPosition)
			{
				m_position = p_newPosition;
			}
			void Transform::SetXAxis(const Coordinate::NormalizedVector<2>& p_newXAxis)
			{
				Data::Storage::Array<float, 2> newAxisData = p_newXAxis.Unload();
				float absAngle = acosf(newAxisData[0]);
				if (newAxisData[1] > 0.0f)
				{
					m_rotation = absAngle;
				}
				else
				{
					m_rotation = -absAngle;
				}
			}
			void Transform::SetYAxis(const Coordinate::NormalizedVector<2>& p_newYAxis)
			{
				SetXAxis(-p_newYAxis.Perpendicular());
			}
			void Transform::SetRotation(float p_newRotation)
			{
				m_rotation = p_newRotation;
			}

			Coordinate::Vector<2> Transform::TransformVector(const Coordinate::Vector<2>& p_vector) const
			{
#if !defined(COLUMN_MAJOR)
				Coordinate::Vector<2> rotatedVec = p_vector * GetRotationMatrix();
#else
				Coordinate::Vector<2> rotatedVec = GetRotationMatrix() * p_vector;
#endif
				return rotatedVec + m_position;
			}

#if !defined(COLUMN_MAJOR)
			Coordinate::Matrix<3, 2> Transform::GetTransformMatrix() const
#else
			Coordinate::Matrix<2, 3> Transform::GetTransformMatrix() const
#endif
			{
				Data::Storage::Array<float, 2> posVars = m_position.Unload();
				Data::Storage::Array<Coordinate::Vector<3>, 2> elements;
				Data::Storage::Array<Coordinate::Vector<2>, 2> RotMatVecs = GetRotationMatrix().GetVectors();
				elements[0] = RotMatVecs[0].ToVector3(posVars[0]);
				elements[1] = RotMatVecs[1].ToVector3(posVars[1]);
#if !defined(COLUMN_MAJOR)
				return Coordinate::Matrix<2, 3>(elements).Transpose();
#else
				return Coordinate::Matrix<3, 2>(elements).Transpose();
#endif
			}

			Coordinate::Matrix<2, 2> Transform::GetRotationMatrix() const
			{
				Data::Storage::Array<Coordinate::Vector<2>, 2> axis;
				DirectX::XMMATRIX rotMatrix = DirectX::XMMatrixRotationZ(m_rotation);
				axis[0] = Coordinate::Vector<2>(rotMatrix.r[0]);
				axis[1] = Coordinate::Vector<2>(rotMatrix.r[1]);
				return Coordinate::Matrix<2, 2>(axis);
			}
		}
	}
}
