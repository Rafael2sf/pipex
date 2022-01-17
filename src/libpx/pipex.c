/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:53:29 by rafernan          #+#    #+#             */
/*   Updated: 2022/01/11 17:53:29 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpx.h"

static int	px_execve(t_data *pdata);
static int	px_exec_out(int fd, char **cmd, t_data *pdata);
static int	px_ewait(t_data *pdata, int pid, int i);
static int	px_eexit(int val, t_data *pdata);

int	pipex(int ifd, char **argv, char **envp, char *outfile)
{
	t_data	*pdata;
	char	**paths;
	int		ret;

	pdata = px_init_pdata();
	if (!pdata)
	{
		perror("");
		return (-1);
	}
	paths = px_mpaths(envp);
	(pdata->ifd) = ifd;
	(pdata->outfile) = outfile;
	(pdata->envp) = envp;
	(pdata->cmds) = argv;
	(pdata->paths) = paths;
	ret = px_execve(pdata);
	free(pdata);
	return (ret);
}

static int	px_execve(t_data *pdata)
{
	char	**cmd;
	int		i;
	int		fd;

	i = 0;
	fd = dup(pdata->ifd);
	while (pdata->cmds[i])
	{
		cmd = px_newcmd(pdata->cmds[i], pdata->paths);
		if (cmd)
		{
			if (pdata->cmds[i + 1])
				fd = px_exec(fd, cmd, pdata->envp, -1);
			else
				fd = px_exec_out(fd, cmd, pdata);
			px_free_matrix(cmd);
			if (fd == -1)
				px_eexit(1, pdata);
		}
		else
			px_close(1, &fd);
		i++;
	}
	return (px_ewait(pdata, fd, i));
}

static int	px_exec_out(int fd, char **cmd, t_data *pdata)
{
	int	ofd;
	int	ret;

	ofd = open(pdata->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ofd == -1)
		return (-1);
	ret = px_exec(fd, cmd, pdata->envp, ofd);
	close(ofd);
	return (ret);
}

static int	px_ewait(t_data *pdata, int pid, int i)
{
	int	wstat;
	int	ofd;

	if (pid >= 0)
		waitpid(pid, &wstat, 0);
	while (i-- > 1)
	{
		if (wait(NULL) == -1)
			break ;
	}
	if (pid < 0)
	{
		unlink(pdata->outfile);
		ofd = open(pdata->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (ofd == -1)
			perror(pdata->outfile);
		else
			close(ofd);
		return (-1);
	}
	//printf("wstat: %d\n", wstat);
	return (wstat);
}

static int	px_eexit(int val, t_data *pdata)
{
	perror("");
	close(pdata->ifd);
	free(pdata->cmds);
	px_free_matrix(pdata->paths);
	free(pdata);
	exit(val);
}
