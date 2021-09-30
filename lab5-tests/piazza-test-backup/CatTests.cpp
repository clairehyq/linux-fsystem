TEST_CLASS(catCommand) {
		TEST_METHOD(executeTextFileNoAppendSaving) { // test executing cat with no append option and saving input to a text file
			// SET UP FILE SYSTEM
			// REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf()); 
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// ADD FILES
			string filename = "file.txt";
			AbstractFile* file = new TextFile(filename);
			Assert::AreEqual(sfs->addFile(filename, file), 0);
			// INITIALIZE FILE CONTENTS
			vector<char> origContents = { 'f','o','o' };
			string origContentsStr(origContents.begin(), origContents.end());
			Assert::AreEqual(file->write(origContents), 0);
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// MIMIC USER INPUT 
			string userInput = "hello world";
			string saveOption = "\n:wq\n";
			ss_in << userInput + saveOption;
			// CREATE AND EXECUTE COMMAND
			CatCommand* cc = new CatCommand(sfs);
			string executeInput = filename;
			Assert::AreEqual(cc->execute(executeInput), 0);
			// EXPECTATION -- CONTENTS MATCH
			vector<char> contents = file->read();
			string contentsStr(contents.begin(), contents.end());
			Assert::AreEqual(userInput, contentsStr);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(executeTextFileNoAppendSavingMultipleLines) { // test executing cat with no append option and saving input with multiple lines to a text file
			// REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// ADD FILES
			string filename = "file.txt";
			AbstractFile* file = new TextFile(filename);
			Assert::AreEqual(sfs->addFile(filename, file), 0);
			// INITIALIZE FILE CONTENTS
			vector<char> origContents = { 'f','o','o' };
			string origContentsStr(origContents.begin(), origContents.end());
			Assert::AreEqual(file->write(origContents), 0);
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// MIMIC USER INPUT 
			string userInput = "hello\nworld\nmultiple\nlines";
			string saveOption = "\n:wq\n";
			ss_in << userInput + saveOption;
			// CREATE AND EXECUTE COMMAND
			CatCommand* cc = new CatCommand(sfs);
			string executeInput = filename;
			Assert::AreEqual(cc->execute(executeInput), 0);
			// EXPECTATION -- CONTENTS MATCH
			vector<char> contents = file->read();
			string contentsStr(contents.begin(), contents.end());
			Assert::AreEqual(userInput, contentsStr);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(executeTextFileNoAppendNoSaving) { // test executing cat with no append option and without saving input to a text file
			// REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// ADD FILES
			string filename = "file.txt";
			AbstractFile* file = new TextFile(filename);
			Assert::AreEqual(sfs->addFile(filename, file), 0);
			// INITIALIZE FILE CONTENTS
			vector<char> origContents = { 'f','o','o' };
			string origContentsStr(origContents.begin(), origContents.end());
			Assert::AreEqual(file->write(origContents), 0);
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// MIMIC USER INPUT 
			string userInput = "hello world";
			string saveOption = "\n:q\n";
			ss_in << userInput + saveOption;
			// CREATE AND EXECUTE COMMAND
			CatCommand* cc = new CatCommand(sfs);
			string executeInput = filename;
			Assert::AreEqual(cc->execute(executeInput), 0);
			// EXPECTATION -- CONTENTS UNTOUCHED
			vector<char> contents = file->read();
			string contentsStr(contents.begin(), contents.end());
			Assert::AreEqual(origContentsStr, contentsStr);
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
			Assert::AreEqual(sfs->addFile(filename, file), 0);
			// INITIALIZE FILE CONTENTS
			vector<char> origContents = { 'f','o','o' };
			string origContentsStr(origContents.begin(), origContents.end());
			Assert::AreEqual(file->write(origContents), 0);
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// MIMIC USER INPUT 
			string userInput = "hello world";
			string saveOption = "\n:wq\n";
			ss_in << userInput + saveOption;
			// CREATE AND EXECUTE COMMAND
			CatCommand* cc = new CatCommand(sfs);
			string executeInput = filename + " -a";
			Assert::AreEqual(cc->execute(executeInput), 0);
			// EXPECTATION -- CONTENTS PRINTED PRINTED
			string word;
			std::vector<string> printedWords;
			while (ss_out >> word) {
				printedWords.push_back(word);
			}
			std::vector<string>::iterator it1;
			it1 = std::find(printedWords.begin(), printedWords.end(), origContentsStr);
			bool notEqual1 = it1 == printedWords.end();
			Assert::IsFalse(notEqual1);
			// EXPECTATION -- CONTENTS CORRECTLY UPDATED
			vector<char> contents = file->read();
			string contentsStr(contents.begin(), contents.end());
			Assert::AreEqual(origContentsStr + userInput, contentsStr);
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
			Assert::AreEqual(sfs->addFile(filename, file), 0);
			// INITIALIZE FILE CONTENTS
			vector<char> origContents = { 'f','o','o' };
			string origContentsStr(origContents.begin(), origContents.end());
			Assert::AreEqual(file->write(origContents), 0);
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// MIMIC USER INPUT 
			string userInput = "hello world";
			string saveOption = "\n:q\n";
			ss_in << userInput + saveOption;
			// CREATE AND EXECUTE COMMAND
			CatCommand* cc = new CatCommand(sfs);
			string executeInput = filename + " -a";
			Assert::AreEqual(cc->execute(executeInput), 0);
			// EXPECTATION -- CONTENTS PRINTED PRINTED
			string word;
			std::vector<string> printedWords;
			while (ss_out >> word) {
				printedWords.push_back(word);
			}
			std::vector<string>::iterator it1;
			it1 = std::find(printedWords.begin(), printedWords.end(), origContentsStr);
			bool notEqual1 = it1 == printedWords.end();
			Assert::IsFalse(notEqual1);
			// EXPECTATION -- CONTENTS CORRECTLY UPDATED
			vector<char> contents = file->read();
			string contentsStr(contents.begin(), contents.end());
			Assert::AreEqual(origContentsStr, contentsStr);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(executeImageFileNoAppendSavingGoodInput) { // test executing cat with no append option and saving valid input to an image file
			// REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// ADD FILES
			string filename = "file.img";
			AbstractFile* file = new ImageFile(filename);
			Assert::AreEqual(sfs->addFile(filename, file), 0);
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// MIMIC USER INPUT 
			string userInput = "X X X X X3";
			string userInputWithoutLength = "X X X X X";
			string saveOption = "\n:wq\n";
			ss_in << userInput + saveOption;
			// CREATE AND EXECUTE COMMAND
			CatCommand* cc = new CatCommand(sfs);
			string executeInput = filename;
			Assert::AreEqual(cc->execute(executeInput), 0);
			// EXPECTATION -- CONTENTS MATCH
			vector<char> contents = file->read();
			string contentsStr(contents.begin(), contents.end());
			Assert::AreEqual(userInputWithoutLength, contentsStr);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(executeImageFileNoAppendSavingBadInput) { // test executing cat with no append option and saving invalid input to an image file, content should be unchanged
			// REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// ADD FILES
			string filename = "file.img";
			AbstractFile* file = new ImageFile(filename);
			Assert::AreEqual(sfs->addFile(filename, file), 0);
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
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
			Assert::AreEqual(contents.size(), static_cast<size_t>(0));
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(executeImageFileNoAppendNoSavingGoodInput) { // test executing cat with no append option and not saving valid input to an image file, contents unchanged
			// REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// ADD FILES
			string filename = "file.img";
			AbstractFile* file = new ImageFile(filename);
			Assert::AreEqual(sfs->addFile(filename, file), 0);
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// MIMIC USER INPUT 
			string userInput = "X X X X X3";
			string userInputWithoutLength = "X X X X X";
			string saveOption = "\n:q\n";
			ss_in << userInput + saveOption;
			// CREATE AND EXECUTE COMMAND
			CatCommand* cc = new CatCommand(sfs);
			string executeInput = filename;
			Assert::AreEqual(cc->execute(executeInput), 0);
			// EXPECTATION -- CONTENTS UNCHANGED
			vector<char> contents = file->read();
			Assert::AreEqual(contents.size(), static_cast<size_t>(0));
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(executeImageFileAppendSavingGoodInput) { // test executing cat with append option and saving valid input to an image file, expect an error returned and contents to be unchanged
			// REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// ADD FILES
			string filename = "file.img";
			AbstractFile* file = new ImageFile(filename);
			Assert::AreEqual(sfs->addFile(filename, file), 0);
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// MIMIC USER INPUT 
			string userInput = "X X X X X3";
			string userInputWithoutLength = "X X X X X";
			string saveOption = "\n:wq\n";
			ss_in << userInput + saveOption;
			// CREATE AND EXECUTE COMMAND
			CatCommand* cc = new CatCommand(sfs);
			string executeInput = filename + " -a";
			Assert::AreNotEqual(cc->execute(executeInput), 0);
			// EXPECTATION -- CONTENTS UNCHANGED
			vector<char> contents = file->read();
			Assert::AreEqual(contents.size(), static_cast<size_t>(0));
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(executeFileDoesNotExist) { // test executing cat with append option and saving valid input to an image file that doesnt exist, expect an error returned 
			// REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// MIMIC USER INPUT 
			string userInput = "hello world";
			string saveOption = "\n:wq\n";
			ss_in << userInput + saveOption;
			// CREATE AND EXECUTE COMMAND
			CatCommand* cc = new CatCommand(sfs);
			string executeInput = "file.txt";
			Assert::AreNotEqual(cc->execute(executeInput), 0);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
	};