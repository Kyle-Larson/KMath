#pragma once

#include <KMathConstants.h>
#include "Coordinate/Vector.h"
#include "Ray.h"

namespace KEngine
{
	namespace Math
	{
		namespace D2
		{
			class Line
			{
			public:
				Line();
				Line(const Coordinate::Vector<2>& p_pointA,
					const Coordinate::Vector<2>& p_pointB);
				constexpr Line(const Data::Storage::Array<Coordinate::Vector<2>, 2>& p_pointArray);
				Line(const Ray& p_ray);

				bool operator==(const Line& p_line) const;
				bool operator!=(const Line& p_line) const;

				bool IsOnLine(const Coordinate::Vector<2>& p_point) const;

				Coordinate::Vector<2> FindIntersection(const Line& p_line) const;
				float DistanceToLine(const Coordinate::Vector<2>& p_point) const;

				const Data::Storage::Array<Coordinate::Vector<2>, 2>& GetPoints() const;
				Data::Storage::Array<Coordinate::Vector<2>, 2>& GetPoints();
			private:
				Data::Storage::Array<Coordinate::Vector<2>, 2> m_points;
			};
		}
	}
}