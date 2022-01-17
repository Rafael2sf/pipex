/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:46:31 by rafernan          #+#    #+#             */
/*   Updated: 2022/01/11 16:46:31 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../libft/libft.h"

typedef struct	s_data
{
	int		ifd;
	char	*outfile;
	char	**cmds;
	char	**envp;
	char	**paths;
}			t_data;

void	px_put_matrix(const char *frmt, const char **matrix);
void	px_free_matrix(char **matrix);
char	**px_mpaths(char **envp);
char	*px_getevar(const char *var, const char **envp);
int		px_close(int count, ...);
int		pipex(int ifd, char **cmds, char **envp, char *outfile);
int		px_exec(int ifd, char **cmd, char **envp, int ofd);
char	**px_newcmd(const char *cmd, char **paths);
t_data	*px_init_pdata(void);