#include "Transform.h"

namespace KEngine
{
	namespace Math
	{
		namespace D3
		{
			Transform::Transform() : m_position(), m_rotation(Quaternion::Identity)
			{}
			Transform::Transform(const Coordinate::NormalizedVector<3>& p_localXAxis, const Coordinate::NormalizedVector<3>& p_localYAxis, const Coordinate::Vector<3>& p_position)
				: m_position(p_position)
			{
				SetXYRotation(p_localXAxis, p_localYAxis);
			}
			Transform::Transform(const Quaternion& p_rotation, const Coordinate::Vector<3>& p_position)
				: m_position(p_position)
			{
				SetRotation(p_rotation);
			}

			Transform::~Transform() {}

			const Coordinate::Vector<3>& Transform::GetPosition() const
			{
				return m_position;
			}
			Coordinate::NormalizedVector<3> Transform::GetXAxis() const
			{
				return Coordinate::NormalizedVector<3>(m_rotation.Rotate(Coordinate::Vector<3>::UnitX));
			}
			Coordinate::NormalizedVector<3> Transform::GetYAxis() const
			{
				return Coordinate::NormalizedVector<3>(m_rotation.Rotate(Coordinate::Vector<3>::UnitY));
			}
			Coordinate::NormalizedVector<3> Transform::GetZAxis() const
			{
				return Coordinate::NormalizedVector<3>(m_rotation.Rotate(Coordinate::Vector<3>::UnitZ));
			}
			Quaternion Transform::GetRotation() const
			{
				return m_rotation;
			}

			void Transform::SetPosition(const Coordinate::Vector<3>& p_newPosition)
			{
				m_position = p_newPosition;
			}
			void Transform::SetXYRotation(const Coordinate::NormalizedVector<3>& p_newXAxis, const Coordinate::NormalizedVector<3>& p_newYAxis)
			{
				assert(p_newXAxis != p_newYAxis);
				assert(p_newXAxis != -p_newYAxis);
				assert(Coordinate::Vector<3>::AngleBetween(p_newXAxis, p_newYAxis) == DirectX::XM_PIDIV2);
				Data::Storage::Array<Coordinate::Vector<3>, 3> rotationVectors;
				rotationVectors[0] = p_newXAxis;
				rotationVectors[1] = p_newYAxis;
				rotationVectors[2] = static_cast<Coordinate::Vector<3>>(p_newXAxis).Cross(p_newYAxis);
				m_rotation = Quaternion(Coordinate::Matrix<3, 3>(rotationVectors));
			}
			void Transform::SetYZRotation(const Coordinate::NormalizedVector<3>& p_newYAxis, const Coordinate::NormalizedVector<3>& p_newZAxis)
			{
				//DESIGN CHOICE: Not checking if axis are perpendicular: Responsibility falls on creator of axis.
				//We can at least assert to make sure the axis are not colinear
				assert(p_newYAxis != p_newZAxis);
				assert(p_newYAxis != -p_newZAxis);
				assert(Coordinate::Vector<3>::AngleBetween(p_newYAxis, p_newZAxis) == DirectX::XM_PIDIV2);
				Data::Storage::Array<Coordinate::Vector<3>, 3> rotationVectors;
				rotationVectors[0] = static_cast<Coordinate::Vector<3>>(p_newYAxis).Cross(p_newZAxis);
				rotationVectors[1] = p_newYAxis;
				rotationVectors[2] = p_newZAxis;
				m_rotation = Quaternion(Coordinate::Matrix<3, 3>(rotationVectors));
			}
			void Transform::SetZXRotation(const Coordinate::NormalizedVector<3>& p_newZAxis, const Coordinate::NormalizedVector<3>& p_newXAxis)
			{
				//DESIGN CHOICE: Not checking if axis are perpendicular: Responsibility falls on creator of axis.
				//We can at least assert to make sure the axis are not colinear
				assert(p_newXAxis != p_newZAxis);
				assert(p_newXAxis != -p_newZAxis);
				assert(Coordinate::Vector<3>::AngleBetween(p_newXAxis, p_newZAxis) == DirectX::XM_PIDIV2);
				Data::Storage::Array<Coordinate::Vector<3>, 3> rotationVectors;
				rotationVectors[0] = p_newXAxis;
				rotationVectors[1] = static_cast<Coordinate::Vector<3>>(p_newZAxis).Cross(p_newXAxis);
				rotationVectors[2] = p_newZAxis;
				m_rotation = Quaternion(Coordinate::Matrix<3, 3>(rotationVectors));
			}
			void Transform::SetRotation(const Quaternion& p_newRotation)
			{
				m_rotation = p_newRotation;
			}

			Coordinate::Vector<3> Transform::TransformVector(const Coordinate::Vector<3>& p_vector) const
			{
				return m_rotation.Rotate(p_vector) + m_position;
			}

#if !defined(COLUMN_MAJOR)
			Coordinate::Matrix<4, 3> Transform::GetTransformMatrix() const {
				return Coordinate::Matrix<4, 3>(DirectX::XMMatrixAffineTransformation(DirectX::XMVectorSplatOne(), DirectX::XMVectorZero(), m_rotation, m_position));
			}
#else
			Coordinate::Matrix<3, 4> Transform::GetTransformMatrix() const {
				return Coordinate::Matrix<4, 3>(DirectX::XMMatrixAffineTransformation(DirectX::XMVectorSplatOne(), DirectX::XMVectorZero(), m_rotation, m_position)).Transpose();
			}
#endif
		}
	}
}