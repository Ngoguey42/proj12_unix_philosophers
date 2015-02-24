/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:30:02 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/24 09:30:10 by wide-aze         ###   ########.fr       */
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
