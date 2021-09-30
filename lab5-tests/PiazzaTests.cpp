/*
 * all tests on piazza with our unittest framework
 */

// unit test framework
#include "unittest.h"

// standard lib
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>

// lab5
#include "CommandPrompt.h"
#include "ErrorCodes.h"
#include "SimpleFileSystem.h"
#include "SimpleFileFactory.h"
#include "AbstractFile.h"
#include "PasswordProxy.h"
#include "MacroCommand.h"
#include "TextFile.h"
#include "ImageFile.h"
#include "RenameParsingStrategy.h"

#include "TouchCommand.h"
#include "RemoveCommand.h"
#include "CatCommand.h"
#include "LSCommand.h"
#include "CopyCommand.h"
#include "RenameCommand.h"
#include "DisplayCommand.h"
#include "GrepCommand.h"
#include "util.h"

#define CAT_TEST
#define COPY_TEST
#define DS_TEST
#define LS_TEST
#define RM_TEST
#define RN_TEST
#define TOUCH_TEST

int main(int argc, char** argv)
{
  if (argc == 2 && !strcmp(argv[1], "on")) verbose = 1;

#ifdef CAT_TEST
  TEST_CLASS(catCommand) {
    TEST_METHOD(executeTextFileNoAppendSaving) { // test executing cat with no append option and saving input to a text file
      // SET UP FILE SYSTEM
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf()); 
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.txt";
      AbstractFile* file = new TextFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      // INITIALIZE FILE CONTENTS
      vector<char> origContents = { 'f','o','o' };
      string origContentsStr(origContents.begin(), origContents.end());
      Assert_AreEqual(file->write(origContents), 0);
      // REDIRECT CIN STREAM
      static streambuf* backup_in;
      backup_in = cin.rdbuf();
      static stringstream ss_in;
      cin.rdbuf(ss_in.rdbuf());
      // MIMIC USER INPUT 
      string userInput = "hello world";
      string saveOption = "\n:wq\n";
      ss_in << userInput + saveOption;
      // CREATE AND EXECUTE COMMAND
      CatCommand* cc = new CatCommand(sfs);
      string executeInput = filename;
      Assert_AreEqual(cc->execute(executeInput), 0);
      // EXPECTATION -- CONTENTS MATCH
      vector<char> contents = file->read();
      string contentsStr(contents.begin(), contents.end());
      Assert_AreEqual(userInput, contentsStr);
      // ASSIGN CIN BACK TO STDIN
      cin.rdbuf(backup_in);
    }
    TEST_METHOD(executeTextFileNoAppendSavingMultipleLines) { // test executing cat with no append option and saving input with multiple lines to a text file
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.txt";
      AbstractFile* file = new TextFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      // INITIALIZE FILE CONTENTS
      vector<char> origContents = { 'f','o','o' };
      string origContentsStr(origContents.begin(), origContents.end());
      Assert_AreEqual(file->write(origContents), 0);
      // REDIRECT CIN STREAM
      static streambuf* backup_in;
      backup_in = cin.rdbuf();
      static stringstream ss_in;
      cin.rdbuf(ss_in.rdbuf());
      // MIMIC USER INPUT 
      string userInput = "hello\nworld\nmultiple\nlines";
      string saveOption = "\n:wq\n";
      ss_in << userInput + saveOption;
      // CREATE AND EXECUTE COMMAND
      CatCommand* cc = new CatCommand(sfs);
      string executeInput = filename;
      Assert_AreEqual(cc->execute(executeInput), 0);
      // EXPECTATION -- CONTENTS MATCH
      vector<char> contents = file->read();
      string contentsStr(contents.begin(), contents.end());
      Assert_AreEqual(userInput, contentsStr);
      // ASSIGN CIN BACK TO STDIN
      cin.rdbuf(backup_in);
    }
    TEST_METHOD(executeTextFileNoAppendNoSaving) { // test executing cat with no append option and without saving input to a text file
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.txt";
      AbstractFile* file = new TextFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      // INITIALIZE FILE CONTENTS
      vector<char> origContents = { 'f','o','o' };
      string origContentsStr(origContents.begin(), origContents.end());
      Assert_AreEqual(file->write(origContents), 0);
      // REDIRECT CIN STREAM
      static streambuf* backup_in;
      backup_in = cin.rdbuf();
      static stringstream ss_in;
      cin.rdbuf(ss_in.rdbuf());
      // MIMIC USER INPUT 
      string userInput = "hello world";
      string saveOption = "\n:q\n";
      ss_in << userInput + saveOption;
      // CREATE AND EXECUTE COMMAND
      CatCommand* cc = new CatCommand(sfs);
      string executeInput = filename;
      Assert_AreEqual(cc->execute(executeInput), 0);
      // EXPECTATION -- CONTENTS UNTOUCHED
      vector<char> contents = file->read();
      string contentsStr(contents.begin(), contents.end());
      Assert_AreEqual(origContentsStr, contentsStr);
      // ASSIGN CIN BACK TO STDIN
      cin.rdbuf(backup_in);
    }
    TEST_METHOD(executeTextFileAppendSaving) { // test executing cat with append option and saving input to a text file
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.txt";
      AbstractFile* file = new TextFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      // INITIALIZE FILE CONTENTS
      vector<char> origContents = { 'f','o','o' };
      string origContentsStr(origContents.begin(), origContents.end());
      Assert_AreEqual(file->write(origContents), 0);
      // REDIRECT COUT STREAM
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // REDIRECT CIN STREAM
      static streambuf* backup_in;
      backup_in = cin.rdbuf();
      static stringstream ss_in;
      cin.rdbuf(ss_in.rdbuf());
      // MIMIC USER INPUT 
      string userInput = "hello world";
      string saveOption = "\n:wq\n";
      ss_in << userInput + saveOption;
      // CREATE AND EXECUTE COMMAND
      CatCommand* cc = new CatCommand(sfs);
      string executeInput = filename + " -a";
      Assert_AreEqual(cc->execute(executeInput), 0);
      // EXPECTATION -- CONTENTS PRINTED PRINTED
      string word;
      std::vector<string> printedWords;
      while (ss_out >> word) {
        printedWords.push_back(word);
      }
      std::vector<string>::iterator it1;
      it1 = std::find(printedWords.begin(), printedWords.end(), origContentsStr);
      bool notEqual1 = it1 == printedWords.end();
      Assert_IsFalse(notEqual1);
      // EXPECTATION -- CONTENTS CORRECTLY UPDATED
      vector<char> contents = file->read();
      string contentsStr(contents.begin(), contents.end());
      Assert_AreEqual(origContentsStr + userInput, contentsStr);
      // ASSIGN COUT BACK TO STDOUT
      cout.rdbuf(backup_out);
      // ASSIGN CIN BACK TO STDIN
      cin.rdbuf(backup_in);
    }
    TEST_METHOD(executeTextFileAppendNoSaving) { // test executing cat with append option and does not save input, no changes should be made to the text file
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.txt";
      AbstractFile* file = new TextFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      // INITIALIZE FILE CONTENTS
      vector<char> origContents = { 'f','o','o' };
      string origContentsStr(origContents.begin(), origContents.end());
      Assert_AreEqual(file->write(origContents), 0);
      // REDIRECT COUT STREAM
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // REDIRECT CIN STREAM
      static streambuf* backup_in;
      backup_in = cin.rdbuf();
      static stringstream ss_in;
      cin.rdbuf(ss_in.rdbuf());
      // MIMIC USER INPUT 
      string userInput = "hello world";
      string saveOption = "\n:q\n";
      ss_in << userInput + saveOption;
      // CREATE AND EXECUTE COMMAND
      CatCommand* cc = new CatCommand(sfs);
      string executeInput = filename + " -a";
      Assert_AreEqual(cc->execute(executeInput), 0);
      // EXPECTATION -- CONTENTS PRINTED PRINTED
      string word;
      std::vector<string> printedWords;
      while (ss_out >> word) {
        printedWords.push_back(word);
      }
      std::vector<string>::iterator it1;
      it1 = std::find(printedWords.begin(), printedWords.end(), origContentsStr);
      bool notEqual1 = it1 == printedWords.end();
      Assert_IsFalse(notEqual1);
      // EXPECTATION -- CONTENTS CORRECTLY UPDATED
      vector<char> contents = file->read();
      string contentsStr(contents.begin(), contents.end());
      Assert_AreEqual(origContentsStr, contentsStr);
      // ASSIGN COUT BACK TO STDOUT
      cout.rdbuf(backup_out);
      // ASSIGN CIN BACK TO STDIN
      cin.rdbuf(backup_in);
    }
    TEST_METHOD(executeImageFileNoAppendSavingGoodInput) { // test executing cat with no append option and saving valid input to an image file
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.img";
      AbstractFile* file = new ImageFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      // REDIRECT CIN STREAM
      static streambuf* backup_in;
      backup_in = cin.rdbuf();
      static stringstream ss_in;
      cin.rdbuf(ss_in.rdbuf());
      // MIMIC USER INPUT 
      string userInput = "X X X X X3";
      string userInputWithoutLength = "X X X X X";
      string saveOption = "\n:wq\n";
      ss_in << userInput + saveOption;
      // CREATE AND EXECUTE COMMAND
      CatCommand* cc = new CatCommand(sfs);
      string executeInput = filename;
      Assert_AreEqual(cc->execute(executeInput), 0);
      // EXPECTATION -- CONTENTS MATCH
      vector<char> contents = file->read();
      string contentsStr(contents.begin(), contents.end());
      Assert_AreEqual(userInputWithoutLength, contentsStr);
      // ASSIGN CIN BACK TO STDIN
      cin.rdbuf(backup_in);
    }
    TEST_METHOD(executeImageFileNoAppendSavingBadInput) { // test executing cat with no append option and saving invalid input to an image file, content should be unchanged
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.img";
      AbstractFile* file = new ImageFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      // REDIRECT CIN STREAM
      static streambuf* backup_in;
      backup_in = cin.rdbuf();
      static stringstream ss_in;
      cin.rdbuf(ss_in.rdbuf());
      // MIMIC USER INPUT 
      string userInput = "X X X X X4";
      string userInputWithoutLength = "X X X X X";
      string saveOption = "\n:wq\n";
      ss_in << userInput + saveOption;
      // CREATE AND EXECUTE COMMAND
      CatCommand* cc = new CatCommand(sfs);
      string executeInput = filename;
      cc->execute(executeInput);
      // EXPECTATION -- CONTENTS UNCHANGED
      vector<char> contents = file->read();
      Assert_AreEqual(contents.size(), static_cast<size_t>(0));
      // ASSIGN CIN BACK TO STDIN
      cin.rdbuf(backup_in);
    }
    TEST_METHOD(executeImageFileNoAppendNoSavingGoodInput) { // test executing cat with no append option and not saving valid input to an image file, contents unchanged
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.img";
      AbstractFile* file = new ImageFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      // REDIRECT CIN STREAM
      static streambuf* backup_in;
      backup_in = cin.rdbuf();
      static stringstream ss_in;
      cin.rdbuf(ss_in.rdbuf());
      // MIMIC USER INPUT 
      string userInput = "X X X X X3";
      string userInputWithoutLength = "X X X X X";
      string saveOption = "\n:q\n";
      ss_in << userInput + saveOption;
      // CREATE AND EXECUTE COMMAND
      CatCommand* cc = new CatCommand(sfs);
      string executeInput = filename;
      Assert_AreEqual(cc->execute(executeInput), 0);
      // EXPECTATION -- CONTENTS UNCHANGED
      vector<char> contents = file->read();
      Assert_AreEqual(contents.size(), static_cast<size_t>(0));
      // ASSIGN CIN BACK TO STDIN
      cin.rdbuf(backup_in);
    }
    TEST_METHOD(executeImageFileAppendSavingGoodInput) { // test executing cat with append option and saving valid input to an image file, expect an error returned and contents to be unchanged
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.img";
      AbstractFile* file = new ImageFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      // REDIRECT CIN STREAM
      static streambuf* backup_in;
      backup_in = cin.rdbuf();
      static stringstream ss_in;
      cin.rdbuf(ss_in.rdbuf());
      // MIMIC USER INPUT 
      string userInput = "X X X X X3";
      string userInputWithoutLength = "X X X X X";
      string saveOption = "\n:wq\n";
      ss_in << userInput + saveOption;
      // CREATE AND EXECUTE COMMAND
      CatCommand* cc = new CatCommand(sfs);
      string executeInput = filename + " -a";
      Assert_AreNotEqual(cc->execute(executeInput), 0);
      // EXPECTATION -- CONTENTS UNCHANGED
      vector<char> contents = file->read();
      Assert_AreEqual(contents.size(), static_cast<size_t>(0));
      // ASSIGN CIN BACK TO STDIN
      cin.rdbuf(backup_in);
    }
    TEST_METHOD(executeFileDoesNotExist) { // test executing cat with append option and saving valid input to an image file that doesnt exist, expect an error returned 
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // REDIRECT CIN STREAM
      static streambuf* backup_in;
      backup_in = cin.rdbuf();
      static stringstream ss_in;
      cin.rdbuf(ss_in.rdbuf());
      // MIMIC USER INPUT 
      string userInput = "hello world";
      string saveOption = "\n:wq\n";
      ss_in << userInput + saveOption;
      // CREATE AND EXECUTE COMMAND
      CatCommand* cc = new CatCommand(sfs);
      string executeInput = "file.txt";
      Assert_AreNotEqual(cc->execute(executeInput), 0);
      // ASSIGN CIN BACK TO STDIN
      cin.rdbuf(backup_in);
    }
  };  
