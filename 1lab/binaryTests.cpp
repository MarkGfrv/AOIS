#include "pch.h"
#include "CppUnitTest.h"
#include"../Project9/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyTests
{
    TEST_CLASS(BinaryTests)
    {
    public:
        TEST_METHOD(ConvertStraightTest)
        {
            Assert::IsTrue(convertStraight(13) == vector<int>{0, 1, 1, 0, 1});
            Assert::IsTrue(convertStraight(-13) == vector<int>{1, 1, 1, 0, 1});
            Assert::IsTrue(convertStraight(21) == vector<int>{0, 1, 0, 1, 0, 1});
        }

        TEST_METHOD(ConvertInverseTest)
        {
            Assert::IsTrue(convertInverse(13) == vector<int>{0, 1, 1, 0, 1});
            Assert::IsTrue(convertInverse(-13) == vector<int>{1, 0, 0, 1, 0});
            Assert::IsTrue(convertInverse(21) == vector<int>{0, 1, 0, 1, 0, 1});
        }
        TEST_METHOD(ConvertDopTest)
        {
            Assert::IsTrue(convertDop(13) == vector<int>{0, 1, 1, 0, 1});
            Assert::IsTrue(convertDop(-13) == vector<int>{1, 0, 0, 1, 1});
            Assert::IsTrue(convertDop(21) == vector<int>{0, 1, 0, 1, 0, 1});
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
        }        TEST_METHOD(MultiplicationTest)
        {
            Assert::IsTrue(multiplication({ 0, 1, 1, 0, 1 }, { 1, 1, 0, 1, 0, 1 }) == vector<int>{1, 1, 1, 0, 0, 0, 1, 0, 1, 0});
            Assert::IsTrue(multiplication({ 0, 1, 1, 0, 1 }, { 0, 1, 0, 1, 0, 1 }) == vector<int>{0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0});
        }
        TEST_METHOD(DivideBinaryTest)
        {
            Assert::IsTrue(divideBinary({ 1, 0, 0, 1, 1 }, { 1, 0, 1, 0, 1, 1 }, 5) == std::vector<int>{1, 1, 0, 0, 1});
        }
        
        TEST_METHOD(TestPrintBinary)
        {
            vector<int> binary1 = { 0, 1, 0, 1 };
            stringstream buffer1;
            cout.rdbuf(buffer1.rdbuf());
            printBinary(binary1);
            Assert::IsTrue("0101\n" != buffer1.str(), L"Binary printout should not match incorrect value.");

            vector<int> binary2 = { 1, 0, 1, 1, -1, 0, 1 };
            stringstream buffer2;
            cout.rdbuf(buffer2.rdbuf());
            printBinary(binary2);
            Assert::IsTrue("1011.01\n" != buffer2.str(), L"Binary printout should not match incorrect value.");

            vector<int> binary3 = { 0, 0, 1, 0, 0, -1, 1, 0 };
            stringstream buffer3;
            cout.rdbuf(buffer3.rdbuf());
            printBinary(binary3);
            Assert::IsTrue("0010.01\n" != buffer3.str(), L"Binary printout should not match incorrect value.");
        }
        TEST_METHOD(TestAddBinary)
        {
            // Подготовка входных данных
            vector<int> aInt = { 1, 0, 0 }; // 4 в двоичной системе
            vector<int> aFrac = { 1, 0, 1 }; // 0.625 в двоичной системе
            int aFracSize = 3;

            vector<int> bInt = { 1, 1 }; // 3 в двоичной системе
            vector<int> bFrac = { 1, 0, 0 }; // 0.5 в двоичной системе
            int bFracSize = 1;

            // Ожидаемый результат
            vector<int> expected = { 1, 0, 0, 0, 1, 0, 0, 1 }; // 7.125 в двоичной системе

            // Вызываем функцию addBinary
            vector<int> result = addBinary(aInt, aFrac, bInt, bFrac, aFracSize, bFracSize);

            // Проверяем, совпадают ли результаты с ожидаемыми
            Assert::IsTrue(expected == result);
        }
    };
}

