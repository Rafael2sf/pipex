/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:05:44 by rafernan          #+#    #+#             */
/*   Updated: 2022/01/24 12:03:44 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpx.h"

static int	px_split_len(char *s);
static int	px_split_len_smc(char *s, int *i, int *j);
static void	px_split2(char **mt, char *s, int len);
static void	px_split2_helper(char *s, int *i);

/* Allocate array and verify size */
char	**px_split(const char *s)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	if (!s || !*s)
		return (NULL);
	size = px_split_len((char *)s);
	if (size < 1)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * size + 1);
	if (!ret)
		return (NULL);
	px_split2(ret, (char *)s, size);
	return (ret);
}

/* Returns the size of the ** array */
static int	px_split_len(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (ft_is(s[i], " \t\n\v\f\r"))
			i++;
		if (s[i] == '\'')
			px_split_len_smc(s, &i, &j);
		else if (s[i])
		{
			j++;
			while (s[i] && !ft_is(s[i], " \t\n\v\f\r") && s[i] != '\'')
				i++;
		}
	}
	return (j);
}

/* handles semicolon */
static int	px_split_len_smc(char *s, int *i, int *j)
{
	(*i)++;
	while (s[*i] && s[*i] != '\'')
			(*i)++;
	if (!s[*i])
		return (1);
	(*j)++;
	(*i)++;
	return (1);
}

/* Allocates and sets each string */
static void	px_split2(char **mt, char *s, int len)
{
	int	i;
	int	j;

	j = 0;
	while (*s && j < len)
	{
		while (ft_is(*s, " \t\n\v\f\r"))
			s++;
		i = 0;
		px_split2_helper(s, &i);
		mt[j] = (char *)malloc(sizeof(char) * i + 1);
		if (!mt[j])
			return ;
		ft_strlcpy(mt[j], s, i + 1);
		s += i;
		j++;
	}
	mt[j] = NULL;
}

static void	px_split2_helper(char *s, int *i)
{
	while (s[*i] && !ft_is(s[*i], " \t\n\v\f\r"))
	{
		if (s[*i] == '\'')
		{
			if (*i != 0)
				break ;
			(*i)++;
			while (s[*i] && s[*i] != '\'')
				(*i)++;
			if (s[*i] == '\'')
			{
				(*i)++;
				break ;
			}
		}
		else
			(*i)++;
	}
}
