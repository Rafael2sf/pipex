/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:30:54 by rafernan          #+#    #+#             */
/*   Updated: 2021/12/17 18:34:07 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpx.h"

static char	*px_srchfp(char	*fname, char **paths);
static char	*px_strpath(const char *path, const char *file);

// Generates a new cmd for execve from a string and a search path list
char	**px_newcmd(const char *cmd, char **paths)
{
	char	**cmdv;
	char	*fp;

	if (!cmd || !*cmd)
	{
		ft_putstr(STDERR_FILENO, "command not found\n");
		return (NULL);
	}
	cmdv = ft_split(cmd, " ");
	if (!cmdv)
		return (NULL);
	fp = px_srchfp(cmdv[0], paths);
	if (!fp)
	{
		ft_putstr(STDERR_FILENO, "command not found: ");
		ft_putstr(STDERR_FILENO, cmdv[0]);
		ft_putchar(STDERR_FILENO, '\n');
		px_free_matrix(cmdv);
		return (NULL);
	}
	free(cmdv[0]);
	cmdv[0] = fp;
	return (cmdv);
}

/* Searches for a file in a matrix of paths */
static char	*px_srchfp(char	*fname, char **paths)
{
	char	*fp;
	int		i;

	i = 0;
	if (access(fname, F_OK | X_OK) == 0)
		return (ft_strdup(fname));
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		fp = px_strpath(paths[i], fname);
		if (access(fp, F_OK | X_OK) == 0)
			return (fp);
		if (fp)
			free(fp);
		i++;
	}
	return (NULL);
}

/* Joins a filename with a path */
static char	*px_strpath(const char *path, const char *file)
{
	char	*new;
	int		extra;
	int		plen;
	int		flen;

	extra = 0;
	plen = ft_strlen(path);
	flen = ft_strlen(file);
	if (file[0] != '/')
		extra++;
	new = malloc(sizeof(char) * (plen + flen + extra + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, path, plen);
	if (extra == 1)
		new[plen] = '/';
	ft_memcpy(new + plen + extra, file, flen);
	new[plen + flen + extra] = '\0';
	return (new);
}
