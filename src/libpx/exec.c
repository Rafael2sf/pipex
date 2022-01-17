/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:12:01 by rafernan          #+#    #+#             */
/*   Updated: 2022/01/11 19:12:01 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpx.h"

static int	px_hndl_parent(int ifd, int *p, int pid, int ofd);
static int	px_hndl_child(int ifd, char **cmd, char **envp, int ofd);
static int	px_epipe(void);

int	px_exec(int ifd, char **cmd, char **envp, int ofd)
{
	int	p[2];
	int	pid;

	if  (pipe(p) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		px_close(2, &p[0], &p[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(p[0]);
		if (ofd > 0)
		{
			close(p[1]);
			return (px_hndl_child(ifd, cmd, envp, ofd));
		}
		else
			return (px_hndl_child(ifd, cmd, envp, p[1]));
	}
	return (px_hndl_parent(ifd, (int *)p, pid, ofd));
}

static int	px_hndl_parent(int ifd, int *p, int pid, int ofd)
{	
	close(ifd);
	close(p[1]);
	if (ofd < 0)
		return (p[0]);
	close(p[0]);
	return (pid);
}

static int	px_hndl_child(int ifd, char **cmd, char **envp, int ofd)
{
	if (ifd < 0)
		ifd = px_epipe();
	if (ifd == -1)
	{
		close(ofd);
		return (-1);
	}
	if (dup2(ifd, STDIN_FILENO) == -1)
	{
		close(ifd);
		close(ofd);
		return (-1);
	}
	if (dup2(ofd, STDOUT_FILENO) == -1)
	{
		close(ifd);
		close(STDIN_FILENO);
		return (-1);
	}
	execve(cmd[0], cmd, envp);
	return (-1);
}

static int	px_epipe(void)
{
	int	p[2];

	if (pipe(p) == -1)
		return (-1);
	close(p[1]);
	return (p[0]);
}