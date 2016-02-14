#pragma once

#include <DirectXMath.h>
#include "Data\Storage\Array.h"
#include "Coordinate\Vector.h"
#include "Ray.h"

namespace KEngine
{
	namespace Math
	{
		namespace D3
		{
			class Line
			{
			public:
				Line();
				Line(const Coordinate::Vector<3>& p_pointA,
					const Coordinate::Vector<3>& p_pointB);
				constexpr Line(const Data::Storage::Array<Coordinate::Vector<3>, 2>& p_pointArray);
				Line(const Ray& p_ray);

				bool operator==(const Line& p_line) const;
				bool operator!=(const Line& p_line) const;

				bool IsOnLine(const Coordinate::Vector<3>& p_point) const;

				float DistanceToLine(const Coordinate::Vector<3>& p_point) const;

				const Data::Storage::Array<Coordinate::Vector<3>, 2>& GetPoints() const;
				Data::Storage::Array<Coordinate::Vector<3>, 2>& GetPoints();
			private:
				Data::Storage::Array<Coordinate::Vector<3>, 2> m_points;
			};
		}
	}
}