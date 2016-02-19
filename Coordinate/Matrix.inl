#pragma once

#include "Matrix.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			template<size_t rows, size_t columns>
			inline void* Matrix<rows, columns>::operator new(std::size_t size)
			{
				return _aligned_malloc(size, XMVectorAlignment);
			}
			template<size_t rows, size_t columns>
			inline void* Matrix<rows, columns>::operator new[](std::size_t size)
			{
				return _aligned_malloc(size, XMVectorAlignment);
			}
			template<size_t rows, size_t columns>
			inline void Matrix<rows, columns>::operator delete(void* ptr, std::size_t size)
			{
				_aligned_free(ptr);
			}
			template<size_t rows, size_t columns>
			inline void Matrix<rows, columns>::operator delete[](void* ptr, std::size_t size)
			{
				_aligned_free(ptr);
			}

			template<size_t rows, size_t columns>
			inline Matrix<rows, columns> Matrix<rows, columns>::MakeIdentity()
			{
				//We need to zero initialize all the values before inserting 1's along
				//The diagonal.
				Data::Storage::Matrix<float, rows, columns> dataContainer = Data::Storage::Matrix<float, rows, columns>();
				for (size_t i = 0; i < rows && i < columns; ++i)
				{
					dataContainer[i][i] = 1.0f;
				}
				return Matrix<rows, columns>(dataContainer);
			}
			template<size_t rows, size_t columns>
			const Matrix<rows, columns> Matrix<rows, columns>::Identity = MakeIdentity();

			template<size_t rows, size_t columns>
			inline Matrix<rows, columns>::Matrix() : m_matrix() {}
			template<size_t rows, size_t columns>
			inline Matrix<rows, columns>::Matrix(const KEngine::Data::Storage::Array<Vector<Matrix<rows, columns>::vecLength>, numVectors>& p_matrix)
				: m_matrix(p_matrix)
			{
			}
			template<size_t rows, size_t columns>
			inline Matrix<rows, columns>::Matrix(const KEngine::Data::Storage::Matrix<float, rows, columns>& p_matrix)
			{
				Load(p_matrix);
			}
			
			template<size_t rows, size_t columns>
			template<size_t newColumns>
			inline Matrix<rows, newColumns> Matrix<rows, columns>::operator*(const Matrix<columns, newColumns>& p_rhs) const
			{
            #if !defined(COLUMN_MAJOR)
				inline size_t numberNewVectors = rows;
				inline size_t newVectorSize = newColumns;
				const Data::Storage::Array<Vector<columns>, rows>& lhsVectors = GetVectors();
				const Data::Storage::Array<Vector<newColumns>, columns>& rhsVectors = p_rhs.GetVectors();
            #else
				constexpr size_t numberNewVectors = newColumns;
				constexpr size_t newVectorSize = rows;
				const Data::Storage::Array<Vector<columns>, newColumns>& lhsVectors = p_rhs.GetVectors();
				const Data::Storage::Array<Vector<rows>, columns>& rhsVectors = GetVectors();
            #endif
				Data::Storage::Array<Vector<newVectorSize>, numberNewVectors> valueContainer;
				for (size_t i = 0; i < numberNewVectors; ++i)
				{
					Data::Storage::Array<float, columns>& vectorValues = lhsVectors[i].Unload();
					Data::Storage::Array<Vector<newVectorSize>, columns> arrayData;
					for (size_t j = 0; j < columns; ++j)
					{
						arrayData[j] = Vector<newVectorSize>(vectorValues[j]);
					}
					for (size_t j = 0; j < columns; ++j)
					{
						arrayData[j] = arrayData[j].MemberwiseMultiply(rhsVectors[j]);
					}
					//Sum up all
					Vector<newVectorSize> sum;
					for (size_t j = 0; j < columns; ++j)
					{
						sum += arrayData[j];
					}

					//Finally
					valueContainer[i] = sum;
				}

				return Matrix<rows, newColumns>(valueContainer);
			}

			template<size_t rows, size_t columns>
			template<size_t index>
			inline auto Matrix<rows, columns>::GetVector() const
				-> const Vector<vecLength>&
			{
				static_assert(index < numVectors, "Invalid index given");
				return m_matrix[index];
			}
			template<size_t rows, size_t columns>
			template<size_t index>
			inline auto Matrix<rows, columns>::GetVector()
				-> Vector<vecLength>&
			{
				static_assert(index < numVectors, "Invalid index given");
				return m_matrix[index];
			}

			template<size_t rows, size_t columns>
			inline auto Matrix<rows, columns>::GetVectors() const
				-> const Data::Storage::Array<Vector<vecLength>, numVectors>&
			{
				return m_matrix;
			}
			template<size_t rows, size_t columns>
			inline auto Matrix<rows, columns>::GetVectors()
				-> Data::Storage::Array<Vector<vecLength>, numVectors>&
			{
				return m_matrix;
			}

			template<size_t rows, size_t columns>
			inline Matrix<columns, rows> Matrix<rows, columns>::Transpose() const
			{
				constexpr size_t MatColumns = Vector<vecLength>::numXMVectors;
				constexpr size_t MatRows = (numVectors + 3) / 4;

				Matrix<columns, rows> returnValue;
				//Expand our matrix to powers of 4
				Data::Storage::Matrix<DirectX::XMMATRIX, MatRows, MatColumns> matrixData;

				//First, store the vectors in the new structure
				for (size_t i = 0; i < MatRows; ++i)
				{
					//Grab a row
					Data::Storage::Array<DirectX::XMMATRIX, MatColumns>& matArray = matrixData[i];
					for (size_t j = 0; j < MatColumns; ++j)
					{
						//Grab an element
						DirectX::XMMATRIX& matrix = matArray[j];
						for (size_t k = 0; k < 4 && i * 4 + k < numVectors; ++k)
						{
							matrix.r[k] = m_matrix[i * 4 + k].GetXMVectors()[j];
						}
					}
				}

				//Then transpose every individual matrix
				for (size_t i = 0; i < MatRows; ++i)
				{
					for (size_t j = 0; j < MatColumns; ++j)
					{
						matrixData[i][j] = DirectX::XMMatrixTranspose(matrixData[i][j]);
					}
				}

				//New matrix data
				Data::Storage::Matrix<DirectX::XMMATRIX, MatColumns, MatRows> newMatrixData;
				//Swap indices of matrices
				for (size_t i = 0; i < MatRows; ++i)
				{
					for (size_t j = 0; j < MatColumns; ++j)
					{
						newMatrixData[j][i] = matrixData[i][j];
					}
				}

				//Store back into return matrix
				for (size_t i = 0; i < MatColumns; ++i)
				{
					Data::Storage::Array<DirectX::XMMATRIX, MatRows> matrixArray = newMatrixData[i];
					for (size_t j = 0; j < 4 && i * 4 + j < vecLength; ++j)
					{
						Vector<numVectors> vectorData;
						auto& xmVectorArray = vectorData.GetXMVectors();
						for (size_t k = 0; k < MatRows; ++k)
						{
							xmVectorArray[k] = matrixArray[k].r[j];
						}
						returnValue.m_matrix[i * 4 + j] = vectorData;
					}
				}

				return returnValue;
			}
			
			template<size_t rows, size_t columns>
			inline Data::Storage::Matrix<float, rows, columns> Matrix<rows, columns>::Unload() const
			{
				Data::Storage::Matrix<float, rows, columns> returnData;
				for (size_t i = 0; i < numVectors; ++i)
				{
					#if defined(ROW_MAJOR)
					returnData[i] = m_matrix[i].Unload();
					#else
					Data::Storage::Array<float, vecLength> vectorData = m_matrix[i].Unload();
					for (size_t j = 0; j < vecLength; ++j)
					{
						returnData[j][i] = vectorData[j];
					}
					#endif
				}
				return returnData;
			}
			
			
			
			
			#pragma endregion

			#pragma region Load(DataMatrix)
			template<size_t rows, size_t columns>
			inline void Matrix<rows, columns>::Load(const Data::Storage::Matrix<float, rows, columns>& p_matrix)
			{
				for (size_t i = 0; i < numVectors; ++i)
				{
					#if defined(ROW_MAJOR)
					m_matrix[i] = Vector<vecLength>(p_matrix[i]);
					#else
					Data::Storage::Array<float, vecLength> vectorData;
					for (size_t j = 0; j < vecLength; ++j)
					{
						vectorData[j] = p_matrix[j][i];
					}
					m_matrix[i] = Vector<vecLength>(vectorData);
					#endif
				}
			}

			#if !defined(COLUMN_MAJOR)
			template<size_t rows, size_t columns>
			inline Vector<columns> operator*(const Vector<rows>& p_lhs, const Matrix<rows, columns>& p_rhs)
			{
				Vector<columns> returnValue;
				Data::Storage::Array<float, rows> vectorData = p_lhs.Unload();
				Data::Storage::Array<Vector<columns>, rows> matrixVectors = p_rhs.GetVectors();
				for (size_t i = 0; i < rows; ++i)
				{
					//TODO: Store memberwise multiply back in matrixVectors,
					//Then loop again to add.  See if that gives performance boost.
					Vector<columns> vector(vectorData[i]);
					returnValue += matrixVectors[i].MemberwiseMultiply(vector);
				}
				return returnValue;
			}
			#else
			template<size_t rows, size_t columns>
			inline Vector<rows> operator*(const Matrix<rows, columns>& p_lhs, const Vector<columns>& p_rhs)
			{
				Vector<rows> returnValue;
				Data::Storage::Array<float, columns> vectorData = p_rhs.Unload();
				Data::Storage::Array<Vector<rows>, columns> matrixVectors = p_lhs.GetVectors();
				for (size_t i = 0; i < columns; ++i)
				{
					Vector<rows> vector(vectorData[i]);
					returnValue += matrixVectors[i].MemberwiseMultiply(vector);
				}
				return returnValue;
			}
			#endif
		}
	}
}