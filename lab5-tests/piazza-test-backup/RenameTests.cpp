TEST_CLASS(renameCommand) {
		TEST_METHOD(renameParsingStrategy) { // checks parse function of RenameParsingStrategy correctly converts input string into a vector of strings representing instructions for copy and remove commands
			// REDIRECT COUT STREAM -- PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// SETUP INPUT AND TEST OUTPUT
			RenameParsingStrategy* rps = new RenameParsingStrategy();
			vector<string> parsed = rps->parse("file.txt renamedFile");
			Assert::AreEqual(parsed.size(), static_cast<size_t>(2));
			string expectedCopyInstructions = "file.txt renamedFile";
			string expectedRemoveInstructions = "file.txt";
			Assert::AreEqual(parsed[0], expectedCopyInstructions);
			Assert::AreEqual(parsed[1], expectedRemoveInstructions);
		}
		TEST_METHOD(renameValid) {
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
			vector<char> v = { 'h','i' };
			Assert::AreEqual(file->write(v), 0);
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
			Assert::AreEqual(mc->execute(userInput), 0);
			// EXPECTATION -- ORIGINAL FILE IS REMOVED
			AbstractFile* originalFile = sfs->openFile(filename);
			bool isNull = originalFile == nullptr;
			Assert::IsTrue(isNull);
			// EXPECTATION -- FILE EXISTS UNDER NEW NAME AND CONTENTS ARE THE SAME
			AbstractFile* newFile = sfs->openFile(newfilename+".txt");
			bool isNull2 = newFile == nullptr;
			Assert::IsFalse(isNull2);
			vector<char> contents = newFile->read();
			Assert::AreEqual(v.size(), contents.size());
			Assert::AreEqual(v[0], contents[0]);
			Assert::AreEqual(v[1], contents[1]);
			// EXPECTATION -- ADDRESSES ARE DIFFERENT
			bool areEqual = &file == &newFile;
			Assert::IsFalse(areEqual);
			// EXPECTATION -- FILE TYPE MATCHES
			TextFile* textCheck = dynamic_cast<TextFile*>(newFile);
			bool isNotTextFile = textCheck == nullptr;
			Assert::IsFalse(isNotTextFile);
		}
		TEST_METHOD(renameInvalidFilename) {
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
			vector<char> v = { 'h','i' };
			Assert::AreEqual(file->write(v), 0);
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
			Assert::AreNotEqual(mc->execute(userInput), 0);
			// EXPECTATION -- ORIGINAL FILE IS NOT REMOVED
			AbstractFile* originalFile = sfs->openFile(filename);
			bool isNull = originalFile == nullptr;
			Assert::IsFalse(isNull);
			// EXPECTATION -- FILE DOES NOT EXIST UNDER NEW NAME 
			AbstractFile* newFile = sfs->openFile(newfilename+".txt");
			bool isNull2 = newFile == nullptr;
			Assert::IsTrue(isNull2);;
		}
		TEST_METHOD(renameInvalidNewFilename) {
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
			string otherfilename = "otherfile";
			AbstractFile* file = new TextFile(filename);
			Assert::AreEqual(sfs->addFile(filename, file), 0);
			AbstractFile* otherfile = new TextFile(otherfilename +".txt");
			Assert::AreEqual(sfs->addFile(otherfilename + ".txt", otherfile), 0);
			// INITIALIZE FILE CONTENTS
			vector<char> v = { 'h','i' };
			Assert::AreEqual(file->write(v), 0);
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
			Assert::AreNotEqual(mc->execute(userInput), 0);
			// EXPECTATION -- ORIGINAL FILE IS NOT REMOVED
			AbstractFile* originalFile = sfs->openFile(filename);
			bool isNull = originalFile == nullptr;
			Assert::IsFalse(isNull);
			// EXPECTATION -- OTHER FILE STILL EXISTS
			AbstractFile* newFile = sfs->openFile(otherfilename+".txt");
			bool isNull2 = newFile == nullptr;
			Assert::IsFalse(isNull2);;
		}
		TEST_METHOD(renameValidPasswordProtected) {
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
			string password = "Adi23ifK";
			AbstractFile* proxy = new PasswordProxy(file, password);
			Assert::AreEqual(sfs->addFile(filename, proxy), 0);
			// INITIALIZE FILE CONTENTS -- WE WRITE DIRECTLY TO FILE IN THIS CASE (FUNCTIONALITY IS TEST OTHER PLACES)
			vector<char> v = { 'h','i' };
			Assert::AreEqual(file->write(v), 0);
			// CREATE MACRO COMMAND USING RENAME PARSING STRATEGY AND COPY/REMOVE COMMANDS
			MacroCommand* mc = new MacroCommand(sfs);
			RenameParsingStrategy* rps = new RenameParsingStrategy;
			AbstractCommand* cpc = new CopyCommand(sfs);
			AbstractCommand* rmc = new RemoveCommand(sfs);
			mc->setParseStrategy(rps);
			mc->addCommand(cpc);
			mc->addCommand(rmc);
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// EXECUTE RENAME COMMAND
			string newfilename = "newfilename";
			string userInput = filename + " " + newfilename;
			Assert::AreEqual(mc->execute(userInput), 0);
			// EXPECTATION -- ORIGINAL FILE IS REMOVED
			AbstractFile* originalFile = sfs->openFile(filename);
			bool isNull = originalFile == nullptr;
			Assert::IsTrue(isNull);
			// EXPECTATION -- FILE EXISTS UNDER NEW NAME AND CONTENTS ARE THE SAME
			AbstractFile* newFile = sfs->openFile(newfilename+".txt");
			bool isNull2 = newFile == nullptr;
			Assert::IsFalse(isNull2);
			// SET UP USER PASSWORD INPUT AND READ AGAIN TO GET TRUE CONTENTS 
			ss_in << password + "\n";
			vector<char> contentswithpassword = newFile->read();
			Assert::AreEqual(v.size(), contentswithpassword.size());
			Assert::AreEqual(v[0], contentswithpassword[0]);
			Assert::AreEqual(v[1], contentswithpassword[1]);
			// SECOND READ CALL NOT GIVEN A PASSWORD -- SHOULD FAIL AND GET AN EMPTY VECTOR
			vector<char> contents = newFile->read();
			Assert::AreEqual(contents.size(), static_cast<size_t>(0));
			// EXPECTATION -- ADDRESSES ARE DIFFERENT
			bool areEqual = &file == &newFile;
			Assert::IsFalse(areEqual);
			// EXPECTATION -- FILE TYPE MATCHES
			PasswordProxy* proxyCheck = dynamic_cast<PasswordProxy*>(newFile);
			bool isNotPasswordProxy = proxyCheck == nullptr;
			Assert::IsFalse(isNotPasswordProxy);
		}
	};