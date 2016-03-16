#include "stdafx.h"
#include "CppUnitTest.h"
#include "Data/Storage/Array.h"
#include <KMath.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace KEngine::Math::Coordinate;
using namespace KEngine::Data::Storage;

namespace KMathTest
{
	TEST_CLASS(Vector2Tests)
	{
		TEST_METHOD(ZeroIsZero)
		{
			Vector<2> vecA = Vector<2>::Zero;

			Array<float, 2> resultArray = vecA.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(0.0f, resultArray[i]);
			}
		}

		TEST_METHOD(OneIsOne)
		{
			Vector<2> vecA = Vector<2>::One;

			Array<float, 2> resultArray = vecA.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(1.0f, resultArray[i]);
			}
		}

		TEST_METHOD(UnitXVector)
		{
			Vector<2> vecA = Vector<2>::UnitX;

			Array<float, 2> resultArray = vecA.Unload();

			Assert::AreEqual(1.0f, resultArray[0]);
			Assert::AreEqual(0.0f, resultArray[1]);
		}

		TEST_METHOD(UnitYVector)
		{
			Vector<2> vecA = Vector<2>::UnitY;

			Array<float, 2> resultArray = vecA.Unload();

			Assert::AreEqual(0.0f, resultArray[0]);
			Assert::AreEqual(1.0f, resultArray[1]);
		}

		TEST_METHOD(DefaultConstruction)
		{
			Vector<2> vecA = Vector<2>();

			Array<float, 2> resultArray = vecA.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(0.0f, resultArray[i]);
			}
		}

		TEST_METHOD(FillConstruction)
		{
			Vector<2> vecA = Vector<2>(3.0f);

			Array<float, 2> resultArray = vecA.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(3.0f, resultArray[i]);
			}
		}

		TEST_METHOD(MemberwiseConstruction)
		{
			Vector<2> vecA = Vector<2>(1.0f, 2.0f);

			Array<float, 2> resultArray = vecA.Unload();

			Assert::AreEqual(1.0f, resultArray[0]);
			Assert::AreEqual(2.0f, resultArray[1]);
		}

		TEST_METHOD(Add)
		{
			Array<float, 2> inputA{ 1.0f, 2.0f };
			Array<float, 2> inputB{ 2.0f, 3.0f };

			Vector<2> vecA = Vector<2>(inputA);
			Vector<2> vecB = Vector<2>(inputB);

			Vector<2> resultVec = vecA + vecB;

			Array<float, 2> results = resultVec.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(i * 2.0f + 3.0f, results[i]);
			}
		}

		TEST_METHOD(Subtract)
		{
			Array<float, 2> arrayA{ 3.0f, 6.0f };
			Array<float, 2> arrayB{ 2.0f, 4.0f };

			Vector<2> vecA = Vector<2>(arrayA);
			Vector<2> vecB = Vector<2>(arrayB);

			Vector<2> vecC = vecA - vecB;

			Array<float, 2> results = vecC.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector subtraction failed");
			}
		}

		TEST_METHOD(Negation)
		{
			Array<float, 2> input = { 1.0f, 1.0f };
			Vector<2> vector = Vector<2>(input);
			Vector<2> resultVector = -vector;
			Array<float, 2> results = resultVector.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(-1.0f, results[i], L"Vector negation failed!");
			}
		}

		TEST_METHOD(Equality)
		{
			Array<float, 2> input = { 1.0f, 2.0f };
			Vector<2> vecA = Vector<2>(input);
			Vector<2> vecB = Vector<2>(input);

			Assert::IsTrue(vecA == vecB, L"Vector Equality failed!");
		}

		TEST_METHOD(Inequality)
		{
			Array<float, 2> inputA = { 1.0f, 2.0f };
			Array<float, 2> inputB = { 1.0f, 1.0f };
			Vector<2> vecA = Vector<2>(inputA);
			Vector<2> vecB = Vector<2>(inputB);

			Assert::IsTrue(vecA != vecB, L"Vector Inequality failed!");
		}

		TEST_METHOD(MultiplyScale)
		{
			Array<float, 2> inputA = { 1.0f, 2.0f };

			Vector<2> vecA = Vector<2>(inputA);

			Vector<2> resultVector = vecA * 2.0f;

			Array<float, 2> results = resultVector.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(i * 2.0f + 2.0f, results[i], L"Vector scale by multiplication failed!");
			}
		}

		TEST_METHOD(DivideScale)
		{
			Array<float, 2> inputA = { 1.0f, 2.0f };

			Vector<2> vecA = Vector<2>(inputA);

			Vector<2> resultVector = vecA / 2.0f;

			Array<float, 2> results = resultVector.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(i * 0.5f + 0.5f, results[i], L"Vector scale by division failed!");
			}
		}

		TEST_METHOD(AddAssign)
		{
			Array<float, 2> inputA = { 1.0f, 2.0f };
			Array<float, 2> inputB = { 2.0f, 3.0f };

			Vector<2> vecA = Vector<2>(inputA);
			Vector<2> vecB = Vector<2>(inputB);

			vecA += vecB;

			Array<float, 2> results = vecA.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(i * 2.0f + 3.0f, results[i], L"Vector += operator test failed!");
			}
		}

		TEST_METHOD(SubtractAssign)
		{
			Array<float, 2> inputA = { 3.0f, 5.0f };
			Array<float, 2> inputB = { 2.0f, 3.0f };

			Vector<2> vecA = Vector<2>(inputA);
			Vector<2> vecB = Vector<2>(inputB);

			vecA -= vecB;

			Array<float, 2> results = vecA.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector -= operator test failed!");
			}
		}

		TEST_METHOD(MultScaleAssign)
		{
			Array<float, 2> inputA = { 1.0f, 2.0f };

			Vector<2> vecA = Vector<2>(inputA);

			vecA *= 2.0f;

			Array<float, 2> results = vecA.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(i * 2.0f + 2.0f, results[i], L"Vector *= operator test failed!");
			}
		}

		TEST_METHOD(DivideScaleAssign)
		{
			Array<float, 2> inputA = { 2.0f, 4.0f };

			Vector<2> vecA = Vector<2>(inputA);

			vecA /= 2.0f;

			Array<float, 2> results = vecA.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector /= operator test failed!");
			}
		}

		TEST_METHOD(GetValueByIndex)
		{
			Array<float, 2> inputA = { 2.0f, 4.0f };

			Vector<2> vecA = Vector<2>(inputA);

			Assert::AreEqual(2.0f, vecA.GetFloatByIndex<0>());
			Assert::AreEqual(4.0f, vecA.GetFloatByIndex<1>());
		}

		TEST_METHOD(SplatValueByIndex)
		{
			Array<float, 2> inputA = { 2.0f, 4.0f };

			Vector<2> vecA = Vector<2>(inputA);

			Vector<4> resultVec = vecA.SplatFloatByIndex<1, 4>();

			Array<float, 4> results = resultVec.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(4.0f, results[i]);
			}
		}

		TEST_METHOD(Normalize)
		{
			Array<float, 2> inputA = { 3.0f, 4.0f };

			Vector<2> vecA = Vector<2>(inputA);

			Vector<2> resultVec = vecA.Normalize();

			Array<float, 2> results = resultVec.Unload();

			Assert::AreEqual(0.6f, results[0]);
			Assert::AreEqual(0.8f, results[1]);
		}

		TEST_METHOD(Magnitude)
		{
			Array<float, 2> inputA = { 6.0f, 8.0f };

			Vector<2> vecA = Vector<2>(inputA);

			float result = vecA.Magnitude();

			Assert::AreEqual(10.0f, result);
		}

		TEST_METHOD(Dot)
		{
			Array<float, 2> inputA = { 1.0f, 2.0f };
			Array<float, 2> inputB = { 2.0f, 3.0f };

			Vector<2> vecA = Vector<2>(inputA);
			Vector<2> vecB = Vector<2>(inputB);

			float result = vecA.Dot(vecB);

			Assert::AreEqual(8.0f, result);
		}

		TEST_METHOD(Cross)
		{
			Array<float, 2> inputA = { 1.0f, 2.0f };
			Array<float, 2> inputB = { 2.0f, 3.0f };

			Vector<2> vecA = Vector<2>(inputA);
			Vector<2> vecB = Vector<2>(inputB);

			auto result = vecA.Cross(vecB);

			Assert::AreEqual(-1.0f, vecA.Cross(vecB));
		}

		TEST_METHOD(MemberwiseMultiply)
		{
			Vector<2> vecA = Vector<2>(1.0f, 2.0f);
			Vector<2> vecB = Vector<2>(3.0f, 4.0f);
			Array<float, 2> expected = { 3.0f, 8.0f };

			Vector<2> vecC = vecA.MemberwiseMultiply(vecB);

			Array<float, 2> results = vecC.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(expected[i], results[i]);
			}
		}

		TEST_METHOD(Load)
		{
			Array<float, 2> inputA = { 1.0f, 2.0f };
			Array<float, 2> inputB = { 2.0f, 3.0f };

			Vector<2> vecA = Vector<2>(inputA);

			vecA.Load(inputB);

			for (size_t i = 0; i < 2; ++i)
			{
				auto results = vecA.Unload();

				Assert::AreEqual(i + 2.0f, results[i]);
			}
		}

		TEST_METHOD(Unload)
		{
			Array<float, 2> inputA = { 1.0f, 2.0f };

			Vector<2> vecA = Vector<2>(inputA);

			Array<float, 2> results = vecA.Unload();

			for (size_t i = 0; i < 2; ++i)
			{
				Assert::AreEqual(inputA[i], results[i]);
			}
		}
	};
}