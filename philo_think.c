/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:32:06 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/27 14:31:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

/*
** les fonctions start doivent etre betes,
** les fonctions end prennent les decisions,
*/

void			phi_think_start_event(t_env *e, int id)
{
	e->official_s[id] = think;
	e->act_end_time[id] = e->last_time + THINK_T;
	if (e->llock[id] == waited)
		e->llock[id] = think_with;
	if (e->rlock[id] == waited)
		e->rlock[id] = think_with;
	e->stick_state_change = 1;
// qprintf("%d  think process OK\n", id);
	return ;
}

void			phi_think_stolen_event(t_env *e, int id, int isright)
{
//	qprintf("%d was stoled from his %d\n", id, e->think_stick[id]);
	int err;
	err = pthread_mutex_unlock(&e->mutex[e->think_stick[id]]);
	qprintf("(%d) was stolen from mutex %s %d {%d}\n", id,
			isright ? "RIGHT" : "LEFT"
			, isright ? P_RSID(id) : P_LSID(id), err);
	if (isright)
		e->rlock[id] = stolen;
	else
		e->llock[id] = stolen;
	return ;
}

void			phi_think_end_event(t_env *e, int id)//callable depuis W
{
	int err;


	if (((e->think_stick[id] == P_RSID(id)) ? e->rlock[id] : e->llock[id]) != stolen)

	{
	err = pthread_mutex_unlock(&e->mutex[e->think_stick[id]]);
	qprintf("(%d) released mutex %d {%d}\n", id,
			e->think_stick[id]
			, err);
	}
	/* pthread_mutex_unlock(&e->mutex[e->think_stick[id]]); */
	e->llock[id] = ignored;
	e->rlock[id] = ignored;
	e->stick_state_change = 1;
	/* if (P_LPHP >= P_HP && P_RPHP > P_HP) */
    if (
		(P_LPHP >= P_HP || P_LP_RLOCK(id) == eat_with)
		        &&
		(P_RPHP > P_HP || P_RP_LLOCK(id) == eat_with)
		)
		phi_waiteat_start_event(e, id);
	else
		phi_rest_start_event(e, id);
		/* e->official_s[id] = rest; */
	return ;
}
