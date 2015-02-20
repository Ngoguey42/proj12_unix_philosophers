/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 10:12:12 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/20 14:53:11 by ngoguey          ###   ########.fr       */
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
** (usleep/time/read/exit)
*/

/*
** 'main'
**	pass env's pointer
*/

static int		check_defines(void)
{
	if (MAX_LIFE <= 0 || EAT_T <= 0 || REST_T <= 0 || THINK_T <= 0
	|| TIMEOUT <= 0)
		return (1);
	return (0);
}

int				main(void)
{
	t_env		e;
	t_thread	tid[7];

	/* int i; */
	/* for (i = -10; i < 10 ; i++) */
		/* qprintf("%3d R%3d  L%3d\n", i, RIGHT_STICK(i), LEFT_STICK(i)); */
	
	if (check_defines())
		return (1);
	if (phi_init_env(&e, tid))
		return (1);
	phi_pause_mlx(&e);
	return (0);
}
