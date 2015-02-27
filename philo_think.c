/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:32:06 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/27 15:56:10 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

void			phi_think_start_event(t_env *e, int id)
{
	e->official_s[id] = think;
	e->act_end_time[id] = e->last_time + THINK_T;
	if (e->llock[id] == waited)
		e->llock[id] = think_with;
	if (e->rlock[id] == waited)
		e->rlock[id] = think_with;
	e->stick_state_change = 1;
	return ;
}

void			phi_think_stolen_event(t_env *e, int id, int isright)
{
	pthread_mutex_unlock(&e->mutex[e->think_stick[id]]);
	if (isright)
		e->rlock[id] = stolen;
	else
		e->llock[id] = stolen;
	return ;
}

void			phi_think_end_event(t_env *e, int id)
{
	if (((e->think_stick[id] == P_RSID(id)) ? e->rlock[id]
	: e->llock[id]) != stolen)
		pthread_mutex_unlock(&e->mutex[e->think_stick[id]]);
	e->llock[id] = ignored;
	e->rlock[id] = ignored;
	e->stick_state_change = 1;
	if ((P_LPHP >= P_HP || P_LP_RLOCK(id) == eat_with)
	&& (P_RPHP > P_HP || P_RP_LLOCK(id) == eat_with))
		phi_waiteat_start_event(e, id);
	else
		phi_rest_start_event(e, id);
	return ;
}