#endif
#ifdef COPY_TEST
  TEST_CLASS(Copy) {
    TEST_METHOD(validcopy) {
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        
        // REDIRECT COUT STREAM
        static streambuf* backup_out;
        backup_out = cout.rdbuf();
        static stringstream ss_out;
        cout.rdbuf(ss_out.rdbuf());
        
        string filename = "file.txt";
        Assert_AreEqual(sfs->addFile(filename, sff->createFile(filename)), 0);
        AbstractFile* f = sfs->openFile(filename);
        vector<char> original = { 'h','i' };
        f->write(original);
        sfs->closeFile(f);
        string copyname = "copy.txt";
        AbstractCommand* cp = new CopyCommand(sfs);
        Assert_AreEqual(cp->execute(filename + " copy"),0);
        f = sfs->openFile(filename);
        bool isNull = f == nullptr;
        Assert_IsFalse(isNull);
        AbstractFile* f_copy = sfs->openFile(copyname);
        isNull = f_copy == nullptr;
        Assert_IsFalse(isNull);
        Assert_AreEqual(f_copy->getName(), copyname);
        bool sameFile = f_copy == f;
        Assert_IsFalse(sameFile);
        vector<char> copy_contents = f_copy->read();
        Assert_AreEqual(copy_contents.size(), original.size());
        Assert_AreEqual((size_t)f->getSize(), original.size());
        for (size_t i = 0; i < original.size(); ++i) {
          Assert_AreEqual(copy_contents[i], original[i]);
        }
      TextFile* t_p = dynamic_cast<TextFile*>(f_copy);
        isNull = t_p == nullptr;
        Assert_IsFalse(isNull);
    }
    TEST_METHOD(invalidcopy) {
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        
        // REDIRECT COUT STREAM
        static streambuf* backup_out;
        backup_out = cout.rdbuf();
        static stringstream ss_out;
        cout.rdbuf(ss_out.rdbuf());
        
        string filename = "file.txt";
        Assert_AreEqual(sfs->addFile(filename, sff->createFile(filename)), 0);
        AbstractFile* f = sfs->openFile(filename);
        vector<char> original = { 'h','i' };
        f->write(original);
        sfs->closeFile(f);
        AbstractCommand* cp = new CopyCommand(sfs);
        Assert_AreNotEqual(cp->execute(filename + " file"), 0);
        Assert_AreNotEqual(cp->execute("madeupname.txt othername"), 0);
        // ensure the original file wasn't changed and is closed
        f = sfs->openFile(filename);
        bool isNull = f == nullptr;
        Assert_IsFalse(isNull);
        vector<char> after_invalid = f->read();
        Assert_AreEqual(after_invalid.size(), original.size());
    }
    TEST_METHOD(copypasswordprotected) {
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        
        // REDIRECT COUT STREAM
        static streambuf* backup_out;
        backup_out = cout.rdbuf();
        static stringstream ss_out;
        cout.rdbuf(ss_out.rdbuf());
        
        string filename = "file.txt";
        AbstractFile* realfile = sff->createFile(filename);
        vector<char> original = { 'h','i' };
        realfile->write(original);
        string pw = "easypassword";
        AbstractFile* proxy_toreal = new PasswordProxy(realfile, pw);
        Assert_AreEqual(sfs->addFile(proxy_toreal->getName(), proxy_toreal), 0);
        AbstractCommand* cp = new CopyCommand(sfs);
        string copyname = "copy.txt";
        Assert_AreEqual(cp->execute(filename + " copy"), 0);
        AbstractFile* proxy_copy = sfs->openFile(copyname);
        bool isNull = proxy_copy == nullptr;
        Assert_IsFalse(isNull);
        PasswordProxy* proxy_tocopy = dynamic_cast<PasswordProxy*>(proxy_copy);
        isNull = proxy_tocopy == nullptr;
        Assert_IsFalse(isNull);
        bool sameProxy = proxy_tocopy == proxy_toreal;
        Assert_IsFalse(sameProxy);
        // REDIRECT CIN STREAM
        static streambuf* backup_in;
        backup_in = cin.rdbuf();
        static stringstream ss_in;
        cin.rdbuf(ss_in.rdbuf());
        // MIMIC USER INPUT
        ss_in << pw << '\n';
        vector<char> newdata = { 'h','e','l','l','o' };
        Assert_AreEqual(proxy_tocopy->write(newdata), 0);
        auto v = realfile->read();
        Assert_AreEqual(v.size(), original.size());
        for (size_t i = 0; i < v.size(); ++i) {
          Assert_AreEqual(v[i], original[i]);
        }
    }
  };
