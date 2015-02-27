/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:31:40 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/27 16:00:11 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

void			phi_waiteat_start_event(t_env *e, int id)
{
	e->official_s[id] = weat;
	e->stick_state_change = 1;
	e->l_asked[P_RPID(id)] = 1;
	e->r_asked[P_LPID(id)] = 1;
	if (((P_LP_RLOCK(id) == eat_with && P_RP_LLOCK(id) == eat_with)
	&& P_LPHP >= P_RPHP) || (P_LP_RLOCK(id) != eat_with))
	{
		e->llock[id] = (e->llock[id] == eat_with) ? eat_with : waited;
		if (e->llock[id] != eat_with)
			pthread_mutex_lock(&e->mutex[P_LSID(id)]);
		e->llock[id] = eat_with;
		e->rlock[id] = (e->rlock[id] == eat_with) ? eat_with : waited;
		if (e->rlock[id] != eat_with)
			pthread_mutex_lock(&e->mutex[P_RSID(id)]);
		e->rlock[id] = eat_with;
	}
	else
	{
		e->rlock[id] = (e->rlock[id] == eat_with) ? eat_with : waited;
		if (e->rlock[id] != eat_with)
			pthread_mutex_lock(&e->mutex[P_RSID(id)]);
		e->rlock[id] = eat_with;
		e->llock[id] = (e->llock[id] == eat_with) ? eat_with : waited;
		if (e->llock[id] != eat_with)
			pthread_mutex_lock(&e->mutex[P_LSID(id)]);
		e->llock[id] = eat_with;
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
