/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 10:12:12 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 12:11:47 by wide-aze         ###   ########.fr       */
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

int		main(void)
{
	t_env	e;

	if (phi_init_env(&e))
		return (1);
	return (0);
}
