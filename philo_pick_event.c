/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pick_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/26 08:08:26 by ngoguey           #+#    #+#             */
/*   Updated: 2015/03/27 09:20:52 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

#define PRIO_HP_LEFT (P_LPHP >= P_HP || P_LP_RLOCK(id) == eat_with)
#define PRIO_HP_RIGHT (P_RPHP > P_HP || P_RP_LLOCK(id) == eat_with)
#define PRIO_HP (PRIO_HP_LEFT && PRIO_HP_RIGHT)

void						phi_can_wait_to_eat_pick(t_env *e, int id)
{
	if (PRIO_HP)
		phi_waiteat_start_event(e, id);
	else
		phi_rest_start_event(e, id);
	return ;
}

static void					lock_to_eat_right_first(t_env *e, int id)
{
	e->rlock[id] = waited;
	e->llock[id] = ignored;
	e->official_s[id] = weat; // ou wthink ?
	pthread_mutex_lock(&e->mutex[P_RSID(id)]);
	e->rlock[id] = eat_with;
	if (!pthread_mutex_trylock(&e->mutex[P_LSID(id)]))
	{
		e->llock[id] = eat_with;
		phi_waiteat_start_event(e, id); 
		return ;// eating ok
	}
	if (e->official_s[P_LPID(id)] == think ||
		e->official_s[P_LPID(id)] == wthink)
	{
		phi_waiteat_start_event(e, id);
		return ;// request and eat
	}
	//merde
	e->rlock[id] = think_with;
	e->think_stick[id] = P_RSID(id);
	phi_waitthink_start_event(e, id);
	
	return ;
}

static void					lock_to_eat_left_first(t_env *e, int id)
{
	e->llock[id] = waited;
	e->rlock[id] = ignored;
	e->official_s[id] = weat; // ou wthink ?
	pthread_mutex_lock(&e->mutex[P_LSID(id)]);
	e->llock[id] = eat_with;
	if (!pthread_mutex_trylock(&e->mutex[P_RSID(id)]))
	{
		e->rlock[id] = eat_with;
		phi_waiteat_start_event(e, id); 
		return ;// eating ok
	}
	if (e->official_s[P_RPID(id)] == think ||
		e->official_s[P_RPID(id)] == wthink)
	{
		phi_waiteat_start_event(e, id);
		return ;// request and eat
	}
	//merde
	e->llock[id] = think_with;
	e->think_stick[id] = P_LSID(id);
	phi_waitthink_start_event(e, id);
	
	return ;
}



void						phi_cant_wait_to_eat_pick(t_env *e, int id)
{
	if (PRIO_HP)
	{
		if (
			(P_RP_LLOCK(id) == eat_with) &&
			(
				(P_LP_RLOCK(id) != eat_with) ||
				(P_LP_RLOCK(id) == eat_with && P_RPHP >= P_LPHP)
				)
			) //start by locking right
			lock_to_eat_right_first(e, id);
		else
			lock_to_eat_left_first(e, id);
	}
	else
	{
		if (REST_T <= THINK_T)
			phi_rest_start_event(e, id);
		else if (!pthread_mutex_trylock(&e->mutex[P_LSID(id)]))
		{
			e->llock[id] = think_with;
			e->think_stick[id] = P_LSID(id);
			phi_waitthink_start_event(e, id);
		}
		else if (!pthread_mutex_trylock(&e->mutex[P_RSID(id)]))
		{
			e->rlock[id] = think_with;
			e->think_stick[id] = P_RSID(id);
			phi_waitthink_start_event(e, id);
		}
		else
			phi_rest_start_event(e, id);
	}
	return ;
}
