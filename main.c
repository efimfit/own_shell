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

int my_echo (char **command)
{
    printf("Here will be my own echo\n");
    return (1);
}

// добавить возможность писать без начальной /
// проверять наличие директории и выводить ошибку 

int my_cd (char **command)
{
    if (chdir(command[1]) == 0)
        return (1);
    else
    {
        ft_putstr("Directory not found\n");
        return (-1);
    }
}

int my_pwd (char **command)
{
    // printf("Here will be my own pwd\n");
    char    dir_name[4096];
    getcwd(dir_name, 4096);

    ft_putstr(dir_name);
    ft_putchar('\n');
    return (1);
}

int my_export (char **command)
{
    printf("Here will be my own export\n");
    return (1);
}

int my_unset (char **command)
{
    printf("Here will be my own unset\n");
    return (1);
}

int my_env (char **command, char **env)
{
    // printf("Here will be my own env\n");
    int i;

    i = 0;
    while (env[i])
    {
        ft_putstr(env[i]);
        ft_putchar('\n');
        i++;
    }
    return (1);
}

int my_exit (char **command)
{
    // printf("Here will be my own exit\n");
    // return (1);
    exit(0);
}

int start_own_function (char **command, char **env)
{
    if (ft_strcmp("echo", command[0]) == 0)
        return(my_echo(command));
    if (ft_strcmp("cd", command[0]) == 0)
        return(my_cd(command));
    if (ft_strcmp("pwd", command[0]) == 0)
        return(my_pwd(command));
    if (ft_strcmp("export", command[0]) == 0)
        return(my_export(command));
    if (ft_strcmp("unset", command[0]) == 0)
        return(my_unset(command));
    if (ft_strcmp("env", command[0]) == 0)
        return(my_env(command, env));
    if (ft_strcmp("exit", command[0]) == 0)
        return(my_exit(command));
    return (0);
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
    int     fd;
    int     is_own;
    int     i = 0;

    is_own = 0;
    dir = find_dir(env);
    dirs = ft_strsplit(dir, ':');

    // int n = chdir("/home/fatima");

    while (1)
	{
        getcwd(dir_name, 4096);
        ft_putstr(dir_name);
        ft_putstr(" \033[0m\033[33msh>\033[0m$ ");
    
        get_next_line(&line);
        command = ft_strsplit(line, ' ');
        is_own = start_own_function(command, env);
        if (is_own == 0)
        {
            while (dirs[i])
            {
                command_dir = ft_strjoin(ft_strjoin(dirs[i], "/"), command[0]);
                fd = open(command_dir, O_RDONLY);
                i++;
                if (fd >= 0)
                {
                    // close(fd); - почему ломается, если раскомментить?
                    break ;
                }
            }
        }
        i = 0;
        pid = fork();
        if (pid == 0)
            execve(command_dir, command, env);
        wait(&pid);
        if (fd < 0)
            ft_putstr("program not fround :(\n");
	}


}