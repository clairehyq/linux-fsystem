# Studio 17

## Group Members

| Group Member | WUSTL ID  | Github ID    |
| ------------ | --------- | ------------ |
| Claire Huo   | huoyuqian | clairehyq    |
| York Liu     | yorkliu   | l0exy1h      |
| Yuqi Lei     | leiy      | ximenshaoxia |

## 2
We test the image name, image initial size,read operation, correctness of 
write and append operation:
parallels@p-vm:~/Desktop/332/oop-work-btw-i-use-arch/targets$ ./studio17
imgName: FileName.img
imgSize: 0
write op(0 represents success): 0
content size: 9
img content: 
X
X
X
X
X
append op(none-zero represents success): 9
img content: 
X
X
X
X
X

Results are all correct.
## 3
Benifits of interface:
(1) Clear instruction for developers to complete the project.
(2) Easy to operate on duplicated tasks and easy to maintian code.

## 4
parallels@p-vm:~/Desktop/332/oop-work-btw-i-use-arch/targets$ ./studio17
addFile_img op:(0 is correct) 0
addFile_txt op:(0 is correct) 0
openfile op:(0 is correct) 0
deletefile op:(0 is correct) 0

To add a new file type, we could use the createFile() method in 
SimpleFileSystem class.






