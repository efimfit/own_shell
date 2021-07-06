#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
#include <term.h>
#include <termios.h>

# define BUFFER_SIZE 10

typedef struct s_list
{
	int				fd;
	char			*ostatok;
	struct s_list	*next;
}				t_list;

typedef struct s_data
{
	int 	fd_read;
	int 	fd_write;
	int 	was_redirect;
	int 	type;
	int 	error;
	int 	j;
}			t_data;

typedef struct s_help
{
	int error;
	int help;
}	t_help;

// libft
void			ft_bzero(void *s, int n);
char			*ft_strnew(int size);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
static int		int_len(const char *str, char c);
static int		ft_ln(const char *str, char c);
char			**ft_strsplit(char const *s, char c);
char			*ft_strdup1(char *s1);
int				ft_strcmp(char *s1, char *s2);
char			*ft_substr(char const *s, unsigned int start, int len);

// my_functions
int				my_echo (char **command, char *line);
int				my_cd(char **command);
int				my_pwd (char **command);
int				my_unset (char **command);
int				my_export (char **command);
int				my_env (char **command, char **env);
int				my_exit (char **command);

//GNL
int				get_next_line(int fd, char **line);
int				clear(t_list **list, int fd, char *buf, int code);
t_list			*ft_lstnew(int content);
char			*ft_strchr(char *s, char c);
char			*ft_strdup(char *s, int len);
char			*ft_strjoin(char *s1, char *s2);

//BIG SPLIT
char			***super_split(char *s, char **env, int ****fd, t_help *help);
char			***split_3d(char **new, int ****fd_three);
void			cleaning_3d(char ****all, char **env, int ****fd, t_help *help);

//SPLIT
char			**ft_split(char *s, int *help);
int				count_spaces(char *s, char *c);
int				count_letters(char *s, char *c);
char			**ft_split2(char *s, int w_count, char *c, char **arr);
char			***split_spaces(char **arr, int ****fd_three);

//SPLITE PIPE
char			**ft_split_pipe(char *s, int p_count, char **arr);
int				count_pipe(char *s);
int				count_letters_pipe(char *s);
char			**split_pipes(char *s);


//SPLIT_PRE
//char		    **ft_split_pre(char *s, char *c, int *help2);
//char 			***split_spaces_pre(char **arr, int *help3, int **help2);

//CLEANER
char			*cleaner_semicolon_pipe_space(char *s);
int				into_quotes_cleaner(char *s, int j, char **new);
int				cleaner_other(char *s, t_data *data, char **new, char **env);
void			cleaner(char **s, t_help *help, char **env, int ****fd);
int				main_cleaning(char *s, char **new, char **env, t_data *data);


//REDIRECT
void			next_redirect(char *s, char **env, t_data *data, char sign);
int				current_redirect(char *s, int j, char **env, t_data *data);
void			clean_filename(int i, t_data *data, char **new);
void			set_data(t_data *data, int ****fd, int i, t_help *help);
void			open_close(t_data *data, char *filename);
void			heredoc(char *limiter);

//PRE PARSER
int				check_empty_redirect(char **arr, t_help *help);
int				check_empty_commands(char **arr, t_help *help);
int				check_opened_quotes(char **array, t_help *help);
int				pre_parser(char *s, t_help *help);
int				into_check_empty_redirect(char *s, int j, t_help *help);

//PRE_CLEANER
int				pre_cleaner(char **s);
int				into_pre_cleaner(char *s, int j, int *quotes);
char			*join_char(char *s, char c);

//CLEANER_UTILS
char			*search_env(char *dollar, char **env);
int				ft_strncmp_env(char *s1, char *s2, int *j);
int				into_dollar(char *s, char **new, t_data *data, char **env);
int				into_dollar2(char *s, int j, char **new, char **env);

//FREEDOMS
void			freedom_2d(char **arr);
void			freedom_3d(char ***arr);
void			freedom_4d(char ****arr);
void			freedom_2d_int(int **arr);
void			freedom_3d_int(int ***arr);

//UTILS
int				into_quotes(char *s, int i);
void			skip_spaces(char *line, int *i);
int				ft_strlen(char *s);
int				count_spaces_help(char *s, int i, int *w_count, char *c);
int				**create_2d(int help);



#endif