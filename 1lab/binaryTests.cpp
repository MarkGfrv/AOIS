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
            Assert::IsTrue(addition({ 0, 1, 1, 0, 1 }, { 0, 1, 0, 1, 0, 1 }) == vector<int>{1, 0, 0, 0, 1, 0});
            Assert::IsTrue(addition({ 1, 0, 0, 1, 1 }, { 1, 0, 1, 0, 1, 1 }) == vector<int>{1, 1, 1, 1, 1, 0});
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
            vector<int> binaryNum1 = { 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1 }; 
            vector<int> binaryNum2 = { 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1 };

            vector<int> expected = { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0 }; 

           
            vector<int> result = addBinary(binaryNum1, binaryNum2);

            
            Assert::IsTrue(expected == result);
        }
    };
}
