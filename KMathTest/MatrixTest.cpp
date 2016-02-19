#include "stdafx.h"
#include "CppUnitTest.h"
#include "Data/Storage/Matrix.h"
#include "Coordinate/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace KEngine::Math;
using namespace KEngine::Data;

namespace KMathTest
{
	TEST_CLASS(MatrixTests)
	{
		TEST_METHOD(DefaultConstruction)
		{
			Coordinate::Matrix<8, 9> matA = Coordinate::Matrix<8, 9>();

			Storage::Matrix<float, 8, 9> results = matA.Unload();

			for (size_t i = 0; i < 8; ++i)
			{
				Storage::Array<float, 9> resultArray = results[i];
				for (size_t j = 0; j < 9; ++j)
				{
					Assert::AreEqual(0.0f, resultArray[j]);
				}
			}
		}
		TEST_METHOD(IdentityIsIdentity)
		{
			Coordinate::Matrix<5, 6> matA = Coordinate::Matrix<5, 6>::Identity;

			Storage::Matrix<float, 5, 6> results = matA.Unload();

			for (size_t i = 0; i < 5; ++i)
			{
				Storage::Array<float, 6> resultArray = results[i];
				for (size_t j = 0; j < 5; ++j)
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
		TEST_METHOD(GetVectorReturnsAppropriateVector)
		{
			Storage::Matrix<float, 6, 5> inputA
				= {
				Storage::Array<float, 5>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
				Storage::Array<float, 5>{6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
				Storage::Array<float, 5>{11.0f, 12.0f, 13.0f, 14.0f, 15.0f},
				Storage::Array<float, 5>{16.0f, 17.0f, 18.0f, 19.0f, 20.0f},
				Storage::Array<float, 5>{21.0f, 22.0f, 23.0f, 24.0f, 25.0f},
				Storage::Array<float, 5>{26.0f, 27.0f, 28.0f, 29.0f, 30.0f}
			};

			Coordinate::Matrix<6, 5> matA = Coordinate::Matrix<6, 5>(inputA);

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
			Storage::Matrix<float, 6, 5> inputA
				= {
				Storage::Array<float, 5>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
				Storage::Array<float, 5>{6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
				Storage::Array<float, 5>{11.0f, 12.0f, 13.0f, 14.0f, 15.0f},
				Storage::Array<float, 5>{16.0f, 17.0f, 18.0f, 19.0f, 20.0f},
				Storage::Array<float, 5>{21.0f, 22.0f, 23.0f, 24.0f, 25.0f},
				Storage::Array<float, 5>{26.0f, 27.0f, 28.0f, 29.0f, 30.0f}
			};

			const Coordinate::Matrix<6, 5> matA = Coordinate::Matrix<6, 5>(inputA);

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
			Storage::Matrix<float, 6, 5> inputA
				= {
				Storage::Array<float, 5>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
				Storage::Array<float, 5>{6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
				Storage::Array<float, 5>{11.0f, 12.0f, 13.0f, 14.0f, 15.0f},
				Storage::Array<float, 5>{16.0f, 17.0f, 18.0f, 19.0f, 20.0f},
				Storage::Array<float, 5>{21.0f, 22.0f, 23.0f, 24.0f, 25.0f},
				Storage::Array<float, 5>{26.0f, 27.0f, 28.0f, 29.0f, 30.0f}
			};

			Coordinate::Matrix<6, 5> matA = Coordinate::Matrix<6, 5>(inputA);

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
			Storage::Matrix<float, 6, 5> inputA
				= {
				Storage::Array<float, 5>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
				Storage::Array<float, 5>{6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
				Storage::Array<float, 5>{11.0f, 12.0f, 13.0f, 14.0f, 15.0f},
				Storage::Array<float, 5>{16.0f, 17.0f, 18.0f, 19.0f, 20.0f},
				Storage::Array<float, 5>{21.0f, 22.0f, 23.0f, 24.0f, 25.0f},
				Storage::Array<float, 5>{26.0f, 27.0f, 28.0f, 29.0f, 30.0f}
			};

			const Coordinate::Matrix<6, 5> matA = Coordinate::Matrix<6, 5>(inputA);

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
		TEST_METHOD(Multiplication)
		{
			Storage::Matrix<float, 6, 5> inputA
				= {
				Storage::Array<float, 5>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
				Storage::Array<float, 5>{6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
				Storage::Array<float, 5>{11.0f, 12.0f, 13.0f, 14.0f, 15.0f},
				Storage::Array<float, 5>{16.0f, 17.0f, 18.0f, 19.0f, 20.0f},
				Storage::Array<float, 5>{21.0f, 22.0f, 23.0f, 24.0f, 25.0f},
				Storage::Array<float, 5>{26.0f, 27.0f, 28.0f, 29.0f, 30.0f}
			};

			Storage::Matrix<float, 5, 2> inputB
				= {
				Storage::Array<float, 2>{1.0f, 2.0f},
				Storage::Array<float, 2>{3.0f, 4.0f},
				Storage::Array<float, 2>{5.0f, 6.0f},
				Storage::Array<float, 2>{7.0f, 8.0f},
				Storage::Array<float, 2>{9.0f, 10.0f}
			};

			Storage::Matrix<float, 6, 2> expectedOutput
				= {
				Storage::Array<float, 2>{95.0f, 110.0f},
				Storage::Array<float, 2>{220.0f, 260.0f},
				Storage::Array<float, 2>{345.0f, 410.0f},
				Storage::Array<float, 2>{470.0f, 560.0f},
				Storage::Array<float, 2>{595.0f, 710.0f},
				Storage::Array<float, 2>{720.0f, 860.0f},
			};

			Coordinate::Matrix<6, 5> matA = Coordinate::Matrix<6, 5>(inputA);
			Coordinate::Matrix<5, 2> matB = Coordinate::Matrix<5, 2>(inputB);

			Coordinate::Matrix<6, 2> matC = matA * matB;

			Storage::Matrix<float, 6, 2> results = matC.Unload();

			for (size_t i = 0; i < 6; ++i)
			{
				auto resultArray = results[i];
				auto expectedArray = expectedOutput[i];
				for (size_t j = 0; j < 2; ++j)
				{
					Assert::AreEqual(expectedArray[j], resultArray[j]);
				}
			}
		}

		TEST_METHOD(Transpose)
		{
			Storage::Matrix<float, 5, 4> inputA
				= {
				Storage::Array<float, 4>{1.0f, 2.0f, 3.0f, 4.0f},
				Storage::Array<float, 4>{5.0f, 6.0f, 7.0f, 8.0f},
				Storage::Array<float, 4>{9.0f, 10.0f, 11.0f, 12.0f},
				Storage::Array<float, 4>{13.0f, 14.0f, 15.0f, 16.0f},
				Storage::Array<float, 4>{17.0f, 18.0f, 19.0f, 20.0f}
			};

			Coordinate::Matrix<5, 4> matA = Coordinate::Matrix<5, 4>(inputA);

			Coordinate::Matrix<4, 5> tMatA = matA.Transpose();

			Storage::Matrix<float, 4, 5> resultMat = tMatA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Storage::Array<float, 5> result = resultMat[i];
				for (size_t j = 0; j < 5; ++j)
				{
					Assert::AreEqual(inputA[j][i], result[j]);
				}
			}
		}

		TEST_METHOD(Unload)
		{
			Storage::Matrix<float, 6, 5> inputA
				= {
				Storage::Array<float, 5>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
				Storage::Array<float, 5>{6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
				Storage::Array<float, 5>{11.0f, 12.0f, 13.0f, 14.0f, 15.0f},
				Storage::Array<float, 5>{16.0f, 17.0f, 18.0f, 19.0f, 20.0f},
				Storage::Array<float, 5>{21.0f, 22.0f, 23.0f, 24.0f, 25.0f},
				Storage::Array<float, 5>{26.0f, 27.0f, 28.0f, 29.0f, 30.0f}
			};

			Coordinate::Matrix<6, 5> matA = Coordinate::Matrix<6, 5>(inputA);

			Storage::Matrix<float, 6, 5> output = matA.Unload();

			for (size_t i = 0; i < 6; ++i)
			{
				auto expectedArray = inputA[i];
				auto resultArray = output[i];
				for (size_t j = 0; j < 5; ++j)
				{
					Assert::AreEqual(expectedArray[j], resultArray[j]);
				}
			}
		}

		TEST_METHOD(Load)
		{
			Storage::Matrix<float, 6, 5> inputA
				= {
				Storage::Array<float, 5>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
				Storage::Array<float, 5>{6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
				Storage::Array<float, 5>{11.0f, 12.0f, 13.0f, 14.0f, 15.0f},
				Storage::Array<float, 5>{16.0f, 17.0f, 18.0f, 19.0f, 20.0f},
				Storage::Array<float, 5>{21.0f, 22.0f, 23.0f, 24.0f, 25.0f},
				Storage::Array<float, 5>{26.0f, 27.0f, 28.0f, 29.0f, 30.0f}
			};

			Coordinate::Matrix<6, 5> matA;

			matA.Load(inputA);

			Storage::Matrix<float, 6, 5> output = matA.Unload();

			for (size_t i = 0; i < 6; ++i)
			{
				auto expectedArray = inputA[i];
				auto resultArray = output[i];
				for (size_t j = 0; j < 5; ++j)
				{
					Assert::AreEqual(expectedArray[j], resultArray[j]);
				}
			}
		}

		TEST_METHOD(VectorMultiply)
		{
#if !defined(COLUMN_MAJOR)
			Storage::Array<float, 6> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
			constexpr size_t vectorLength = 6;
			constexpr size_t resultLength = 5;
#else
			Storage::Array<float, 5> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
			constexpr size_t vectorLength = 5;
			constexpr size_t resultLength = 6;
#endif

			Storage::Matrix<float, 6, 5> inputB
				= {
				Storage::Array<float, 5>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f},
				Storage::Array<float, 5>{6.0f, 7.0f, 8.0f, 9.0f, 10.0f},
				Storage::Array<float, 5>{11.0f, 12.0f, 13.0f, 14.0f, 15.0f},
				Storage::Array<float, 5>{16.0f, 17.0f, 18.0f, 19.0f, 20.0f},
				Storage::Array<float, 5>{21.0f, 22.0f, 23.0f, 24.0f, 25.0f},
				Storage::Array<float, 5>{26.0f, 27.0f, 28.0f, 29.0f, 30.0f}
			};

			Coordinate::Vector<vectorLength> vecA = Coordinate::Vector<vectorLength>(inputA);
			Coordinate::Matrix<6, 5> matB = Coordinate::Matrix<6, 5>(inputB);
#if !defined(COLUMN_MAJOR)
			Coordinate::Vector<5> resultVec = vecA * matB;
#else
			Coordinate::Vector<6> resultVec = matB * vecA;
#endif

			Storage::Array<float, resultLength> resultArray = resultVec.Unload();

#if !defined(COLUMN_MAJOR)
			Storage::Array<float, 5> expectedArray = { 371.0f, 392.0f, 413.0f, 434.0f, 455.0f };
#else
			Storage::Array<float, 6> expectedArray = { 55.0f, 130.0f, 205.0f, 280.0f, 355.0f, 430.0f };
#endif

			for (size_t i = 0; i < resultLength; ++i)
			{
				Assert::AreEqual(expectedArray[i], resultArray[i]);
			}
		}
	};
}