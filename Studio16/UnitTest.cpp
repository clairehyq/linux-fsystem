/*
 * Because the subsequent studios changed interfaces,
 * some tests have been disabled or modified.
 *   search for MODIFIED to locate disabled tests.
 */

// unit test framework
#include "unittest.h"

// standard lib
#include <sstream>
#include <vector>
#include <cstring>

// lab5
#include "TextFile.h"
#include "ImageFile.h"

int main(int argc, char** argv)
{
  if (argc == 2 && !strcmp(argv[1], "on")) verbose = 1;

	TEST_CLASS(textFile)
	{
		TEST_METHOD(contstructor)  // checks that the file is initialized with proper name and size, expects size to be 0 and the name to match the input to the constructor
		{
			std::string fileName = "FileName.txt";
			unsigned int fileSize = 0;
			TextFile t(fileName);
			Assert_AreEqual(t.getName(), fileName);
			Assert_AreEqual(t.getSize(), fileSize);
		}
		TEST_METHOD(write) // tests write, expects that the function returns success and that the size of the file is updated correctly
		{
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert_AreEqual(t.write(v), 0);
			Assert_AreEqual(t.getSize(), static_cast<unsigned int>(v.size()));

		}
		TEST_METHOD(append) // tests append, expects the write and append functions to return 0 and the size of the file to update correctly
		{
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert_AreEqual(t.write(v), 0);
			unsigned int fileSize = t.getSize();
			Assert_AreEqual(t.append(v), 0);
			Assert_AreEqual(t.getSize(), static_cast<unsigned int>(fileSize + v.size()));

		}
		TEST_METHOD(read) // tests that the read function outputs the contents of the file
		{
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			int resWrite = t.write(v);
      // MODIFIED because read() no longer writes to cout
      /*
			 * // REDIRECT STD STREAM
			 * streambuf* backup;
			 * backup = cout.rdbuf();
			 * stringstream ss;
			 * cout.rdbuf(ss.rdbuf());
			 * t.read();
			 * string word;
			 * ss >> word;
			 * // ASSIGN COUT BACK TO STDOUT
			 * cout.rdbuf(backup);
       */
      auto read = t.read();
      string word{read.begin(), read.end()};
      string wordShouldBe = "hi";
			Assert_AreEqual(word, wordShouldBe);
			Assert_AreEqual(resWrite, 0);
		}
		TEST_METHOD(readWithAppend) // tests that read also works with appending to a file
		{
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert_AreEqual(t.write(v), 0);
			unsigned int fileSize = t.getSize();
			Assert_AreEqual(t.append(v), 0);
			Assert_AreEqual(t.getSize(), static_cast<unsigned int>(fileSize + v.size()));
      // MODIFIED because read() no longer writes to cout
      /*
			 * // REDIRECT STD STREAM
			 * streambuf* backup;
			 * backup = cout.rdbuf();
			 * stringstream ss;
			 * cout.rdbuf(ss.rdbuf());
			 * t.read();
			 * string word;
			 * ss >> word;
			 * // ASSIGN COUT BACK TO STDOUT
			 * cout.rdbuf(backup);
       */
      auto read = t.read();
      string word{read.begin(), read.end()};
      string wordShouldBe = "hihi";
			Assert_AreEqual(word, wordShouldBe);
		}
	};

  print_stats();
  return 0;
}
