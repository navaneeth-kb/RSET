Implement the system calls:- fork, exec, getpid, exit, wait, close, stat, opendir and readdir.

Qn1 : Write a program using fork() to create a child process that print “hello”, the parent
process should print “goodbye”. The child process should always prints first.

Qn2 : . Create a parent-child relationship between two processes.
The parent should print two statements:
1-> Process ID of Parent is <PID> 2 -> Child of <PID> is <PID_of_Child>
The child should print two statements:
3-> Process Id of Child is <PID> 4 -> Parent of <PID> is <PID_ of _parent>
Make use of wait() in such a manner that the order of printing four statements is 1,3,4,2

Qn 3 : Write a program to print ‘hello’ 16 times using fork system call.

Qn4: Write a program using fork to create a child process, and then call any exec system call
from within the child process, to execute ‘pwd’ in the new process..

Qn 5: Write your own version of the command line program stat, which simply calls the stat()
system call on a given file or directory. Print out file name, file size, number of blocks allocated.

Qn 6: Write a program using opendir, readdir and closedir system calls to display the contents
in current directory.

Qn 7: Write a program to copy content of one file to another using I/O system call.
