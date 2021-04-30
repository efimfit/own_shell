# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>

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


char	*get_env_var(char *var, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_strstartswith(env[i], tmp))
		{
			free(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}


void	proc_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, proc_signal_handler);
	}
}

static int		run_cmd(char *path, char **command, char **env)
{
	pid_t	pid;

	pid = fork();
	// signal(SIGINT, proc_signal_handler);
	if (pid == 0)
		execve(path, command, env);
	else if (pid < 0)
	{
		free(path);
		ft_putstr("Fork failed to create a new process.");
		return (-1);
	}
	wait(&pid);
	if (path)
		free(path);
	return (1);
}

int main (int argc, char **argv, char **env)
{
    char dir[4096];

	int		r;
	char	*line;
    char    **command;
	char	*bin_path;


    int i = -1;

    getcwd(dir, 4096);

    ft_putstr(dir);
    ft_putstr(" \033[0m\033[33msh>\033[0m$ ");

    
	line = NULL;
	r = get_next_line(&line);
   	command = ft_strsplit(line, ' ');

    char    *path;
	path = "/bin";
    
    bin_path = ft_pathjoin(path, command[0]);
    run_cmd(bin_path, command, env);

    free(line);
    line = NULL;
}