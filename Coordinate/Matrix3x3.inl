#pragma once

#include "Matrix.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			inline void* Matrix<3, 3>::operator new(std::size_t size)
			{
				return _aligned_malloc(size, XMVectorAlignment);
			}
			inline void* Matrix<3, 3>::operator new[](std::size_t size)
			{
				return _aligned_malloc(size, XMVectorAlignment);
			}
			inline void Matrix<3, 3>::operator delete(void* ptr, std::size_t size)
			{
				_aligned_free(ptr);
			}
			inline void Matrix<3, 3>::operator delete[](void* ptr, std::size_t size)
			{
				_aligned_free(ptr);
			}

			constexpr Matrix<3, 3>::Matrix() : m_matrix(DirectX::XMVectorZero(), DirectX::XMVectorZero(), DirectX::XMVectorZero(), DirectX::XMVectorZero()) {}
			inline Matrix<3, 3>::Matrix(const KEngine::Data::Storage::Array<Vector<3>, 3>& p_matrix)
				: m_matrix()
			{
				//Even if we are column major, we can store and do calculations as a row-major matrix
				//When we convert this into a float matrix, we can then convert this row matrix into
				//A column matrix.
				for (size_t i = 0; i < 3; ++i)
				{
					m_matrix.r[i] = p_matrix[i];
				}
			}
			inline Matrix<3, 3>::Matrix(const Data::Storage::Matrix<float, 3, 3>& p_matrix) :
#if !defined(COLUMN_MAJOR)
				m_matrix(DirectX::XMLoadFloat3x3(reinterpret_cast<const DirectX::XMFLOAT3X3*>(&p_matrix)))
#else
				m_matrix(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat3x3(reinterpret_cast<const DirectX::XMFLOAT3X3*>(&p_matrix))))
#endif
			{
			}
			constexpr Matrix<3, 3>::Matrix(const DirectX::XMMATRIX& p_matrix)
				: m_matrix(p_matrix)
			{
			}

			constexpr Matrix<3, 3>::operator DirectX::XMMATRIX() const
			{
				return m_matrix;
			}

			template<size_t newNumColumns>
			inline Matrix<3, newNumColumns> Matrix<3, 3>::operator*(const Matrix<3, newNumColumns>& p_rhs) const
			{
				Data::Storage::Matrix<float, 3, newNumColumns> dataContainer;

#if !defined(COLUMN_MAJOR)
				Matrix<newNumColumns, 3> transpose = p_rhs.Transpose();
				auto lhsVectorData = GetVectors();
				auto rhsVectorData = transpose.GetVectors();
#else
				Matrix<3, 3> transpose = Transpose();
				auto lhsVectorData = transpose.GetVectors();
				auto rhsVectorData = p_rhs.GetVectors();
#endif
				for (size_t i = 0; i < 3; ++i)
				{
					Vector<3> vectorA = lhsVectorData[i];
					for (size_t j = 0; j < newNumColumns; ++j)
					{
						dataContainer[i][j] = vectorA.Dot(rhsVectorData[j]);
					}
				}

				return Matrix<3, newNumColumns>(dataContainer);
			}
			constexpr Matrix<3, 3> Matrix<3, 3>::operator*(const Matrix<3, 3>& p_rhs) const
			{
#if !defined(COLUMN_MAJOR)
				return Matrix<3, 3>(DirectX::XMMatrixMultiply(m_matrix, p_rhs.m_matrix));
#else			
				return Matrix<3, 3>(DirectX::XMMatrixMultiply(p_rhs.m_matrix, m_matrix));
#endif
			}
			constexpr Matrix<3, 4> Matrix<3, 3>::operator*(const Matrix<3, 4>& p_rhs) const
			{
#if !defined(COLUMN_MAJOR)
				return Matrix<3, 4>(DirectX::XMMatrixMultiply(m_matrix, p_rhs.m_matrix));
#else
				return Matrix<3, 4>(DirectX::XMMatrixMultiply(p_rhs.m_matrix, m_matrix));
#endif
			}

			template<size_t index>
			inline const Vector<3>& Matrix<3, 3>::GetVector() const
			{
				static_assert(index < 3, "Invalid index given");
				return *reinterpret_cast<const Vector<3>*>(&m_matrix.r[index]);
			}
			template<size_t index>
			inline Vector<3>& Matrix<3, 3>::GetVector()
			{
				static_assert(index < 3, "Invalid index given");
				return *reinterpret_cast<Vector<3>*>(&m_matrix.r[index]);
			}
			inline const Data::Storage::Array<Vector<3>, 3>& Matrix<3, 3>::GetVectors() const
			{
				return *reinterpret_cast<const Data::Storage::Array<Vector<3>, 3>*>(&m_matrix);
			}
			inline Data::Storage::Array<Vector<3>, 3>& Matrix<3, 3>::GetVectors()
			{
				return *reinterpret_cast<Data::Storage::Array<Vector<3>, 3>*>(&m_matrix);
			}
			inline Matrix<3, 3> Matrix<3, 3>::Transpose() const
			{
				return Matrix<3, 3>(DirectX::XMMatrixTranspose(m_matrix));
			}

			inline void Matrix<3, 3>::Load(const Data::Storage::Matrix<float, 3, 3>& p_matrix)
			{
				DirectX::XMMATRIX matrix = DirectX::XMLoadFloat3x3(reinterpret_cast<const DirectX::XMFLOAT3X3*>(&p_matrix));
#if !defined(COLUMN_MAJOR)
				m_matrix = matrix;
#else
				m_matrix = DirectX::XMMatrixTranspose(matrix);
#endif
			}
			inline Data::Storage::Matrix<float, 3, 3> Matrix<3, 3>::Unload() const
			{
				Data::Storage::Matrix<float, 3, 3> returnValue;
				DirectX::XMFLOAT3X3* containerPtr = reinterpret_cast<DirectX::XMFLOAT3X3*>(&returnValue);
#if !defined(COLUMN_MAJOR)
				DirectX::XMStoreFloat3x3(containerPtr, m_matrix);
#else
				DirectX::XMStoreFloat3x3(containerPtr, DirectX::XMMatrixTranspose(m_matrix));
#endif
				return returnValue;
			}

#if !defined(COLUMN_MAJOR)
			inline Vector<3> operator*(const Vector<3>& p_lhs, const Matrix<3, 3>& p_rhs)
			{
				return Vector<3>(DirectX::XMVector3Transform(p_lhs, p_rhs));
			}
#else
			inline Vector<3> operator*(const Matrix<3, 3>& p_lhs, const Vector<3>& p_rhs)
			{
				return Vector<3>(DirectX::XMVector3Transform(p_rhs, p_lhs));
			}
#endif
		}
	}
}