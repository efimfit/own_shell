#include "minishell.h"

int pre_cleaner(char **s)
{
	int i;
	int j;
	int quotes;

	i = -1;
	while(s[++i])
	{
//		printf("small string: [%s]\n", s[i]);
		quotes = 0;
		j = 0;
		skip_spaces(s[i], &j);
		while(s[i][j])
		{
			j = into_pre_cleaner(s[i], j, &quotes);
			if (!s[i][j])
				break;
			j++;
		}
		if (quotes)
			return (1);
	}
	return (0);
}

int into_pre_cleaner(char *s, int j, int *quotes)
{
	char q;

	while (s[j] != '"' && s[j] != '\'' && s[j])
	{
		if (s[j] == '\\' && s[j + 1])
			j++;
		j++;
	}
	if (s[j] == '"' || s[j] == '\'')
	{
		(*quotes)++;
		q = s[j++];
		while (s[j] != q && s[j])
		{
			if (s[j] == '\\' && q == '"' &&
				(s[j+1] == '\\' || s[j+1] == '"'))
				j++;
			j++;
		}
		if ((s[j] == '"' && q == '"') ||
			(s[j] == '\'' && q =='\''))
			(*quotes)--;
	}
	return (j);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*new;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	new = (char *)malloc((i + 1) + 1);
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	new[i++] = c;
	new[i] = '\0';
	return (new);
}

char *join_char(char *s, char c)
{
	char *new;

	if (!s)
		return (NULL);
	new = ft_strjoin_char(s, c);
		free(s);
	return (new);

}
