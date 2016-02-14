#pragma once

#include "Coordinate\Vector.h"
#include "Coordinate\Matrix.h"
#include "Quaternion.h"

namespace KEngine
{
	namespace Math
	{
		namespace D3
		{
			class Transform
			{
			public:
				Transform();
				Transform(const Coordinate::NormalizedVector<3>& p_localXAxis,
					const Coordinate::NormalizedVector<3>& p_localYAxis,
					const Coordinate::Vector<3>& p_position);
				Transform(const Quaternion& rotation, const Coordinate::Vector<3>& p_position);
				~Transform();

				const Coordinate::Vector<3>& GetPosition() const;
				Coordinate::NormalizedVector<3> GetXAxis() const;
				Coordinate::NormalizedVector<3> GetYAxis() const;
				Coordinate::NormalizedVector<3> GetZAxis() const;
				Quaternion GetRotation() const;

				void SetPosition(const Coordinate::Vector<3>& p_newPosition);
				void SetXYRotation(const Coordinate::NormalizedVector<3>& p_newXAxis, const Coordinate::NormalizedVector<3>& p_newYAxis);
				void SetYZRotation(const Coordinate::NormalizedVector<3>& p_newYAxis, const Coordinate::NormalizedVector<3>& p_newZAxis);
				void SetZXRotation(const Coordinate::NormalizedVector<3>& p_newZAxis, const Coordinate::NormalizedVector<3>& p_newXAxis);
				void SetRotation(const Quaternion& p_newRotation);

				Coordinate::Vector<3> TransformVector(const Coordinate::Vector<3>& p_vector) const;

#if !defined(COLUMN_MAJOR)
				Coordinate::Matrix<4, 3> GetTransformMatrix() const;
#else
				Coordinate::Matrix<3, 4> GetTransformMatrix() const;
#endif
			private:
				Coordinate::Vector<3> m_position;
				Quaternion m_rotation;
			};
		}
	}
}