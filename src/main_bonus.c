/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:19:32 by rafernan          #+#    #+#             */
/*   Updated: 2022/01/17 13:19:32 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpx/libpx_bonus.h"

static char	**px_hndl_cmds(int argc, char **argv);
static int	px_hndl_ifd(int argc, char **argv);

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	int		ifd;
	char	**cmds;

	ret = 1;
	if (argc < 5)
	{
		write(2, "Usage:\t./prog file1 cmd1...cmdn file2\n", 39);
		write(2, "\t./prog here_doc DELIMITER cmd1...cmdn file2\n", 46);
		return (1);
	}
	ifd = px_hndl_ifd(argc, argv);
	cmds = px_hndl_cmds(argc, argv);
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

static char	**px_hndl_cmds(int argc, char **argv)
{
	char	**cmdl;
	int		i;

	i = 0;
	cmdl = (char **)malloc(sizeof(char *) * argc - 2);
	if (!cmdl)
		return (NULL);
	while (i + 2 != argc)
	{
		cmdl[i] = argv[i + 1];
		i++;
	}
	cmdl[i] = NULL;
	return (cmdl);
}

static int	px_hndl_ifd(int argc, char **argv)
{
	int	ifd;

	ifd = -1;
	if (ft_strncmp("here_doc", argv[1], 8) != 0)
	{
		ifd = open(argv[1], O_RDONLY);
		if (ifd == -1)
			perror(argv[1]);
	}
	else
	{
		ifd = px_heredoc(argv[2], argc - 4);
		if (ifd == -1)
			perror("");
	}
	return (ifd);
}
