# Studio 18

## Group Members

| Group Member | WUSTL ID  | Github ID    |
| ------------ | --------- | ------------ |
| Claire Huo   | huoyuqian | clairehyq    |
| York Liu     | yorkliu   | l0exy1h      |
| Yuqi Lei     | leiy      | ximenshaoxia |

## 2
By using the factory method, we just need to determine the file type
and then return a new object of that kind of object.

## 3
Advantage of Abstract factory: easy to create multiple different file type.
How to realize(two file types):
AbstractFile* SimpleFileFactory::createFile(string name)
{
  string pre, ext;
  if (OK != splitExt(name, pre, ext)) return nullptr;

  if (ext == IMG_EXT) return new ImageFile(name);
  else if (ext == TXT_EXT) return new TextFile(name);
  else return nullptr;
}

## 4
/* code */
SimpleFileFactory sff;
AbstractFile* res = sff.createFile("FileName.txt");
bool isNull = res == nullptr;
cout << "insert op: " << isNull << endl;
std::vector<char> v = { 'h', 'i' };
cout << "write op(0 represents success): " << res->write(v) << endl;
auto read1 = res->read();
string word1{read1.begin(), read1.end()};
cout << "file content: " << word1 << endl;

/* result */
insert op: 0
write op(0 represents success): 0
file content: hi

Result are all correct.

## 5
SimpleFileSystem depends on the AbstractFile interface only.

