# Lab 5

## Group Members

| Group Member | WUSTL ID  | Github ID    |
| ------------ | --------- | ------------ |
| York Liu     | yorkliu   | l0exy1h      |
| Claire Huo   | huoyuqian | clairehyq    |
| Yuqi Lei     | leiy      | ximenshaoxia |

## 1: LSCommand

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ls
file.txt            file2.txt           
image.img           image2.img          
other.txt  
```

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ls -m
file.txt    	text	0
file2.txt   	text	0
image.img   	image	0
image2.img  	image	0
other.txt   	text	0
```

## 2: RemoveCommand

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ rm file.txt

Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ls
file2.txt           image.img           
image2.img          other.txt
```

## 3: TouchCommand:

without password:

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ touch file_without_password.txt

Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ls
file2.txt           file_without_password.txt
image.img           image2.img          
other.txt           
```

Touch with password:

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ touch file_with_password.txt -p
please enter the password: 
112358
```

## 4: ​CatCommand:

overwrite

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ cat file_without_password.txt
Hi, this is testtttt!
:wq

Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ds file_without_password.txt
Hi, this is testtttt!
```

append:

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ cat file_with_password.txt -a
please enter the password: 
112358
Hi, this is testtttt!
Hi, this is testtttt again!
:wq
please enter the password: 
112358

Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ds file_with_password.txt
please enter the password: 
112358
Hi, this is testtttt!
Hi, this is testtttt again!
```

cat without saving

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ds file.txt
123
45678
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ cat file.txt -a
123
45678
quit op test     
:q

Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ds file.txt
123
45678
```

## 5: DisplayCommand:

formatted output:

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ cat image.img
X X X X X3
:wq

Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ds image.img
X X
 X 
X X
```

unformatted output:

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ds image.img -d
X X X X X
```

## 6: CopyCommand:

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ cp file.txt file_copy

Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ds file_copy.txt
123
45678

Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ cat file_copy.txt
Check whether the file is unique
:wq

Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ds file.txt
123
45678
```

## 8: RenameCommand:

```
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ds file.txt
123
45678
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ rn file.txt rename_test

Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ ls
file_copy.txt       image.img           
rename_test.txt
```


## Extra Credit

We write 'unique' into a file named file_copy.txt:

```
#a: GrepCommand:
Enter a command, q to quit, help for a list of commands, or help followed by a
command name for more information about that command.
$ grep unique
file_copy.txt
```


