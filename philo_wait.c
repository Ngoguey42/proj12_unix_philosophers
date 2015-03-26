/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:31:40 by wide-aze          #+#    #+#             */
/*   Updated: 2015/03/26 08:47:54 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

#define NEIGHBORS_EAT (P_LP_RLOCK(id) == eat_with && P_RP_LLOCK(id) == eat_with)
#define RIGHT_P_LESS_HP (P_LPHP >= P_RPHP)
#define RIGHT_P_NOT_EATING (P_LP_RLOCK(id) != eat_with)
#define LEFT_FIRST ((NEIGHBORS_EAT && RIGHT_P_LESS_HP) || RIGHT_P_NOT_EATING)

void			phi_waiteat_start_event(t_env *e, int id)
{
	e->official_s[id] = weat;
	e->stick_state_change = 1;
	e->l_asked[P_RPID(id)] = 1;
	e->r_asked[P_LPID(id)] = 1;
	if (LEFT_FIRST)
	{
		if (e->llock[id] != eat_with && (e->llock[id] = waited))
			pthread_mutex_lock(&e->mutex[P_LSID(id)]), e->llock[id] = eat_with;
		if (e->rlock[id] != eat_with && (e->rlock[id] = waited))
			pthread_mutex_lock(&e->mutex[P_RSID(id)]), e->rlock[id] = eat_with;
	}
	else
	{
		if (e->rlock[id] != eat_with && (e->rlock[id] = waited))
			pthread_mutex_lock(&e->mutex[P_RSID(id)]), e->rlock[id] = eat_with;
		if (e->llock[id] != eat_with && (e->llock[id] = waited))
			pthread_mutex_lock(&e->mutex[P_LSID(id)]), e->llock[id] = eat_with;
	}
	phi_waiteat_end_event(e, id);
	return ;
}

void			phi_waiteat_end_event(t_env *e, int id)
{
	e->l_asked[P_RPID(id)] = 0;
	e->r_asked[P_LPID(id)] = 0;
	phi_eat_start_event(e, id);
	return ;
}

void			phi_waitthink_start_event(t_env *e, int id)
{
	t_philock	*ptr;

	e->official_s[id] = wthink;
	e->stick_state_change = 1;
	ptr = (e->think_stick[id] == P_RSID(id)) ? &e->rlock[id] : &e->llock[id];
	if (*ptr != think_with)
	{
		*ptr = waited;
		pthread_mutex_lock(&e->mutex[e->think_stick[id]]);
	}
	phi_waitthink_end_event(e, id);
	return ;
}

void			phi_waitthink_end_event(t_env *e, int id)
{
	phi_think_start_event(e, id);
	return ;
}
