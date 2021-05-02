# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>
# include <fcntl.h>

# include "minishell.h"
 
int        get_next_line(char **line)
{
    char    c;
    char    *buf;
    int        rv;
    int        i = 0;

    if (!(buf = (char*)malloc(10000)))
        return (-1);
    *line = buf;
    while ((rv = read(0, &c, 1)) > 0 && c != '\n' && c != '\0')
    {
        buf[i] = c;
        i++;
    }
    buf[i] = '\0';
    if (rv == -1)
        return (-1);
    return (rv ? 1 : 0);
}

char* find_dir(char **env)
{
    int i;

    i = 0;

    while (env[i])
    {
        // printf("%s\n\n\n", env[i]);
        if (env[i][0] == 'P' && env[i][1] == 'A' 
        && env[i][2] == 'T' && env[i][3] == 'H')
        return(env[i]);
        i++;   
    }
}

int main (int argc, char **argv, char **env)
{
    char    dir_name[4096];
	char	*line;
    char    **command;
	char	*command_dir;
    char    *dir;
    char    **dirs;
	pid_t	pid;
    int fd;

    int i = 0;

    // получаем название директории, в которой находимся 
    getcwd(dir_name, 4096);

    // получаем переменную PATH целиком
    dir = find_dir(env);

    // двумерный массив с директориями в которых лежат бинарники
    dirs = ft_strsplit(dir, ':');
    while (1)
	{
        // выводим то, что до курсора
        ft_putstr(dir_name);
        ft_putstr(" \033[0m\033[33msh>\033[0m$ ");
    
        get_next_line(&line);
        command = ft_strsplit(line, ' ');

        while (dirs[i])
        {
            // получаем команду типа /bin/ls
            command_dir = ft_strjoin(ft_strjoin(dirs[i], "/"), command[0]);

            // пытаемся открыть бинарник, чтобы проверить в той ли папке он лежит
            // если fd > 0, значит, он там. Прерываем цикл
            fd = open(command_dir, O_RDONLY);
            i++;
            if (fd >= 0)
            {
                // close(fd); - почему ломается, если раскомментить?
                break ;
            }
        }
        i = 0;
        pid = fork();
        if (pid == 0)
            execve(command_dir, command, env);
        wait(&pid);
    if (fd < 0)
        ft_putstr("program not fround\n");
	}
}