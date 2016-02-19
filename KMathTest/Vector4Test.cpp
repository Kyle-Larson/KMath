#include "stdafx.h"
#include "CppUnitTest.h"
#include "Data/Storage/Array.h"
#include "Coordinate/Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace KEngine::Math::Coordinate;
using namespace KEngine::Data::Storage;

namespace KMathTest
{
	TEST_CLASS(Vector4Tests)
	{
		TEST_METHOD(ZeroIsZero)
		{
			Vector<4> vecA = Vector<4>::Zero;

			Array<float, 4> resultArray = vecA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(0.0f, resultArray[i]);
			}
		}

		TEST_METHOD(OneIsOne)
		{
			Vector<4> vecA = Vector<4>::One;

			Array<float, 4> resultArray = vecA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(1.0f, resultArray[i]);
			}
		}

		TEST_METHOD(UnitXVector)
		{
			Vector<4> vecA = Vector<4>::UnitX;

			Array<float, 4> resultArray = vecA.Unload();

			Assert::AreEqual(1.0f, resultArray[0]);
			Assert::AreEqual(0.0f, resultArray[1]);
			Assert::AreEqual(0.0f, resultArray[2]);
			Assert::AreEqual(0.0f, resultArray[3]);
		}

		TEST_METHOD(UnitYVector)
		{
			Vector<4> vecA = Vector<4>::UnitY;

			Array<float, 4> resultArray = vecA.Unload();

			Assert::AreEqual(0.0f, resultArray[0]);
			Assert::AreEqual(1.0f, resultArray[1]);
			Assert::AreEqual(0.0f, resultArray[2]);
			Assert::AreEqual(0.0f, resultArray[3]);
		}

		TEST_METHOD(UnitZVector)
		{
			Vector<4> vecA = Vector<4>::UnitZ;

			Array<float, 4> resultArray = vecA.Unload();

			Assert::AreEqual(0.0f, resultArray[0]);
			Assert::AreEqual(0.0f, resultArray[1]);
			Assert::AreEqual(1.0f, resultArray[2]);
			Assert::AreEqual(0.0f, resultArray[3]);
		}

		TEST_METHOD(UnitWVector)
		{
			Vector<4> vecA = Vector<4>::UnitW;

			Array<float, 4> resultArray = vecA.Unload();

			Assert::AreEqual(0.0f, resultArray[0]);
			Assert::AreEqual(0.0f, resultArray[1]);
			Assert::AreEqual(0.0f, resultArray[2]);
			Assert::AreEqual(1.0f, resultArray[3]);
		}

		TEST_METHOD(DefaultConstruction)
		{
			Vector<4> vecA = Vector<4>();

			Array<float, 4> resultArray = vecA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(0.0f, resultArray[i]);
			}
		}

		TEST_METHOD(FillConstruction)
		{
			Vector<4> vecA = Vector<4>(3.0f);

			Array<float, 4> resultArray = vecA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(3.0f, resultArray[i]);
			}
		}

		TEST_METHOD(MemberwiseConstruction)
		{
			Vector<4> vecA = Vector<4>(1.0f, 2.0f, 3.0f, 4.0f);

			Array<float, 4> resultArray = vecA.Unload();

			Assert::AreEqual(1.0f, resultArray[0]);
			Assert::AreEqual(2.0f, resultArray[1]);
			Assert::AreEqual(3.0f, resultArray[2]);
			Assert::AreEqual(4.0f, resultArray[3]);
		}

		TEST_METHOD(Add)
		{
			Array<float, 4> inputA{ 1.0f, 2.0f, 3.0f, 4.0f };
			Array<float, 4> inputB{ 2.0f, 3.0f, 4.0f, 5.0f };

			Vector<4> vecA = Vector<4>(inputA);
			Vector<4> vecB = Vector<4>(inputB);

			Vector<4> resultVec = vecA + vecB;

			Array<float, 4> results = resultVec.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(i * 2.0f + 3.0f, results[i]);
			}
		}

		TEST_METHOD(Subtract)
		{
			Array<float, 4> arrayA{ 3.0f, 6.0f, 9.0f, 12.0f };
			Array<float, 4> arrayB{ 2.0f, 4.0f, 6.0f, 8.0f };

			Vector<4> vecA = Vector<4>(arrayA);
			Vector<4> vecB = Vector<4>(arrayB);

			Vector<4> vecC = vecA - vecB;

			Array<float, 4> results = vecC.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector subtraction failed");
			}
		}

		TEST_METHOD(Negation)
		{
			Array<float, 4> input = { 1.0f, 1.0f, 1.0f, 1.0f };
			Vector<4> vector = Vector<4>(input);
			Vector<4> resultVector = -vector;
			Array<float, 4> results = resultVector.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(-1.0f, results[i], L"Vector negation failed!");
			}
		}

		TEST_METHOD(Equality)
		{
			Array<float, 4> input = { 1.0f, 2.0f, 3.0f, 4.0f };
			Vector<4> vecA = Vector<4>(input);
			Vector<4> vecB = Vector<4>(input);

			Assert::IsTrue(vecA == vecB, L"Vector Equality failed!");
		}

		TEST_METHOD(Inequality)
		{
			Array<float, 4> inputA = { 1.0f, 2.0f, 3.0f, 4.0f };
			Array<float, 4> inputB = { 1.0f, 1.0f, 3.0f, 4.0f };
			Vector<4> vecA = Vector<4>(inputA);
			Vector<4> vecB = Vector<4>(inputB);

			Assert::IsTrue(vecA != vecB, L"Vector Inequality failed!");
		}

		TEST_METHOD(MultiplyScale)
		{
			Array<float, 4> inputA = { 1.0f, 2.0f, 3.0f, 4.0f };

			Vector<4> vecA = Vector<4>(inputA);

			Vector<4> resultVector = vecA * 2.0f;

			Array<float, 4> results = resultVector.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(i * 2.0f + 2.0f, results[i], L"Vector scale by multiplication failed!");
			}
		}

		TEST_METHOD(DivideScale)
		{
			Array<float, 4> inputA = { 1.0f, 2.0f, 3.0f, 4.0f };

			Vector<4> vecA = Vector<4>(inputA);

			Vector<4> resultVector = vecA / 2.0f;

			Array<float, 4> results = resultVector.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(i * 0.5f + 0.5f, results[i], L"Vector scale by division failed!");
			}
		}

		TEST_METHOD(AddAssign)
		{
			Array<float, 4> inputA = { 1.0f, 2.0f, 3.0f, 4.0f };
			Array<float, 4> inputB = { 2.0f, 3.0f, 4.0f, 5.0f };

			Vector<4> vecA = Vector<4>(inputA);
			Vector<4> vecB = Vector<4>(inputB);

			vecA += vecB;

			Array<float, 4> results = vecA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(i * 2.0f + 3.0f, results[i], L"Vector += operator test failed!");
			}
		}

		TEST_METHOD(SubtractAssign)
		{
			Array<float, 4> inputA = { 3.0f, 5.0f, 7.0f, 9.0f };
			Array<float, 4> inputB = { 2.0f, 3.0f, 4.0f, 5.0f };

			Vector<4> vecA = Vector<4>(inputA);
			Vector<4> vecB = Vector<4>(inputB);

			vecA -= vecB;

			Array<float, 4> results = vecA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector -= operator test failed!");
			}
		}

		TEST_METHOD(MultScaleAssign)
		{
			Array<float, 4> inputA = { 1.0f, 2.0f, 3.0f, 4.0f };

			Vector<4> vecA = Vector<4>(inputA);

			vecA *= 2.0f;

			Array<float, 4> results = vecA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(i * 2.0f + 2.0f, results[i], L"Vector *= operator test failed!");
			}
		}

		TEST_METHOD(DivideScaleAssign)
		{
			Array<float, 4> inputA = { 2.0f, 4.0f, 6.0f, 8.0f };

			Vector<4> vecA = Vector<4>(inputA);

			vecA /= 2.0f;

			Array<float, 4> results = vecA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector /= operator test failed!");
			}
		}

		TEST_METHOD(GetValueByIndex)
		{
			Array<float, 4> inputA = { 2.0f, 4.0f, 6.0f, 8.0f };

			Vector<4> vecA = Vector<4>(inputA);

			Assert::AreEqual(2.0f, vecA.GetFloatByIndex<0>());
			Assert::AreEqual(4.0f, vecA.GetFloatByIndex<1>());
			Assert::AreEqual(6.0f, vecA.GetFloatByIndex<2>());
			Assert::AreEqual(8.0f, vecA.GetFloatByIndex<3>());
		}

		TEST_METHOD(SplatValueByIndex)
		{
			Array<float, 4> inputA = { 2.0f, 4.0f, 6.0f, 8.0f };

			Vector<4> vecA = Vector<4>(inputA);

			Vector<4> resultVec = vecA.SplatFloatByIndex<1, 4>();

			Array<float, 4> results = resultVec.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(4.0f, results[i]);
			}
		}

		TEST_METHOD(Normalize)
		{
			Array<float, 4> inputA = { 3.0f, 4.0f, 0.0f, 0.0f };

			Vector<4> vecA = Vector<4>(inputA);

			Vector<4> resultVec = vecA.Normalize();

			Array<float, 4> results = resultVec.Unload();

			Assert::AreEqual(0.6f, results[0]);
			Assert::AreEqual(0.8f, results[1]);
			Assert::AreEqual(0.0f, results[2]);
			Assert::AreEqual(0.0f, results[3]);
		}

		TEST_METHOD(Magnitude)
		{
			Array<float, 4> inputA = { 6.0f, 8.0f, 10.0f, 12.0f };

			Vector<4> vecA = Vector<4>(inputA);

			float result = vecA.Magnitude();

			Assert::AreEqual(static_cast<float>(sqrt(344.0)), result);
		}

		TEST_METHOD(Dot)
		{
			Array<float, 4> inputA = { 1.0f, 2.0f, 3.0f, 4.0f };
			Array<float, 4> inputB = { 2.0f, 3.0f, 4.0f, 5.0f };

			Vector<4> vecA = Vector<4>(inputA);
			Vector<4> vecB = Vector<4>(inputB);

			float result = vecA.Dot(vecB);

			Assert::AreEqual(40.0f, result);
		}

		TEST_METHOD(MemberwiseMultiply)
		{
			Vector<4> vecA = Vector<4>(1.0f, 2.0f, 3.0f, 4.0f);
			Vector<4> vecB = Vector<4>(5.0f, 6.0f, 7.0f, 8.0f);
			Array<float, 4> expected = { 5.0f, 12.0f, 21.0f, 32.0f };

			Vector<4> vecC = vecA.MemberwiseMultiply(vecB);

			Array<float, 4> result = vecC.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(expected[i], result[i]);
			}
		}

		TEST_METHOD(Load)
		{
			Array<float, 4> inputA = { 1.0f, 2.0f, 3.0f, 4.0f };
			Array<float, 4> inputB = { 2.0f, 3.0f, 4.0f, 5.0f };

			Vector<4> vecA = Vector<4>(inputA);

			vecA.Load(inputB);

			for (size_t i = 0; i < 4; ++i)
			{
				auto results = vecA.Unload();

				Assert::AreEqual(i + 2.0f, results[i]);
			}
		}

		TEST_METHOD(Unload)
		{
			Array<float, 4> inputA = { 1.0f, 2.0f, 3.0f, 4.0f };

			Vector<4> vecA = Vector<4>(inputA);

			Array<float, 4> results = vecA.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(inputA[i], results[i]);
			}
		}
	};
}