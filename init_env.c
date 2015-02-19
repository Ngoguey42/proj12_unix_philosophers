/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 11:06:03 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 17:43:51 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>
#include <time.h>

static void		init_game(t_env *e, t_thread tid[7])
{
	int		i;

	i = 0;
	while (i < 7)
	{
		tid[i].e = e;
		tid[i].id = i;
		pthread_create(&e->tid[i], NULL, &phi_thread_split, &tid[i]);
		i++;
	}
}

int				phi_init_env(t_env *e, t_thread tid[7])
{
	int		i;

	ft_bzero(e, sizeof(t_env));
	i = 0;
	while (i < 7)
		pthread_mutex_init(&e->mutex[i++], NULL);
	time(&e->saved_time);
	e->play = 1;
	e->g.redraw = 1;
	D(int, e->play);
	init_game(e, tid);
	if (phi_init_mlx(e))
		return (0);
	return (0);
}
