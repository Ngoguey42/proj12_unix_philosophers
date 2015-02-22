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
#include <stdio.h> //sys_errlist

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

static void		init_sticks(t_env *e)
{
	int		i;
	int		err;

	i = 0;
	while (i < 7)
	{
		e->own_type[i] = available;
		e->owner[i] = -1;
		if ((err = pthread_mutex_init(&e->mutex[i++], NULL)))
			phi_leave_correctly(e, 0, i, sys_errlist[err]);
	}
	return ;
}

static void		init_philosophers(t_env *e, t_thread tid[7])
{
	int		i;
	int		err;

	i = 0;
	while (i < 7)
	{
		tid[i].e = e;
		tid[i].id = i;
		e->phi_hp[i] = MAX_LIFE;
		e->official_s[i] = start;
		e->act_end_time[i] = 0;
		e->eating_delta[i] = 1;
		e->llock[i] = ignoring;
		e->rlock[i] = ignoring;
		if ((err = pthread_create(&e->tid[i], NULL, &phi_thread_split, &tid[i])))
			phi_leave_correctly(e, i, 7, sys_errlist[err]);
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
	e->last_time = e->init_time;
	if (phi_init_mlx(e))
		return (1);
	init_sticks(e, tid);
	init_philosophers(e, tid);
	return (0);
}
