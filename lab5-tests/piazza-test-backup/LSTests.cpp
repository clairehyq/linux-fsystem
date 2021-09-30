TEST_CLASS(lSCommand) {
		TEST_METHOD(getAllFiles) { // confirms that execute, when passed a valid filename, will remove the given file from the filesystem -- removing the file again should fail, adding the file again should pass
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// ADD FILES
			string filename1 = "file.txt";
			string filename2 = "file.img";
			Assert::AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
			Assert::AreEqual(sfs->addFile(filename2, sff->createFile(filename2)), 0);
			// CHECK FILES IN SYSTEM USING GETFILENAMES() FUCNTION
			set<string> files = sfs->getFileNames();
			Assert::AreEqual(files.size(), static_cast<size_t>(2));
			// EXPECTATION -- TEXT FILE EXISTS IN THE FILE SYSTEM
			std::set<std::string>::iterator it1 = files.find(filename1);
			bool found1 = it1 == files.end();
			Assert::IsFalse(found1);
			// EXPECTATION -- IMAGE FILE EXISTS IN THE FILE SYSTEM
			std::set<std::string>::iterator it2 = files.find(filename2);
			bool found2 = it2 == files.end();
			Assert::IsFalse(found2);
		}
		TEST_METHOD(nooption) {
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// ADD FILES
			string filename1 = "file.txt";
			string filename2 = "file.img";
			string filename3 = "adifferentfile.txt";
			Assert::AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
			Assert::AreEqual(sfs->addFile(filename2, sff->createFile(filename2)), 0);
			Assert::AreEqual(sfs->addFile(filename3, sff->createFile(filename3)), 0);
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// execute ls
			AbstractCommand* ls = new LSCommand(sfs);
			Assert::AreEqual(ls->execute(""),0);
			// check output
			string firstLine;
			string secondLine;
			// ensure 2 lines of output
			bool extractSuccessful = false;
			if (getline(ss_out, firstLine)) {
				extractSuccessful = true;
			}
			Assert::IsTrue(extractSuccessful);
			extractSuccessful = false;
			if (getline(ss_out, secondLine)) {
				extractSuccessful = true;
			}
			Assert::IsTrue(extractSuccessful);
			string firstFile;
			string secondFile;
			istringstream iss(firstLine);
			iss >> firstFile;
			iss >> secondFile;
			string thirdFile;
			istringstream iss2(secondLine);
			iss2 >> thirdFile;
			string expectedFirst = "adifferentfile.txt";
			string expectedSecond = "file.img";
			string expectedThird = "file.txt";
			Assert::AreEqual(firstFile, expectedFirst);
			Assert::AreEqual(secondFile, expectedSecond);
			Assert::AreEqual(thirdFile, expectedThird);
		}
		TEST_METHOD(metadata) {
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// ADD FILES
			string filename1 = "file.txt";
			string filename2 = "file.img";
			string filename3 = "adifferentfile.txt";
			Assert::AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
			Assert::AreEqual(sfs->addFile(filename2, sff->createFile(filename2)), 0);
			Assert::AreEqual(sfs->addFile(filename3, sff->createFile(filename3)), 0);
			AbstractFile* f1 = sfs->openFile(filename1);
			AbstractFile* f2 = sfs->openFile(filename2);
			f1->write({ 'h','i' });
			int f1Size = f1->getSize();
			Assert::AreEqual(f1Size, 2);
			f2->write({ 'X',' ', ' ', 'X', '2' });
			int f2Size = f2->getSize();
			Assert::AreEqual(f2Size, 4);
			int f3Size = 0;
			sfs->closeFile(f1);
			sfs->closeFile(f2);
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// execute ls
			AbstractCommand* ls = new LSCommand(sfs);
			Assert::AreEqual(ls->execute("-m"), 0);
			string line1;
			string line2;
			string line3;
			getline(ss_out, line1);
			getline(ss_out, line2);
			getline(ss_out, line3);
			istringstream iss(line1);
			istringstream iss2(line2);
			istringstream iss3(line3);
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
			Assert::AreEqual(f1Name, filename3);
			Assert::AreEqual(f2Name, filename2);
			Assert::AreEqual(f3Name, filename1);
			string txtType = "text";
			string imgType = "image";
			Assert::AreEqual(f1Type, txtType);
			Assert::AreEqual(f2Type, imgType);
			Assert::AreEqual(f3Type, txtType);
			Assert::AreEqual(sizeF1, f3Size);
			Assert::AreEqual(sizeF2, f2Size);
			Assert::AreEqual(sizeF3, f1Size);
			// did the files get closed?
			f1 = sfs->openFile(filename1);
			f2 = sfs->openFile(filename2);
			AbstractFile* f3 = sfs->openFile(filename3);
			bool allOpen = false;
			if (f1 != nullptr && f2 != nullptr && f3 != nullptr) {
				allOpen = true;
			}
			Assert::IsTrue(allOpen);
		}
	};