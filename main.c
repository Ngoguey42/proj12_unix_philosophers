/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 10:12:12 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 14:25:41 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

/*
** Authorized functions:
** free, malloc, write  (NO exit)
** pthread_create
** pthread_detach
** pthread_join
** pthread_mutex_init
** pthread_mutex_destroy
** pthread_mutex_trylock
** pthread_mutex_lock
** pthread_mutex_unlock
*/

/*
** 'main'
**	pass env's pointer
*/

static void		init_game(t_env *e, t_thread tid[7])
{
	int		i;

	i = 0;
	while (i < 7)
	{
		tid[i]->e = e;
		tid[i]->id = i;
 		pthread_create(e->thread[i], NULL, &phi_thread_split, t_thread[i]);
		i++;
	}
}

int				main(void)
{
	t_env		e;
	t_thread	tid[7];

	if (check_defines())
		return (1);
	if (phi_init_env(&e, tid))
		return (1);
	init_game(&e);
	return (0);
}
