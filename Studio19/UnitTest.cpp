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
#include <algorithm>

// lab5
#include "TextFile.h"
#include "ImageFile.h"
#include "SimpleFileSystem.h"
#include "SimpleFileFactory.h"
#include "MetadataDisplayVisitor.h"
#include "BasicDisplayVisitor.h"

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
			Assert_AreEqual(t.write(v), 0);
			std::vector<char> contents = t.read();
			Assert_AreEqual(t.getSize(), v.size());
			Assert_AreEqual(contents.size(), v.size());
			for (size_t i = 0; i < contents.size(); ++i) {
				Assert_AreEqual(v[i], contents[i]);
			}
		}
		TEST_METHOD(readWithAppend) // tests that read also works with appending to a file
		{
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert_AreEqual(t.write(v), 0);
			Assert_AreEqual(t.append(v), 0);
			std::vector<char> newExpectedV = { 'h', 'i',  'h', 'i' };
			std::vector<char> contents = t.read();
			Assert_AreEqual(t.getSize(), static_cast<unsigned int>(newExpectedV.size()));
			Assert_AreEqual(contents.size(), newExpectedV.size());
			for (size_t i = 0; i < contents.size(); ++i) {
				Assert_AreEqual(newExpectedV[i], contents[i]);
			}

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
		TEST_METHOD(read) // tests that read returns the contents that are written to the file
		{
			std::string fileName = "FileName.img";
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
			Assert_AreEqual(t.write(v), 0);
			std::vector<char> contents = t.read();
			Assert_AreEqual(contents.size(), v.size() - 1);
			for (size_t i = 0; i < contents.size(); ++i) {
				Assert_AreEqual(contents[i], v[i]);
			}
		}
	};
	TEST_CLASS(simpleFileSystem)
	{

		TEST_METHOD(addValid) // adds two different files to the system, expects success as return value both times
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			AbstractFile* txt = sff.createFile("FileName.txt");
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
		}
		TEST_METHOD(addFileAlreadyExists) // adds the same file twice, the first time should return success, the second time should return a non-zero value
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert_AreEqual(sfs.addFile(img->getName(), img), 0);
			Assert_AreNotEqual(sfs.addFile(img->getName(), img), 0);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(deleteValid) // deletes a valid file (a file that exists and is not open), expects 0 as a return value
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert_AreEqual(sfs.addFile(img->getName(), img), 0);
			Assert_AreEqual(sfs.deleteFile(img->getName()), 0);
		}
		TEST_METHOD(deleteFileDoesNotExist) // deletes a file that has not been added, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert_AreNotEqual(sfs.deleteFile(img->getName()), 0);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(openValid) //  opens a valid file that exists and is not already open, expect to see the same file returned
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert_AreEqual(sfs.addFile(img->getName(), img), 0);
			AbstractFile* res1 = sfs.openFile(img->getName());
			bool sameAddress = &(*img) == &(*res1);
			Assert_IsTrue(sameAddress);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(openFileNotAdded) // opens a file that has not been added, expects a null pointer
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			AbstractFile* res1 = sfs.openFile(img->getName());
			bool isNull = res1 == nullptr;
			Assert_IsTrue(isNull);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(openAlreadyOpenedFile) // opens a file twice, the first time should return the same file, the second time should return nullptr
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
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
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
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
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert_AreEqual(sfs.addFile(img->getName(), img), 0);
			Assert_AreNotEqual(sfs.closeFile(img), 0);
      // MODIFIED: added delete
      delete img;
		}
		TEST_METHOD(closeNotAdded) // closes a file that has not been added or opened, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert_AreNotEqual(sfs.closeFile(img), 0);
      // MODIFIED: added delete
      delete img;
		}
	};
	TEST_CLASS(simpleFileFactory) {
    TEST_METHOD(createFileValid) // creates two files by calling create on the file factory, the calls should return the new file objects that are both not null
    {
      SimpleFileFactory sff;
      AbstractFile* res1 = sff.createFile("FileName.img");
      bool isNull1 = res1 == nullptr;
      Assert_IsFalse(isNull1);
      AbstractFile* res2 = sff.createFile("FileName.txt");
      bool isNull2 = res2 == nullptr;
      Assert_IsFalse(isNull2);
      // MODIFIED: added delete
      delete res1; delete res2;
    }
    TEST_METHOD(createUnknownExtension) // when a bad extension is passed, the factory should pass back a nullptr
    {
      SimpleFileFactory sfs;
      AbstractFile* res1 = sfs.createFile("FileName.bla");
      bool isNull = res1 == nullptr;
      Assert_IsTrue(isNull);
    }
  };
  TEST_CLASS(basicDisplayVisitor) {
    TEST_METHOD(visitTextFile) { // tests output of basic display visitor for a text file, expects the contents of the file
      std::string fileName = "FileName.txt";
      TextFile t(fileName);
      std::vector<char> v = { 'h', 'i' };
      int resWrite = t.write(v);
      // REDIRECT STD STREAM
      streambuf* backup;
      backup = cout.rdbuf();
      stringstream ss;
      cout.rdbuf(ss.rdbuf());
      AbstractFileVisitor* bdv = new BasicDisplayVisitor;
      t.accept(bdv);
      string wordShouldBe = "hi";
      string word;
      ss >> word;
      // ASSIGN COUT BACK TO STDOUT
      cout.rdbuf(backup);
      Assert_AreEqual(word, wordShouldBe);
      Assert_AreEqual(resWrite, 0);
      // MODIFIED: added delete
      delete bdv;
    }
    TEST_METHOD(visitImageFile) { // tests the output the basic display visitor for an image file, expects 5 Xs
      std::string fileName = "FileName.img";
      ImageFile t(fileName);
      std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
      Assert_AreEqual(t.write(v), 0);
      // REDIRECT STD STREAM
      streambuf* backup;
      backup = cout.rdbuf();
      stringstream ss;
      cout.rdbuf(ss.rdbuf());
      AbstractFileVisitor* bdv = new BasicDisplayVisitor;
      t.accept(bdv);
      string outputShouldBe = "X";
      string word;
      int count = 0;
      while (ss >> word) { // no skip ws -- wont skip white space! would have to extract one character at a time
        Assert_AreEqual(word, outputShouldBe);
        ++count;
      }
      // ASSIGN COUT BACK TO STDOUT
      cout.rdbuf(backup);
      Assert_AreEqual(count, 5);
      // MODIFIED: added delete
      delete bdv;
    }
	};
	TEST_CLASS(metadataDisplayVisitor) {
    TEST_METHOD(visitTextFile) { // tests the output of the metadata display visitor for a text file, expects the filename, type and size to be included in the print statement
      std::string fileName = "FileName.txt";
      TextFile t(fileName);
      std::vector<char> v = { 'h', 'i' };
      Assert_AreEqual(t.write(v), 0);
      // REDIRECT STD STREAM
      streambuf* backup;
      backup = cout.rdbuf();
      stringstream ss;
      cout.rdbuf(ss.rdbuf());
      AbstractFileVisitor* bdv = new MetadataDisplayVisitor;
      t.accept(bdv);
      string word;
      std::vector<string> printedWords;
      while (ss >> word) {
        printedWords.push_back(word);
      }
      std::vector<string>::iterator it1;
      std::vector<string>::iterator it2;
      std::vector<string>::iterator it3;
      it1 = std::find(printedWords.begin(), printedWords.end(), fileName);
      bool notEqual1 = it1 == printedWords.end();
      Assert_IsFalse(notEqual1);
      it2 = std::find(printedWords.begin(), printedWords.end(), to_string(t.getSize()));
      bool notEqual2 = it2 == printedWords.end();
      Assert_IsFalse(notEqual2);
      it3 = std::find(printedWords.begin(), printedWords.end(), "text");
      bool notEqual3 = it3 == printedWords.end();
      Assert_IsFalse(notEqual3);
      // ASSIGN COUT BACK TO STDOUT
      cout.rdbuf(backup);
      // MODIFIED: added delete
      delete bdv;
    }
    TEST_METHOD(visitImageFile) { // tests the output of the metadata display visitor for an image file, expects the filename, type and size to be included in the output
      std::string fileName = "FileName.img";
      ImageFile t(fileName);
      std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
      Assert_AreEqual(t.write(v), 0);
      // REDIRECT STD STREAM
      streambuf* backup;
      backup = cout.rdbuf();
      stringstream ss;
      cout.rdbuf(ss.rdbuf());
      AbstractFileVisitor* bdv = new MetadataDisplayVisitor;
      t.accept(bdv);
      string word;
      std::vector<string> printedWords;
      while (ss >> word) {
        printedWords.push_back(word);
      }
      std::vector<string>::iterator it1;
      std::vector<string>::iterator it2;
      std::vector<string>::iterator it3;
      it1 = std::find(printedWords.begin(), printedWords.end(), fileName);
      bool notEqual1 = it1 == printedWords.end();
      Assert_IsFalse(notEqual1);
      it2 = std::find(printedWords.begin(), printedWords.end(), to_string(t.getSize()));
      bool notEqual2 = it2 == printedWords.end();
      Assert_IsFalse(notEqual2);
      it3 = std::find(printedWords.begin(), printedWords.end(), "image");
      bool notEqual3 = it3 == printedWords.end();
      Assert_IsFalse(notEqual3);
      // ASSIGN COUT BACK TO STDOUT
      cout.rdbuf(backup);
      // MODIFIED: added delete
      delete bdv;
    }
	};
  print_stats();
  return 0;
}
