/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:30:02 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/24 09:12:12 by ngoguey          ###   ########.fr       */
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
	// call first ****_start_event;
	(void)e; (void)id;
}




void			phi_waiteat_start_event(t_env *e, int id)//callable en next
{
	(void)e; (void)id;

	//request les baguettes aux voisins
	//lock les mutexes
	//phi_wait_end_event(e, id);
}
void			phi_waiteat_end_event(t_env *e, int id)//called after mutex
{
	//equivalent de On_Mutex_locked
	
	//phi_eat_start_event(e, id);
	(void)e; (void)id;
}
void			phi_eat_start_event(t_env *e, int id)
{
	//set act_end_time
	//set eating_delta
	
	/* e->eating_delta[id] = (HP_MAX - e->phi_hp[id]) / EAT_T; */
	//set les llock && rlock && official_s
	(void)e; (void)id;
}
void			phi_eat_end_event(t_env *e, int id)//callable depuis W
{
	//set self->hp to HP_MAX
	//phi_rest_start_event(e, id);
	(void)e; (void)id;
}
void			phi_rest_start_event(t_env *e, int id)//callable en next
{
	//set self->hp to HP_MAX
	(void)e; (void)id;
}
void			phi_rest_end_event(t_env *e, int id)//callable depuis W
{(void)e; (void)id;}




void			phi_waitthink_start_event(t_env *e, int id)//callable en next
{
	(void)e; (void)id;
}
void			phi_waitthink_end_event(t_env *e, int id)//called after mutex
{
	(void)e; (void)id;
}
void			phi_think_start_event(t_env *e, int id)
{
	(void)e; (void)id;
	//set les llock && rlock
	return ;
}
void			phi_think_stolen_event(t_env *e, int id, int isright)
{
	(void)e; (void)id;(void)isright;
	return ;
}
void			phi_think_end_event(t_env *e, int id)//callable depuis W
{
	(void)e; (void)id;
	return ;
}



void			phi_pick_action(t_env *e, int id)
{
	/* e->g.redrawt = 1; */
	(void)e;
	(void)id;
/*	if (P_ACT == eating)
	{
		phi_eat_end_event(e, id);

	}
	if (!ISLPICKNG && !ISRPICKNG)
	{
		if ()
			
			}
	if (P_LHP < P_HP)
	{
	}
	else
	{
	}
	if ()
		
		setstatus(t_env *e, int id, t_pstat prevstatus, t_pstat newstatus);
	{
		phi_eat_start_event()   =>lock mutex x2   =>update events  =>update stick status
			phi_wait_start_event()
			phi_rest_start_event()
			phi_think_start_event() =>lock mutex x1
			phi_eat_end_event()
			phi_rest_end_event()
			phi_think_end_event()
			phi_wait_end_event()
	}*/
	return ;
}

/*
	lock left stick()
	lock right stick()


	num sticks available (0/1/2)
	time left on stick left
	time left on stick right
	is left available
	is right available

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
			/* phi_pick_action(e, id); */
			f[P_ACT](e, id);
	}
	return ;
}

void			*phi_thread_split(void *ptr)
{
	philo(((t_thread*)ptr)->e, ((t_thread*)ptr)->id);
	return (NULL);
}
