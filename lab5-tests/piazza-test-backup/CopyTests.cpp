	TEST_CLASS(Copy) {
		TEST_METHOD(validcopy) {
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			string filename = "file.txt";
			Assert::AreEqual(sfs->addFile(filename, sff->createFile(filename)), 0);
			AbstractFile* f = sfs->openFile(filename);
			vector<char> original = { 'h','i' };
			f->write(original);
			sfs->closeFile(f);
			string copyname = "copy.txt";
			AbstractCommand* cp = new CopyCommand(sfs);
			Assert::AreEqual(cp->execute(filename + " copy"),0);
			f = sfs->openFile(filename);
			bool isNull = f == nullptr;
			Assert::IsFalse(isNull);
			AbstractFile* f_copy = sfs->openFile(copyname);
			isNull = f_copy == nullptr;
			Assert::IsFalse(isNull);
			Assert::AreEqual(f_copy->getName(), copyname);
			bool sameFile = f_copy == f;
			Assert::IsFalse(sameFile);
			vector<char> copy_contents = f_copy->read();
			Assert::AreEqual(copy_contents.size(), original.size());
			Assert::AreEqual((size_t)f->getSize(), original.size());
			for (size_t i = 0; i < original.size(); ++i) {
				Assert::AreEqual(copy_contents[i], original[i]);
			}
			TextFile* t_p = dynamic_cast<TextFile*>(f_copy);
			isNull = t_p == nullptr;
			Assert::IsFalse(isNull);
		}
		TEST_METHOD(invalidcopy) {
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();

			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			string filename = "file.txt";
			Assert::AreEqual(sfs->addFile(filename, sff->createFile(filename)), 0);
			AbstractFile* f = sfs->openFile(filename);
			vector<char> original = { 'h','i' };
			f->write(original);
			sfs->closeFile(f);
			AbstractCommand* cp = new CopyCommand(sfs);
			Assert::AreNotEqual(cp->execute(filename + " file"), 0);
			Assert::AreNotEqual(cp->execute("madeupname.txt othername"), 0);
			// ensure the original file wasn't changed and is closed
			f = sfs->openFile(filename);
			bool isNull = f == nullptr;
			Assert::IsFalse(isNull);
			vector<char> after_invalid = f->read();
			Assert::AreEqual(after_invalid.size(), original.size());
		}
		TEST_METHOD(copypasswordprotected) {
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();

			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			string filename = "file.txt";
			AbstractFile* realfile = sff->createFile(filename);
			vector<char> original = { 'h','i' };
			realfile->write(original);
			string pw = "easypassword";
			AbstractFile* proxy_toreal = new PasswordProxy(realfile, pw);
			Assert::AreEqual(sfs->addFile(proxy_toreal->getName(), proxy_toreal), 0);
			AbstractCommand* cp = new CopyCommand(sfs);
			string copyname = "copy.txt";
			Assert::AreEqual(cp->execute(filename + " copy"), 0);
			AbstractFile* proxy_copy = sfs->openFile(copyname);
			bool isNull = proxy_copy == nullptr;
			Assert::IsFalse(isNull);
			PasswordProxy* proxy_tocopy = dynamic_cast<PasswordProxy*>(proxy_copy);
			isNull = proxy_tocopy == nullptr;
			Assert::IsFalse(isNull);
			bool sameProxy = proxy_tocopy == proxy_toreal;
			Assert::IsFalse(sameProxy);
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// MIMIC USER INPUT
			ss_in << pw << '\n';
			vector<char> newdata = { 'h','e','l','l','o' };
			Assert::AreEqual(proxy_tocopy->write(newdata), 0);
			auto v = realfile->read();
			Assert::AreEqual(v.size(), original.size());
			for (size_t i = 0; i < v.size(); ++i) {
				Assert::AreEqual(v[i], original[i]);
			}
		}
	};