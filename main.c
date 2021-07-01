#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>

int start_own_function (char **command, char **env, char *line)
{
    if (ft_strcmp("echo", command[0]) == 0)
        return(my_echo(command, line));
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

char* find_path(char **env)
{
    int i;

    i = 0;

    while (env[i])
    {
        if (env[i][0] == 'P' && env[i][1] == 'A' 
        && env[i][2] == 'T' && env[i][3] == 'H')
        return(env[i]);
        i++;   
    }
    return (NULL);
}

void put_prompt(void)
{
    char dir_name[4096 + 1];
    getcwd(dir_name, 4096);
    ft_putstr(dir_name);
    // ft_putstr(" \033[0m\033[33me-bash>\033[0m$ ");
}

char *find_dir_path(char **command, char **dirs)
{
    int fd;
    int m = 0;
    char *command_dir;
    while (dirs[m])
    {
        command_dir = ft_strjoin(ft_strjoin(dirs[m], "/"), command[0]);
        fd = open(command_dir, O_RDONLY);
        m++;
        if (fd >= 0)
            break ;
    }
    if (fd < 0)
    {
        ft_putstr("program not found :(\n");
        return (NULL);
    }
    return (command_dir);
}

// void	ctrl_c(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		ft_putstr("\n");
// 		put_prompt();
// 		signal(SIGINT, ctrl_c);
// 	}
// }

// void	ctrl_slash(int signo)
// {
// 	if (signo == SIGQUIT)
// 	{
// 		exit(0);
// 	}
// }

char **cut_command(char ** command)
{
    int i;
    int j;

    i = 0;
    int len = 0;

    char ** res;
    while (command[i] || command[i + 1])
    {
        i++;
        len++;
    }
    res = malloc (sizeof(char *) * (len + 1));
    i = 0;
    j = 0;

    while (i < len)
    {
        if (command[i])
        {
            res[j] = command[i];
            i++;
            j++;
        }
        i++;
    }
    res[j] = NULL;
    return (res);
}

int start_builtin(char **command, char **dirs, char **env)
{
    char *command_dir;
	pid_t	pid;

    command_dir = find_dir_path(command, dirs);
    pid = fork();
    if (pid == 0 && command_dir)
        execve(command_dir, command, env);
    wait(&pid);
    return (1);
}

int start_term(void)
{
    struct  termios term;

    tcgetattr(0, &term); // получаем значения терминала
    term.c_lflag &= ~(ECHO); // пишем в них
    term.c_lflag &= ~(ICANON); // неканонич режим 
    tcsetattr(0, TCSANOW, &term); // записываем обратно в терм
    tgetent(0, "xterm-256color"); // запуск термкапа (аналог - terminfo)
    return (1);
}

int main (int argc, char **argv, char **env)
{
    struct  termios term;
	char    ****new;
    int     ****fd;
    char    **command;
    char    **dirs;
	char	*command_dir;
    char    *line;
    char    temp[2];
    int     i;
    int     j;
    char    str[2000];
    int     len_read;

    char* input;

    line = malloc(1000);
    dirs = ft_strsplit(find_path(env), ':');
    if (!start_term())
        write(1, "term error", 10);
    while (1)
	{
        put_prompt();
        input = readline(" \033[0m\033[33me-bash>\033[0m$ ");
        // line[0] = '\0';
        // while (1)
        // {
        //     str[0] = '\0';
        //     len_read = read(0, str, 100);
        //     if (!ft_strcmp(str, "\e[A"))
        //         printf("previous\n");
        //     else if (!ft_strcmp(str, "\e[B"))
        //         printf("next\n");
        //     else
        //         write(1, str, len_read);
        //     temp[0] = str[0];
        //     temp[1] = '\0';
        //     line = ft_strjoin(line, temp);
        //     if (str[0] =='\n')
        //         break;
        // }
        line = ft_substr(line, 0, ft_strlen(line)-1);
        // printf("input: %s\n", input);
        // printf("line: %s\n", line);
        new = super_split(input, env, &fd);

        i = 0;
        j = 0;
        while (new[j])
        {
            i = 0;
            while (new[j][i])
            {
                command = new[j][i];
                if (!start_own_function(command, env, line))
                    start_builtin(command, dirs, env);
                i++;
            }
            j++;
        }
	}
}


