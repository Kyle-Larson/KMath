#include "stdafx.h"
#include "CppUnitTest.h"
#include "Data/Storage/Matrix.h"
#include "Coordinate/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace KEngine::Math;
using namespace KEngine::Data;

namespace KMathTest
{
	TEST_CLASS(Matrix3x3Tests)
	{
		TEST_METHOD(IdentityIsIdentity)
		{
			Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>::Identity;

			Storage::Matrix<float, 3, 3> resultMat = matA.Unload();

			for (size_t i = 0; i < 3; ++i)
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
			Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>();

			Storage::Matrix<float, 3, 3> resultMat = matA.Unload();

			for (size_t i = 0; i < 3; ++i)
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
			Storage::Matrix<float, 3, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f}
			};
			Storage::Matrix<float, 3, 5> inputB
				= {
				Storage::Array<float, 5>{10.0f, 11.0f, 12.0f, 13.0f, 14.0f},
				Storage::Array<float, 5>{15.0f, 16.0f, 17.0f, 18.0f, 19.0f},
				Storage::Array<float, 5>{20.0f, 21.0f, 22.0f, 23.0f, 24.0f}
			};
			Storage::Matrix<float, 3, 5> expectedResults
				= {
				Storage::Array<float, 5>{100.0f, 106.0f, 112.0f, 118.0f, 124.0f},
				Storage::Array<float, 5>{235.0f, 250.0f, 265.0f, 280.0f, 295.0f},
				Storage::Array<float, 5>{370.0f, 394.0f, 418.0f, 442.0f, 466.0f}
			};

			Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>(inputA);
			Coordinate::Matrix<3, 5> matB = Coordinate::Matrix<3, 5>(inputB);

			Coordinate::Matrix<3, 5> results = matA * matB;

			Storage::Matrix<float, 3, 5> resultMat = results.Unload();

			for (size_t i = 0; i < 3; ++i)
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
			Storage::Matrix<float, 3, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f}
			};

			Storage::Matrix<float, 3, 3> inputB
				= {
				Storage::Array<float, 3>{10.0f, 11.0f, 12.0f},
				Storage::Array<float, 3>{13.0f, 14.0f, 15.0f},
				Storage::Array<float, 3>{16.0f, 17.0f, 18.0f}
			};

			Storage::Matrix<float, 3, 3> expectedResults
				= {
				Storage::Array<float, 3>{84.0f, 90.0f, 96.0f},
				Storage::Array<float, 3>{201.0f, 216.0f, 231.0f},
				Storage::Array<float, 3>{318.0f, 342.0f, 366.0f}
			};

			Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>(inputA);
			Coordinate::Matrix<3, 3> matB = Coordinate::Matrix<3, 3>(inputB);

			Coordinate::Matrix<3, 3> resultMat = matA * matB;

			Storage::Matrix<float, 3, 3> actualMat = resultMat.Unload();

			for (size_t i = 0; i < 3; ++i)
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
			Storage::Matrix<float, 3, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f}
			};

			Storage::Matrix<float, 3, 4> inputB
				= {
				Storage::Array<float, 4>{10.0f, 11.0f, 12.0f, 13.0f},
				Storage::Array<float, 4>{14.0f, 15.0f, 16.0f, 17.0f},
				Storage::Array<float, 4>{18.0f, 19.0f, 20.0f, 21.0f}
			};

			Storage::Matrix<float, 3, 4> expectedResults
				= {
				Storage::Array<float, 4>{92.0f, 98.0f, 104.0f, 110.0f},
				Storage::Array<float, 4>{218.0f, 233.0f, 248.0f, 263.0f},
				Storage::Array<float, 4>{344.0f, 368.0f, 392.0f, 416.0f}
			};

			Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>(inputA);
			Coordinate::Matrix<3, 4> matB = Coordinate::Matrix<3, 4>(inputB);

			Coordinate::Matrix<3, 4> resultMat = matA * matB;

			Storage::Matrix<float, 3, 4> actualMat = resultMat.Unload();

			for (size_t i = 0; i < 3; ++i)
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
			Storage::Matrix<float, 3, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f}
			};

			Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>(inputA);

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
			Storage::Matrix<float, 3, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f}
			};

			const Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>(inputA);

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
			Storage::Matrix<float, 3, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f}
			};

			Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>(inputA);

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
			Storage::Matrix<float, 3, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f}
			};

			const Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>(inputA);

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
			Storage::Matrix<float, 3, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f}
			};

			Storage::Matrix<float, 3, 3> expectedMat
				= {
				Storage::Array<float, 3>{1.0f, 4.0f, 7.0f},
				Storage::Array<float, 3>{2.0f, 5.0f, 8.0f},
				Storage::Array<float, 3>{3.0f, 6.0f, 9.0f}
			};

			Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>(inputA);

			Coordinate::Matrix<3, 3> results = matA.Transpose();

			Storage::Matrix<float, 3, 3> resultMat = results.Unload();
			for (size_t i = 0; i < 3; ++i)
			{
				Storage::Array<float, 3> resultArray = resultMat[i];
				Storage::Array<float, 3> expectedArray = expectedMat[i];
				for (size_t j = 0; j < 3; ++j)
				{
					Assert::AreEqual(expectedArray[j], resultArray[j]);
				}
			}
		}

		TEST_METHOD(Unload)
		{
			Storage::Matrix<float, 3, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f}
			};

			Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>(inputA);

			Storage::Matrix<float, 3, 3> results = matA.Unload();

			for (size_t i = 0; i < 3; ++i)
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
			Storage::Matrix<float, 3, 3> inputA
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f}
			};

			Coordinate::Matrix<3, 3> matA = Coordinate::Matrix<3, 3>();

			matA.Load(inputA);

			Storage::Matrix<float, 3, 3> results = matA.Unload();

			for (size_t i = 0; i < 3; ++i)
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
			Storage::Array<float, 3> inputA = { 1.0f, 2.0f, 3.0f };
			constexpr size_t vectorLength = 3;
			constexpr size_t resultLength = 3;

			Storage::Matrix<float, 3, 3> inputB
				= {
				Storage::Array<float, 3>{1.0f, 2.0f, 3.0f},
				Storage::Array<float, 3>{4.0f, 5.0f, 6.0f},
				Storage::Array<float, 3>{7.0f, 8.0f, 9.0f}
			};

			Coordinate::Vector<vectorLength> vecA = Coordinate::Vector<vectorLength>(inputA);
			Coordinate::Matrix<3, 3> matB = Coordinate::Matrix<3, 3>(inputB);
#if !defined(COLUMN_MAJOR)
			Coordinate::Vector<3> resultVec = vecA * matB;
#else
			Coordinate::Vector<3> resultVec = matB * vecA;
#endif

			Storage::Array<float, resultLength> resultArray = resultVec.Unload();

#if !defined(COLUMN_MAJOR)
			Storage::Array<float, 3> expectedArray = { 30.0f, 36.0f, 42.0f };
#else
			Storage::Array<float, 3> expectedArray = { 14.0f, 32.0f, 50.0f };
#endif

			for (size_t i = 0; i < resultLength; ++i)
			{
				Assert::AreEqual(expectedArray[i], resultArray[i]);
			}
		}
	};
}