#endif
#ifdef DS_TEST
  TEST_CLASS(DSCommand) {
    TEST_METHOD(displaytext) {
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        string filename1 = "file.txt";
        Assert_AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
        AbstractFile* f = sfs->openFile(filename1);
        vector<char> v = { 'h', 'i','\n','h','e','l','l','o' };
        f->write(v);
        sfs->closeFile(f);
        // REDIRECT COUT STREAM
        static streambuf* backup_out;
        backup_out = cout.rdbuf();
        static stringstream ss_out;
        cout.rdbuf(ss_out.rdbuf());
        // execute ds
        AbstractCommand* ds = new DisplayCommand(sfs);
        Assert_AreEqual(ds->execute(filename1), 0);
        ss_out >> noskipws;
        char c;
        for (size_t i = 0; i < v.size(); ++i) {
          ss_out >> c;
            Assert_AreEqual(c, v[i]);
        }
      // ensure the file was closed
      f = sfs->openFile(filename1);
        bool isNull = f == nullptr;
        Assert_IsFalse(isNull);
    }
    TEST_METHOD(displaytextunformatted) {
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        string filename1 = "file.txt";
        Assert_AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
        AbstractFile* f = sfs->openFile(filename1);
        vector<char> v = { 'h', 'i','\n','h','e','l','l','o' };
        f->write(v);
        sfs->closeFile(f);
        // REDIRECT COUT STREAM
        static streambuf* backup_out;
        backup_out = cout.rdbuf();
        static stringstream ss_out;
        cout.rdbuf(ss_out.rdbuf());
        // execute ds
        AbstractCommand* ds = new DisplayCommand(sfs);
        Assert_AreEqual(ds->execute(filename1 + " -d"), 0);
        ss_out >> noskipws;
        char c;
        for (size_t i = 0; i < v.size(); ++i) {
          ss_out >> c;
            Assert_AreEqual(c, v[i]);
        }
      // ensure the file was closed
      f = sfs->openFile(filename1);
        bool isNull = f == nullptr;
        Assert_IsFalse(isNull);
    }
    TEST_METHOD(displayimageformatted) {
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        string filename1 = "file.img";
        Assert_AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
        AbstractFile* f = sfs->openFile(filename1);
        vector<char> v = { 'X',' ',' ','X',' ',' ','X', ' ',' ','3' };
        vector<char> expectedOutput = { 'X',' ',' ','\n','X',' ',' ','\n','X',' ',' ','\n' };
        f->write(v);
        sfs->closeFile(f);
        // REDIRECT COUT STREAM
        static streambuf* backup_out;
        backup_out = cout.rdbuf();
        static stringstream ss_out;
        cout.rdbuf(ss_out.rdbuf());
        // execute ds
        AbstractCommand* ds = new DisplayCommand(sfs);
        Assert_AreEqual(ds->execute(filename1), 0);
        ss_out >> noskipws;
        char c;
        for (size_t i = 0; i < expectedOutput.size(); ++i) {
          ss_out >> c;
            Assert_AreEqual(c, expectedOutput[i]);
        }
      // ensure the file was closed
      f = sfs->openFile(filename1);
        bool isNull = f == nullptr;
        Assert_IsFalse(isNull);
    }
    
      TEST_METHOD(displayimageunformatted) {
        AbstractFileSystem* sfs = new SimpleFileSystem();
          AbstractFileFactory* sff = new SimpleFileFactory();
          string filename1 = "file.img";
          Assert_AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
          AbstractFile* f = sfs->openFile(filename1);
          vector<char> v = { 'X',' ',' ','X',' ',' ','X', ' ',' ','3' };
          vector<char> expectedOutput = { 'X',' ',' ','X',' ',' ','X',' ',' ','\n' };
          f->write(v);
          sfs->closeFile(f);
          // REDIRECT COUT STREAM
          static streambuf* backup_out;
          backup_out = cout.rdbuf();
          static stringstream ss_out;
          cout.rdbuf(ss_out.rdbuf());
          // execute ds
          AbstractCommand* ds = new DisplayCommand(sfs);
          Assert_AreEqual(ds->execute(filename1 + " -d"), 0);
          ss_out >> noskipws;
          char c;
          for (size_t i = 0; i < expectedOutput.size(); ++i) {
            ss_out >> c;
              Assert_AreEqual(c, expectedOutput[i]);
          }
        // ensure the file was closed
        f = sfs->openFile(filename1);
          bool isNull = f == nullptr;
          Assert_IsFalse(isNull);
      }
    TEST_METHOD(displayinvalid) {
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        // REDIRECT COUT STREAM
        static streambuf* backup_out;
        backup_out = cout.rdbuf();
        static stringstream ss_out;
        cout.rdbuf(ss_out.rdbuf());
        string filename1 = "file.img";
        Assert_AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
        AbstractCommand* ds = new DisplayCommand(sfs);
        Assert_AreNotEqual(ds->execute("file.txt"), 0);
    }
  };
