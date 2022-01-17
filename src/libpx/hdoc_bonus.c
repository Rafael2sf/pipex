/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:24:29 by rafernan          #+#    #+#             */
/*   Updated: 2022/01/17 14:24:29 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpx_bonus.h"

static void	px_read_heredoc(const char *delimitir, int dlen, int fd, int npipe);

int	px_heredoc(const char *delimitir, int npipe)
{
	int		p[2];
	int		dlen;

	dlen = ft_strlen(delimitir);
	if (dlen <= 0)
		return (-1);
	if (pipe(p) < 0)
		return (-1);
	px_read_heredoc(delimitir, dlen, p[1], npipe);
	close(p[1]);
	return (p[0]);
}

static void	px_read_heredoc(const char *delimitir, int dlen, int fd, int npipe)
{
	char	*line;
	int		len;
	int		j;

	while (1)
	{
		j = 0;
		while (j++ < npipe)
			ft_putstr(STDOUT_FILENO, "pipe ");
		ft_putstr(STDOUT_FILENO, "heredoc> ");
		line = ft_getnl(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, delimitir, dlen) == 0
			&& line[dlen] == '\n')
		{
			free(line);
			break ;
		}
		len = ft_strlen(line);
		write(fd, line, sizeof(char) * len);
		free(line);
	}
}
