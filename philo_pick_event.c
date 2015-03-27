/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pick_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/26 08:08:26 by ngoguey           #+#    #+#             */
/*   Updated: 2015/03/26 09:20:11 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

void						phi_can_wait_to_eat_pick(t_env *e, int id)
{
	if ((P_LPHP >= P_HP || P_LP_RLOCK(id) == eat_with)
		&& (P_RPHP > P_HP || P_RP_LLOCK(id) == eat_with))
		phi_waiteat_start_event(e, id);
	else
		phi_rest_start_event(e, id);
	return ;
}

void						phi_cant_wait_to_eat_pick(t_env *e, int id)
{
	// rest
	// wait think
	// think
	// eat
	if (!pthread_mutex_trylock(&e->mutex[P_LSID(id)]))
	{
		e->llock[id] = eat_with;
		if (!pthread_mutex_trylock(&e->mutex[P_RSID(id)]))
		{
			e->rlock[id] = eat_with;
			phi_waiteat_start_event(e, id);
			return ;
		}
		if (e->official_s[P_RPID(id)] == think ||
				e->official_s[P_RPID(id)] == wthink)
		{
			phi_waiteat_start_event(e, id);
			return ;
		}
		e->llock[id] = think_with;
		e->think_stick[id] = P_LSID(id);
		phi_waitthink_start_event(e, id);
		return ;
	}
	phi_rest_start_event(e, id);
	return ;
}
