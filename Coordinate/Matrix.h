#pragma once

//If you want to use Column Major, uncomment this pragma
#define COLUMN_MAJOR
#include <DirectXMath.h>

#include "Vector.h"
#include "Data/Storage/Matrix.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			template<size_t rows, size_t columns>
			class alignas(XMVectorAlignment) Matrix
			{
				#if !defined(COLUMN_MAJOR)
				static const size_t numVectors = rows;
				static const size_t vecLength = columns;
				#else
				static const size_t numVectors = columns;
				static const size_t vecLength = rows;
				#endif

			public:
				static void* operator new(std::size_t size);
				static void* operator new[](std::size_t size);
				static void operator delete(void* ptr, size_t size);
				static void operator delete[](void* ptr, size_t size);
			private:
				static Matrix MakeIdentity();

			public:
				static const Matrix Identity;

				template<size_t rows, size_t columns>
				friend class Matrix;
				friend class Matrix<3, 3>;
				friend class Matrix<3, 4>;
				friend class Matrix<4, 3>;
				friend class Matrix<4, 4>;

			public:
				Matrix();
				Matrix(const KEngine::Data::Storage::Array<Vector<Matrix::vecLength>, numVectors>& p_matrix);
				Matrix(const KEngine::Data::Storage::Matrix<float, rows, columns>& p_matrix);

			public:
				template<size_t newColumns>
				Matrix<rows, newColumns> operator*(const Matrix<columns, newColumns>& p_rhs) const;

				template<size_t index>
				const Vector<vecLength>& GetVector() const;
				template<size_t index>
				Vector<vecLength>& GetVector();
				const Data::Storage::Array<Vector<vecLength>, numVectors>& GetVectors() const;
				Data::Storage::Array<Vector<vecLength>, numVectors>& GetVectors();

			public:
				Matrix<columns, rows> Transpose() const;

				Data::Storage::Matrix<float, rows, columns> Unload() const;
				void Load(const Data::Storage::Matrix<float, rows, columns>& p_matrix);

			private:
				KEngine::Data::Storage::Array<Vector<vecLength>, numVectors> m_matrix;
			};

			template<>
			class alignas(XMVectorAlignment) Matrix<3, 3>
			{
				static const size_t numVectors = 3;
				static const size_t vecLength = 3;

			public:
				static void* operator new(std::size_t size);
				static void* operator new[](std::size_t size);
				static void operator delete(void* ptr, size_t size);
				static void operator delete[](void* ptr, size_t size);

			public:
				const static Matrix<3, 3> Identity;

				template<size_t rows, size_t columns>
				friend class Matrix;
				friend class Matrix<3, 4>;
				friend class Matrix<4, 3>;
				friend class Matrix<4, 4>;

			public:
				Matrix();
				Matrix(const KEngine::Data::Storage::Array<Vector<3>, 3>& p_matrix);
				Matrix(const KEngine::Data::Storage::Matrix<float, 3, 3>& p_matrix);
				Matrix(const DirectX::XMMATRIX& p_matrix);

			public:
				template<size_t newNumColumns>
				Matrix<3, newNumColumns> operator*(const Matrix<3, newNumColumns>& p_rhs) const;

				Matrix<3, 3> operator*(const Matrix<3, 3>& p_rhs) const;
				Matrix<3, 4> operator*(const Matrix<3, 4>& p_rhs) const;

				operator DirectX::XMMATRIX() const;

				template<size_t index>
				const Vector<vecLength>& GetVector() const;
				template<size_t index>
				Vector<vecLength>& GetVector();
				const Data::Storage::Array<Vector<vecLength>, numVectors>& GetVectors() const;
				Data::Storage::Array<Vector<vecLength>, numVectors>& GetVectors();

			public:
				Matrix<3, 3> Transpose() const;

				Data::Storage::Matrix<float, 3, 3> Unload() const;
				void Load(const Data::Storage::Matrix<float, 3, 3>& p_matrix);

			private:
				DirectX::XMMATRIX m_matrix;

			};

			template<>
			class alignas(XMVectorAlignment) Matrix<4, 3>
			{
#if !defined(COLUMN_MAJOR)
				static const size_t numVectors = 4;
				static const size_t vecLength = 3;
#else
				static const size_t numVectors = 3;
				static const size_t vecLength = 4;
#endif
			public:
				static void* operator new(std::size_t size);
				static void* operator new[](std::size_t size);
				static void operator delete(void* ptr, size_t size);
				static void operator delete[](void* ptr, size_t size);

			public:
				const static Matrix<4, 3> Identity;

				template<size_t rows, size_t columns>
				friend class Matrix;
				friend class Matrix<3, 3>;
				friend class Matrix<3, 4>;
				friend class Matrix<4, 4>;

			public:
				Matrix();
				Matrix(const KEngine::Data::Storage::Array<Vector<vecLength>, numVectors>& p_matrix);
				Matrix(const Data::Storage::Matrix<float, 4, 3>& p_matrix);
				Matrix(const DirectX::XMMATRIX& p_matrix);

			public:
				template<size_t newNumColumns>
				Matrix<4, newNumColumns> operator*(const Matrix<3, newNumColumns>& p_rhs) const;

				Matrix<4, 3> operator*(const Matrix<3, 3>& p_rhs) const;
				Matrix<4, 4> operator*(const Matrix<3, 4>& p_rhs) const;

				operator DirectX::XMMATRIX() const;

				template<size_t index>
				const Vector<vecLength>& GetVector() const;
				template<size_t index>
				Vector<vecLength>& GetVector();

				const Data::Storage::Array<Vector<vecLength>, numVectors>& GetVectors() const;
				Data::Storage::Array<Vector<vecLength>, numVectors>& GetVectors();

			public:
				 Matrix<3, 4> Transpose() const;

				 Data::Storage::Matrix<float, 4, 3> Unload() const;
				 void Load(const Data::Storage::Matrix<float, 4, 3>& p_matrix);

			private:
				DirectX::XMMATRIX m_matrix;

			};

			template<>
			class alignas(XMVectorAlignment)Matrix<3, 4>
			{
#if !defined(COLUMN_MAJOR)
				static const size_t numVectors = 3;
				static const size_t vecLength = 4;
#else
				static const size_t numVectors = 4;
				static const size_t vecLength = 3;
#endif
			public:
				static void* operator new(std::size_t size);
				static void* operator new[](std::size_t size);
				static void operator delete(void* ptr, size_t size);
				static void operator delete[](void* ptr, size_t size);

			public:
				const static Matrix<3, 4> Identity;

				template<size_t rows, size_t columns>
				friend class Matrix;
				friend class Matrix<3, 3>;
				friend class Matrix<4, 3>;
				friend class Matrix<4, 4>;

			public:
				Matrix();
				Matrix(const KEngine::Data::Storage::Array<Vector<vecLength>, numVectors>& p_matrix);
				Matrix(const Data::Storage::Matrix<float, 3, 4>& p_matrix);
				Matrix(const DirectX::XMMATRIX& p_matrix);

			public:
				template<size_t newNumColumns>
				Matrix<3, newNumColumns> operator*(const Matrix<4, newNumColumns>& p_rhs) const;

				Matrix<3, 3> operator*(const Matrix<4, 3>& p_rhs) const;
				Matrix<3, 4> operator*(const Matrix<4, 4>& p_rhs) const;

				operator DirectX::XMMATRIX() const;

				template<size_t index>
				const Vector<vecLength>& GetVector() const;
				template<size_t index>
				Vector<vecLength>& GetVector();

				const Data::Storage::Array<Vector<vecLength>, numVectors>& GetVectors() const;
				Data::Storage::Array<Vector<vecLength>, numVectors>& GetVectors();

			public:
				Matrix<4, 3> Transpose() const;

				Data::Storage::Matrix<float, 3, 4> Unload() const;
				void Load(const Data::Storage::Matrix<float, 3, 4>& p_matrix);

			private:
				DirectX::XMMATRIX m_matrix;

			};

			template<>
			class alignas(XMVectorAlignment) Matrix<4, 4>
			{
				static const size_t numVectors = 4;
				static const size_t vecLength = 4;

			public:
				static void* operator new(std::size_t size);
				static void* operator new[](std::size_t size);
				static void operator delete(void* ptr, size_t size);
				static void operator delete[](void* ptr, size_t size);

			public:
				const static Matrix<4, 4> Identity;

				template<size_t rows, size_t columns>
				friend class Matrix;
				friend class Matrix<3, 3>;
				friend class Matrix<3, 4>;
				friend class Matrix<4, 3>;

			public:
				Matrix();
				Matrix(const KEngine::Data::Storage::Array<Vector<4>, 4>& p_matrix);
				Matrix(const Data::Storage::Matrix<float, 4, 4>& p_matrix);
				Matrix(const DirectX::XMMATRIX& p_matrix);

			public:
				template<size_t newNumColumns>
				Matrix<4, newNumColumns> operator*(const Matrix<4, newNumColumns>& p_rhs) const;
				
				Matrix<4, 3> operator*(const Matrix<4, 3>& p_rhs) const;
				Matrix<4, 4> operator*(const Matrix<4, 4>& p_rhs) const;

				operator DirectX::XMMATRIX() const;

				template<size_t index>
				const Vector<4>& GetVector() const;
				template<size_t index>
				Vector<4>& GetVector();
				const Data::Storage::Array<Vector<4>, 4>& GetVectors() const;
				Data::Storage::Array<Vector<4>, 4>& GetVectors();

			public:
				 Matrix<4, 4> Transpose() const;

				 Data::Storage::Matrix<float, 4, 4> Unload() const;
				 void Load(const Data::Storage::Matrix<float, 4, 4>& p_matrix);

			private:
				DirectX::XMMATRIX m_matrix;

			};

			#pragma region Matrix Vector Multiplication
			#if !defined(COLUMN_MAJOR)
			template<size_t rows, size_t columns>
			Vector<columns> operator*(const Vector<rows>& p_lhs, const Matrix<rows, columns>& p_rhs);

			Vector<3> operator*(const Vector<3>& p_lhs, const Matrix<3, 3>& p_rhs);
			Vector<4> operator*(const Vector<3>& p_lhs, const Matrix<3, 4>& p_rhs);
			Vector<3> operator*(const Vector<4>& p_lhs, const Matrix<4, 3>& p_rhs);
			Vector<4> operator*(const Vector<4>& p_lhs, const Matrix<4, 4>& p_rhs);
			#else
			template<size_t rows, size_t columns>
			Vector<rows> operator*(const Matrix<rows, columns>& p_lhs, const Vector<columns>& p_rhs);

			Vector<3> operator*(const Matrix<3, 3>& p_lhs, const Vector<3>& p_rhs);
			Vector<3> operator*(const Matrix<3, 4>& p_lhs, const Vector<4>& p_rhs);
			Vector<4> operator*(const Matrix<4, 3>& p_lhs, const Vector<3>& p_rhs);
			Vector<4> operator*(const Matrix<4, 4>& p_lhs, const Vector<4>& p_rhs);
			#endif
			#pragma endregion
		}
	}
}

#include "Matrix.inl"
#include "Matrix3x3.inl"
#include "Matrix3x4.inl"
#include "Matrix4x3.inl"
#include "Matrix4x4.inl"