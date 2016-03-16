#include "stdafx.h"
#include "CppUnitTest.h"
#include "Data/Storage/Array.h"
#include <KMath.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace KEngine::Math::Coordinate;
using namespace KEngine::Data::Storage;

namespace KMathTest
{
	TEST_CLASS(Vector3Tests)
	{
		TEST_METHOD(ZeroIsZero)
		{
			Vector<3> vecA = Vector<3>::Zero;

			Array<float, 3> resultArray = vecA.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(0.0f, resultArray[i]);
			}
		}

		TEST_METHOD(OneIsOne)
		{
			Vector<3> vecA = Vector<3>::One;

			Array<float, 3> resultArray = vecA.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(1.0f, resultArray[i]);
			}
		}

		TEST_METHOD(UnitXVector)
		{
			Vector<3> vecA = Vector<3>::UnitX;

			Array<float, 3> resultArray = vecA.Unload();

			Assert::AreEqual(1.0f, resultArray[0]);
			Assert::AreEqual(0.0f, resultArray[1]);
			Assert::AreEqual(0.0f, resultArray[2]);
		}

		TEST_METHOD(UnitYVector)
		{
			Vector<3> vecA = Vector<3>::UnitY;

			Array<float, 3> resultArray = vecA.Unload();

			Assert::AreEqual(0.0f, resultArray[0]);
			Assert::AreEqual(1.0f, resultArray[1]);
			Assert::AreEqual(0.0f, resultArray[2]);
		}

		TEST_METHOD(UnitZVector)
		{
			Vector<3> vecA = Vector<3>::UnitZ;

			Array<float, 3> resultArray = vecA.Unload();

			Assert::AreEqual(0.0f, resultArray[0]);
			Assert::AreEqual(0.0f, resultArray[1]);
			Assert::AreEqual(1.0f, resultArray[2]);
		}

		TEST_METHOD(DefaultConstruction)
		{
			Vector<3> vecA = Vector<3>();

			Array<float, 3> resultArray = vecA.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(0.0f, resultArray[i]);
			}
		}

		TEST_METHOD(FillConstruction)
		{
			Vector<3> vecA = Vector<3>(3.0f);

			Array<float, 3> resultArray = vecA.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(3.0f, resultArray[i]);
			}
		}

		TEST_METHOD(MemberwiseConstruction)
		{
			Vector<3> vecA = Vector<3>(1.0f, 2.0f, 3.0f);

			Array<float, 3> resultArray = vecA.Unload();

			Assert::AreEqual(1.0f, resultArray[0]);
			Assert::AreEqual(2.0f, resultArray[1]);
			Assert::AreEqual(3.0f, resultArray[2]);
		}

		TEST_METHOD(Add)
		{
			Array<float, 3> inputA{ 1.0f, 2.0f, 3.0f };
			Array<float, 3> inputB{ 2.0f, 3.0f, 4.0f };

			Vector<3> vecA = Vector<3>(inputA);
			Vector<3> vecB = Vector<3>(inputB);

			Vector<3> resultVec = vecA + vecB;

			Array<float, 3> results = resultVec.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i * 2.0f + 3.0f, results[i]);
			}
		}

		TEST_METHOD(Subtract)
		{
			Array<float, 3> arrayA{ 3.0f, 6.0f, 9.0f };
			Array<float, 3> arrayB{ 2.0f, 4.0f, 6.0f };

			Vector<3> vecA = Vector<3>(arrayA);
			Vector<3> vecB = Vector<3>(arrayB);

			Vector<3> vecC = vecA - vecB;

			Array<float, 3> results = vecC.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector subtraction failed");
			}
		}

		TEST_METHOD(Negation)
		{
			Array<float, 3> input = { 1.0f, 1.0f, 1.0f };
			Vector<3> vector = Vector<3>(input);
			Vector<3> resultVector = -vector;
			Array<float, 3> results = resultVector.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(-1.0f, results[i], L"Vector negation failed!");
			}
		}

		TEST_METHOD(Equality)
		{
			Array<float, 3> input = { 1.0f, 2.0f, 3.0f };
			Vector<3> vecA = Vector<3>(input);
			Vector<3> vecB = Vector<3>(input);

			Assert::IsTrue(vecA == vecB, L"Vector Equality failed!");
		}

		TEST_METHOD(Inequality)
		{
			Array<float, 3> inputA = { 1.0f, 2.0f, 3.0f };
			Array<float, 3> inputB = { 1.0f, 1.0f, 3.0f };
			Vector<3> vecA = Vector<3>(inputA);
			Vector<3> vecB = Vector<3>(inputB);

			Assert::IsTrue(vecA != vecB, L"Vector Inequality failed!");
		}

		TEST_METHOD(MultiplyScale)
		{
			Array<float, 3> inputA = { 1.0f, 2.0f, 3.0f };

			Vector<3> vecA = Vector<3>(inputA);

			Vector<3> resultVector = vecA * 2.0f;

			Array<float, 3> results = resultVector.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i * 2.0f + 2.0f, results[i], L"Vector scale by multiplication failed!");
			}
		}

		TEST_METHOD(DivideScale)
		{
			Array<float, 3> inputA = { 1.0f, 2.0f, 3.0f };

			Vector<3> vecA = Vector<3>(inputA);

			Vector<3> resultVector = vecA / 2.0f;

			Array<float, 3> results = resultVector.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i * 0.5f + 0.5f, results[i], L"Vector scale by division failed!");
			}
		}

		TEST_METHOD(AddAssign)
		{
			Array<float, 3> inputA = { 1.0f, 2.0f, 3.0f };
			Array<float, 3> inputB = { 2.0f, 3.0f, 4.0f };

			Vector<3> vecA = Vector<3>(inputA);
			Vector<3> vecB = Vector<3>(inputB);

			vecA += vecB;

			Array<float, 3> results = vecA.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i * 2.0f + 3.0f, results[i], L"Vector += operator test failed!");
			}
		}

		TEST_METHOD(SubtractAssign)
		{
			Array<float, 3> inputA = { 3.0f, 5.0f, 7.0f };
			Array<float, 3> inputB = { 2.0f, 3.0f, 4.0f };

			Vector<3> vecA = Vector<3>(inputA);
			Vector<3> vecB = Vector<3>(inputB);

			vecA -= vecB;

			Array<float, 3> results = vecA.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector -= operator test failed!");
			}
		}

		TEST_METHOD(MultScaleAssign)
		{
			Array<float, 3> inputA = { 1.0f, 2.0f, 3.0f };

			Vector<3> vecA = Vector<3>(inputA);

			vecA *= 2.0f;

			Array<float, 3> results = vecA.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i * 2.0f + 2.0f, results[i], L"Vector *= operator test failed!");
			}
		}

		TEST_METHOD(DivideScaleAssign)
		{
			Array<float, 3> inputA = { 2.0f, 4.0f, 6.0f };

			Vector<3> vecA = Vector<3>(inputA);

			vecA /= 2.0f;

			Array<float, 3> results = vecA.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i + 1.0f, results[i], L"Vector /= operator test failed!");
			}
		}

		TEST_METHOD(GetValueByIndex)
		{
			Array<float, 3> inputA = { 2.0f, 4.0f, 6.0f };

			Vector<3> vecA = Vector<3>(inputA);

			Assert::AreEqual(2.0f, vecA.GetFloatByIndex<0>());
			Assert::AreEqual(4.0f, vecA.GetFloatByIndex<1>());
			Assert::AreEqual(6.0f, vecA.GetFloatByIndex<2>());
		}

		TEST_METHOD(SplatValueByIndex)
		{
			Array<float, 3> inputA = { 2.0f, 4.0f, 6.0f };

			Vector<3> vecA = Vector<3>(inputA);

			Vector<4> resultVec = vecA.SplatFloatByIndex<1, 4>();

			Array<float, 4> results = resultVec.Unload();

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(4.0f, results[i]);
			}
		}

		TEST_METHOD(Normalize)
		{
			Array<float, 3> inputA = { 3.0f, 4.0f, 0.0f };

			Vector<3> vecA = Vector<3>(inputA);

			Vector<3> resultVec = vecA.Normalize();

			Array<float, 3> results = resultVec.Unload();

			Assert::AreEqual(0.6f, results[0]);
			Assert::AreEqual(0.8f, results[1]);
			Assert::AreEqual(0.0f, results[2]);
		}

		TEST_METHOD(Magnitude)
		{
			Array<float, 3> inputA = { 6.0f, 8.0f, 10.0f };

			Vector<3> vecA = Vector<3>(inputA);

			float result = vecA.Magnitude();

			Assert::AreEqual(static_cast<float>(sqrt(200.0)), result);
		}

		TEST_METHOD(Dot)
		{
			Array<float, 3> inputA = { 1.0f, 2.0f, 3.0f };
			Array<float, 3> inputB = { 2.0f, 3.0f, 4.0f };

			Vector<3> vecA = Vector<3>(inputA);
			Vector<3> vecB = Vector<3>(inputB);

			float result = vecA.Dot(vecB);

			Assert::AreEqual(20.0f, result);
		}

		TEST_METHOD(Cross)
		{
			Array<float, 3> inputA = { 1.0f, 2.0f, 3.0f };
			Array<float, 3> inputB = { 2.0f, 3.0f, 4.0f };

			Vector<3> vecA = Vector<3>(inputA);
			Vector<3> vecB = Vector<3>(inputB);

			auto resultVec = vecA.Cross(vecB);

			Array<float, 3> results = resultVec.Unload();

			Assert::AreEqual(-1.0f, results[0]);
			Assert::AreEqual(2.0f, results[1]);
			Assert::AreEqual(-1.0f, results[2]);
		}

		TEST_METHOD(MemberwiseMultiply)
		{
			Vector<3> vecA = Vector<3>(1.0f, 2.0f, 3.0f);
			Vector<3> vecB = Vector<3>(4.0f, 5.0f, 6.0f);
			Array<float, 3> expected = { 4.0f, 10.0f, 18.0f };

			Vector<3> vecC = vecA.MemberwiseMultiply(vecB);

			Array<float, 3> result = vecC.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(expected[i], result[i]);
			}
		}

		TEST_METHOD(Load)
		{
			Array<float, 3> inputA = { 1.0f, 2.0f, 3.0f };
			Array<float, 3> inputB = { 2.0f, 3.0f, 4.0f };

			Vector<3> vecA = Vector<3>(inputA);

			vecA.Load(inputB);

			for (size_t i = 0; i < 3; ++i)
			{
				auto results = vecA.Unload();

				Assert::AreEqual(i + 2.0f, results[i]);
			}
		}

		TEST_METHOD(Unload)
		{
			Array<float, 3> inputA = { 1.0f, 2.0f, 3.0f };

			Vector<3> vecA = Vector<3>(inputA);

			Array<float, 3> results = vecA.Unload();

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(inputA[i], results[i]);
			}
		}
	};
}