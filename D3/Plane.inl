#pragma once
#include "Plane.h"

namespace KEngine
{
	namespace Math
	{
		namespace D3
		{
			inline Plane::Plane() 
				: m_vector(DirectX::XMPlaneFromPointNormal(
					Coordinate::Vector<3>(0.0f, 0.0f, 0.0f), 
					Coordinate::Vector<3>(1.0f, 0.0f, 0.0f))) {}
			inline Plane::Plane(const Coordinate::NormalizedVector<3>& p_planeNormal, const Coordinate::Vector<3>& p_pointOnPlane)
				: m_vector(DirectX::XMPlaneFromPointNormal(
					static_cast<Coordinate::Vector<3>>(p_planeNormal),
					p_pointOnPlane)) {}
			inline Plane::Plane(const Coordinate::Vector<3>& p_pointAOnPlane,
				const Coordinate::Vector<3>& p_pointBOnPlane,
				const Coordinate::Vector<3>& p_pointCOnPlane)
				: m_vector(DirectX::XMPlaneFromPoints(
					p_pointAOnPlane,
					p_pointBOnPlane,
					p_pointCOnPlane)) {}
			inline Plane::Plane(const DirectX::XMVECTOR& p_vector)
				: m_vector(p_vector) {}

			inline bool Plane::operator==(const Plane& p_rhs) const
			{
				return DirectX::XMPlaneEqual(m_vector, p_rhs.m_vector);
			}
			inline bool Plane::operator!=(const Plane& p_rhs) const
			{
				return DirectX::XMPlaneNotEqual(m_vector, p_rhs.m_vector);
			}

			inline bool Plane::IsValid() const
			{
				return DirectX::XMPlaneIsInfinite(m_vector) && DirectX::XMPlaneIsNaN(m_vector);
			}

			inline Plane Plane::Normalize() const
			{
				return Plane(DirectX::XMPlaneNormalize(m_vector));
			}

			inline float Plane::Dot(const Coordinate::Vector<4>& p_vector) const
			{
				return DirectX::XMVectorGetX(DirectX::XMPlaneDot(m_vector, p_vector));
			}
			inline float Plane::Dot(const Coordinate::Vector<3>& p_vector) const
			{
				return DirectX::XMVectorGetX(DirectX::XMPlaneDotCoord(m_vector, p_vector));
			}
			inline float Plane::DotWithNormal(const Coordinate::Vector<3>& p_vector) const
			{
				return DirectX::XMVectorGetX(DirectX::XMPlaneDotNormal(m_vector, p_vector));
			}

			inline Coordinate::Vector<3> Plane::GetIntersection(const Line& p_line) const
			{
				const Data::Storage::Array<Coordinate::Vector<3>, 2>& points = p_line.GetPoints();
				return Coordinate::Vector<3>(DirectX::XMPlaneIntersectLine(m_vector, points[0], points[1]));
			}
			inline Line Plane::GetIntersection(const Plane& p_plane) const
			{
				DirectX::XMVECTOR pointA;
				DirectX::XMVECTOR pointB;
				DirectX::XMPlaneIntersectPlane(&pointA, &pointB, m_vector, p_plane.m_vector);
				Coordinate::Vector<3> pointVA(pointA);
				Coordinate::Vector<3> pointVB(pointB);
				return Line(pointVA, pointVB);
			}
		}
	}
}