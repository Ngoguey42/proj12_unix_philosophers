/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:31:40 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/24 10:39:18 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

/*
** les fonctions start doivent etre betes, 
** les fonctions end prennent les decisions,
*/

void			phi_waiteat_start_event(t_env *e, int id)//callable en next
{
	t_philock	prev[2];

	e->official_s[id] = weat;
	e->l_asked[P_RPID(id)] = 1;
	e->r_asked[P_LPID(id)] = 1;
	prev[0] = e->llock[id];
	prev[1] = e->rlock[id];
	e->llock[id] = waited;
	e->rlock[id] = waited;
	if (prev[0] != eat_with)
		pthread_mutex_lock(&e->mutex[P_LSID(id)]);
	if (prev[1] != eat_with)
		pthread_mutex_lock(&e->mutex[P_RSID(id)]);
	phi_waiteat_end_event(e, id);
	return ;
}

void			phi_waiteat_end_event(t_env *e, int id)//called after mutex
{
	e->l_asked[P_RPID(id)] = 0;
	e->r_asked[P_LPID(id)] = 0;
	phi_eat_start_event(e, id);
	return ;
}

void			phi_waitthink_start_event(t_env *e, int id)//callable en next
{
	(void)e; (void)id;
}

void			phi_waitthink_end_event(t_env *e, int id)//called after mutex
{
	e->l_asked[P_RPID(id)] = 0;
	e->r_asked[P_LPID(id)] = 0;
	phi_eat_start_event(e, id);
	return ;
}
