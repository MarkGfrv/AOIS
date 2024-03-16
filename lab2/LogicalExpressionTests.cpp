
#include "pch.h"
#include "CppUnitTest.h"
#include"../Project11/LogicalExxpresion.h"
#include<sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(LogicalExpressionTests)
    {
    public:
        TEST_METHOD(LogicalTest1)
        {
            stringstream buffer;
            streambuf* sbuf = cout.rdbuf();
            cout.rdbuf(buffer.rdbuf()); 

            string expression = "(a | b) & !c";
            solveExpression(expression);

            string output = buffer.str();
            string expectedOutput = "Variables: a b c \n";
            expectedOutput += "Truth table:\n";
            expectedOutput += "0\t0\t0\t0\n";
            expectedOutput += "0\t0\t1\t0\n";
            expectedOutput += "0\t1\t0\t1\n";
            expectedOutput += "0\t1\t1\t0\n";
            expectedOutput += "1\t0\t0\t1\n";
            expectedOutput += "1\t0\t1\t0\n";
            expectedOutput += "1\t1\t0\t1\n";
            expectedOutput += "1\t1\t1\t0\n";
            expectedOutput += "\nSKNF: (a | b | c) & (a | b | !c) & (a | !b | !c) & (!a | b | !c) & (!a | !b | !c)\n";
            expectedOutput += "NumSKNF: (0,1,3,5,7)\n";
            expectedOutput += "SDNF: (!a & b & !c) | (a & !b & !c) | (a & b & !c)\n";
            expectedOutput += "NumSDNF: (2,4,6)\n";
            expectedOutput += "Index form: 00101010\n";
            expectedOutput += "Numeric form: 42\n";

            Assert::AreEqual(expectedOutput, output);
            cout.rdbuf(sbuf); 
        }
        TEST_METHOD(LogicalTest2)
        {
            stringstream buffer;
            streambuf* sbuf = cout.rdbuf();
            cout.rdbuf(buffer.rdbuf()); 

            string expression = "(a -> b) & c";
            solveExpression(expression);

            string output = buffer.str();
            string expectedOutput = "Variables: a b c \n";
            expectedOutput += "Truth table:\n";
            expectedOutput += "0\t0\t0\t0\n";
            expectedOutput += "0\t0\t1\t1\n";
            expectedOutput += "0\t1\t0\t0\n";
            expectedOutput += "0\t1\t1\t1\n";
            expectedOutput += "1\t0\t0\t0\n";
            expectedOutput += "1\t0\t1\t0\n";
            expectedOutput += "1\t1\t0\t0\n";
            expectedOutput += "1\t1\t1\t1\n";
            expectedOutput += "\nSKNF: (a | b | c) & (a | !b | c) & (!a | b | c) & (!a | b | !c) & (!a | !b | c)\n";
            expectedOutput += "NumSKNF: (0,2,4,5,6)\n";
            expectedOutput += "SDNF: (!a & !b & c) | (!a & b & c) | (a & b & c)\n";
            expectedOutput += "NumSDNF: (1,3,7)\n";
            expectedOutput += "Index form: 01010001\n";
            expectedOutput += "Numeric form: 81\n";

            Assert::AreEqual(expectedOutput, output);
            cout.rdbuf(sbuf);
        }
        TEST_METHOD(LogicalTest3)
        {
            stringstream buffer;
            streambuf* sbuf = cout.rdbuf();
            cout.rdbuf(buffer.rdbuf()); 

            string expression = "(a ~ b) | c";
            solveExpression(expression);

            string output = buffer.str();
            string expectedOutput = "Variables: a b c \n";
            expectedOutput += "Truth table:\n";
            expectedOutput += "0\t0\t0\t1\n";
            expectedOutput += "0\t0\t1\t1\n";
            expectedOutput += "0\t1\t0\t0\n";
            expectedOutput += "0\t1\t1\t1\n";
            expectedOutput += "1\t0\t0\t0\n";
            expectedOutput += "1\t0\t1\t1\n";
            expectedOutput += "1\t1\t0\t1\n";
            expectedOutput += "1\t1\t1\t1\n";
            expectedOutput += "\nSKNF: (a | !b | c) & (!a | b | c)\n";
            expectedOutput += "NumSKNF: (2,4)\n";
            expectedOutput += "SDNF: (!a & !b & !c) | (!a & !b & c) | (!a & b & c) | (a & !b & c) | (a & b & !c) | (a & b & c)\n";
            expectedOutput += "NumSDNF: (0,1,3,5,6,7)\n";
            expectedOutput += "Index form: 11010111\n";
            expectedOutput += "Numeric form: 215\n";

            Assert::AreEqual(expectedOutput, output);
            cout.rdbuf(sbuf); 
        }
        TEST_METHOD(LogicalTest4)
        {
            stringstream buffer;
            streambuf* sbuf = cout.rdbuf();
            cout.rdbuf(buffer.rdbuf());

            string expression = "(a & b) ~ c";
            solveExpression(expression);

            string output = buffer.str();
            string expectedOutput = "Variables: a b c \n";
            expectedOutput += "Truth table:\n";
            expectedOutput += "0\t0\t0\t1\n";
            expectedOutput += "0\t0\t1\t0\n";
            expectedOutput += "0\t1\t0\t1\n";
            expectedOutput += "0\t1\t1\t0\n";
            expectedOutput += "1\t0\t0\t1\n";
            expectedOutput += "1\t0\t1\t0\n";
            expectedOutput += "1\t1\t0\t0\n";
            expectedOutput += "1\t1\t1\t1\n";
            expectedOutput += "\nSKNF: (a | b | !c) & (a | !b | !c) & (!a | b | !c) & (!a | !b | c)\n";
            expectedOutput += "NumSKNF: (1,3,5,6)\n";
            expectedOutput += "SDNF: (!a & !b & !c) | (!a & b & !c) | (a & !b & !c) | (a & b & c)\n";
            expectedOutput += "NumSDNF: (0,2,4,7)\n";
            expectedOutput += "Index form: 10101001\n";
            expectedOutput += "Numeric form: 169\n";

            Assert::AreEqual(expectedOutput, output);
            cout.rdbuf(sbuf); 
        }
    };
}
