/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khouten <khouten@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:19:45 by khouten           #+#    #+#             */
/*   Updated: 2020/12/03 16:19:47 by khouten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

# define BUFFER_SIZE 10

typedef struct	s_list
{
	int				fd;
	char			*ostatok;
	struct s_list	*next;
}				t_list;

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

int 			my_echo (char **command, char *line);
int 			my_cd(char **command);
int 			my_pwd (char **command);
int 			my_unset (char **command);
int 			my_export (char **command);
int 			my_env (char **command, char **env);
int 			my_exit (char **command);

//GNL
int				get_next_line(int fd, char **line);
int				clear(t_list **list, int fd, char *buf, int code);
t_list			*ft_lstnew(int content);
char			*ft_strchr(char *s, char c);
char			*ft_strdup(char *s, int len);
char			*ft_strjoin(char *s1, char *s2);

//BIG SPLIT
char 			****super_split(char *s, char **env, int *****fd);
char			****split_4d(char ***new, int *****fd_four);

//SPLIT
char			**ft_split(char *s, int *help2);
int 			count_spaces(char *s, char *c);
int 			count_letters(char *s, char *c);
char			**ft_split2(char *s, int w_count, char *c, char **arr);
char 			***split_spaces(char **arr, int *help3, int **help2);
int				 count_spaces_help(char *s, int i, int *w_count, char *c);


//SPLITE PIPE
char			**ft_split_pipe(char *s);
char			**ft_split2_pipe(char *s, int p_count, char **arr);
int 			count_pipe(char *s);
int 			count_letters_pipe(char *s);
char 			***split_pipes(char **arr);

//SPLIT_SEMI
int 			into_semicolon(char *s, int i);
char 			**split_semicolon(char *s);
int 			w_count(char *s);

//SPLIT_PRE
//char		    **ft_split_pre(char *s, char *c, int *help2);
//char 			***split_spaces_pre(char **arr, int *help3, int **help2);

//CLEANER
char 			*cleaner_semicolon_pipe(char *s);
int 			into_quotes_cleaner(char *s, int *j, char **new, char **env);
int 			into_redirect(char **s, int i, int j, char **new);
int 			into_cleaner(char **s, int i, int j, char **new, char **env);
int 			cleaner(char **s, char **env);

//PRE PARSER
int 			check_empty_redirect(char **arr);
int 			check_empty_commands(char **arr);
int 			check_opened_quotes(char **array);
int 			pre_parser(char **arr);
int				into_check_empty_redirect(char *s,  int j);

//PRE_CLEANER
int 			pre_cleaner(char **s);
int 			into_pre_cleaner(char *s, int j, int *quotes);
char			*ft_strjoin_char(char *s1, char c);
char 			*join_char(char *s, char c);


//UTILS
int 			into_quotes(char *s, int i);
void			skip_spaces(char *line, int *i);
int				ft_strlen(char *s);

//UTILS2
char 			*search_env(char *dollar, char **env);
int				ft_strncmp_env(char *s1, char *s2, int n, int *j);
int 			into_dollar(char *s, char **new, int *j, char **env);
int 			into_dollar2(char *s, int *j, char **new, char **env);

//UTILS3
int 			**create_two(int help);
int				 ***create_three(int help3, int *help2);

//UTILS4
void			freedom_2d(char **arr);
void 			freedom_3d(char ***arr);



#endif