#pragma once

#include <DirectXMath.h>
#include "Vector.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			template<size_t vectorLength>
			class NormalizedVector
			{
			public:
				NormalizedVector();
				NormalizedVector(const Vector<vectorLength>& p_vector);

				operator Vector<vectorLength>() const;

				bool operator==(const NormalizedVector& p_rhs) const;
				bool operator!=(const NormalizedVector& p_rhs) const;
				bool operator==(const Vector<vectorLength>& p_rhs) const;
				bool operator!=(const Vector<vectorLength>& p_rhs) const;

				NormalizedVector operator-() const;

				///<summary>Calculates the magnitude of the vector</summary>
				///<returns>Magnitude of vector</returns>
				float Magnitude() const;
				///<summary>Calculates the dot product of both vectors</summary>
				///<returns>Dot product of vectors</returns>
				float Dot(const Vector<vectorLength>& p_v) const;

				///<summary>Copies data from its internal XMVECTOR
				///array and returns them in a float array</summary>
				///<returns>Array with values from vector components</returns>
				Data::Storage::Array<float, vectorLength> Unload() const;
			private:
				Vector<vectorLength> m_vector;
			};

			template<>
			class NormalizedVector<2>
			{
			public:
				NormalizedVector();
				NormalizedVector(const Vector<2>& p_vector);

				operator Vector<2>() const;

				bool operator==(const NormalizedVector<2>& p_rhs) const;
				bool operator!=(const NormalizedVector<2>& p_rhs) const;
				bool operator==(const Vector<2>& p_rhs) const;
				bool operator!=(const Vector<2>& p_rhs) const;

				NormalizedVector<2> operator-() const;

				///<summary>Calculates the magnitude of the vector</summary>
				///<returns>Magnitude of vector</returns>
				float Magnitude() const;
				///<summary>Calculates the dot product of both vectors</summary>
				///<returns>Dot product of vectors</returns>
				float Dot(const Vector<2>& p_v) const;
				///<summary>Creates a normalized vector that is perpendicular to this vector</summary>
				///<returns>PerpendicularVector, which is this vector rotated half-pi CCW</returns>
				NormalizedVector<2> Perpendicular() const;
				///<summary>Copies data from its internal XMVECTOR
				///array and returns them in a float array</summary>
				///<returns>Array with values from vector components</returns>
				Data::Storage::Array<float, 2> Unload() const;
			private:
				Vector<2> m_vector;
			};

			template<>
			class NormalizedVector<3>
			{
			public:
				NormalizedVector();
				NormalizedVector(const Vector<3>& p_vector);

				operator Vector<3>() const;

				bool operator==(const NormalizedVector<3>& p_rhs) const;
				bool operator!=(const NormalizedVector<3>& p_rhs) const;
				bool operator==(const Vector<3>& p_rhs) const;
				bool operator!=(const Vector<3>& p_rhs) const;

				NormalizedVector operator-() const;

				///<summary>Calculates the magnitude of the vector</summary>
				///<returns>Magnitude of vector</returns>
				float Magnitude() const;
				///<summary>Calculates the dot product of both vectors</summary>
				///<returns>Dot product of vectors</returns>
				float Dot(const Vector<3>& p_v) const;

				///<summary>Copies data from its internal XMVECTOR
				///array and returns them in a float array</summary>
				///<returns>Array with values from vector components</returns>
				Data::Storage::Array<float, 3> Unload() const;
			private:
				Vector<3> m_vector;
			};

			template<>
			class NormalizedVector<4>
			{
			public:
				NormalizedVector();
				NormalizedVector(const Vector<4>& p_vector);

				operator Vector<4>() const;

				bool operator==(const NormalizedVector<4>& p_rhs) const;
				bool operator!=(const NormalizedVector<4>& p_rhs) const;
				bool operator==(const Vector<4>& p_rhs) const;
				bool operator!=(const Vector<4>& p_rhs) const;

				NormalizedVector operator-() const;

				///<summary>Calculates the magnitude of the vector</summary>
				///<returns>Magnitude of vector</returns>
				float Magnitude() const;
				///<summary>Calculates the dot product of both vectors</summary>
				///<returns>Dot product of vectors</returns>
				float Dot(const Vector<4>& p_v) const;

				///<summary>Copies data from its internal XMVECTOR
				///array and returns them in a float array</summary>
				///<returns>Array with values from vector components</returns>
				Data::Storage::Array<float, 4> Unload() const;
			private:
				Vector<4> m_vector;
			};
		}
	}
}

#include "NormalizedVector.inl"