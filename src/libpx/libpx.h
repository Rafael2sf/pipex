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

#ifndef LIBPX_H
# define LIBPX_H

# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"

/* Will hold all the necessary data for the project */
typedef struct s_data
{
	int		ifd;
	char	*outfile;
	char	**cmds;
	char	**envp;
	char	**paths;
}			t_data;

/* Similar to ft_split except it splits strings on spaces and semi-colons */
char	**px_split(const char *s);
/* Displays a string matrix */
void	px_put_matrix(const char *frmt, const char **matrix);
/* Free all the allocated memory of a matrix */
void	px_free_matrix(char **matrix);
/* Returns a matrix of the separated paths by : of path envp */
char	**px_mpaths(char **envp);
/* Returns the value of a variable from envp */
char	*px_getevar(const char *var, const char **envp);
/* Closes multiple files, passed by adress changing the value of the int * */
int		px_close(int count, ...);
/* Collects all the necessary data, and calls exec in a loop */
int		pipex(int ifd, char **cmds, char **envp, char *outfile);
/* Executed a cmd, reading from ifd and writing to ofd */
int		px_exec(int ifd, char **cmd, char **envp, int ofd);
/* Generated a new cmd matrix from a string */
char	**px_newcmd(const char *cmd, char **paths);
/* Initialises the data sturct */
t_data	*px_init_pdata(void);

#endif
