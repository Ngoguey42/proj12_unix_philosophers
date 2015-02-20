/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 11:06:03 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/20 11:05:29 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>
#include <time.h>
#include <stdlib.h>

 void			phi_leave_correctly(t_env *e, int nthread, int nmutexes)
{
	e->play = 0;
	phi_quit_mlx(&e->g);
	while (nthread-- > 7)
		pthread_join(e->tid[nthread], NULL);
	while (nmutexes-- > 7)
		pthread_mutex_destroy(&e->mutex[nmutexes]);
	exit(0);
}

static void		init_game(t_env *e, t_thread tid[7])
{
	int		i;
	int		err;
	
	i = 0;
	while (i < 7)
		if ((err = pthread_mutex_init(&e->mutex[i++], NULL)))
		{
			//print error
			phi_leave_correctly(e, 0, i);
		}
	i = 0;
	while (i < 7)
	{
		tid[i].e = e;
		tid[i].id = i;
		if ((err = pthread_create(&e->tid[i], NULL, &phi_thread_split, &tid[i])))
		{
			//print err
			phi_leave_correctly(e, i, 7);
		}
		i++;
	}
}

int				phi_init_env(t_env *e, t_thread tid[7])
{
	ft_bzero(e, sizeof(t_env));
	e->play = 1;
	e->g.redraw = 1;
	time(&e->saved_time);
	if (phi_init_mlx(e))
		return (1);
	init_game(e, tid);
	return (0);
}
