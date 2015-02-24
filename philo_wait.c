;;/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:31:40 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/24 09:36:16 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

/*
** les fonctions start doivent etre betes, 
** les fonctions end prennent les decisions,
*/

void			phi_waiteat_start_event(t_env *e, int id)//callable en next
{
	(void)e; (void)id;

	//request les baguettes aux voisins
	//lock les mutexes
	//phi_wait_end_event(e, id);
}

void			phi_waiteat_end_event(t_env *e, int id)//called after mutex
{
	//equivalent de On_Mutex_locked
	
	//phi_eat_start_event(e, id);
	(void)e; (void)id;
}

void			phi_waitthink_start_event(t_env *e, int id)//callable en next
{
	(void)e; (void)id;
}

void			phi_waitthink_end_event(t_env *e, int id)//called after mutex
{
	(void)e; (void)id;
}
