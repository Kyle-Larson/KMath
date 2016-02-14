#pragma once
#include "Quaternion.h"

namespace KEngine
{
	namespace Math
	{
		namespace D3
		{
			inline Quaternion Quaternion::Slerp(
				const Quaternion& p_start, 
				const Quaternion& p_end, 
				float p_fraction)
			{
				return Quaternion(DirectX::XMQuaternionSlerp(p_start, p_end, p_fraction));
			}

			inline Quaternion Quaternion::Squad(
				const Quaternion& p_start, 
				const Quaternion& p_controlQuatA, 
				const Quaternion& p_controlQuatB, 
				const Quaternion& p_end, 
				float p_fraction)
			{
				DirectX::XMVECTOR controlVectors[3];
				DirectX::XMQuaternionSquadSetup(
					&controlVectors[0],
					&controlVectors[1],
					&controlVectors[2],
					p_start, 
					p_controlQuatA, 
					p_controlQuatB, 
					p_end);

				return Quaternion(DirectX::XMQuaternionSquad(
					p_start, 
					controlVectors[0], 
					controlVectors[1], 
					controlVectors[2], 
					p_fraction));
			}

			constexpr Quaternion::Quaternion() : m_vector() {}
			inline Quaternion::Quaternion(float p_x, float p_y, float p_z, float p_w) :
				m_vector(DirectX::XMVectorSet(p_x, p_y, p_z, p_w)) {}
			inline Quaternion::Quaternion(const Data::Storage::Array<float, 4>& p_array) :
				m_vector(DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(&p_array))) {}
			inline Quaternion::Quaternion(const Coordinate::Vector<3>& p_axis, float p_angle) :
				m_vector(DirectX::XMQuaternionRotationAxis(p_axis, p_angle)) {}
			inline Quaternion::Quaternion(float p_roll, float p_pitch, float p_yaw) :
				m_vector(DirectX::XMQuaternionRotationRollPitchYaw(p_roll, p_pitch, p_yaw)) {}
			inline Quaternion::Quaternion(const Coordinate::Matrix<3, 3>& p_rotationMatrix) :
				m_vector(DirectX::XMQuaternionRotationMatrix(p_rotationMatrix)) {}
			constexpr Quaternion::Quaternion(const DirectX::XMVECTOR& p_vector) :
				m_vector(p_vector) {}

			inline bool Quaternion::operator==(const Quaternion& p_rhs) const
			{
				return DirectX::XMQuaternionEqual(m_vector, p_rhs);
			}
			inline bool Quaternion::operator!=(const Quaternion& p_rhs) const
			{
				return DirectX::XMQuaternionNotEqual(m_vector, p_rhs);
			}

			inline Quaternion Quaternion::operator*(const Quaternion& p_rhs) const
			{
				return Quaternion(DirectX::XMQuaternionMultiply(m_vector, p_rhs));
			}

			inline Quaternion& Quaternion::operator*=(const Quaternion& p_rhs)
			{
				m_vector = DirectX::XMQuaternionMultiply(m_vector, p_rhs);
				return *this;
			}

			inline Quaternion::operator DirectX::XMVECTOR() const
			{
				return m_vector;
			}

			inline bool Quaternion::IsValid() const
			{
				return DirectX::XMQuaternionIsInfinite(m_vector) &&
					DirectX::XMQuaternionIsNaN(m_vector);
			}

			inline Quaternion Quaternion::GetConjugate() const
			{
				return Quaternion(DirectX::XMQuaternionConjugate(m_vector));
			}

			inline Quaternion Quaternion::GetInverse() const
			{
				return Quaternion(DirectX::XMQuaternionInverse(m_vector));
			}

			inline Quaternion Quaternion::GetExponential() const
			{
				return Quaternion(DirectX::XMQuaternionExp(m_vector));
			}

			inline Quaternion Quaternion::GetLn() const
			{
				return Quaternion(DirectX::XMQuaternionLn(m_vector));
			}

			inline Coordinate::Matrix<3, 3> Quaternion::MakeRotationMatrix() const
			{
				DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationQuaternion(m_vector);
				return Coordinate::Matrix<3, 3>(rotMat);
			}

			inline float Quaternion::Magnitude() const
			{
				return DirectX::XMVectorGetX(DirectX::XMQuaternionLength(m_vector));
			}
			inline float Quaternion::MagnitudeSq() const
			{
				return DirectX::XMVectorGetX(DirectX::XMQuaternionLengthSq(m_vector));
			}

			inline Quaternion Quaternion::Normalize() const
			{
				return Quaternion(DirectX::XMQuaternionNormalize(m_vector));
			}

			inline float Quaternion::Dot(const Quaternion& p_rhs) const
			{
				return DirectX::XMVectorGetX(DirectX::XMQuaternionDot(m_vector, p_rhs));
			}

			inline void Quaternion::GetAxisAngle(Coordinate::Vector<3>* axis, float* angle) const
			{
				DirectX::XMQuaternionToAxisAngle(reinterpret_cast<DirectX::XMVECTOR*>(axis), angle, m_vector);
			}

			inline Coordinate::Vector<3> Quaternion::Rotate(const Coordinate::Vector<3>& p_vector) const
			{
				return Coordinate::Vector<3>(DirectX::XMVector3Rotate(p_vector, m_vector));
			}

			template<size_t numVectors>
			inline Data::Storage::Array<Coordinate::Vector<3>, numVectors> Quaternion::RotateStream(
				const Data::Storage::Array<Coordinate::Vector<3>, numVectors>& p_vectorArray) const
			{
				Data::Storage::Array<Coordinate::Vector<3>, numVectors> returnValue;
				for (size_t i = 0; i < numVectors; ++i)
				{
					returnValue[i] = Rotate(p_vectorArray[i]);
				}
			}

			inline void Quaternion::RotateStream(
				Coordinate::Vector<3>* p_dataInput, 
				size_t p_numInput, 
				size_t p_inputStride, 
				Coordinate::Vector<3>* p_dataOutput, 
				size_t p_outputStride) const
			{
				for (size_t i = 0; i < p_numInput; ++i)
				{
					*p_dataOutput = Rotate(*p_dataInput);
					p_dataInput += p_inputStride;
					p_dataOutput += p_outputStride;
				}
			}
		}
	}
}