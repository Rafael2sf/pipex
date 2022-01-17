/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:46:12 by rafernan          #+#    #+#             */
/*   Updated: 2022/01/11 16:46:12 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libpx/libpx.h"

static char	**px_hndl_cmds(char **argv);

int		main(int argc, char **argv, char **envp)
{
	int		ret;
	int		ifd;
	char	**cmds;

	ret = 1;
	if (argc != 5)
	{
		write(STDERR_FILENO, "Usage: ./prog file1 cmd1 cmd2 file2\n", 37);
		return (1);
	}
	ifd = open(argv[1], O_RDONLY);
	if (ifd == -1)
		perror(argv[1]);
	cmds = px_hndl_cmds(argv);
	if (cmds)
	{
		ret = pipex(ifd, cmds, envp, argv[argc - 1]);
		free(cmds);
	}
	else
		perror("");
	close(ifd);
	return (ft_abs(ret));
}

static char	**px_hndl_cmds(char **argv)
{
	char	**cmdl;

	cmdl = (char **)malloc(sizeof(char *) * 3);
	if (!cmdl)
		return (NULL);
	cmdl[0] = argv[2];
	cmdl[1] = argv[3];
	cmdl[2] = NULL;
	return (cmdl);
}
