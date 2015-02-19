/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 11:06:03 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 15:54:39 by wide-aze         ###   ########.fr       */
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
	if (phi_init_mlx(e))
		return (0);
	return (0);
}
