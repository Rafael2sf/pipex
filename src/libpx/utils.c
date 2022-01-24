/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:54:27 by rafernan          #+#    #+#             */
/*   Updated: 2022/01/14 10:54:27 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpx.h"

char	**px_mpaths(char **envp)
{
	char	*vpath;
	char	**paths;

	paths = NULL;
	vpath = px_getevar("PATH", (const char **)envp);
	if (vpath)
	{
		paths = ft_split(vpath, ": \t\v\b\r\n");
		free(vpath);
	}
	return (paths);
}

// Returns var from envp
char	*px_getevar(const char *var, const char **envp)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(var);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], var, len) == 0)
		{
			j = len;
			while (envp[i][j] && envp[i][j] != '\n')
				j++;
			ret = malloc(sizeof(char) * j + 1);
			if (!ret)
				return (NULL);
			ft_memcpy(ret, &envp[i][len + 1], j);
			ret[j] = '\0';
			return (ret);
		}
		i++;
	}
	return (NULL);
}

/* Allows closing of multiple fds */
int	px_close(int count, ...)
{
	va_list	ap;
	int		ret;
	int		*next_fd;

	ret = 0;
	va_start(ap, count);
	while (count--)
	{
		next_fd = va_arg(ap, int *);
		if (*next_fd > 0 && close(*next_fd) == 0)
		{
			ret++;
			*next_fd = -1;
		}
	}
	va_end(ap);
	return (ret);
}
