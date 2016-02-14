#pragma once

#include "Coordinate\Vector.h"
#include "Coordinate\Matrix.h"

namespace KEngine
{
	namespace Math
	{
		namespace D2
		{
			class Transform
			{
			public:
				Transform();
				Transform(const Coordinate::NormalizedVector<2>& p_localXAxis, const Coordinate::Vector<2>& p_position);
				Transform(float p_rotation, const Coordinate::Vector<2>& p_position);
				~Transform();

				const Coordinate::Vector<2>& GetPosition() const;
				Coordinate::NormalizedVector<2> GetXAxis() const;
				Coordinate::NormalizedVector<2> GetYAxis() const;
				float GetRotation() const;

				void SetPosition(const Coordinate::Vector<2>& p_newPosition);
				void SetXAxis(const Coordinate::NormalizedVector<2>& p_newXAxis);
				void SetYAxis(const Coordinate::NormalizedVector<2>& p_newYAxis);
				void SetRotation(float p_newRotation);

				Coordinate::Vector<2> TransformVector(const Coordinate::Vector<2>& p_vector) const;

#if !defined(COLUMN_MAJOR)
				Coordinate::Matrix<3, 2> GetTransformMatrix() const;
#else
				Coordinate::Matrix<2, 3> GetTransformMatrix() const;
#endif
				Coordinate::Matrix<2, 2> GetRotationMatrix() const;
			private:
				Coordinate::Vector<2> m_position;
				float m_rotation;
			};
		}
	}
}