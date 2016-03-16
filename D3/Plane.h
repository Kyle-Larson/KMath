#pragma once

#include <DirectXMath.h>

#include <KMathConstants.h>
#include <Coordinate/Vector.h>
#include <Coordinate/NormalizedVector.h>
#include "Line.h"

namespace KEngine
{
	namespace Math
	{
		namespace D3
		{
			class alignas(M128Alignment) Plane
			{
				#pragma region Public Interface
			public:
				#pragma region Constructors
				Plane();
				Plane(const Coordinate::NormalizedVector<3>& p_planeNormal, const Coordinate::Vector<3>& p_pointOnPlane);
				Plane(const Coordinate::Vector<3>& p_pointAOnPlane,
					const Coordinate::Vector<3>& p_pointBOnPlane,
					const Coordinate::Vector<3>& p_pointCOnPlane);
				#pragma endregion

				#pragma region Operators
				bool operator==(const Plane& p_rhs) const;
				bool operator!=(const Plane& p_rhs) const;
				#pragma endregion

				#pragma region Methods
				bool IsValid() const;

				Plane Normalize() const;

				float Dot(const Coordinate::Vector<4>& p_vector) const;
				float Dot(const Coordinate::Vector<3>& p_vector) const;
				float DotWithNormal(const Coordinate::Vector<3>& p_vector) const;

				Coordinate::Vector<3> GetIntersection(const Line& p_line) const;
				Line GetIntersection(const Plane& p_plane) const;
				#pragma endregion

				#pragma endregion

#pragma region Private Interface
			private:
				explicit Plane(DirectX::XMVECTOR p_vector);

				DirectX::XMVECTOR m_vector;
#pragma endregion
			};
		}
	}
}

#include "Plane.inl"