#endif
#ifdef LS_TEST
  TEST_CLASS(lSCommand) {
    TEST_METHOD(getAllFiles) { // confirms that execute, when passed a valid filename, will remove the given file from the filesystem -- removing the file again should fail, adding the file again should pass
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        // ADD FILES
        string filename1 = "file.txt";
        string filename2 = "file.img";
        Assert_AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
        Assert_AreEqual(sfs->addFile(filename2, sff->createFile(filename2)), 0);
        // CHECK FILES IN SYSTEM USING GETFILENAMES() FUCNTION
        set<string> files = sfs->getFileNames();
        Assert_AreEqual(files.size(), static_cast<size_t>(2));
        // EXPECTATION -- TEXT FILE EXISTS IN THE FILE SYSTEM
        std::set<std::string>::iterator it1 = files.find(filename1);
        bool found1 = it1 == files.end();
        Assert_IsFalse(found1);
        // EXPECTATION -- IMAGE FILE EXISTS IN THE FILE SYSTEM
        std::set<std::string>::iterator it2 = files.find(filename2);
        bool found2 = it2 == files.end();
        Assert_IsFalse(found2);
    }
    TEST_METHOD(nooption) {
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        // ADD FILES
        string filename1 = "file.txt";
        string filename2 = "file.img";
        string filename3 = "adifferentfile.txt";
        Assert_AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
        Assert_AreEqual(sfs->addFile(filename2, sff->createFile(filename2)), 0);
        Assert_AreEqual(sfs->addFile(filename3, sff->createFile(filename3)), 0);
        // REDIRECT COUT STREAM
        static streambuf* backup_out;
        backup_out = cout.rdbuf();
        static stringstream ss_out;
        cout.rdbuf(ss_out.rdbuf());
        // execute ls
        AbstractCommand* ls = new LSCommand(sfs);
        Assert_AreEqual(ls->execute(""),0);
        // check output
        string firstLine;
        string secondLine;
        // ensure 2 lines of output
        bool extractSuccessful = false;
        if (getline(ss_out, firstLine)) {
          extractSuccessful = true;
        }
      Assert_IsTrue(extractSuccessful);
        extractSuccessful = false;
        if (getline(ss_out, secondLine)) {
          extractSuccessful = true;
        }
      Assert_IsTrue(extractSuccessful);
        string firstFile;
        string secondFile;
        static stringstream iss(firstLine);
        iss >> firstFile;
        iss >> secondFile;
        string thirdFile;
        static stringstream iss2(secondLine);
        iss2 >> thirdFile;
        string expectedFirst = "adifferentfile.txt";
        string expectedSecond = "file.img";
        string expectedThird = "file.txt";
        Assert_AreEqual(firstFile, expectedFirst);
        Assert_AreEqual(secondFile, expectedSecond);
        Assert_AreEqual(thirdFile, expectedThird);
    }
    TEST_METHOD(metadata) {
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        // ADD FILES
        string filename1 = "file.txt";
        string filename2 = "file.img";
        string filename3 = "adifferentfile.txt";
        Assert_AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
        Assert_AreEqual(sfs->addFile(filename2, sff->createFile(filename2)), 0);
        Assert_AreEqual(sfs->addFile(filename3, sff->createFile(filename3)), 0);
        AbstractFile* f1 = sfs->openFile(filename1);
        AbstractFile* f2 = sfs->openFile(filename2);
        f1->write({ 'h','i' });
        int f1Size = f1->getSize();
        Assert_AreEqual(f1Size, 2);
        f2->write({ 'X',' ', ' ', 'X', '2' });
        int f2Size = f2->getSize();
        Assert_AreEqual(f2Size, 4);
        int f3Size = 0;
        sfs->closeFile(f1);
        sfs->closeFile(f2);
        // REDIRECT COUT STREAM
        static streambuf* backup_out;
        backup_out = cout.rdbuf();
        static stringstream ss_out;
        cout.rdbuf(ss_out.rdbuf());
        // execute ls
        AbstractCommand* ls = new LSCommand(sfs);
        Assert_AreEqual(ls->execute("-m"), 0);
        string line1;
        string line2;
        string line3;
        getline(ss_out, line1);
        getline(ss_out, line2);
        getline(ss_out, line3);
        static stringstream iss(line1);
        static stringstream iss2(line2);
        static stringstream iss3(line3);
        string f1Name;
        string f2Name;
        string f3Name;
        string f1Type;
        string f2Type;
        string f3Type;
        int sizeF1;
        int sizeF2;
        int sizeF3;
        iss >> f1Name >> f1Type >> sizeF1;
        iss2 >> f2Name >> f2Type >> sizeF2;
        iss3 >> f3Name >> f3Type >> sizeF3;
        Assert_AreEqual(f1Name, filename3);
        Assert_AreEqual(f2Name, filename2);
        Assert_AreEqual(f3Name, filename1);
        string txtType = "text";
        string imgType = "image";
        Assert_AreEqual(f1Type, txtType);
        Assert_AreEqual(f2Type, imgType);
        Assert_AreEqual(f3Type, txtType);
        Assert_AreEqual(sizeF1, f3Size);
        Assert_AreEqual(sizeF2, f2Size);
        Assert_AreEqual(sizeF3, f1Size);
        // did the files get closed?
        f1 = sfs->openFile(filename1);
        f2 = sfs->openFile(filename2);
        AbstractFile* f3 = sfs->openFile(filename3);
        bool allOpen = false;
        if (f1 != nullptr && f2 != nullptr && f3 != nullptr) {
          allOpen = true;
        }
      Assert_IsTrue(allOpen);
    }
  };  
