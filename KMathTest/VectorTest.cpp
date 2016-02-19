#include "stdafx.h"
#include "CppUnitTest.h"
#include "Data/Storage/Array.h"
#include "Coordinate/Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace KEngine::Math::Coordinate;
using namespace KEngine::Data::Storage;

namespace KMathTest
{
	TEST_CLASS(VectorTests)
	{
	public:
		TEST_METHOD(VectorZeroIsZero)
		{
			Vector<8> vecA = Vector<8>::Zero;

			Array<float, 8> resultArray = vecA.Unload();

			for (size_t i = 0; i < 8; ++i)
			{
				Assert::AreEqual(0.0f, resultArray[i]);
			}
		}

		TEST_METHOD(VectorOneIsOne)
		{
			Vector<8> vecA = Vector<8>::One;

			Array<float, 8> resultArray = vecA.Unload();

			for (size_t i = 0; i < 8; ++i)
			{
				Assert::AreEqual(1.0f, resultArray[i]);
			}
		}

		TEST_METHOD(DefaultConstructorEqualVectorZero)
		{
			Vector<9> vecA = Vector<9>();

			Array<float, 9> resultArray = vecA.Unload();

			for (size_t i = 0; i < 9; ++i)
			{
				Assert::AreEqual(0.0f, resultArray[i]);
			}
		}

		TEST_METHOD(FillConstructorFillsEveryElement)
		{
			Vector<15> vecA = Vector<15>(5.0f);

			Array<float, 15> resultArray = vecA.Unload();

			for (size_t i = 0; i < 15; ++i)
			{
				Assert::AreEqual(5.0f, resultArray[i]);
			}
		}

		TEST_METHOD(VectorAdd)
		{
			Array<float, 5> arrayA{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

			Vector<5> vecA = Vector<5>(arrayA);
			Vector<5> vecB = Vector<5>(arrayA);

			Vector<5> vecC = vecA + vecB;

			Array<float, 5> results = vecC.Unload();

			for (size_t i = 0; i < 5; ++i)
			{
				Assert::AreEqual(i * 2.0f + 2.0f, results[i], L"Vector addition failed");
			}
			// TODO: Your test code here
		}

		TEST_METHOD(VectorSubtract)
		{
			Array<float, 10> arrayA{ 3.0f, 6.0f, 9.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f, 27.0f, 30.0f };
			Array<float, 10> arrayB{ 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f };

			Vector<10> vecA = Vector<10>(arrayA);
			Vector<10> vecB = Vector<10>(arrayB);

			Vector<10> vecC = vecA - vecB;

			Array<float, 10> results = vecC.Unload();

			for (size_t i = 0; i < 10; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector subtraction failed");
			}
		}

		TEST_METHOD(VectorNegation)
		{
			Array<float, 6> input = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
			Vector<6> vector = Vector<6>(input);
			Vector<6> resultVector = -vector;
			Array<float, 6> results = resultVector.Unload();

			for (size_t i = 0; i < 6; ++i)
			{
				Assert::AreEqual(-1.0f, results[i], L"Vector negation failed!");
			}
		}

		TEST_METHOD(VectorEquality)
		{
			Array<float, 15> input = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f };
			Vector<15> vecA = Vector<15>(input);
			Vector<15> vecB = Vector<15>(input);

			Assert::IsTrue(vecA == vecB, L"Vector Equality failed!");
		}

		TEST_METHOD(VectorInequality)
		{
			Array<float, 15> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f };
			Array<float, 15> inputB = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 15.0f, 15.0f };
			Vector<15> vecA = Vector<15>(inputA);
			Vector<15> vecB = Vector<15>(inputB);

