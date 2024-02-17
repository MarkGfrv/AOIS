#include "pch.h"
#include "CppUnitTest.h"
#include"../Project8/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyTests
{
	TEST_CLASS(BinaryTests)
	{
	public:
        TEST_METHOD(ConvertStraightTest)
        {
            Assert::IsTrue(convert_straight(13) == vector<int>{0, 1, 1, 0, 1});
            Assert::IsTrue(convert_straight(-13) == vector<int>{1, 1, 1, 0, 1});
            Assert::IsTrue(convert_straight(21) == vector<int>{0, 1, 0, 1, 0, 1});
        }

        TEST_METHOD(ConvertInverseTest)
        {
            Assert::IsTrue(convert_inverse(13) == vector<int>{0, 0, 0, 1, 0});
            Assert::IsTrue(convert_inverse(-13) == vector<int>{1, 0, 0, 1, 0});
            Assert::IsTrue(convert_inverse(21) == vector<int>{0, 0, 1, 0, 1, 0});
        }
        TEST_METHOD(ConvertDopTest)
        {
            Assert::IsTrue(convert_dop(13) == vector<int>{1, 0, 0, 1, 1});
            Assert::IsTrue(convert_dop(-13) == vector<int>{1, 0, 0, 1, 1});
            Assert::IsTrue(convert_dop(21) == vector<int>{1, 0, 1, 0, 1, 1});
        }
        TEST_METHOD(AdditionTest)
        {
            Assert::IsTrue(addition({ 0, 1, 1, 0, 1 }, { 0, 1, 0, 1, 0, 1 }) == vector<int>{1, 0, 1, 1, 1});
            Assert::IsTrue(addition({ 1, 1, 1, 0, 1 }, { 1, 1, 0, 1, 0, 1 }) == vector<int>{1, 1, 0, 1, 1, 1});
        }

        TEST_METHOD(SubtractionTest)
        {
            Assert::IsTrue(substraction({ 1, 0, 1 }, { 0, 1, 0 }) == vector<int>{0, 1, 1});
            Assert::IsTrue(substraction({ 1, 1, 1 }, { 1, 1, 1 }) == vector<int>{0, 0, 0});
        }
        TEST_METHOD(IncrementTest)
        {
            Assert::IsTrue(increment({ 1, 1, 0 }) == vector<int>{1, 1, 1});
            Assert::IsTrue(increment({ 1, 1, 1 }) == vector<int>{0, 0, 0});
        }
        TEST_METHOD(MultiplicationTest)
        {
            Assert::IsTrue(multiplication({ 0, 1, 1, 0, 1 }, { 1, 1, 0, 1, 0, 1 }) == vector<int>{1, 1, 1, 0, 0, 0, 1, 0, 1, 0});
            Assert::IsTrue(multiplication({ 0, 1, 1, 0, 1 }, { 0, 1, 0, 1, 0, 1 }) == vector<int>{0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0});
        }
        TEST_METHOD(DivideBinaryTest)
        {
            Assert::IsTrue(divide_binary({ 1, 0, 0, 1, 1 }, { 1, 0, 1, 0, 1, 1 }, 5) == std::vector<int>{1, 1, 0, 0, 1});
        }
        TEST_METHOD(PrintBinaryTest) {
            ostringstream buffer;
            vector<int> binary = { 1, 0, 1, 0, 1 };
            streambuf* old = cout.rdbuf(buffer.rdbuf());
            printBinary(binary);
            cout.rdbuf(old);
            Assert::IsTrue(buffer.str() == "10101\n");
        }
	};
}