#endif
#ifdef RM_TEST
  TEST_CLASS(removeCommand) {
    TEST_METHOD(execute) { // confirms that execute, when passed a valid filename, will remove the given file from the filesystem -- removing the file again should fail, adding the file again should pass
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        // ADD FILES
        string filename1 = "file.txt";
        string filename2 = "file.img";
        Assert_AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
        Assert_AreEqual(sfs->addFile(filename2, sff->createFile(filename2)), 0);
        // CREATE COMMAND
        RemoveCommand* rc = new RemoveCommand(sfs);
        // CALL EXECUTE ON REMOVE COMMAND
        Assert_AreEqual(rc->execute(filename2), 0);
        // EXPECTATION -- TEXT FILE EXISTS IN THE FILE SYSTEM
        AbstractFile* file1 = sfs->openFile(filename1);
        bool isNull1 = file1 == nullptr;
        Assert_IsFalse(isNull1);
        Assert_AreEqual(filename1, file1->getName());
        // EXPECTATION -- IMAGE FILE REMOVED IN THE FILE SYSTEM
        AbstractFile* file2 = sfs->openFile(filename2);
        bool isNull2 = file2 == nullptr;
        Assert_IsTrue(isNull2);
        // CLOSE TEXT FILE
        Assert_AreEqual(sfs->closeFile(file1), 0);
        // CHECK FILES IN SYSTEM USING GETFILENAMES() FUCNTION
        set<string> files = sfs->getFileNames();
        Assert_AreEqual(files.size(), static_cast<size_t>(1));
        // EXPECTATION -- TEXT FILE EXISTS IN THE FILE SYSTEM
        std::set<std::string>::iterator it1 = files.find(filename1);
        bool found1 = it1 == files.end();
        Assert_IsFalse(found1);
        // EXPECTATION -- IMAGE FILE REMOVED IN THE FILE SYSTEM
        std::set<std::string>::iterator it2 = files.find(filename2);
        bool found2 = it2 == files.end();
        Assert_IsTrue(found2);
        // RE-ADD FILE
        Assert_AreEqual(sfs->addFile(filename2, sff->createFile(filename2)), 0);
        set<string> files2 = sfs->getFileNames();
        Assert_AreEqual(files2.size(), static_cast<size_t>(2));
        // EXPECTATION -- IMAGE FILE EXISTS IN THE FILE SYSTEM - OPEN FILE CHEC AND GETFILENAMES CHECK
        std::set<std::string>::iterator it3 = files2.find(filename2);
        bool found3 = it3 == files2.end();
        Assert_IsFalse(found3);
        AbstractFile* file3 = sfs->openFile(filename2);
        bool isNull3 = file3 == nullptr;
        Assert_IsFalse(isNull3);
    }
    TEST_METHOD(executeFileOpen) { // confirms that execute, when passed a valid filename for a file that is open, execute will return an error and filesystem is untouched, so we expect to be able to close it
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        // REDIRECT COUT STREAM
        static streambuf* backup_out;
        backup_out = cout.rdbuf();
        static stringstream ss_out;
        cout.rdbuf(ss_out.rdbuf());
        // ADD FILE
        string filename1 = "file.txt";
        Assert_AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
        // OPEN FILE
        AbstractFile* file1 = sfs->openFile(filename1);
        bool isNull = file1 == nullptr;
        Assert_IsFalse(isNull);      
        Assert_AreEqual(filename1, file1->getName());
        // CREATE COMMAND
        RemoveCommand* rc = new RemoveCommand(sfs);
        // CALL EXECUTE ON REMOVE COMMAND
        Assert_AreNotEqual(rc->execute(filename1), 0);
        // EXPECTATION -- TEXT FILE EXISTS IN THE FILE SYSTEM -- SO WE CAN CLOSE IT
        // CLOSE FILE
        Assert_AreEqual(sfs->closeFile(file1),0);
    }
  };
