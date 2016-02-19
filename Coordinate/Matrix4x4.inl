#pragma once

#include "Matrix.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			inline void* Matrix<4, 4>::operator new(std::size_t size)
			{
				return _aligned_malloc(size, XMVectorAlignment);
			}
			inline void* Matrix<4, 4>::operator new[](std::size_t size)
			{
				return _aligned_malloc(size, XMVectorAlignment);
			}
			inline void Matrix<4, 4>::operator delete(void* ptr, std::size_t size)
			{
				_aligned_free(ptr);
			}
			inline void Matrix<4, 4>::operator delete[](void* ptr, std::size_t size)
			{
				_aligned_free(ptr);
			}

			inline Matrix<4, 4>::Matrix() : m_matrix(DirectX::XMVectorZero(), DirectX::XMVectorZero(), DirectX::XMVectorZero(), DirectX::XMVectorZero()) {}
			inline Matrix<4, 4>::Matrix(const KEngine::Data::Storage::Array<Vector<4>, 4>& p_matrix) : m_matrix()
			{
#if _MSC_VER <= 1900
				m_matrix.r[0] = p_matrix[0];
				m_matrix.r[1] = p_matrix[1];
				m_matrix.r[2] = p_matrix[2];
				m_matrix.r[3] = p_matrix[3];
#else	
				for (size_t i = 0; i < 4; ++i)
				{
					m_matrix.r[i] = p_matrix[i];
				}
#endif
			}
			inline Matrix<4, 4>::Matrix(const Data::Storage::Matrix<float, 4, 4>& p_matrix) :
#if !defined(COLUMN_MAJOR)
				m_matrix(DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(&p_matrix)))
#else
				m_matrix(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(&p_matrix))))
#endif
			{
			}
			inline Matrix<4, 4>::Matrix(const DirectX::XMMATRIX& p_matrix)
				: m_matrix(p_matrix)
			{
			}
			template<size_t newNumColumns>
			inline Matrix<4, newNumColumns> Matrix<4, 4>::operator*(const Matrix<4, newNumColumns>& p_rhs) const
			{
				Data::Storage::Matrix<float, 4, newNumColumns> dataContainer;

#if !defined(COLUMN_MAJOR)
				Matrix<newNumColumns, 4> transpose = p_rhs.Transpose();
				auto lhsVectorData = GetVectors();
				auto rhsVectorData = transpose.GetVectors();
#else
				Matrix<4, 4> transpose = Transpose();
				auto lhsVectorData = transpose.GetVectors();
				auto rhsVectorData = p_rhs.GetVectors();
#endif
				for (size_t i = 0; i < 4; ++i)
				{
					Vector<4> vectorA = lhsVectorData[i];
					for (size_t j = 0; j < newNumColumns; ++j)
					{
						dataContainer[i][j] = vectorA.Dot(rhsVectorData[j]);
					}
				}

				return Matrix<4, newNumColumns>(dataContainer);
			}
			inline Matrix<4, 3> Matrix<4, 4>::operator*(const Matrix<4, 3>& p_rhs) const
			{
#if !defined(COLUMN_MAJOR)
				return Matrix<4, 3>(DirectX::XMMatrixMultiply(m_matrix, p_rhs.m_matrix));
#else
				return Matrix<4, 3>(DirectX::XMMatrixMultiply(p_rhs.m_matrix, m_matrix));
#endif
			}
			inline Matrix<4, 4> Matrix<4, 4>::operator*(const Matrix<4, 4>& p_rhs) const
			{
#if !defined(COLUMN_MAJOR)
				return Matrix<4, 4>(DirectX::XMMatrixMultiply(m_matrix, p_rhs.m_matrix));
#else
				return Matrix<4, 4>(DirectX::XMMatrixMultiply(p_rhs.m_matrix, m_matrix));
#endif
			}
			
			inline Matrix<4, 4>::operator DirectX::XMMATRIX() const
			{
				return m_matrix;
			}

			template<size_t index>
			inline const Vector<4>& Matrix<4, 4>::GetVector() const
			{
				static_assert(index < 4, "Invalid Index given");
				return *reinterpret_cast<const Vector<4>*>(&m_matrix.r[index]);
			}
			template<size_t index>
			inline Vector<4>& Matrix<4, 4>::GetVector()
			{
				static_assert(index < 4, "Invalid Index given");
				return *reinterpret_cast<Vector<4>*>(&m_matrix.r[index]);
			}
			inline const Data::Storage::Array<Vector<4>, 4>& Matrix<4, 4>::GetVectors() const
			{
				return *reinterpret_cast<const Data::Storage::Array<Vector<4>, 4>*>(&m_matrix);
			}
			inline Data::Storage::Array<Vector<4>, 4>& Matrix<4, 4>::GetVectors()
			{
				return *reinterpret_cast<Data::Storage::Array<Vector<4>, 4>*>(&m_matrix);
			}

			inline Matrix<4, 4> Matrix<4, 4>::Transpose() const
			{
				return Matrix<4, 4>(DirectX::XMMatrixTranspose(m_matrix));
			}

			inline void Matrix<4, 4>::Load(const Data::Storage::Matrix<float, 4, 4>& p_matrix)
			{
#if !defined(COLUMN_MAJOR)
				m_matrix = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(&p_matrix));
#else
				m_matrix = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(&p_matrix)));
#endif
			}
			inline Data::Storage::Matrix<float, 4, 4> Matrix<4, 4>::Unload() const
			{
				Data::Storage::Matrix<float, 4, 4> returnValue;
				DirectX::XMFLOAT4X4* containerPtr = reinterpret_cast<DirectX::XMFLOAT4X4*>(&returnValue);
#if !defined(COLUMN_MAJOR)
				DirectX::XMStoreFloat4x4(containerPtr, m_matrix);
#else
				DirectX::XMStoreFloat4x4(containerPtr, DirectX::XMMatrixTranspose(m_matrix));
#endif
				return returnValue;
			}

#if !defined(COLUMN_MAJOR)
			inline Vector<4> operator*(const Vector<4>& p_lhs, const Matrix<4, 4>& p_rhs)
			{
				return Vector<4>(DirectX::XMVector4Transform(p_lhs, p_rhs));
			}
#else
			inline Vector<4> operator*(const Matrix<4, 4>& p_lhs, const Vector<4>& p_rhs)
			{
				return Vector<4>(DirectX::XMVector4Transform(p_rhs, p_lhs));
			}
#endif
		}
	}
}