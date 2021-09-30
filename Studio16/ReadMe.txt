# Studio 16

## Group Members

| Group Member | WUSTL ID  | Github ID    |
| ------------ | --------- | ------------ |
| Claire Huo   | huoyuqian | clairehyq    |
| York Liu     | yorkliu   | l0exy1h      |
| Yuqi Lei     | leiy      | ximenshaoxia |

## 2.a 

The process of declaring an interface in C++ is to declare the method that we
need to use in the class and then make them all virtual and public.

## 3.a 
It is interface inheritance.

## 3.b
std::string name and std::vector<char> content both are private.

## 4 
We test the filename, filesize, write operation, append operation and then 
print the file content:
parallels@parallels-vm:~/Desktop/332/oop-work-btw-i-use-arch/targets$ ./studio16
fileName: FileName.txt
fileSize: 0
write op(0 represents success): 0
content size: 2
file content: hi
append op(0 represents success): 0
file content: hihi

They are all correct.

## 5.a 
We create a new file type t2 and append the content in t1 to t2:
/* code */
TextFile t2(Another_fileName);
std::vector<char> vv(word2.begin(), word2.end());
t2.append(vv);
auto read3 = t2.read();
string word3{read3.begin(), read3.end()};
cout << "interact content: " << word3 << endl;

/* result*/
interact content: hihi






