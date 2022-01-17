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

#include "libpx_bonus.h"

static int	px_execve(t_data *pdata, int i);
static int	px_exec_out(int fd, char **cmd, t_data *pdata);
static int	px_ewait(t_data *pdata, int pid, int i);
static int	px_eexit(int val, t_data *pdata);

int	pipex(int ifd, char **cmdv, char **envp, char *outfile)
{
	t_data	*pdata;
	int		ret;
	int		i;

	i = 1;
	pdata = px_init_pdata();
	if (!pdata)
	{
		perror("");
		return (-1);
	}
	(pdata->ifd) = ifd;
	(pdata->outfile) = outfile;
	(pdata->envp) = envp;
	(pdata->cmds) = cmdv;
	(pdata->paths) = px_mpaths(envp);
	if (ft_strncmp("here_doc", cmdv[0], 8) == 0)
	{
		(pdata->here_doc) = 1;
		i = 2;
	}
	px_put_matrix("- %s\n", (const char **)cmdv);
	ret = px_execve(pdata, i);
	free(pdata);
	return (ret);
}

static int	px_execve(t_data *pdata, int i)
{
	char	**cmd;
	int		fd;

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

	if (pdata->here_doc == 1)
		ofd = open(pdata->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
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
		if (pdata->here_doc == 0)
			unlink(pdata->outfile);
		ofd = open(pdata->outfile, O_CREAT, 0644);
		if (ofd == -1)
			perror(pdata->outfile);
		else
			close(ofd);
		return (-1);
	}
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
