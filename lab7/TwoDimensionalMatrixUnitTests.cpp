#include "pch.h"
#include "CppUnitTest.h"
#include"../TwoDimensionalMatrix/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixUnitTest
{
	TEST_CLASS(MatrixUnitTest)
	{
	public:
		
		TEST_METHOD(PrintWordTest)
		{
			Matrix mat;
			string check = "1110000000000000";
			mat.WriteWord(check, 2);
			string word = mat.PrintWord(2);
		    Assert::AreEqual(word, check);
		}
		TEST_METHOD(PrintAddressRowTest) {
			Matrix mat;
			string check = "1100011110001000";
			mat.WriteAddressRow(check, 3);
			string row = mat.PrintAddressRow(3);
			Assert::AreEqual(row, check);
		}
		TEST_METHOD(F5Test) {
			Matrix mat;
			string secondWord = "1111100111111010";
			mat.WriteWord(secondWord, 6);
			mat.F5(0, 6, 12);
			string result = mat.PrintWord(12);
			Assert::AreEqual(secondWord, result);
		}
		TEST_METHOD(F10Test) {
			Matrix mat;
			string secondWord = "1111100111111010";
			string negatedSecondWord = "0000011000000101";
			mat.WriteWord(secondWord, 4);
			mat.F10(0, 4, 10);
			string result = mat.PrintWord(10);
			Assert::AreEqual(negatedSecondWord, result);
		}
		TEST_METHOD(F0Test) {
			Matrix mat;
			string word = "0000000000000000";
			mat.F0(8);
			string result = mat.PrintWord(8);
			Assert::AreEqual(word, result);
		}
		TEST_METHOD(F15Test) {
			Matrix mat;
			string word = "1111111111111111";
			mat.F15(14);
			string result = mat.PrintWord(14);
			Assert::AreEqual(word, result);
		}
		TEST_METHOD(KeySummTest) {
			Matrix mat;
			string key = "111";
			string word = "1111100001110000";
			mat.WriteWord(word, 5);
			string newWord = mat.Search(key);
			string summa = mat.Summa(newWord);
			string check = "1111100001101111";
			Assert::AreEqual(summa, check);
		}
		TEST_METHOD(SearchByMatchTest) {
			Matrix mat;
			string searchWord = "1111000011001010";
			string word = searchWord;
			mat.WriteWord(word, 15);
			string result = mat.SearchMatch(searchWord);
			string check = mat.PrintWord(15);
		    Assert::AreEqual(result, check);
		}
		TEST_METHOD(SearchByBestMatchTest) {
			Matrix mat;
			string searchWord = "1110011000011110";
			string firstWord = "1110111001111110";
			string secondWord = "1111111000011110";
			mat.WriteWord(firstWord, 5);
			mat.WriteWord(secondWord, 12);
			string check = mat.PrintWord(12);
			string result = mat.SearchMatch(searchWord);
			Assert::AreEqual(result, check);
		}
	};
}
