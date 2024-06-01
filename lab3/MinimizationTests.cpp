#include "pch.h"
#include "CppUnitTest.h"
#include"../MinimizationProject/Minimkzation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(MinimizationTest1)
	{
	public:
		
		TEST_METHOD(glueSdnf2)
		{
			vector<string> sdnf = { "(!a & !b & !c)", "(!a & !b & c)", "(!a & b & !c)", "(!a & b & c)", "(a & !b & !c)", "(a & !b & c)", "(a & b & !c)" };
			vector<string> dupSdnf = { "(!a & !b & !c)", "(!a & !b & c)", "(!a & b & !c)", "(!a & b & c)", "(a & !b & !c)", "(a & !b & c)", "(a & b & !c)" };
			vector<string> gluedSdnf = glueSDNFBy2(sdnf);
			vector<string> notGlued = addNotGlued(dupSdnf);
			gluedSdnf.insert(gluedSdnf.end(), notGlued.begin(), notGlued.end());
			vector<string> check = { "(!a & !b)", "(!a & !c)", "(!b & !c)", "(!a & c)", "(!b & c)", "(!a & b)", "(b & !c)", "(a & !b)", "(a & !c)" };
			string answer, checkAnswer;
			for (int i = 0; i < gluedSdnf.size(); i++)
				answer += gluedSdnf[i];
			for (int i = 0; i < check.size(); i++)
				checkAnswer += check[i];
			Assert::AreEqual(answer, checkAnswer);
		}
		TEST_METHOD(glueSknf2)
		{
			vector<string> sknf = { "(!a | b | c)", "(!a | b | !c)", "(!a | !b | c)" };
			vector<string> gluedSknf = glueSKNFBy2(sknf);
			vector<string> check = { "(!a | b)", "(!a | c)" };
			string answer, checkAnswer;
			for (int i = 0; i < gluedSknf.size(); i++)
				answer += gluedSknf[i];
			for (int i = 0; i < check.size(); i++)
				checkAnswer += check[i];
			Assert::AreEqual(answer, checkAnswer);
		}

		TEST_METHOD(TestEvaluateClause)
		{
			unordered_map<char, bool> variableAssignments;
			variableAssignments['A'] = true;
			variableAssignments['B'] = false;
			variableAssignments['C'] = true;
			Assert::IsTrue(evaluateClause("(A|!B)&C", variableAssignments)); 
		}

		TEST_METHOD(TestTryGlue)
		{
			string clause1 = "(a | b)";
			string clause2 = "(a | !b)";
			string result = tryGlue(clause1, clause2);
			Assert::AreEqual(string("(a)"), result);
		}

		TEST_METHOD(TestGlueSdnfBy1)
		{
			vector<string> sdnf = { "(!a & !b & !c)", "(!a & !b & c)", "(!a & b & !c)", "(!a & b & c)", "(a & !b & !c)", "(a & !b & c)", "(a & b & !c)" };
			vector<string> dupSdnf = { "(!a & !b & !c)", "(!a & !b & c)", "(!a & b & !c)", "(!a & b & c)", "(a & !b & !c)", "(a & !b & c)", "(a & b & !c)" };
			vector<string> result1 = glueSDNFBy2(sdnf);
			vector<string> result3 = glueSDNFBy1(result1);
			vector<string> result2 = addNotGlued(dupSdnf);
			result1.insert(result1.end(), result2.begin(), result2.end());
			result3.insert(result3.end(), result2.begin(), result2.end());
			vector<string> checkAnswer = { "(!a)", "(!b)" };
			string answer, check;
			for (int i = 0; i < result3.size(); i++)
				answer += result3[i];
			for (int i = 0; i < checkAnswer.size(); i++)
				check += checkAnswer[i];
			Assert::AreEqual(check, answer);
		}

		TEST_METHOD(TestFirstMethod)
		{
			vector<string> sdnfClauses = { "(A|B)", "(!A|C)" };
			vector<string> sdnfClausess = { "(A|B)", "(!A|C)" };
			vector<string> sknfClauses = { "(A&B)", "(!A|!B)" };
			vector<string> sknfClauses33 = { "(A&B)", "(!A|!B)" };
			vector<string> result = FirstMethod(sdnfClauses, sdnfClausess, sknfClauses, sknfClauses33);
			Assert::AreEqual(string("(A&B)"), result[0]); 
		}

		TEST_METHOD(TestSecondMethod)
		{
			string expression = "((a -> ((!b & c) ~ d)) | e)";
			int numVariables = countVariables(expression);
			vector<bool> variables(numVariables, false);
			vector<string> sknfClauses3;
			vector<string> sdnfClauses3;
			vector<string> sknfClauses4;
			vector<string> sdnfClauses4;
			int rowNumber2 = 0;
			for (int i = 0; i < pow(2, numVariables); ++i) {
				for (int j = 0; j < numVariables; ++j) {
					variables[j] = ((i >> (numVariables - j - 1)) & 1) == 1;
				}
				bool result = evaluateLogicalExpression(variables, expression);
				calculateSknfAndSdnf(variables, result, rowNumber2, numVariables, sknfClauses3, sdnfClauses3);
				calculateSknfAndSdnf(variables, result, rowNumber2, numVariables, sknfClauses4, sdnfClauses4);
				rowNumber2++;
			}
			cout << endl;
			cout << endl;
			vector<string> answer = SecondMethod(sdnfClauses3, sdnfClauses4, variables, numVariables, expression, rowNumber2, sknfClauses3, sknfClauses4);
			string finalAnswer;
			string check = "(!b | !d)(!a)(!a | !d)(!a | e)(b | e)(!d | e)(c | !d)(c | e)(!c | e)(!b | e)";
			for (int i = 0; i < answer.size(); i++)
				finalAnswer += answer[i];
			Assert::AreEqual(check, finalAnswer);
		}

		TEST_METHOD(TestGetOnlyVariables)
		{
			vector<string> sdnf = { "(!a & !b & !c)" };
			vector<string> variables = GetOnlyVariables(sdnf);
			string answer;
			string check = "!a!b!c";
			for (int i = 0; i < variables.size(); i++)
				answer += variables[i];
			Assert::AreEqual(check, answer);
		}

		TEST_METHOD(TestGetTable)
		{
			vector<string> sdnf = { "(!a & !b & !c)", "(!a & !b & c)", "(!a & b & !c)", "(!a & b & c)", "(a & !b & !c)", "(a & !b & c)", "(a & b & !c)" };
			string tableSdnf = GetTable(sdnf);
			string check = "11111101";
		    Assert::AreEqual(check, tableSdnf);
		}

		TEST_METHOD(TestMinimizeKarnaughSdnf)
		{
			string expression = "a -> (b & c)";
			vector<string> variableNames;
			for (char c : expression) {
				if (isalpha(c)) {
					variableNames.push_back(string(1, c));
				}
			}
			vector<string> sdnf = { "(!a & !b & !c)", "(!a & !b & c)", "(!a & b & !c)", "(!a & b & c)", "(a & !b & !c)", "(a & !b & c)", "(a & b & !c)" };
			string tableSdnf = GetTable(sdnf);
			vector<string> result = MinimizeKarnaughMap(tableSdnf, variableNames);
			string answer;
			string check = "!a!b!c";
			for (int i = 0; i < result.size(); i++)
				answer += result[i];
			Assert::AreEqual(check, answer);
		}

		TEST_METHOD(TestMinimizeKarnaughSknf)
		{
			string expression = "a -> (b & c)";
			vector<string> variableNames;
			for (char c : expression) {
				if (isalpha(c)) {
					variableNames.push_back(string(1, c));
				}
			}
			vector<string> sdnf = { "(!a & !b & !c)", "(!a & !b & c)", "(!a & b & !c)", "(!a & b & c)", "(a & !b & !c)", "(a & !b & c)", "(a & b & !c)" };
			string tableSdnf = GetTable(sdnf);
			vector<string> result = MinimizeSknfKarnaughMap(tableSdnf, variableNames);
			string answer;
			string check = "(b | c)";
			for (int i = 0; i < result.size(); i++)
				answer += result[i];
			Assert::AreEqual(check, answer);
		}

		TEST_METHOD(TestThirdMethod)
		{
			string expression = "a -> (b & c)";
			int numVariables = countVariables(expression);
			vector<bool> variables(numVariables, false);
			vector<string> sknfClauses3;
			vector<string> sdnfClauses3;
			vector<string> sknfClauses4;
			vector<string> sdnfClauses4;
			int rowNumber2 = 0;
			for (int i = 0; i < pow(2, numVariables); ++i) {
				for (int j = 0; j < numVariables; ++j) {
					variables[j] = ((i >> (numVariables - j - 1)) & 1) == 1;
				}
				bool result = evaluateLogicalExpression(variables, expression);
				calculateSknfAndSdnf(variables, result, rowNumber2, numVariables, sknfClauses3, sdnfClauses3);
				calculateSknfAndSdnf(variables, result, rowNumber2, numVariables, sknfClauses4, sdnfClauses4);
				rowNumber2++;
			}
			cout << endl;
			cout << endl;
			vector<string> answer = ThirdMethod(sdnfClauses3, sdnfClauses4, variables, numVariables, expression, rowNumber2, sknfClauses3, sknfClauses4);
			string finalAnswer;
			string check = "!a(b & c)";
			for (int i = 0; i < answer.size(); i++)
				finalAnswer += answer[i];
			Assert::AreEqual(check, finalAnswer);
		}
	};
}