#endif
#ifdef RN_TEST
  TEST_CLASS(renameCommand) {
    TEST_METHOD(renameParsingStrategy) { // checks parse function of RenameParsingStrategy correctly converts input string into a vector of strings representing instructions for copy and remove commands
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SETUP INPUT AND TEST OUTPUT
      RenameParsingStrategy* rps = new RenameParsingStrategy();
      vector<string> parsed = rps->parse("file.txt renamedFile");
      Assert_AreEqual(parsed.size(), static_cast<size_t>(2));
      string expectedCopyInstructions = "file.txt renamedFile";
      string expectedRemoveInstructions = "file.txt";
      Assert_AreEqual(parsed[0], expectedCopyInstructions);
      Assert_AreEqual(parsed[1], expectedRemoveInstructions);
    }
    TEST_METHOD(renameValid) {
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.txt";
      AbstractFile* file = new TextFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      // INITIALIZE FILE CONTENTS
      vector<char> v = { 'h','i' };
      Assert_AreEqual(file->write(v), 0);
      // CREATE MACRO COMMAND USING RENAME PARSING STRATEGY AND COPY/REMOVE COMMANDS
      MacroCommand* mc = new MacroCommand(sfs);
      RenameParsingStrategy* rps = new RenameParsingStrategy;
      AbstractCommand* cpc = new CopyCommand(sfs);
      AbstractCommand* rmc = new RemoveCommand(sfs);
      mc->setParseStrategy(rps);
      mc->addCommand(cpc);
      mc->addCommand(rmc);
      // EXECUTE RENAME COMMAND
      string newfilename = "newfilename";
      string userInput = filename + " " + newfilename;
      Assert_AreEqual(mc->execute(userInput), 0);
      // EXPECTATION -- ORIGINAL FILE IS REMOVED
      AbstractFile* originalFile = sfs->openFile(filename);
      bool isNull = originalFile == nullptr;
      Assert_IsTrue(isNull);
      // EXPECTATION -- FILE EXISTS UNDER NEW NAME AND CONTENTS ARE THE SAME
      AbstractFile* newFile = sfs->openFile(newfilename+".txt");
      bool isNull2 = newFile == nullptr;
      Assert_IsFalse(isNull2);
      vector<char> contents = newFile->read();
      Assert_AreEqual(v.size(), contents.size());
      Assert_AreEqual(v[0], contents[0]);
      Assert_AreEqual(v[1], contents[1]);
      // EXPECTATION -- ADDRESSES ARE DIFFERENT
      bool areEqual = &file == &newFile;
      Assert_IsFalse(areEqual);
      // EXPECTATION -- FILE TYPE MATCHES
      TextFile* textCheck = dynamic_cast<TextFile*>(newFile);
      bool isNotTextFile = textCheck == nullptr;
      Assert_IsFalse(isNotTextFile);
    }
    TEST_METHOD(renameInvalidFilename) {
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.txt";
      AbstractFile* file = new TextFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      // INITIALIZE FILE CONTENTS
      vector<char> v = { 'h','i' };
      Assert_AreEqual(file->write(v), 0);
      // CREATE MACRO COMMAND USING RENAME PARSING STRATEGY AND COPY/REMOVE COMMANDS
      MacroCommand* mc = new MacroCommand(sfs);
      RenameParsingStrategy* rps = new RenameParsingStrategy;
      AbstractCommand* cpc = new CopyCommand(sfs);
      AbstractCommand* rmc = new RemoveCommand(sfs);
      mc->setParseStrategy(rps);
      mc->addCommand(cpc);
      mc->addCommand(rmc);
      // EXECUTE RENAME COMMAND
      string invalidfilename = "wrongfilename.txt";
      string newfilename = "newfilename";
      string userInput = invalidfilename + " " + newfilename;
      Assert_AreNotEqual(mc->execute(userInput), 0);
      // EXPECTATION -- ORIGINAL FILE IS NOT REMOVED
      AbstractFile* originalFile = sfs->openFile(filename);
      bool isNull = originalFile == nullptr;
      Assert_IsFalse(isNull);
      // EXPECTATION -- FILE DOES NOT EXIST UNDER NEW NAME 
      AbstractFile* newFile = sfs->openFile(newfilename+".txt");
      bool isNull2 = newFile == nullptr;
      Assert_IsTrue(isNull2);;
    }
    TEST_METHOD(renameInvalidNewFilename) {
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.txt";
      string otherfilename = "otherfile";
      AbstractFile* file = new TextFile(filename);
      Assert_AreEqual(sfs->addFile(filename, file), 0);
      AbstractFile* otherfile = new TextFile(otherfilename +".txt");
      Assert_AreEqual(sfs->addFile(otherfilename + ".txt", otherfile), 0);
      // INITIALIZE FILE CONTENTS
      vector<char> v = { 'h','i' };
      Assert_AreEqual(file->write(v), 0);
      // CREATE MACRO COMMAND USING RENAME PARSING STRATEGY AND COPY/REMOVE COMMANDS
      MacroCommand* mc = new MacroCommand(sfs);
      RenameParsingStrategy* rps = new RenameParsingStrategy;
      AbstractCommand* cpc = new CopyCommand(sfs);
      AbstractCommand* rmc = new RemoveCommand(sfs);
      mc->setParseStrategy(rps);
      mc->addCommand(cpc);
      mc->addCommand(rmc);
      // EXECUTE RENAME COMMAND
      string userInput = filename + " " + otherfilename;
      Assert_AreNotEqual(mc->execute(userInput), 0);
      // EXPECTATION -- ORIGINAL FILE IS NOT REMOVED
      AbstractFile* originalFile = sfs->openFile(filename);
      bool isNull = originalFile == nullptr;
      Assert_IsFalse(isNull);
      // EXPECTATION -- OTHER FILE STILL EXISTS
      AbstractFile* newFile = sfs->openFile(otherfilename+".txt");
      bool isNull2 = newFile == nullptr;
      Assert_IsFalse(isNull2);;
    }
    TEST_METHOD(renameValidPasswordProtected) {
      // REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
      static streambuf* backup_out;
      backup_out = cout.rdbuf();
      static stringstream ss_out;
      cout.rdbuf(ss_out.rdbuf());
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
      AbstractFileFactory* sff = new SimpleFileFactory();
      // ADD FILES
      string filename = "file.txt";
      AbstractFile* file = new TextFile(filename);
      string password = "Adi23ifK";
      AbstractFile* proxy = new PasswordProxy(file, password);
      Assert_AreEqual(sfs->addFile(filename, proxy), 0);
      // INITIALIZE FILE CONTENTS -- WE WRITE DIRECTLY TO FILE IN THIS CASE (FUNCTIONALITY IS TEST OTHER PLACES)
      vector<char> v = { 'h','i' };
      Assert_AreEqual(file->write(v), 0);
      // CREATE MACRO COMMAND USING RENAME PARSING STRATEGY AND COPY/REMOVE COMMANDS
      MacroCommand* mc = new MacroCommand(sfs);
      RenameParsingStrategy* rps = new RenameParsingStrategy;
      AbstractCommand* cpc = new CopyCommand(sfs);
      AbstractCommand* rmc = new RemoveCommand(sfs);
      mc->setParseStrategy(rps);
      mc->addCommand(cpc);
      mc->addCommand(rmc);
      // REDIRECT CIN STREAM
      static streambuf* backup_in;
      backup_in = cin.rdbuf();
      static stringstream ss_in;
      cin.rdbuf(ss_in.rdbuf());
      // EXECUTE RENAME COMMAND
      string newfilename = "newfilename";
      string userInput = filename + " " + newfilename;
      Assert_AreEqual(mc->execute(userInput), 0);
      // EXPECTATION -- ORIGINAL FILE IS REMOVED
      AbstractFile* originalFile = sfs->openFile(filename);
      bool isNull = originalFile == nullptr;
      Assert_IsTrue(isNull);
      // EXPECTATION -- FILE EXISTS UNDER NEW NAME AND CONTENTS ARE THE SAME
      AbstractFile* newFile = sfs->openFile(newfilename+".txt");
      bool isNull2 = newFile == nullptr;
      Assert_IsFalse(isNull2);
      // SET UP USER PASSWORD INPUT AND READ AGAIN TO GET TRUE CONTENTS 
      ss_in << password + "\n";
      vector<char> contentswithpassword = newFile->read();
      Assert_AreEqual(v.size(), contentswithpassword.size());
      Assert_AreEqual(v[0], contentswithpassword[0]);
      Assert_AreEqual(v[1], contentswithpassword[1]);
      // SECOND READ CALL NOT GIVEN A PASSWORD -- SHOULD FAIL AND GET AN EMPTY VECTOR
      vector<char> contents = newFile->read();
      Assert_AreEqual(contents.size(), static_cast<size_t>(0));
      // EXPECTATION -- ADDRESSES ARE DIFFERENT
      bool areEqual = &file == &newFile;
      Assert_IsFalse(areEqual);
      // EXPECTATION -- FILE TYPE MATCHES
      PasswordProxy* proxyCheck = dynamic_cast<PasswordProxy*>(newFile);
      bool isNotPasswordProxy = proxyCheck == nullptr;
      Assert_IsFalse(isNotPasswordProxy);
    }
  };
