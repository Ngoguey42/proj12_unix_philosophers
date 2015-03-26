/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:32:06 by wide-aze          #+#    #+#             */
/*   Updated: 2015/03/26 08:48:23 by ngoguey          ###   ########.fr       */
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
	if (CAN_WAIT_TO_EAT)
		phi_can_wait_to_eat_pick(e, id);
	else
		phi_cant_wait_to_eat_pick(e, id);
	return ;
}
