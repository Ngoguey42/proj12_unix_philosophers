/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:31:40 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/27 15:28:30 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

/*
** les fonctions start doivent etre betes,
** les fonctions end prennent les decisions,
*/

void			phi_waiteat_start_event(t_env *e, int id)//callable en next
{
	/* t_philock	prev[2]; */
	e->official_s[id] = weat;
	e->stick_state_change = 1;
	e->l_asked[P_RPID(id)] = 1;
	e->r_asked[P_LPID(id)] = 1;
	/* prev[0] = e->llock[id]; */
	/* prev[1] = e->rlock[id]; */
	/* e->llock[id] = (e->llock[id] == eat_with) ? eat_with : waited; */
	/* e->rlock[id] = (e->rlock[id] == eat_with) ? eat_with : waited; */
	/* e->llock[id] = waited; */
	/* e->rlock[id] = waited; */
	/* if (P_RP_LLOCK(id) == eat_with) */
	/* if (P_LPHP < P_RPHP) */
	/* if (P_LP_RLOCK(id) != eat_with) */
	
	int err;
	if ((
		(P_LP_RLOCK(id) == eat_with && P_RP_LLOCK(id) == eat_with)
		&& P_LPHP >= P_RPHP) || (P_LP_RLOCK(id) != eat_with)
		)
	{
		//l->eat_with && r->eat_with && LHP == RHP
		//l->eat_with && r->eat_with && LHP > RHP
		//NOT(l->eat_with)
		//pick left first
		e->llock[id] = (e->llock[id] == eat_with) ? eat_with : waited;//left
		if (e->llock[id] != eat_with)//left
		{
			err = pthread_mutex_lock(&e->mutex[P_LSID(id)]);//left
			qprintf("%d took mutex %s %d {%d}\n", id, "LEFT", P_LSID(id), err);
		}
		e->llock[id] = eat_with;//left
		e->rlock[id] = (e->rlock[id] == eat_with) ? eat_with : waited;//right
		if (e->rlock[id] != eat_with)//right
		{
			err = pthread_mutex_lock(&e->mutex[P_RSID(id)]);//right
			qprintf("%d took mutex %s %d {%d}\n", id, "RIGHT", P_RSID(id), err);
		}
		e->rlock[id] = eat_with;//right
	}
	else
	{
		//l->eat_with && r->eat_with && LHP < RHP
		//l->eat_with
		//pick right first
		e->rlock[id] = (e->rlock[id] == eat_with) ? eat_with : waited;//right
		if (e->rlock[id] != eat_with)//right
		{
			err = pthread_mutex_lock(&e->mutex[P_RSID(id)]);//right
			qprintf("%d took mutex %s %d {%d}\n", id, "RIGHT", P_RSID(id), err);
		}

		e->rlock[id] = eat_with;//right
		e->llock[id] = (e->llock[id] == eat_with) ? eat_with : waited;//left
		if (e->llock[id] != eat_with)//left
		{
			err = pthread_mutex_lock(&e->mutex[P_LSID(id)]);//left
			qprintf("%d took mutex %s %d {%d}\n", id, "LEFT", P_LSID(id), err);
		}

		e->llock[id] = eat_with;//left
	}
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

void			phi_waitthink_end_event(t_env *e, int id)//called after mutex
{
	phi_think_start_event(e, id);
	return ;
}
