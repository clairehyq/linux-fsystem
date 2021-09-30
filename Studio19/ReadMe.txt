# Studio 19

## Group Members

| Group Member | WUSTL ID  | Github ID    |
| ------------ | --------- | ------------ |
| Claire Huo   | huoyuqian | clairehyq    |
| York Liu     | yorkliu   | l0exy1h      |
| Yuqi Lei     | leiy      | ximenshaoxia |

## 2
We created a new file and stored it's content.
Then we created a new vector<char> with "pig" inside to be the 
new content of the file.
The original content will be blank since we did not store 
anything in it before.
The new file ocntent should be "pig".

[leiy@shell targets]$ ./studio19
file content : 
new file content : pig
Hello World!

## 3
new file, new visitor
file -> file.accept(visitor) -> visitor will visitcorrectFile

## 4
visitor pattern will get the delegation once the file accept the visitor.
Then the accept method wil direct visitor pattern to the correct method.
The only thing need to be added to the interface will be the accept method.

## 5
All the interface of AbstractFileVisitor need to be modified if 
we add a new file type.
Maybe if we have a lot of things to display for a file type, then it 
will be hard for us to modified them all.
