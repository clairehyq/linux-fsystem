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
#include "SimpleFileSystem.h"

int main(int argc, char** argv)
{
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
	TEST_CLASS(imageFile)
	{

		TEST_METHOD(contstructor) // checks that the file is initialized with proper name and size, expects size to be 0 and the name to match the input to the constructor
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			Assert_AreEqual(t.getName(), fileName);
			Assert_AreEqual(t.getSize(), fileSize);
		}
		TEST_METHOD(writeValid) // tests write with a valid vector input, expects write to return success, and the size of the contents to be equal to that of the input vector -1 (for the last index that is removed
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
			Assert_AreEqual(t.write(v), 0);
			Assert_AreEqual(t.getSize(), static_cast<unsigned int>(v.size() - 1));
		}
		TEST_METHOD(writeSizeMismatch) // tests write with a size mismatch in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '4' };
			Assert_AreNotEqual(t.write(v), 0); // non-zero error returned
			Assert_AreEqual(t.getSize(), fileSize); // contents not added
		}
		TEST_METHOD(writeInvalidPixel) // tests write with an invalid pixel in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
			Assert_AreNotEqual(t.write(v), 0);
			Assert_AreEqual(t.getSize(), fileSize); // contents not added
		}
		TEST_METHOD(appendInvalid) // tests that append returns a non-zero value (can't append to an image)
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
			Assert_AreNotEqual(t.append(v), 0); // can't append to image
		}
		TEST_METHOD(read) // tests that read prints out the contents that are written to the file
		{
			std::string fileName = "FileName.img";
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
			Assert_AreEqual(t.write(v), 0);
      // MODIFIED because read() no longer writes to cout
      /*
			 * // REDIRECT STD STREAM
			 * streambuf* backup;
			 * backup = cout.rdbuf();
			 * stringstream ss;
			 * cout.rdbuf(ss.rdbuf());
			 * t.read();
			 * string outputShouldBe = "X";
			 * string word;
			 * int count = 0;
			 * while (ss >> word) {
			 *   Assert_AreEqual(word, outputShouldBe);
			 *   ++count;
			 * }
			 * // ASSIGN COUT BACK TO STDOUT
			 * cout.rdbuf(backup);
       */
      auto read = t.read();
      istringstream ss(string{read.begin(), read.end()});
			string word;
			int count = 0;
			while (ss >> word) {
        Assert_AreEqual(word, "X");
			  ++count;
			}
			Assert_AreEqual(count, 5);
		}
	};
	TEST_CLASS(simpleFileSystem)
	{
    // MODIFIED because createFile is removed
    /*
		 * TEST_METHOD(createFileValid) // creates a valid (unused) file and expects 0 (success) as a return value
		 * {
		 *   SimpleFileSystem sfs;
		 *   Assert_AreEqual(sfs.createFile("FileName.img"), 0);
		 *   Assert_AreEqual(sfs.createFile("FileName.txt"), 0);
		 * }
		 * TEST_METHOD(createFileAlreadyExists) // creates a file that has already been created, expects a non-zero return value
		 * {
		 *   SimpleFileSystem sfs;
		 *   Assert_AreEqual(sfs.createFile("FileName.img"), 0);
		 *   Assert_AreNotEqual(sfs.createFile("FileName.img"), 0); // accepts any non-zero value
		 * }
		 * TEST_METHOD(createUnknownExtension) // creates a file with an unknown extension, expects a non-zero return value
		 * {
		 *   SimpleFileSystem sfs;
		 *   Assert_AreNotEqual(sfs.createFile("FileName.bla"), 0);
		 * }
     */
		TEST_METHOD(addValid) // adds two different files to the system, expects success as return value both times
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			TextFile* txt = new TextFile("FileName.txt");
			Assert_AreEqual(sfs.addFile(img->getName(), img), 0);
			Assert_AreEqual(sfs.addFile(txt->getName(), txt), 0);
      // MODIFIED: added delete
      delete img; delete txt;
		}
		TEST_METHOD(addNullFile) // adds a nullptr to the filesystem, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			ImageFile* img = nullptr;
			Assert_AreNotEqual(sfs.addFile("FileName.img", img), 0);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(addFileAlreadyExists) // adds the same file twice, the first time should return success, the second time should return a non-zero value
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			Assert_AreEqual(sfs.addFile(img->getName(), img), 0);
			Assert_AreNotEqual(sfs.addFile(img->getName(), img), 0);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(deleteValid) // deletes a valid file (a file that exists and is not open), expects 0 as a return value
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			Assert_AreEqual(sfs.addFile(img->getName(), img), 0);
			Assert_AreEqual(sfs.deleteFile(img->getName()), 0);
		}
		TEST_METHOD(deleteFileDoesNotExist) // deletes a file that has not been added, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			Assert_AreNotEqual(sfs.deleteFile(img->getName()), 0);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(openValid) //  opens a valid file that exists and is not already open -- checked using add and create methods
		{
			SimpleFileSystem sfs;
			// check using add -- expect to see the same file returned
			AbstractFile* img = new ImageFile("FileName.img");
			Assert_AreEqual(sfs.addFile(img->getName(), img), 0);
			AbstractFile* res1 = sfs.openFile(img->getName());
			bool sameAddress = &(*img) == &(*res1);
			Assert_IsTrue(sameAddress);

			// check using create -- a quick check to see that create adds successfully and open finds the file by returning a pointer that  is not null
    // MODIFIED because createFile is removed
      /*
			 * Assert_AreEqual(sfs.createFile("FileName.txt"), 0);
			 * AbstractFile* res2 = sfs.openFile("FileName.txt");
			 * bool nullCheck = res2 == nullptr;
			 * Assert_IsFalse(nullCheck);
       */
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(openFileNotAdded) // opens a file that has not been added, expects a null pointer
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			AbstractFile* res1 = sfs.openFile(img->getName());
			bool isNull = res1 == nullptr;
			Assert_IsTrue(isNull);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(openAlreadyOpenedFile) // opens a file twice, the first time should return the same file, the second time should return nullptr
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			Assert_AreEqual(sfs.addFile(img->getName(), img), 0);
			AbstractFile* firstOpen = sfs.openFile(img->getName());
			bool sameAddress = &(*img) == &(*firstOpen);
			Assert_IsTrue(sameAddress);
			AbstractFile* secondOpen = sfs.openFile(img->getName());
			bool isNull = secondOpen == nullptr;
			Assert_IsTrue(isNull);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(closeValid) // closes a file that has been added and opened, expect success
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			sfs.addFile(img->getName(), img);
			sfs.openFile(img->getName());
			int res1 = sfs.closeFile(img);
			Assert_AreEqual(res1, 0);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(closeNotOpen) // closes a file that has been added but not opened, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			Assert_AreEqual(sfs.addFile(img->getName(), img), 0);
			Assert_AreNotEqual(sfs.closeFile(img), 0);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(closeNotAdded) // closes a file that has not been added or opened, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			Assert_AreNotEqual(sfs.closeFile(img), 0);
      // MODIFIED: added delete
      delete img;
		}
	};

  print_stats();
  return 0;
}
