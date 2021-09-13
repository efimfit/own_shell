# :white_check_mark: own_shell

Выполнено вместе с  @sabitova-fatima

Имплементация shell на языке С с возможностью запускать встроенные команды (cat, ls, ...), пайпами и редиректами. Также обрабатываются сигналы ctrl + C, ctrl + D и ctrl + \.

Для запуска нужна бибилиотека readline. Чтобы обеспечить коррекнутную работы сигналов, необходимо установить её через homebrew:

```
brew install readline
```

 ### Для запуска в терминале выполнить:

```
make && ./minishell
```

## Description
Minishell is a minimum viable version of a real shell. The main goal is to have a good understanding of process creation and synchronisation using the C programmming language.

### :page_facing_up: Fork
**The Fork system call** is used to create a new process called a child process that runs simultaneously with the process that makes the fork () call (the parent process). After creating a new child process, both processes will execute the following statement after the fork () system call. The child process uses the same computer (program counter), the same CPU registers, and the same open files that are used in the parent process.  

It does not accept parameters and returns an integer value. The various values returned by fork () are shown below.  

**Negative value:** creating a child process failed.
**Zero:** returned to the newly created child process.
**A positive value** is returned to the parent or to the subscriber. This value contains the process ID of the newly created child process.  
  
![](https://github.com/markveligod/minishell/raw/master/img/1.jpg)  

### :page_facing_up: Execve()
**The execve() system call function** is used to execute a binary executable or a script.  
The function returns nothing on success and -1 on error.  
The first parameter must be the path of a binary executable or a script.  
The second must be an array of pointers on a character (char *myArray[]), and the last pointer must be set to NULL.  
The third parameter must be an environment.  

### :page_facing_up: pipe
Conceptually, a pipe is a connection between two processes, so that the standard output of one process becomes the standard input of the other process. In the UNIX operating system, pipe are useful for communicating between related processes (inter-process communication).  
  
* The pipe is a one-way link, i.e. We can use the channel so that one process writes to the channel and the other writes from the channel. It opens a channel that is an area of main memory that is treated as a" virtual file".
* The pipe can be used by the creation process, as well as by all its child processes for reading and writing. One process can write to this "virtual file" or channel, and another related process can read from it.
* If a process tries to read before something is written to the feed, the process is paused until something is written.
The pipe system call finds the first two available positions in the open file table of the process and distributes them at the ends of the pipe for reading and writing.  
![](https://github.com/markveligod/minishell/raw/master/img/2.jpg)  

