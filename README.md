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


### :page_facing_up: Fork
**The Fork system call** is used to create a new process called a child process that runs simultaneously with the process that makes the fork () call (the parent process). After creating a new child process, both processes will execute the following statement after the fork () system call. The child process uses the same computer (program counter), the same CPU registers, and the same open files that are used in the parent process.  

It does not accept parameters and returns an integer value. The various values returned by fork () are shown below.  

**Negative value:** creating a child process failed.
**Zero:** returned to the newly created child process.
**A positive value** is returned to the parent or to the subscriber. This value contains the process ID of the newly created child process.  
  
![](https://github.com/markveligod/minishell/raw/master/img/1.jpg)  

