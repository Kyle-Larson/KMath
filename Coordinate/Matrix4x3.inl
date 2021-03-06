#pragma once

#include "Matrix.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			inline void* Matrix<4, 3>::operator new(std::size_t size)
			{
				return _aligned_malloc(size, M128Alignment);
			}
			inline void* Matrix<4, 3>::operator new[](std::size_t size)
			{
				return _aligned_malloc(size, M128Alignment);
			}
			inline void Matrix<4, 3>::operator delete(void* ptr, std::size_t size)
			{
				_aligned_free(ptr);
			}
			inline void Matrix<4, 3>::operator delete[](void* ptr, std::size_t size)
			{
				_aligned_free(ptr);
			}

			inline Matrix<4, 3>::Matrix() : m_matrix(DirectX::XMVectorZero(), DirectX::XMVectorZero(), DirectX::XMVectorZero(), DirectX::XMVectorZero()) {}
			inline Matrix<4, 3>::Matrix(const KEngine::Data::Storage::Array<Vector<Matrix<4, 3>::vecLength>, Matrix<4, 3>::numVectors>& p_matrix)
				: m_matrix()
			{
#if _MSC_VER <= 1900
				m_matrix.r[0] = p_matrix[0];
				m_matrix.r[1] = p_matrix[1];
				m_matrix.r[2] = p_matrix[2];
#if !defined(COLUMN_MAJOR)
				m_matrix.r[3] = p_matrix[3];
#else
				m_matrix.r[3] = DirectX::XMVectorZero();
#endif
#else
				for (size_t i = 0; i < numVectors; ++i)
				{
					m_matrix.r[i] = p_matrix[i];
				}
#endif
			}
			inline Matrix<4, 3>::Matrix(const Data::Storage::Matrix<float, 4, 3>& p_matrix) :
#if !defined(COLUMN_MAJOR)
				m_matrix(DirectX::XMLoadFloat4x3(reinterpret_cast<const DirectX::XMFLOAT4X3*>(&p_matrix)))
#else
				m_matrix(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x3(reinterpret_cast<const DirectX::XMFLOAT4X3*>(&p_matrix))))
#endif
			{
				m_matrix.r[3] = DirectX::XMVectorSetW(m_matrix.r[3], 0.0f);
			}
			inline Matrix<4, 3>::Matrix(const DirectX::XMMATRIX& p_matrix)
				: m_matrix(p_matrix)
			{
			}

			template<size_t newNumColumns>
			inline Matrix<4, newNumColumns> Matrix<4, 3>::operator*(const Matrix<3, newNumColumns>& p_rhs) const
			{
				Data::Storage::Matrix<float, 4, newNumColumns> dataContainer;

#if !defined(COLUMN_MAJOR)
				Matrix<newNumColumns, 3> transpose = p_rhs.Transpose();
				auto lhsVectorData = GetVectors();
				auto rhsVectorData = transpose.GetVectors();
#else
				Matrix<3, 4> transpose = Transpose();
				auto lhsVectorData = transpose.GetVectors();
				auto rhsVectorData = p_rhs.GetVectors();
#endif
				for (size_t i = 0; i < 4; ++i)
				{
					Vector<3> vectorA = lhsVectorData[i];
					for (size_t j = 0; j < newNumColumns; ++j)
					{
						dataContainer[i][j] = vectorA.Dot(rhsVectorData[j]);
					}
				}

				return Matrix<4, newNumColumns>(dataContainer);
			}
			inline Matrix<4, 4> Matrix<4, 3>::operator*(const Matrix<3, 4>& p_rhs) const
			{
#if !defined(COLUMN_MAJOR)
				return Matrix<4, 4>(DirectX::XMMatrixMultiply(m_matrix, p_rhs.m_matrix));
#else
				return Matrix<4, 4>(DirectX::XMMatrixMultiply(p_rhs.m_matrix, m_matrix));
#endif
			}
			inline Matrix<4, 3> Matrix<4, 3>::operator*(const Matrix<3, 3>& p_rhs) const
			{
#if !defined(COLUMN_MAJOR)
				return Matrix<4, 3>(DirectX::XMMatrixMultiply(m_matrix, p_rhs.m_matrix));
#else
				return Matrix<4, 3>(DirectX::XMMatrixMultiply(p_rhs.m_matrix, m_matrix));
#endif
			}

			inline Matrix<4, 3>::operator DirectX::XMMATRIX() const
			{
				return m_matrix;
			}

			template<size_t index>
			inline auto Matrix<4, 3>::GetVector() const
				-> const Vector<vecLength>&
			{
				static_assert(index < numVectors, "Invalid index given");
				return *reinterpret_cast<const Vector<vecLength>*>(&m_matrix.r[index]);
			}
			template<size_t index>
			inline auto Matrix<4, 3>::GetVector()
				-> Vector<vecLength>&
			{
				static_assert(index < numVectors, "Invalid index given");
				return *reinterpret_cast<Vector<vecLength>*>(&m_matrix.r[index]);
			}
			inline auto Matrix<4, 3>::GetVectors() const
				-> const Data::Storage::Array<Vector<vecLength>, numVectors>&
			{
				return *reinterpret_cast<const Data::Storage::Array<Vector<vecLength>, numVectors>*>(&m_matrix);
			}
			inline auto Matrix<4, 3>::GetVectors()
				-> Data::Storage::Array<Vector<vecLength>, numVectors>&
			{
				return *reinterpret_cast<Data::Storage::Array<Vector<vecLength>, numVectors>*>(&m_matrix);
			}

			inline Matrix<3, 4> Matrix<4, 3>::Transpose() const
			{
				DirectX::XMMATRIX transposedMatrix(DirectX::XMMatrixTranspose(m_matrix));
				return Matrix<3, 4>(transposedMatrix);
			}

			inline void Matrix<4, 3>::Load(const Data::Storage::Matrix<float, 4, 3>& p_matrix)
			{
				DirectX::XMMATRIX matrix = DirectX::XMLoadFloat4x3(reinterpret_cast<const DirectX::XMFLOAT4X3*>(&p_matrix));
#if !defined(COLUMN_MAJOR)
				m_matrix = matrix;
#else
				m_matrix = DirectX::XMMatrixTranspose(matrix);
#endif
			}
			inline Data::Storage::Matrix<float, 4, 3> Matrix<4, 3>::Unload() const
			{
				Data::Storage::Matrix<float, 4, 3> returnValue;
				DirectX::XMFLOAT4X4 container;
#if !defined(COLUMN_MAJOR)
				DirectX::XMStoreFloat4x4(&container, m_matrix);
#else
				DirectX::XMStoreFloat4x4(&container, DirectX::XMMatrixTranspose(m_matrix));
#endif
				for (size_t i = 0; i < 4; ++i)
				{
					//memcpy(returnValue[i], contianer.m[i], sizeof(float) * 3);
					for (size_t j = 0; j < 3; ++j)
					{
						returnValue[i][j] = container.m[i][j];
					}
				}

				return returnValue;
			}

#if !defined(COLUMN_MAJOR)
			inline Vector<3> operator*(const Vector<4>& p_lhs, const Matrix<4, 3>& p_rhs)
			{
				return Vector<3>(DirectX::XMVector4Transform(p_lhs, p_rhs));
			}
#else
			inline Vector<4> operator*(const Matrix<4, 3>& p_lhs, const Vector<3>& p_rhs)
			{
				return Vector<4>(DirectX::XMVector3Transform(p_rhs, p_lhs));
			}
#endif
		}
	}
}