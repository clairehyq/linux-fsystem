	TEST_CLASS(removeCommand) {
		TEST_METHOD(execute) { // confirms that execute, when passed a valid filename, will remove the given file from the filesystem -- removing the file again should fail, adding the file again should pass
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// ADD FILES
			string filename1 = "file.txt";
			string filename2 = "file.img";
			Assert::AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
			Assert::AreEqual(sfs->addFile(filename2, sff->createFile(filename2)), 0);
			// CREATE COMMAND
			RemoveCommand* rc = new RemoveCommand(sfs);
			// CALL EXECUTE ON REMOVE COMMAND
			Assert::AreEqual(rc->execute(filename2), 0);
			// EXPECTATION -- TEXT FILE EXISTS IN THE FILE SYSTEM
			AbstractFile* file1 = sfs->openFile(filename1);
			bool isNull1 = file1 == nullptr;
			Assert::IsFalse(isNull1);
			Assert::AreEqual(filename1, file1->getName());
			// EXPECTATION -- IMAGE FILE REMOVED IN THE FILE SYSTEM
			AbstractFile* file2 = sfs->openFile(filename2);
			bool isNull2 = file2 == nullptr;
			Assert::IsTrue(isNull2);
			// CLOSE TEXT FILE
			Assert::AreEqual(sfs->closeFile(file1), 0);
			// CHECK FILES IN SYSTEM USING GETFILENAMES() FUCNTION
			set<string> files = sfs->getFileNames();
			Assert::AreEqual(files.size(), static_cast<size_t>(1));
			// EXPECTATION -- TEXT FILE EXISTS IN THE FILE SYSTEM
			std::set<std::string>::iterator it1 = files.find(filename1);
			bool found1 = it1 == files.end();
			Assert::IsFalse(found1);
			// EXPECTATION -- IMAGE FILE REMOVED IN THE FILE SYSTEM
			std::set<std::string>::iterator it2 = files.find(filename2);
			bool found2 = it2 == files.end();
			Assert::IsTrue(found2);
			// RE-ADD FILE
			Assert::AreEqual(sfs->addFile(filename2, sff->createFile(filename2)), 0);
			set<string> files2 = sfs->getFileNames();
			Assert::AreEqual(files2.size(), static_cast<size_t>(2));
			// EXPECTATION -- IMAGE FILE EXISTS IN THE FILE SYSTEM - OPEN FILE CHEC AND GETFILENAMES CHECK
			std::set<std::string>::iterator it3 = files2.find(filename2);
			bool found3 = it3 == files2.end();
			Assert::IsFalse(found3);
			AbstractFile* file3 = sfs->openFile(filename2);
			bool isNull3 = file3 == nullptr;
			Assert::IsFalse(isNull3);
		}
		TEST_METHOD(executeFileOpen) { // confirms that execute, when passed a valid filename for a file that is open, execute will return an error and filesystem is untouched, so we expect to be able to close it
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// ADD FILE
			string filename1 = "file.txt";
			Assert::AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
			// OPEN FILE
			AbstractFile* file1 = sfs->openFile(filename1);
			bool isNull = file1 == nullptr;
			Assert::IsFalse(isNull);			
			Assert::AreEqual(filename1, file1->getName());
			// CREATE COMMAND
			RemoveCommand* rc = new RemoveCommand(sfs);
			// CALL EXECUTE ON REMOVE COMMAND
			Assert::AreNotEqual(rc->execute(filename1), 0);
			// EXPECTATION -- TEXT FILE EXISTS IN THE FILE SYSTEM -- SO WE CAN CLOSE IT
			// CLOSE FILE
			Assert::AreEqual(sfs->closeFile(file1),0);
		}
	};