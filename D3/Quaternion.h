#pragma once

#include <DirectXMath.h>

#include <KMathConstants.h>
#include <Coordinate/Vector.h>
#include <Coordinate/Matrix.h>

namespace KEngine
{
	namespace Math
	{
		namespace D3
		{
			class alignas(M128Alignment) Quaternion
			{
				#pragma region Public Interface
			public:
				#pragma region Static Functions
				static Quaternion Slerp(const Quaternion& p_start, const Quaternion& p_end, float p_fraction);
				static Quaternion Squad(
					const Quaternion& p_start, 
					const Quaternion& p_controlQuatA, 
					const Quaternion& p_controlQuatB, 
					const Quaternion& p_end, 
					float p_fraction);
				#pragma endregion
				
				#pragma region Static Members
				static const Quaternion Identity;
				#pragma endregion
				
				#pragma region Constructors
				constexpr Quaternion();
				Quaternion(float p_x, float p_y, float p_z, float p_w);
				Quaternion(const Data::Storage::Array<float, 4>& p_floatArray);
				Quaternion(const Coordinate::Vector<3>& p_axis, float p_angle);
				Quaternion(float p_roll, float p_pitch, float p_yaw);
				Quaternion(const Coordinate::Matrix<3, 3>& p_rotationMatrix);
				constexpr explicit Quaternion(const DirectX::XMVECTOR& p_quatVector);
				#pragma endregion
				
				#pragma region Operators

				bool operator==(const Quaternion& p_rhs) const;
				bool operator!=(const Quaternion& p_rhs) const;

				Quaternion operator*(const Quaternion& p_rhs) const;

				Quaternion& operator*=(const Quaternion& p_rhs);

				operator DirectX::XMVECTOR() const;
				
				#pragma endregion
				
				#pragma region Methods
				bool IsValid() const;

				Quaternion GetConjugate() const;
				Quaternion GetInverse() const;
				Quaternion GetLn() const;
				Quaternion GetExponential() const;
				Coordinate::Matrix<3, 3> MakeRotationMatrix() const;

				float Magnitude() const;
				float MagnitudeSq() const;
				Quaternion Normalize() const;
				
				float Dot(const Quaternion& p_rhs) const;

				void GetAxisAngle(Coordinate::Vector<3>* Axis, float* angle) const;

				Coordinate::Vector<3> Rotate(const Coordinate::Vector<3>& p_vector) const;

				template<size_t numVectors>
				Data::Storage::Array<Coordinate::Vector<3>, numVectors> RotateStream(const Data::Storage::Array<Coordinate::Vector<3>, numVectors>& p_vectorArray) const;
				void RotateStream(Coordinate::Vector<3>* p_dataInput, size_t p_numInput, size_t p_inputStride, Coordinate::Vector<3>* p_dataOutput, size_t p_outputStride) const;

				#pragma endregion
				
				#pragma region Data
				
				#pragma endregion

				#pragma endregion

				#pragma region Private Interface
			private:
				#pragma region Data
				DirectX::XMVECTOR m_vector;
				#pragma endregion

				#pragma endregion
			};
		}
	}
}

#include "Quaternion.inl"