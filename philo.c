/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:40:04 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/24 11:29:35 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>
#include <unistd.h>

/*
** les fonctions start doivent etre betes, 
** les fonctions end prennent les decisions,
*/

void			phi_start_end_event(t_env *e, int id)//callable depuis W
{
	if (!pthread_mutex_trylock(&e->mutex[P_LSID(id)]))
	{
/**/		qprintf("%d locks %d #1\n", id, P_LSID(id));
		e->llock[id] = eat_with;
		if (!pthread_mutex_trylock(&e->mutex[P_RSID(id)]))
		{
/**/			qprintf("%d locks %d #2\n", id, P_RSID(id));
			/* qprintf("%d: got both %d %d\n", id, P_RSID(id), P_LSID(id)); */
			e->rlock[id] = eat_with;
			phi_waiteat_start_event(e, id);
			return ;
		}
		if (e->official_s[P_RSID(id)] == think ||
				e->official_s[P_RSID(id)] == wthink)
		{
/**/		qprintf("%d requs %d #2\n", id, P_RSID(id));
			phi_waiteat_start_event(e, id);
		}
		/* pthread_mutex_unlock(&e->mutex[P_LSID(id)]); */
		e->llock[id] = think_with;
		e->think_stick[id] = P_LSID(id);
		phi_waitthink_start_event(e, id);
	}
	return ;
}

/*
	lock left stick()
	lock right stick()


	num sticks available (0/1/2)
	time left on stick left
	time left on stick right

 */

static void		philo(t_env *e, int id)
{
	void	(*f[5])(t_env *e, int id);

	f[0] = &phi_start_end_event;
	f[1] = &phi_rest_end_event;
	f[2] = &phi_think_end_event;
	f[3] = &phi_eat_end_event;
	while (e->play)
	{
		if (P_ACT == think)
		{
			if (P_LLOCK(id) == think_with && ISLASKED)
				phi_think_stolen_event(e, id, 0);
			else
				phi_think_stolen_event(e, id, 1);
		}
		if (e->last_time >= e->act_end_time[id])
			f[P_ACT](e, id);
	}
	return ;
}

void			*phi_thread_split(void *ptr)
{
	philo(((t_thread*)ptr)->e, ((t_thread*)ptr)->id);
	return (NULL);
}
