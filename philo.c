/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:30:02 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/23 12:02:40 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>
#include <unistd.h>

void			phi_eat_start_event(t_env *e, int id){(void)e; (void)id;};
void			phi_wait_start_event(t_env *e, int id){(void)e; (void)id;};
void			phi_rest_start_event(t_env *e, int id){(void)e; (void)id;};
void			phi_think_start_event(t_env *e, int id){(void)e; (void)id;};
void			phi_eat_end_event(t_env *e, int id){(void)e; (void)id;};
void			phi_rest_end_event(t_env *e, int id){(void)e; (void)id;};
void			phi_think_end_event(t_env *e, int id){(void)e; (void)id;};
void			phi_wait_end_event(t_env *e, int id){(void)e; (void)id;};

void			phi_pick_action(t_env *e, int id)
{
	e->g.redraw = 1;
	(void)e;
	(void)id;
/*	if (P_ACT == eating)
	{
		phi_eat_end_event(e, id);
		phi_rest_start_event(e, id);
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
	while (e->play)
	{
		if (e->last_time >= e->act_end_time[id])
			phi_pick_action(e, id);
	}
	return ;
}

void			*phi_thread_split(void *ptr)
{
	philo(((t_thread*)ptr)->e, ((t_thread*)ptr)->id);
	return (NULL);
}
