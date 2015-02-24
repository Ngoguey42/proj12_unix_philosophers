/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 10:38:03 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/24 09:50:27 by ngoguey          ###   ########.fr       */
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
			phi_leave_correctly(e, 0, i, (char*)sys_errlist[err]);
	}
	return ;
}

static void		init_philosophers(t_env *e, t_thread tid[7])
{
	int		i;
	int		err;

	i = -1;
	while (++i < 7)
	{
		tid[i].e = e;
		tid[i].id = i;
		e->phi_hp[i] = MAX_LIFE;
		e->official_s[i] = start;
		e->act_end_time[i] = 0;
		e->eating_delta[i] = 1;
		e->llock[i] = ignored;
		e->rlock[i] = ignored;
		e->r_asked[i] = 0;
		e->l_asked[i] = 0;
	}
	i = -1;
	while (++i < 7)
		if ((err = pthread_create(&e->tid[i], NULL, &phi_thread_split,
				&tid[i])))
			phi_leave_correctly(e, i, 7, (char*)sys_errlist[err]);
	return ;
}

int				phi_init_env(t_env *e, t_thread tid[7])
{
	ft_bzero(e, sizeof(t_env));
	e->play = 1;
	e->g.redraw = 1;
	if (phi_init_mlx(e))
		return (1);
	if (time(&e->last_time) == (time_t) - 1)
		phi_leave_correctly(e, 0, 0, "Could not retrieve time\n");
	e->end_time = e->last_time + TIMEOUT + 1;
	e->init_time = e->last_time;
	init_sticks(e);
	init_philosophers(e, tid);
	return (0);
}