			Assert::IsTrue(vecA != vecB, L"Vector Inequality failed!");
		}

		TEST_METHOD(VectorMultiplyScale)
		{
			Array<float, 6> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };

			Vector<6> vecA = Vector<6>(inputA);

			Vector<6> resultVector = vecA * 2.0f;

			Array<float, 6> results = resultVector.Unload();

			for (size_t i = 0; i < 6; ++i)
			{
				Assert::AreEqual(i * 2.0f + 2.0f, results[i], L"Vector scale by multiplication failed!");
			}
		}

		TEST_METHOD(VectorDivideScale)
		{
			Array<float, 6> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };

			Vector<6> vecA = Vector<6>(inputA);

			Vector<6> resultVector = vecA / 2.0f;

			Array<float, 6> results = resultVector.Unload();

			for (size_t i = 0; i < 6; ++i)
			{
				Assert::AreEqual(i * 0.5f + 0.5f, results[i], L"Vector scale by division failed!");
			}
		}

		TEST_METHOD(VectorAddAssign)
		{
			Array<float, 6> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
			Array<float, 6> inputB = { 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f };

			Vector<6> vecA = Vector<6>(inputA);
			Vector<6> vecB = Vector<6>(inputB);

			vecA += vecB;

			Array<float, 6> results = vecA.Unload();

			for (size_t i = 0; i < 6; ++i)
			{
				Assert::AreEqual(i * 2.0f + 3.0f, results[i], L"Vector += operator test failed!");
			}
		}

		TEST_METHOD(VectorSubtractAssign)
		{
			Array<float, 6> inputA = { 3.0f, 5.0f, 7.0f, 9.0f, 11.0f, 13.0f };
			Array<float, 6> inputB = { 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f };

			Vector<6> vecA = Vector<6>(inputA);
			Vector<6> vecB = Vector<6>(inputB);

			vecA -= vecB;

			Array<float, 6> results = vecA.Unload();

			for (size_t i = 0; i < 6; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector -= operator test failed!");
			}
		}

		TEST_METHOD(VectorMultScaleAssign)
		{
			Array<float, 6> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };

			Vector<6> vecA = Vector<6>(inputA);

			vecA *= 2.0f;

			Array<float, 6> results = vecA.Unload();

			for (size_t i = 0; i < 6; ++i)
			{
				Assert::AreEqual(i * 2.0f + 2.0f, results[i], L"Vector *= operator test failed!");
			}
		}

		TEST_METHOD(VectorDivideScaleAssign)
		{
			Array<float, 6> inputA = { 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f };

			Vector<6> vecA = Vector<6>(inputA);

			vecA /= 2.0f;

			Array<float, 6> results = vecA.Unload();

			for (size_t i = 0; i < 6; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector /= operator test failed!");
			}
		}

		TEST_METHOD(VectorGetValueByIndex)
		{
			Array<float, 6> inputA = { 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f };

			Vector<6> vecA = Vector<6>(inputA);

			Assert::AreEqual(2.0f, vecA.GetFloatByIndex<0>());
			Assert::AreEqual(4.0f, vecA.GetFloatByIndex<1>());
			Assert::AreEqual(6.0f, vecA.GetFloatByIndex<2>());
			Assert::AreEqual(8.0f, vecA.GetFloatByIndex<3>());
			Assert::AreEqual(10.0f, vecA.GetFloatByIndex<4>());
			Assert::AreEqual(12.0f, vecA.GetFloatByIndex<5>());
		}

		TEST_METHOD(VectorSplatValueByIndex)
		{
			Array<float, 5> inputA = { 2.0f, 4.0f, 6.0f, 8.0f, 10.0f };

			Vector<5> vecA = Vector<5>(inputA);

			Vector<4> resultVec = vecA.SplatFloatByIndex<4, 4>();

			Array<float, 4> results = resultVec.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(10.0f, results[i]);
			}
		}

		TEST_METHOD(VectorGetXMVectors)
		{
			Array<float, 7> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f };

			Vector<7> vecA = Vector<7>(inputA);

			Array<DirectX::XMVECTOR, 2> XMVectors = vecA.GetXMVectors();

			Array<DirectX::XMFLOAT4, 2> unloadedVectors;
			for (size_t i = 0; i < 2; ++i)
			{
				DirectX::XMStoreFloat4(&unloadedVectors[i], XMVectors[i]);
			}
			Assert::AreEqual(inputA[0], unloadedVectors[0].x);
			Assert::AreEqual(inputA[1], unloadedVectors[0].y);
			Assert::AreEqual(inputA[2], unloadedVectors[0].z);
			Assert::AreEqual(inputA[3], unloadedVectors[0].w);
			Assert::AreEqual(inputA[4], unloadedVectors[1].x);
			Assert::AreEqual(inputA[5], unloadedVectors[1].y);
			Assert::AreEqual(inputA[6], unloadedVectors[1].z);
		}

		TEST_METHOD(ConstVectorGetXMVectors)
		{
			Array<float, 7> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f };

			const Vector<7> vecA = Vector<7>(inputA);

			Array<DirectX::XMVECTOR, 2> XMVectors = vecA.GetXMVectors();

			Array<DirectX::XMFLOAT4, 2> unloadedVectors;
			for (size_t i = 0; i < 2; ++i)
			{
				DirectX::XMStoreFloat4(&unloadedVectors[i], XMVectors[i]);
			}
			Assert::AreEqual(inputA[0], unloadedVectors[0].x);
			Assert::AreEqual(inputA[1], unloadedVectors[0].y);
			Assert::AreEqual(inputA[2], unloadedVectors[0].z);
			Assert::AreEqual(inputA[3], unloadedVectors[0].w);
			Assert::AreEqual(inputA[4], unloadedVectors[1].x);
			Assert::AreEqual(inputA[5], unloadedVectors[1].y);
			Assert::AreEqual(inputA[6], unloadedVectors[1].z);
		}

		TEST_METHOD(VectorNormalize)
		{
			Array<float, 6> inputA = { 3.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f };

			Vector<6> vecA = Vector<6>(inputA);

			Vector<6> resultVec = vecA.Normalize();

			Array<float, 6> results = resultVec.Unload();

			Assert::AreEqual(0.6f, results[0]);
			Assert::AreEqual(0.8f, results[1]);
			for (size_t i = 2; i < 6; ++i)
			{
				Assert::AreEqual(0.0f, results[i]);
			}
		}

		TEST_METHOD(VectorMagnitude)
		{
			Array<float, 6> inputA = { 0.0f, 6.0f, 0.0f, 8.0f, 0.0f, 0.0f };

			Vector<6> vecA = Vector<6>(inputA);

			float result = vecA.Magnitude();

			Assert::AreEqual(10.0f, result);
		}

		TEST_METHOD(VectorDot)
		{
			Array<float, 6> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
			Array<float, 6> inputB = { 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f };

			Vector<6> vecA = Vector<6>(inputA);
			Vector<6> vecB = Vector<6>(inputB);

			float result = vecA.Dot(vecB);

			Assert::AreEqual(112.0f, result);
		}

		TEST_METHOD(VectorMemberwiseMultiply)
		{
			Array<float, 5> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
			Array<float, 5> inputB = { 6.0f, 7.0f, 8.0f, 9.0f, 10.0f };
			Array<float, 5> expected = { 6.0f, 14.0f, 24.0f, 36.0f, 50.0f };

			Vector<5> vecA = Vector<5>(inputA);
			Vector<5> vecB = Vector<5>(inputB);

			Vector<5> resultVec = vecA.MemberwiseMultiply(vecB);

			Array<float, 5> resultArray = resultVec.Unload();

			for (size_t i = 0; i < 5; ++i)
			{
				Assert::AreEqual(expected[i], resultArray[i]);
			}
		}

		TEST_METHOD(VectorLoad)
		{
			Array<float, 6> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
			Array<float, 6> inputB = { 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f };

			Vector<6> vecA = Vector<6>(inputA);

			vecA.Load(inputB);

			for (size_t i = 0; i < 6; ++i)
			{
				auto results = vecA.Unload();

				Assert::AreEqual(i + 2.0f, results[i]);
			}
		}

		TEST_METHOD(VectorUnload)
		{
			Array<float, 6> inputA = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };

			Vector<6> vecA = Vector<6>(inputA);

			Array<float, 6> results = vecA.Unload();

			for (size_t i = 0; i < 6; ++i)
			{
				Assert::AreEqual(inputA[i], results[i]);
			}
		}
	};
}