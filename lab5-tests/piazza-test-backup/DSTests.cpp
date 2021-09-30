TEST_CLASS(DSCommand) {
		TEST_METHOD(displaytext) {
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			string filename1 = "file.txt";
			Assert::AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
			AbstractFile* f = sfs->openFile(filename1);
			vector<char> v = { 'h', 'i','\n','h','e','l','l','o' };
			f->write(v);
			sfs->closeFile(f);
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// execute ds
			AbstractCommand* ds = new DisplayCommand(sfs);
			Assert::AreEqual(ds->execute(filename1), 0);
			ss_out >> noskipws;
			char c;
			for (size_t i = 0; i < v.size(); ++i) {
				ss_out >> c;
				Assert::AreEqual(c, v[i]);
			}
			// ensure the file was closed
			f = sfs->openFile(filename1);
			bool isNull = f == nullptr;
			Assert::IsFalse(isNull);
		}
		TEST_METHOD(displaytextunformatted) {
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			string filename1 = "file.txt";
			Assert::AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
			AbstractFile* f = sfs->openFile(filename1);
			vector<char> v = { 'h', 'i','\n','h','e','l','l','o' };
			f->write(v);
			sfs->closeFile(f);
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// execute ds
			AbstractCommand* ds = new DisplayCommand(sfs);
			Assert::AreEqual(ds->execute(filename1 + " -d"), 0);
			ss_out >> noskipws;
			char c;
			for (size_t i = 0; i < v.size(); ++i) {
				ss_out >> c;
				Assert::AreEqual(c, v[i]);
			}
			// ensure the file was closed
			f = sfs->openFile(filename1);
			bool isNull = f == nullptr;
			Assert::IsFalse(isNull);
		}
		TEST_METHOD(displayimageformatted) {
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			string filename1 = "file.img";
			Assert::AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
			AbstractFile* f = sfs->openFile(filename1);
			vector<char> v = { 'X',' ',' ','X',' ',' ','X', ' ',' ','3' };
			vector<char> expectedOutput = { 'X',' ',' ','\n','X',' ',' ','\n','X',' ',' ','\n' };
			f->write(v);
			sfs->closeFile(f);
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// execute ds
			AbstractCommand* ds = new DisplayCommand(sfs);
			Assert::AreEqual(ds->execute(filename1), 0);
			ss_out >> noskipws;
			char c;
			for (size_t i = 0; i < expectedOutput.size(); ++i) {
				ss_out >> c;
				Assert::AreEqual(c, expectedOutput[i]);
			}
			// ensure the file was closed
			f = sfs->openFile(filename1);
			bool isNull = f == nullptr;
			Assert::IsFalse(isNull);
		}

		TEST_METHOD(displayimageunformatted) {
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			string filename1 = "file.img";
			Assert::AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
			AbstractFile* f = sfs->openFile(filename1);
			vector<char> v = { 'X',' ',' ','X',' ',' ','X', ' ',' ','3' };
			vector<char> expectedOutput = { 'X',' ',' ','X',' ',' ','X',' ',' ','\n' };
			f->write(v);
			sfs->closeFile(f);
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// execute ds
			AbstractCommand* ds = new DisplayCommand(sfs);
			Assert::AreEqual(ds->execute(filename1 + " -d"), 0);
			ss_out >> noskipws;
			char c;
			for (size_t i = 0; i < expectedOutput.size(); ++i) {
				ss_out >> c;
				Assert::AreEqual(c, expectedOutput[i]);
			}
			// ensure the file was closed
			f = sfs->openFile(filename1);
			bool isNull = f == nullptr;
			Assert::IsFalse(isNull);
		}
		TEST_METHOD(displayinvalid) {
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			string filename1 = "file.img";
			Assert::AreEqual(sfs->addFile(filename1, sff->createFile(filename1)), 0);
			AbstractCommand* ds = new DisplayCommand(sfs);
			Assert::AreNotEqual(ds->execute("file.txt"), 0);
		}
	};