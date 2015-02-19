/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 11:06:03 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 15:09:53 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

int			phi_init_env(t_env *e)
{
	int		i;

	ft_bzero(e, sizeof(t_env));
	i = 0;
	while (i < 7)
		pthread_mutex_init(&e->mutex[i++], NULL);
	e->play = 1;
	e->g.redraw = 1;
	D(int, e->play);
	if (phi_init_mlx(e))
		return (0);
	return (0);
}
