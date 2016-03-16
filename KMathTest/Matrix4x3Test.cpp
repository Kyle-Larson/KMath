#include "stdafx.h"
#include "CppUnitTest.h"
#include "Data/Storage/Matrix.h"
#include <KMath.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace KEngine::Math;
using namespace KEngine::Data;

namespace KMathTest
{
	TEST_CLASS(Matrix4x3Tests)
	{
		TEST_METHOD(IdentityIsIdentity)
		{
			Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>::Identity;

			Storage::Matrix<float, 4, 3> resultMat = matA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Storage::Array<float, 3> resultArray = resultMat[i];
				for (size_t j = 0; j < 3; ++j)
				{
					if (i == j)
					{
						Assert::AreEqual(1.0f, resultArray[j]);
					}
					else
					{
						Assert::AreEqual(0.0f, resultArray[j]);
					}
				}
			}
		}
		TEST_METHOD(DefaultConstruction)
		{
			Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>();

			Storage::Matrix<float, 4, 3> resultMat = matA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Storage::Array<float, 3> resultArray = resultMat[i];
				for (size_t j = 0; j < 3; ++j)
				{
					Assert::AreEqual(0.0f, resultArray[j]);
				}
			}
		}
		TEST_METHOD(Multiply3xN)
		{
			Storage::Matrix<float, 4, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f},
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f}
			};
			Storage::Matrix<float, 3, 5> inputB
				= {
				Storage::Array<float, 5>{13.0f, 14.0f, 15.0f, 16.0f, 17.0f},
				Storage::Array<float, 5>{18.0f, 19.0f, 20.0f, 21.0f, 22.0f},
				Storage::Array<float, 5>{23.0f, 24.0f, 25.0f, 26.0f, 27.0f}
			};
			Storage::Matrix<float, 4, 5> expectedResults
				= {
				Storage::Array<float, 5>{118.0f, 124.0f, 130.0f, 136.0f, 142.0f},
				Storage::Array<float, 5>{280.0f, 295.0f, 310.0f, 325.0f, 340.0f},
				Storage::Array<float, 5>{442.0f, 466.0f, 490.0f, 514.0f, 538.0f},
				Storage::Array<float, 5>{604.0f, 637.0f, 670.0f, 703.0f, 736.0f}
			};

			Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>(inputA);
			Coordinate::Matrix<3, 5> matB = Coordinate::Matrix<3, 5>(inputB);

			Coordinate::Matrix<4, 5> results = matA * matB;

			Storage::Matrix<float, 4, 5> resultMat = results.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Storage::Array<float, 5> resultArray = resultMat[i];
				Storage::Array<float, 5> expectedArray = expectedResults[i];
				for (size_t j = 0; j < 5; ++j)
				{
					Assert::AreEqual(expectedArray[j], resultArray[j]);
				}
			}
		}
		TEST_METHOD(Multiply3x3)
		{
			Storage::Matrix<float, 4, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f},
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f}
			};

			Storage::Matrix<float, 3, 3> inputB
				= {
				Storage::Array<float, 3>{13.0f, 14.0f, 15.0f},
				Storage::Array<float, 3>{16.0f, 17.0f, 18.0f},
				Storage::Array<float, 3>{19.0f, 20.0f, 21.0f}
			};

			Storage::Matrix<float, 4, 3> expectedResults
				= {
				Storage::Array<float, 3>{102.0f, 108.0f, 114.0f},
				Storage::Array<float, 3>{246.0f, 261.0f, 276.0f},
				Storage::Array<float, 3>{390.0f, 414.0f, 438.0f},
				Storage::Array<float, 3>{534.0f, 567.0f, 600.0f}
			};

			Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>(inputA);
			Coordinate::Matrix<3, 3> matB = Coordinate::Matrix<3, 3>(inputB);

			Coordinate::Matrix<4, 3> resultMat = matA * matB;

			Storage::Matrix<float, 4, 3> actualMat = resultMat.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				auto actualArray = actualMat[i];
				auto expectedArray = expectedResults[i];
				for (size_t j = 0; j < 3; ++j)
				{
					Assert::AreEqual(expectedArray[j], actualArray[j]);
				}
			}
		}
		TEST_METHOD(Multiply3x4)
		{
			Storage::Matrix<float, 4, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f},
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f}
			};

			Storage::Matrix<float, 3, 4> inputB
				= {
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f},
				Storage::Array<float, 4>{17.0f, 18.0f, 19.0f, 20.0f},
				Storage::Array<float, 4>{21.0f, 22.0f, 23.0f, 24.0f}
			};

			Storage::Matrix<float, 4, 4> expectedResults
				= {
				Storage::Array<float, 4>{110.0f, 116.0f, 122.0f, 128.0f},
				Storage::Array<float, 4>{263.0f, 278.0f, 293.0f, 308.0f},
				Storage::Array<float, 4>{416.0f, 440.0f, 464.0f, 488.0f},
				Storage::Array<float, 4>{569.0f, 602.0f, 635.0f, 668.0f}
			};

			Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>(inputA);
			Coordinate::Matrix<3, 4> matB = Coordinate::Matrix<3, 4>(inputB);

			Coordinate::Matrix<4, 4> resultMat = matA * matB;

			Storage::Matrix<float, 4, 4> actualMat = resultMat.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				auto actualArray = actualMat[i];
				auto expectedArray = expectedResults[i];
				for (size_t j = 0; j < 4; ++j)
				{
					Assert::AreEqual(expectedArray[j], actualArray[j]);
				}
			}
		}

		TEST_METHOD(GetVectorReturnsAppropriateVector)
		{
			Storage::Matrix<float, 4, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f},
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f}
			};

			Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>(inputA);

			auto resultVector = matA.GetVector<2>();

			auto resultArray = resultVector.Unload();

			for (size_t i = 0; i < resultArray.size(); ++i)
			{
				float result = resultArray[i];
#if !defined(COLUMN_MAJOR)
				float expected = inputA[2][i];
#else
				float expected = inputA[i][2];
#endif
				Assert::AreEqual(expected, result);
			}

		}
		TEST_METHOD(ConstGetVectorReturnsAppropriateVector)
		{
			Storage::Matrix<float, 4, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f},
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f}
			};

			const Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>(inputA);

			auto resultVector = matA.GetVector<2>();

			auto resultArray = resultVector.Unload();

			for (size_t i = 0; i < resultArray.size(); ++i)
			{
				float result = resultArray[i];
#if !defined(COLUMN_MAJOR)
				float expected = inputA[2][i];
#else
				float expected = inputA[i][2];
#endif
				Assert::AreEqual(expected, result);
			}
		}
		TEST_METHOD(GetVectorsReturnsAppropriateVectors)
		{
			Storage::Matrix<float, 4, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f},
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f}
			};

			Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>(inputA);

			auto results = matA.GetVectors();

			for (size_t i = 0; i < results.size(); ++i)
			{
				auto resultVec = results[i];
				auto resultArray = resultVec.Unload();
				for (size_t j = 0; j < resultArray.size(); ++j)
				{
					float result = resultArray[j];
#if !defined(COLUMN_MAJOR)
					float expected = inputA[i][j];
#else
					float expected = inputA[j][i];
#endif
					Assert::AreEqual(expected, result);
				}
			}
		}
		TEST_METHOD(ConstGetVectorsReturnsAppropriateVectors)
		{
			Storage::Matrix<float, 4, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f},
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f}
			};

			const Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>(inputA);

			auto results = matA.GetVectors();

			for (size_t i = 0; i < results.size(); ++i)
			{
				auto resultVec = results[i];
				auto resultArray = resultVec.Unload();
				for (size_t j = 0; j < resultArray.size(); ++j)
				{
					float result = resultArray[j];
#if !defined(COLUMN_MAJOR)
					float expected = inputA[i][j];
#else
					float expected = inputA[j][i];
#endif
					Assert::AreEqual(expected, result);
				}
			}
		}

		TEST_METHOD(Transpose)
		{
			Storage::Matrix<float, 4, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f},
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f}
			};

			Storage::Matrix<float, 3, 4> expectedMat
				= {
				Storage::Array<float, 4>{1.0f, 4.0f, 7.0f, 10.0f},
				Storage::Array<float, 4>{2.0f, 5.0f, 8.0f, 11.0f},
				Storage::Array<float, 4>{3.0f, 6.0f, 9.0f, 12.0f}
			};

			Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>(inputA);

			Coordinate::Matrix<3, 4> results = matA.Transpose();

			Storage::Matrix<float, 3, 4> resultMat = results.Unload();
			for (size_t i = 0; i < 3; ++i)
			{
				Storage::Array<float, 4> resultArray = resultMat[i];
				Storage::Array<float, 4> expectedArray = expectedMat[i];
				for (size_t j = 0; j < 4; ++j)
				{
					Assert::AreEqual(expectedArray[j], resultArray[j]);
				}
			}
		}

		TEST_METHOD(Unload)
		{
			Storage::Matrix<float, 4, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f},
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f}
			};

			Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>(inputA);

			Storage::Matrix<float, 4, 3> results = matA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Storage::Array<float, 3> resultArray = results[i];
				Storage::Array<float, 3> expectedArray = inputA[i];
				for (size_t j = 0; j < 3; ++j)
				{
					Assert::AreEqual(expectedArray[j], resultArray[j]);
				}
			}
		}

		TEST_METHOD(Load)
		{
			Storage::Matrix<float, 4, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f},
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f}
			};

			Coordinate::Matrix<4, 3> matA = Coordinate::Matrix<4, 3>();

			matA.Load(inputA);

			Storage::Matrix<float, 4, 3> results = matA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Storage::Array<float, 3> resultArray = results[i];
				Storage::Array<float, 3> expectedArray = inputA[i];
				for (size_t j = 0; j < 3; ++j)
				{
					Assert::AreEqual(expectedArray[j], resultArray[j]);
				}
			}
		}

		TEST_METHOD(VectorMultiply)
		{
#if !defined(COLUMN_MAJOR)
			Storage::Array<float, 4> inputA = { 1.0f, 2.0f, 3.0f, 4.0f };
			constexpr size_t vectorLength = 4;
			constexpr size_t resultLength = 3;
#else
			Storage::Array<float, 3> inputA = { 1.0f, 2.0f, 3.0f };
			constexpr size_t vectorLength = 3;
			constexpr size_t resultLength = 4;
#endif

			Storage::Matrix<float, 4, 3> inputB
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f},
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f}
			};

			Coordinate::Vector<vectorLength> vecA = Coordinate::Vector<vectorLength>(inputA);
			Coordinate::Matrix<4, 3> matB = Coordinate::Matrix<4, 3>(inputB);
#if !defined(COLUMN_MAJOR)
			Coordinate::Vector<resultLength> resultVec = vecA * matB;
#else
			Coordinate::Vector<resultLength> resultVec = matB * vecA;
#endif

			Storage::Array<float, resultLength> resultArray = resultVec.Unload();

#if !defined(COLUMN_MAJOR)
			Storage::Array<float, 3> expectedArray = { 70.0f, 80.0f, 90.0f };
#else
			Storage::Array<float, 4> expectedArray = { 14.0f, 32.0f, 50.0f, 68.0f };
#endif

			for (size_t i = 0; i < resultLength; ++i)
			{
				Assert::AreEqual(expectedArray[i], resultArray[i]);
			}
		}
	};
}