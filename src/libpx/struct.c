/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:27:28 by rafernan          #+#    #+#             */
/*   Updated: 2022/01/14 10:27:28 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpx.h"

t_data	*px_init_pdata(void)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (new)
	{
		(new->ifd) = -1;
		(new->outfile) = NULL;
		(new->cmds) = NULL;
		(new->envp) = NULL;
		(new->paths) = NULL;
		return (new);
	}
	return (NULL);
}