#endif
#ifdef TOUCH_TEST
  TEST_CLASS(touchCommand) { 
    
    TEST_METHOD(execute) { // confirms that execute, when passed a valid filename, will create and add a file in the filesystem
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        // CREATE COMMAND
        TouchCommand* tc = new TouchCommand(sfs, sff);
        // CALL EXECUTE ON TOUCH COMMAND
        string filename = "file.txt";
        Assert_AreEqual(tc->execute(filename), 0);
        // EXPECTATION -- FILE EXISTS IN THE FILE SYSTEM
        AbstractFile* file = sfs->openFile(filename);
        bool isNull = file == nullptr;
        Assert_IsFalse(isNull);
        Assert_AreEqual(filename, file->getName());
    }
    
    TEST_METHOD(executePasswordProxy) { // confirms that execute, when passed a valid filename with a password, will create and add a password proxy file to the filesystem
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        // CREATE COMMAND
        TouchCommand* tc = new TouchCommand(sfs, sff);
        // REDIRECT COUT STREAM
        static streambuf* backup_out;
        backup_out = cout.rdbuf();
        static stringstream ss_out;
        cout.rdbuf(ss_out.rdbuf());
        // REDIRECT CIN STREAM
        static streambuf* backup_in;
        backup_in = cin.rdbuf();
        static stringstream ss_in;
        cin.rdbuf(ss_in.rdbuf());
        // MIMIC USER INPUT
        string password = "Jdi320dD";
        string wrongpassword = "DKR32sdfRR";
        string input = password + "\n" + password + "\n" + wrongpassword + "\n" + password;
        ss_in << input;
        // CALL EXECUTE ON TOUCH COMMAND
        string filename = "file.txt";
        Assert_AreEqual(tc->execute(filename + " -p"), 0);
        // EXPECTATION -- FILE EXISTS IN THE FILE SYSTEM
        AbstractFile* file = sfs->openFile(filename);
        bool isNull = file == nullptr;
        Assert_IsFalse(isNull);
        Assert_AreEqual(filename, file->getName());
        // EXPECTATION -- PASSWORD REQUIRED FOR WRITE -- GIVEN VALID PASSWORD
        vector<char> v = { 'h', 'i' };
        Assert_AreEqual(file->write(v), 0);
        Assert_AreEqual(file->getSize(), static_cast<unsigned int>(v.size()));
        // EXPECTATION -- PASSWORD REQUIRED FOR READ -- GIVEN INVALID PASSWORD
        vector<char> contents1 = file->read();
        Assert_AreEqual(contents1.size(), static_cast<size_t>(0));
        // EXPECTATION -- PASSWORD REQUIRED FOR READ -- GIVEN VALID PASSWORD
        vector<char> contents2 = file->read();
        Assert_AreEqual(contents2.size(), v.size());
        // ASSIGN COUT BACK TO STDOUT
        cout.rdbuf(backup_out);
        // ASSIGN CIN BACK TO STDIN
        cin.rdbuf(backup_in);
    }
    TEST_METHOD(executeInvalidExtension) { // confirms that execute, when passed a valid filename, will create and add a file in the filesystem
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        // CREATE COMMAND
        TouchCommand* tc = new TouchCommand(sfs, sff);
        // CALL EXECUTE ON TOUCH COMMAND
        string filename = "file.foo";
        Assert_AreNotEqual(tc->execute(filename), 0);
        // EXPECTATION -- FILE DOES NOT EXISTS IN THE FILE SYSTEM
        AbstractFile* file = sfs->openFile(filename);
        bool isNull = file == nullptr;
        Assert_IsTrue(isNull);
    }
    TEST_METHOD(executeFileAlreadyExists) { // confirms that execute, when passed a valid filename, will create and add a file in the filesystem
      // SET UP FILE SYSTEM
      AbstractFileSystem* sfs = new SimpleFileSystem();
        AbstractFileFactory* sff = new SimpleFileFactory();
        // CREATE COMMAND
        TouchCommand* tc = new TouchCommand(sfs, sff);
        // CALL EXECUTE ON TOUCH COMMAND
        string filename = "file.txt";
        Assert_AreEqual(tc->execute(filename), 0);
        Assert_AreNotEqual(tc->execute(filename), 0);
        // EXPECTATION -- FILE DOES EXISTS IN THE FILE SYSTEM - FIRST EXECUTION
        AbstractFile* file = sfs->openFile(filename);
        bool isNull = file == nullptr;
        Assert_IsFalse(isNull);
    }
  };
#endif
  print_stats();
  return 0;
}
