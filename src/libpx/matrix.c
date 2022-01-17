/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:02:02 by rafernan          #+#    #+#             */
/*   Updated: 2021/12/17 18:34:43 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpx.h"

void	px_put_matrix(const char *frmt, const char **matrix)
{
	int		i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		ft_printf(frmt, matrix[i]);
		i++;
	}
}

void	px_free_matrix(char **matrix)
{
	int		i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}
