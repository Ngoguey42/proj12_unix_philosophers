/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:32:06 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/24 11:13:02 by ngoguey          ###   ########.fr       */
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
	e->llock[id] = eat_with;
	e->rlock[id] = eat_with;
	e->stick_state_change = 1;
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
