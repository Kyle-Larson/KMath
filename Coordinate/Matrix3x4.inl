#pragma once

#include "Matrix.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			inline void* Matrix<3, 4>::operator new(std::size_t size)
			{
				return _aligned_malloc(size, XMVectorAlignment);
			}
			inline void* Matrix<3, 4>::operator new[](std::size_t size)
			{
				return _aligned_malloc(size, XMVectorAlignment);
			}
			inline void Matrix<3, 4>::operator delete(void* ptr, std::size_t size)
			{
				_aligned_free(ptr);
			}
			inline void Matrix<3, 4>::operator delete[](void* ptr, std::size_t size)
			{
				_aligned_free(ptr);
			}

			inline Matrix<3, 4>::Matrix() : m_matrix(DirectX::XMVectorZero(), DirectX::XMVectorZero(), DirectX::XMVectorZero(), DirectX::XMVectorZero()) {}
			inline Matrix<3, 4>::Matrix(const KEngine::Data::Storage::Array<Vector<Matrix<3, 4>::vecLength>, Matrix<3, 4>::numVectors>& p_matrix)
				: m_matrix()
			{
#if _MSC_VER <= 1900
				m_matrix.r[0] = p_matrix[0];
				m_matrix.r[1] = p_matrix[1];
				m_matrix.r[2] = p_matrix[2];
#if defined(COLUMN_MAJOR)
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
			inline Matrix<3, 4>::Matrix(const Data::Storage::Matrix<float, 3, 4>& p_matrix)
			{
				Load(p_matrix);
			}
			inline Matrix<3, 4>::Matrix(const DirectX::XMMATRIX& p_matrix)
				: m_matrix(p_matrix)
			{
			}

			template<size_t newNumColumns>
			inline Matrix<3, newNumColumns> Matrix<3, 4>::operator*(const Matrix<4, newNumColumns>& p_rhs) const
			{
				Data::Storage::Matrix<float, 3, newNumColumns> dataContainer;

#if !defined(COLUMN_MAJOR)
				Matrix<newNumColumns, 4> transpose = p_rhs.Transpose();
				auto lhsVectorData = GetVectors();
				auto rhsVectorData = transpose.GetVectors();
#else
				Matrix<4, 3> transpose = Transpose();
				auto lhsVectorData = transpose.GetVectors();
				auto rhsVectorData = p_rhs.GetVectors();
#endif
				for (size_t i = 0; i < 3; ++i)
				{
					Vector<4> vectorA = lhsVectorData[i];
					for (size_t j = 0; j < newNumColumns; ++j)
					{
						dataContainer[i][j] = vectorA.Dot(rhsVectorData[j]);
					}
				}

				return Matrix<3, newNumColumns>(dataContainer);
			}
			inline Matrix<3, 3> Matrix<3, 4>::operator*(const Matrix<4, 3>& p_rhs) const
			{
#if !defined(COLUMN_MAJOR)
				return Matrix<3, 3>(DirectX::XMMatrixMultiply(m_matrix, p_rhs.m_matrix));
#else
				return Matrix<3, 3>(DirectX::XMMatrixMultiply(p_rhs.m_matrix, m_matrix));
#endif
			}
			inline Matrix<3, 4> Matrix<3, 4>::operator*(const Matrix<4, 4>& p_rhs) const
			{
#if !defined(COLUMN_MAJOR)
				return Matrix<3, 4>(DirectX::XMMatrixMultiply(m_matrix, p_rhs.m_matrix));
#else
				return Matrix<3, 4>(DirectX::XMMatrixMultiply(p_rhs.m_matrix, m_matrix));
#endif
			}

			inline Matrix<3, 4>::operator DirectX::XMMATRIX() const
			{
				return m_matrix;
			}

			template<size_t index>
			inline auto Matrix<3, 4>::GetVector() const
				-> const Vector<vecLength>&
			{
				static_assert(index < numVectors, "Invalid index given");
				return *reinterpret_cast<const Vector<vecLength>*>(&m_matrix.r[index]);
			}
			template<size_t index>
			inline auto Matrix<3, 4>::GetVector()
				-> Vector<vecLength>&
			{
				static_assert(index < numVectors, "Invalid index given");
				return *reinterpret_cast<Vector<vecLength>*>(&m_matrix.r[index]);
			}
			inline auto Matrix<3, 4>::GetVectors() const
				-> const Data::Storage::Array<Vector<vecLength>, numVectors>&
			{
				return *reinterpret_cast<const Data::Storage::Array<Vector<vecLength>, numVectors>*>(&m_matrix);
			}
			inline auto Matrix<3, 4>::GetVectors()
				-> Data::Storage::Array<Vector<vecLength>, numVectors>&
			{
				return *reinterpret_cast<Data::Storage::Array<Vector<vecLength>, numVectors>*>(&m_matrix);
			}

			inline Matrix<4, 3> Matrix<3, 4>::Transpose() const
			{
				DirectX::XMMATRIX transposedMatrix(DirectX::XMMatrixTranspose(m_matrix));
				return Matrix<4, 3>(transposedMatrix);
			}

			inline void Matrix<3, 4>::Load(const Data::Storage::Matrix<float, 3, 4>& p_matrix)
			{
				for (size_t i = 0; i < numVectors; ++i)
				{
#if !defined(COLUMN_MAJOR)
					m_matrix.r[i] = DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(&p_matrix[i]));
#else
					m_matrix.r[i] = DirectX::XMVectorSet(p_matrix[0][i], p_matrix[1][i], p_matrix[2][i], 0.0f);
#endif
				}
#if !defined(COLUMN_MAJOR)
				m_matrix.r[3] = DirectX::XMVectorZero();
#endif
			}
			inline Data::Storage::Matrix<float, 3, 4> Matrix<3, 4>::Unload() const
			{
				Data::Storage::Matrix<float, 3, 4> returnValue;
				DirectX::XMFLOAT4X4 container;	//Need added space to fit transposed data
#if !defined(COLUMN_MAJOR)
				DirectX::XMStoreFloat4x4(&container, m_matrix);
#else
				DirectX::XMStoreFloat4x4(&container, DirectX::XMMatrixTranspose(m_matrix));
#endif
				for (size_t i = 0; i < 3; ++i)
				{
					//memcpy(returnValue[i], container.m[i], sizeof(float) * 4);
					for (size_t j = 0; j < 4; ++j)
					{
						returnValue[i][j] = container.m[i][j];
					}
				}
				return returnValue;
			}

#if !defined(COLUMN_MAJOR)
			inline Vector<4> operator*(const Vector<3>& p_lhs, const Matrix<3, 4>& p_rhs)
			{
				return Vector<4>(DirectX::XMVector3Transform(p_lhs, p_rhs));
			}
#else
			inline Vector<3> operator*(const Matrix<3, 4>& p_lhs, const Vector<4>& p_rhs)
			{
				return Vector<3>(DirectX::XMVector4Transform(p_rhs, p_lhs));
			}
#endif
		}
	}
}