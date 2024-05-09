#include "pch.h"
#include "CppUnitTest.h"
#include"../Project18/Header.h"
#include<sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTests
{
	TEST_CLASS(TableTest)
	{
	public:
		
		TEST_METHOD(TestCreate)
		{
			Table ht(10);
			ht.create("key1", "biology");
			ht.create("key1", "informatics");
			ht.create("key2", "chemistry");
			ht.create("key3", "math");
		    Assert::AreEqual("biology", ht.read("key1").c_str());
		    Assert::AreEqual("chemistry", ht.read("key2").c_str());
		    Assert::AreEqual("math", ht.read("key3").c_str());
		}

		TEST_METHOD(TestUpdate)
		{
			Table ht(10);
			ht.create("key1", "physics");
			ht.create("key2", "algebra");
			ht.create("key3", "grammar");
			ht.update("key1", "radiophysics");
			ht.update("key2", "geometry");
			ht.update("key3", "literature");
			ht.update("key4", "grammar");
		    Assert::AreEqual("radiophysics", ht.read("key1").c_str());
		    Assert::AreEqual("geometry", ht.read("key2").c_str());
			Assert::AreEqual("literature", ht.read("key3").c_str());
			Assert::AreEqual("Key not found!", ht.read("key4").c_str());
		}

		TEST_METHOD(TestDelete)
		{
			Table ht(10);
			ht.create("key1", "literature");
			ht.create("key2", "geography");
			ht.create("key2", "grammar");
			ht.remove("key1");
			ht.remove("key2");
			ht.remove("key3");
		    Assert::AreEqual("Key not found!", ht.read("key1").c_str());
		    Assert::AreEqual("Key not found!", ht.read("key2").c_str());
			Assert::AreEqual("Key not found!", ht.read("key3").c_str());
		}

		TEST_METHOD(TestEmptyTable)
		{
			Table ht(10);
			Assert::AreEqual("Key not found!", ht.read("key1").c_str());
		}

		TEST_METHOD(TestFullTable)
		{
			Table ht(10);
			ht.create("key1", "a");
			ht.create("key2", "b");
			ht.create("key3", "c");
			ht.create("key4", "d");
			ht.create("key5", "e");
			ht.create("key6", "f");
			ht.create("key7", "g");
			ht.create("key8", "h");
			ht.create("key9", "i");
			ht.create("keyk", "j");
			ht.create("keyy", "k");
		    Assert::AreEqual("Key not found!", ht.read("keyy").c_str());
		}

		TEST_METHOD(TestDisplayTable) {
			Table ht(10);
			ht.create("key1", "biology");
			ht.create("key2", "maths");
			ht.create("key3", "physics");
			stringstream buffer;
			streambuf* oldOut = cout.rdbuf(buffer.rdbuf()); 
			ht.display();
			cout.rdbuf(oldOut);
			string expectedOutput = "Key\tData\nkey1\tbiology\nkey2\tmaths\nkey3\tphysics\n";
			Assert::AreEqual(expectedOutput, buffer.str());
		}
	};
}
