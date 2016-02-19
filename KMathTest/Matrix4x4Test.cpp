#include "stdafx.h"
#include "CppUnitTest.h"
#include "Data/Storage/Matrix.h"
#include "Coordinate/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace KEngine::Math;
using namespace KEngine::Data;

namespace KMathTest
{
	TEST_CLASS(Matrix4x4Tests)
	{
		TEST_METHOD(IdentityIsIdentity)
		{
			Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>::Identity;

			Storage::Matrix<float, 4, 4> resultMat = matA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Storage::Array<float, 4> resultArray = resultMat[i];
				for (size_t j = 0; j < 4; ++j)
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
			Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>();

			Storage::Matrix<float, 4, 4> resultMat = matA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Storage::Array<float, 4> resultArray = resultMat[i];
				for (size_t j = 0; j < 4; ++j)
				{
					Assert::AreEqual(0.0f, resultArray[j]);
				}
			}
		}
		TEST_METHOD(Multiply4xN)
		{
			Storage::Matrix<float, 4, 4> inputA
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f}
			};
			Storage::Matrix<float, 4, 5> inputB
				= {
				Storage::Array<float, 5>{17.0f, 18.0f, 19.0f, 20.0f, 21.0f},
				Storage::Array<float, 5>{22.0f, 23.0f, 24.0f, 25.0f, 26.0f},
				Storage::Array<float, 5>{27.0f, 28.0f, 29.0f, 30.0f, 31.0f},
				Storage::Array<float, 5>{32.0f, 33.0f, 34.0f, 35.0f, 36.0f}
			};
			Storage::Matrix<float, 4, 5> expectedResults
				= {
				Storage::Array<float, 5>{270.0f, 280.0f, 290.0f, 300.0f, 310.0f},
				Storage::Array<float, 5>{662.0f, 688.0f, 714.0f, 740.0f, 766.0f},
				Storage::Array<float, 5>{1054.0f, 1096.0f, 1138.0f, 1180.0f, 1222.0f},
				Storage::Array<float, 5>{1446.0f, 1504.0f, 1562.0f, 1620.0f, 1678.0f}
			};

			Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>(inputA);
			Coordinate::Matrix<4, 5> matB = Coordinate::Matrix<4, 5>(inputB);

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
		TEST_METHOD(Multiply4x3)
		{
			Storage::Matrix<float, 4, 4> inputA
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f}
			};

			Storage::Matrix<float, 4, 3> inputB
				= {
				Storage::Array<float, 3>{17.0f, 18.0f, 19.0f},
				Storage::Array<float, 3>{20.0f, 21.0f, 22.0f},
				Storage::Array<float, 3>{23.0f, 24.0f, 25.0f},
				Storage::Array<float, 3>{26.0f, 27.0f, 28.0f}
			};

			Storage::Matrix<float, 4, 3> expectedResults
				= {
				Storage::Array<float, 3>{230.0f, 240.0f, 250.0f},
				Storage::Array<float, 3>{574.0f, 600.0f, 626.0f},
				Storage::Array<float, 3>{918.0f, 960.0f, 1002.0f},
				Storage::Array<float, 3>{1262.0f, 1320.0f, 1378.0f}
			};

			Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>(inputA);
			Coordinate::Matrix<4, 3> matB = Coordinate::Matrix<4, 3>(inputB);

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
		TEST_METHOD(Multiply4x4)
		{
			Storage::Matrix<float, 4, 4> inputA
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f}
			};

			Storage::Matrix<float, 4, 4> inputB
				= {
				Storage::Array<float, 4>{17.0f, 18.0f, 19.0f, 20.0f},
				Storage::Array<float, 4>{21.0f, 22.0f, 23.0f, 24.0f},
				Storage::Array<float, 4>{25.0f, 26.0f, 27.0f, 28.0f},
				Storage::Array<float, 4>{29.0f, 30.0f, 31.0f, 32.0f}
			};

			Storage::Matrix<float, 4, 4> expectedResults
				= {
				Storage::Array<float, 4>{250.0f, 260.0f, 270.0f, 280.0f},
				Storage::Array<float, 4>{618.0f, 644.0f, 670.0f, 696.0f},
				Storage::Array<float, 4>{986.0f, 1028.0f, 1070.0f, 1112.0f},
				Storage::Array<float, 4>{1354.0f, 1412.0f, 1470.0f, 1528.0f}
			};

			Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>(inputA);
			Coordinate::Matrix<4, 4> matB = Coordinate::Matrix<4, 4>(inputB);

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
			Storage::Matrix<float, 4, 4> inputA
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f}
			};

			Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>(inputA);

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
			Storage::Matrix<float, 4, 4> inputA
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f}
			};

			const Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>(inputA);

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
			Storage::Matrix<float, 4, 4> inputA
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f}
			};

			Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>(inputA);

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
			Storage::Matrix<float, 4, 4> inputA
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f}
			};

			const Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>(inputA);

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
			Storage::Matrix<float, 4, 4> inputA
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f}
			};

			Storage::Matrix<float, 4, 4> expectedMat
				= {
				Storage::Array<float, 4>{1.0f, 5.0f, 9.0f, 13.0f},
				Storage::Array<float, 4>{2.0f, 6.0f, 10.0f, 14.0f},
				Storage::Array<float, 4>{3.0f, 7.0f, 11.0f, 15.0f},
				Storage::Array<float, 4>{4.0f, 8.0f, 12.0f, 16.0f}
			};

			Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>(inputA);

			Coordinate::Matrix<4, 4> results = matA.Transpose();

			Storage::Matrix<float, 4, 4> resultMat = results.Unload();
			for (size_t i = 0; i < 4; ++i)
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
			Storage::Matrix<float, 4, 4> inputA
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f}
			};

			Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>(inputA);

			Storage::Matrix<float, 4, 4> results = matA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Storage::Array<float, 4> resultArray = results[i];
				Storage::Array<float, 4> expectedArray = inputA[i];
				for (size_t j = 0; j < 4; ++j)
				{
					Assert::AreEqual(expectedArray[j], resultArray[j]);
				}
			}
		}

		TEST_METHOD(Load)
		{
			Storage::Matrix<float, 4, 4> inputA
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f}
			};

			Coordinate::Matrix<4, 4> matA = Coordinate::Matrix<4, 4>();

			matA.Load(inputA);

			Storage::Matrix<float, 4, 4> results = matA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Storage::Array<float, 4> resultArray = results[i];
				Storage::Array<float, 4> expectedArray = inputA[i];
				for (size_t j = 0; j < 4; ++j)
				{
					Assert::AreEqual(expectedArray[j], resultArray[j]);
				}
			}
		}

		TEST_METHOD(VectorMultiply)
		{
			Storage::Array<float, 4> inputA = { 1.0f, 2.0f, 3.0f, 4.0f };
			constexpr size_t vectorLength = 4;
			constexpr size_t resultLength = 4;

			Storage::Matrix<float, 4, 4> inputB
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f}
			};

			Coordinate::Vector<vectorLength> vecA = Coordinate::Vector<vectorLength>(inputA);
			Coordinate::Matrix<4, 4> matB = Coordinate::Matrix<4, 4>(inputB);
#if !defined(COLUMN_MAJOR)
			Coordinate::Vector<resultLength> resultVec = vecA * matB;
#else
			Coordinate::Vector<resultLength> resultVec = matB * vecA;
#endif

			Storage::Array<float, resultLength> resultArray = resultVec.Unload();

#if !defined(COLUMN_MAJOR)
			Storage::Array<float, 4> expectedArray = { 90.0f, 100.0f, 110.0f, 120.0f };
#else
			Storage::Array<float, 4> expectedArray = { 30.0f, 70.0f, 110.0f, 150.0f };
#endif

			for (size_t i = 0; i < resultLength; ++i)
			{
				Assert::AreEqual(expectedArray[i], resultArray[i]);
			}
		}
	};
}