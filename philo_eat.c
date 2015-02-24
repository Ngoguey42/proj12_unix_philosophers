/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:23:23 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/24 09:27:28 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

/*
** les fonctions start doivent etre betes, 
** les fonctions end prennent les decisions,
*/

void			phi_eat_start_event(t_env *e, int id)
{
	//set act_end_time
	//set eating_delta
	
	/* e->eating_delta[id] = (HP_MAX - e->phi_hp[id]) / EAT_T; */
	//set les llock && rlock && official_s
	(void)e; (void)id;
}
void			phi_eat_end_event(t_env *e, int id)//callable depuis W
{
	//set self->hp to HP_MAX
	//phi_rest_start_event(e, id);
	(void)e; (void)id;
}
