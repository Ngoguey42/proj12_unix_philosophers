/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 11:06:03 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/20 17:45:13 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>
#include <time.h>
#include <stdlib.h>

void			phi_leave_correctly(t_env *e, int nthrd, int nmutx, char *msg)
{
	e->play = 0;
	phi_quit_mlx(&e->g);
	while (nthrd-- > 7)
		pthread_join(e->tid[nthrd], NULL);
	while (nmutx-- > 7)
		pthread_mutex_destroy(&e->mutex[nmutx]);
	ft_dprintf(2, msg);
	exit(0);
	return ;
}

static void		init_game(t_env *e, t_thread tid[7])
{
	int		i;
	int		err;
	
	i = 0;
	while (i < 7)
		if ((err = pthread_mutex_init(&e->mutex[i++], NULL)))
			phi_leave_correctly(e, 0, i, ERR_INIT_MUTEXES);
	i = 0;
	while (i < 7)
	{
		tid[i].e = e;
		tid[i].id = i;
		e->phi_hp[i] = MAX_LIFE;
		if ((err = pthread_create(&e->tid[i], NULL, &phi_thread_split, &tid[i])))
			phi_leave_correctly(e, i, 7, ERR_CREATE_THREADS);
		i++;
	}
	return ;
}

int				phi_init_env(t_env *e, t_thread tid[7])
{
	ft_bzero(e, sizeof(t_env));
	e->play = 1;
	e->g.redraw = 1;
	if (time(&e->init_time) == (time_t)-1)
		return (ft_putendl_fd("Could not retrieve time", 2), 1);
	e->end_time = e->init_time + TIMEOUT;
	if (phi_init_mlx(e))
		return (1);
	init_game(e, tid);
	return (0);
}
