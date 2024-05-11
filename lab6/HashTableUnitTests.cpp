#include "pch.h"
#include "CppUnitTest.h"
#include"../HashTable/Header.h"
#include<sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTests
{
	TEST_CLASS(TableTest)
	{
	public:

		TEST_METHOD(TestCreate)
		{
			Table table(10);
			table.create("key1", "biology");
			table.create("key1", "informatics");
			table.create("key2", "chemistry");
			table.create("key3", "math");
			Assert::AreEqual("biology", table.read("key1").c_str());
			Assert::AreEqual("chemistry", table.read("key2").c_str());
			Assert::AreEqual("math", table.read("key3").c_str());
		}

		TEST_METHOD(TestUpdate)
		{
			Table table(10);
			table.create("key1", "physics");
			table.create("key2", "algebra");
			table.create("key3", "grammar");
			table.update("key1", "radiophysics");
			table.update("key2", "geometry");
			table.update("key3", "literature");
			table.update("key4", "grammar");
			Assert::AreEqual("radiophysics", table.read("key1").c_str());
			Assert::AreEqual("geometry", table.read("key2").c_str());
			Assert::AreEqual("literature", table.read("key3").c_str());
			Assert::AreEqual("Key not found!", table.read("key4").c_str());
		}

		TEST_METHOD(TestDelete)
		{
			Table table(10);
			table.create("key1", "literature");
			table.create("key2", "geography");
			table.create("key2", "grammar");
			table.remove("key1");
			table.remove("key2");
			table.remove("key3");
			Assert::AreEqual("Key not found!", table.read("key1").c_str());
			Assert::AreEqual("Key not found!", table.read("key2").c_str());
			Assert::AreEqual("Key not found!", table.read("key3").c_str());
		}

		TEST_METHOD(TestEmptyTable)
		{
			Table table(10);
			Assert::AreEqual("Key not found!", table.read("key1").c_str());
		}

		TEST_METHOD(TestFullTable)
		{
			Table table(10);
			table.create("key1", "a");
			table.create("key2", "b");
			table.create("key3", "c");
			table.create("key4", "d");
			table.create("key5", "e");
			table.create("key6", "f");
			table.create("key7", "g");
			table.create("key8", "h");
			table.create("key9", "i");
			table.create("keyk", "j");
			table.create("keyy", "k");
			Assert::AreEqual("Key not found!", table.read("keyy").c_str());
		}

		TEST_METHOD(TestDisplayTable) {
			Table table(10);
			table.create("key1", "biology");
			table.create("key2", "maths");
			table.create("key3", "physics");
			stringstream buffer;
			streambuf* oldOut = cout.rdbuf(buffer.rdbuf());
			table.display();
			cout.rdbuf(oldOut);
			string expectedOutput = "Key\tData\nkey1\tbiology\nkey2\tmaths\nkey3\tphysics\n";
			Assert::AreEqual(expectedOutput, buffer.str());
		}
	};
}
