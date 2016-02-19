#pragma once

#include <DirectXMath.h>

#include "Data/Storage/Array.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			template<size_t vectorLength>
			class NormalizedVector;

			constexpr size_t XMVectorAlignment = 16;

			template<size_t vectorLength>
			class alignas(XMVectorAlignment) Vector
			{
				template<size_t rows, size_t columns>
				friend class Matrix;
			public:
				static void* operator new(std::size_t size);
				static void* operator new[](std::size_t size);
				static void operator delete(void* ptr, size_t size);
				static void operator delete[](void* ptr, size_t size);

			public:
				static const Vector Zero;	//Cannot be constexpr because class is being defined
				static const Vector One;	//At this point.
			private:
				constexpr static size_t numXMVectors = (vectorLength + 3) / 4;

				template<size_t rows, size_t columns>
				friend class Matrix;

			public:
				Vector();
				Vector(const Data::Storage::Array<float, vectorLength>& p_array);
				Vector(float fillValue);

			public:
				Vector operator-() const;

				bool operator==(const Vector& p_rhs) const;
				bool operator!=(const Vector& p_rhs) const;

				Vector operator+(const Vector& p_v) const;
				Vector operator-(const Vector& p_v) const;
				
				Vector operator*(float p_scale) const;
				Vector operator/(float p_scale) const;

				Vector& operator+=(const Vector& p_v);
				Vector& operator-=(const Vector& p_v);

				Vector& operator*=(float p_scale);
				Vector& operator/=(float p_scale);

			public:
				//Accessors
				///<summary>Grabs the value from the index provided and returns it (read only)</summary>
				///<returns>Copy of value from component</returns>
				template<size_t index>
				float GetFloatByIndex() const;

				///<summary>Grabs the value indicated by index and replicates the value
				///into each component of a new vector.  New vector's length defaults to
				///original vector's length</summary>
				///<returns>New vector with value duplicated in every component</returns>
				template<size_t index, size_t newVectorLength = vectorLength>
				Vector<newVectorLength> SplatFloatByIndex() const;

				///<summary>Grabs the internal XMVECTOR array used in the vector</summary>
				///<returns>Internal XMVECTOR array reference</returns>
				const Data::Storage::Array<DirectX::XMVECTOR, numXMVectors>& GetXMVectors() const;
				///<summary>Grabs the internal XMVECTOR array used in the vector</summary>
				///<returns>Internal XMVECTOR array reference</returns>
				Data::Storage::Array<DirectX::XMVECTOR, numXMVectors>& GetXMVectors();

			public:
				//Common Vector functions
				///<summary>Generates a vector that has the same direction, but a magnitude of one</summary>
				///<returns>New vector with magnitude one</returns>
				Vector Normalize() const;
				///<summary>Calculates the magnitude of the vector</summary>
				///<returns>Magnitude of vector</returns>
				float Magnitude() const;
				///<summary>Calculates the dot product of both vectors</summary>
				///<returns>Dot product of vectors</returns>
				float Dot(const Vector& p_v) const;
				//Memberwise function
				///<summary>Multiplies every component of this and passed in vector</summary>
				///<returns>Vector with results of per-component multiplication</returns>
				Vector MemberwiseMultiply(const Vector& p_rhs) const;

				//Loading and Unloading
				///<summary>Copies data from the given array and 
				///loads them into its internal XMVECTOR array</summary>
				void Load(const KEngine::Data::Storage::Array<float, vectorLength>& p_array);
				///<summary>Copies data from its internal XMVECTOR
				///array and returns them in a float array</summary>
				///<returns>Array with values from vector components</returns>
				KEngine::Data::Storage::Array<float, vectorLength> Unload() const;

			private:
				Data::Storage::Array<DirectX::XMVECTOR, numXMVectors> m_vectorArray;

			};

			template<>
			class alignas(XMVectorAlignment)Vector<2>
			{
				template<size_t vectorLength>
				friend class Vector;
				template<size_t rows, size_t columns>
				friend class Matrix;

			public:
				static void* operator new(std::size_t size);
				static void* operator new[](std::size_t size);
				static void operator delete(void* ptr, size_t size);
				static void operator delete[](void* ptr, size_t size);

				static float AngleBetween(const NormalizedVector<2>& vectorA, const NormalizedVector<2>& vectorB);
				static float AngleBetween(const Vector<2>& vectorA, const Vector<2>& vectorB);

			public:
				static const Vector<2> Zero;
				static const Vector<2> One;
				static const Vector<2> UnitX;
				static const Vector<2> UnitY;
			private:
				constexpr static size_t numXMVectors = 1;

			public:
				Vector();
				Vector(const KEngine::Data::Storage::Array<float, 2>& p_array);
				Vector(float fillValue);
				Vector(float p_x, float p_y);
				Vector(const DirectX::FXMVECTOR p_vector);

			public:
				operator DirectX::XMVECTOR() const;
				Vector<3> ToVector3(float p_Z) const;
				Vector<4> ToVector4(float p_Z, float p_W) const;

				bool operator==(const Vector<2>& p_v) const;
				bool operator!=(const Vector<2>& p_v) const;

				Vector<2> operator-() const;

				Vector<2> operator+(const Vector<2>& p_v) const;
				Vector<2> operator-(const Vector<2>& p_v) const;

				Vector<2> operator*(float p_scale) const;
				Vector<2> operator/(float p_scale) const;

				Vector<2>& operator+=(const Vector<2>& p_v);
				Vector<2>& operator-=(const Vector<2>& p_v);

				Vector<2>& operator*=(float p_scale);
				Vector<2>& operator/=(float p_scale);

			public:
				Vector<2> Normalize() const;
				float Magnitude() const;
				Vector<2> Orthogonal() const;

				Vector<2> ClampLength(float minLength, float maxLength) const;

				float Dot(const Vector<2>& p_v) const;
				float Cross(const Vector<2>& p_v) const;
				Vector<2> Reflect(const NormalizedVector<2>& p_reflectionNormal) const;
				Vector<2> Refract(const NormalizedVector<2>& p_refractionNormal, float p_refractionIndex) const;
				//Memberwise function
				///<summary>Multiplies every component of this and passed in vector</summary>
				///<returns>Vector with results of per-component multiplication</returns>
				Vector<2> MemberwiseMultiply(const Vector<2>& p_rhs) const;

				template<size_t index>
				float GetFloatByIndex() const;

				///<summary>Grabs the value indicated by index and replicates the value
				///into each component of a new vector.  New vector's length defaults to
				///original vector's length</summary>
				///<returns>New vector with value duplicated in every component</returns>
				template<size_t index, size_t newVectorLength = vectorLength>
				Vector<newVectorLength> SplatFloatByIndex() const;

				//Loading and Unloading
				void Load(const KEngine::Data::Storage::Array<float, 2>& p_array);
				KEngine::Data::Storage::Array<float, 2> Unload() const;

			private:
				///<summary>Grabs the internal XMVECTOR array used in the vector</summary>
				///<returns>Internal XMVECTOR array reference</returns>
				const Data::Storage::Array<DirectX::XMVECTOR, 1>& GetXMVectors() const;
				///<summary>Grabs the internal XMVECTOR array used in the vector</summary>
				///<returns>Internal XMVECTOR array reference</returns>
				Data::Storage::Array<DirectX::XMVECTOR, 1>& GetXMVectors();

				

			private:
				Data::Storage::Array<DirectX::XMVECTOR, 1> m_vectorArray;

			};

			template<>
			class alignas(XMVectorAlignment)Vector<3>
			{
				template<size_t vectorLength>
				friend class Vector;
				template<size_t rows, size_t columns>
				friend class Matrix;

			public:
				static void* operator new(std::size_t size);
				static void* operator new[](std::size_t size);
				static void operator delete(void* ptr, size_t size);
				static void operator delete[](void* ptr, size_t size);

				static float AngleBetween(const NormalizedVector<3>& vectorA, const NormalizedVector<3>& vectorB);
				static float AngleBetween(const Vector<3>& vectorA, const Vector<3>& vectorB);

			public:
				static const Vector<3> Zero;
				static const Vector<3> One;
				static const Vector<3> UnitX;
				static const Vector<3> UnitY;
				static const Vector<3> UnitZ;
			private:
				constexpr static size_t numXMVectors = 1;

			public:
				Vector();
				Vector(const KEngine::Data::Storage::Array<float, 3>& p_array);
				Vector(float fillValue);
				Vector(float p_x, float p_y, float p_z);
				Vector(const DirectX::FXMVECTOR p_vector);

			public:
				operator DirectX::XMVECTOR() const;
				Vector<2> ToVector2() const;
				Vector<4> ToVector4(float p_W) const;

				Vector<3> operator-() const;

				bool operator==(const Vector<3>& p_v) const;
				bool operator!=(const Vector<3>& p_v) const;

				Vector<3> operator+(const Vector<3>& p_v) const;
				Vector<3> operator-(const Vector<3>& p_v) const;

				Vector<3> operator*(float p_scale) const;
				Vector<3> operator/(float p_scale) const;

				Vector<3>& operator+=(const Vector<3>& p_v);
				Vector<3>& operator-=(const Vector<3>& p_v);

				Vector<3>& operator*=(float p_scale);
				Vector<3>& operator/=(float p_scale);

			public:

				Vector<3> Normalize() const;
				float Magnitude() const;
				Vector<3> Orthogonal() const;

				Vector<3> ClampLength(float minLength, float maxLength) const;

				float Dot(const Vector<3>& p_v) const;
				Vector<3> Cross(const Vector<3>& p_v) const;
				//Memberwise function
				///<summary>Multiplies every component of this and passed in vector</summary>
				///<returns>Vector with results of per-component multiplication</returns>
				Vector<3> MemberwiseMultiply(const Vector<3>& p_rhs) const;
				Vector<3> Reflect(const NormalizedVector<3>& p_reflectionNormal) const;
				Vector<3> Refract(const NormalizedVector<3>& p_refractionNormal, float p_refractionIndex) const;

				template<size_t index>
				float GetFloatByIndex() const;

				template<size_t index, size_t newVectorLength = 3>
				Vector<newVectorLength> SplatFloatByIndex() const;

				//Loading and Unloading
				void Load(const KEngine::Data::Storage::Array<float, 3>& p_array);
				KEngine::Data::Storage::Array<float, 3> Unload() const;

				///<summary>Grabs the internal XMVECTOR array used in the vector</summary>
				///<returns>Internal XMVECTOR array reference</returns>
				const Data::Storage::Array<DirectX::XMVECTOR, 1>& GetXMVectors() const;
				///<summary>Grabs the internal XMVECTOR array used in the vector</summary>
				///<returns>Internal XMVECTOR array reference</returns>
				Data::Storage::Array<DirectX::XMVECTOR, 1>& GetXMVectors();

				

			private:
				Data::Storage::Array<DirectX::XMVECTOR, 1> m_vectorArray;
			};

			template<>
			class alignas(XMVectorAlignment)Vector<4>
			{
				template<size_t vectorLength>
				friend class Vector;
				template<size_t rows, size_t columns>
				friend class Matrix;

			public:
				static void* operator new(std::size_t size);
				static void* operator new[](std::size_t size);
				static void operator delete(void* ptr, size_t size);
				static void operator delete[](void* ptr, size_t size);

				static float AngleBetween(const NormalizedVector<4>& vectorA, const NormalizedVector<4>& vectorB);
				static float AngleBetween(const Vector<4>& vectorA, const Vector<4>& vectorB);

			public:
				static const Vector<4> Zero;
				static const Vector<4> One;
				static const Vector<4> UnitX;
				static const Vector<4> UnitY;
				static const Vector<4> UnitZ;
				static const Vector<4> UnitW;
			private:
				constexpr static size_t numXMVectors = 1;

			public:
				Vector();
				Vector(const KEngine::Data::Storage::Array<float, 4>& p_array);
				Vector(float fillValue);
				Vector(float p_x, float p_y, float p_z, float p_w);
				Vector(const DirectX::FXMVECTOR p_vector);

			public:
				operator DirectX::XMVECTOR() const;
				Vector<2> ToVector2() const;
				Vector<3> ToVector3() const;

				bool operator==(const Vector<4>& p_v) const;
				bool operator!=(const Vector<4>& p_v) const;

				Vector<4> operator-() const;

				Vector<4> operator+(const Vector<4>& p_v) const;
				Vector<4> operator-(const Vector<4>& p_v) const;

				Vector<4> operator*(float p_scale) const;
				Vector<4> operator/(float p_scale) const;

				Vector<4>& operator+=(const Vector<4>& p_v);
				Vector<4>& operator-=(const Vector<4>& p_v);

				Vector<4>& operator*=(float p_scale);
				Vector<4>& operator/=(float p_scale);

			public:
				Vector<4> Normalize() const;
				float Magnitude() const;
				Vector<4> Orthogonal() const;

				Vector<4> ClampLength(float minLength, float maxLength) const;

				float Dot(const Vector<4>& p_v) const;
				//Memberwise function
				///<summary>Multiplies every component of this and passed in vector</summary>
				///<returns>Vector with results of per-component multiplication</returns>
				Vector MemberwiseMultiply(const Vector<4>& p_rhs) const;
				Vector<4> Reflect(const NormalizedVector<4>& p_reflectionNormal) const;
				Vector<4> Refract(const NormalizedVector<4>& p_refractionNormal, float p_refractionIndex) const;

				template<size_t index>
				float GetFloatByIndex() const;

				template<size_t index, size_t newVectorLength = 4>
				Vector<newVectorLength> SplatFloatByIndex() const;

				//Loading and Unloading
				void Load(const KEngine::Data::Storage::Array<float, 4>& p_array);
				KEngine::Data::Storage::Array<float, 4> Unload() const;

				///<summary>Grabs the internal XMVECTOR array used in the vector</summary>
				///<returns>Internal XMVECTOR array reference</returns>
				const Data::Storage::Array<DirectX::XMVECTOR, 1>& GetXMVectors() const;
				///<summary>Grabs the internal XMVECTOR array used in the vector</summary>
				///<returns>Internal XMVECTOR array reference</returns>
				Data::Storage::Array<DirectX::XMVECTOR, 1>& GetXMVectors();

			private:
				Data::Storage::Array<DirectX::XMVECTOR, 1> m_vectorArray;
			};
		}
	}
}

#include "Vector.inl"
#include "Vector2.inl"
#include "Vector3.inl"
#include "Vector4.inl"