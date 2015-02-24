/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:29:06 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/24 16:53:14 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

/*
** les fonctions start doivent etre betes,
** les fonctions end prennent les decisions,
*/

void			phi_rest_start_event(t_env *e, int id)//callable en next
{
	e->official_s[id] = rest;
	e->act_end_time[id] = e->last_time + REST_T;
	return ;
}

void			phi_rest_end_event(t_env *e, int id)//callable depuis W
{
//pick next action
	if (P_LPHP >= P_HP && P_RPHP > P_HP)
		phi_waiteat_start_event(e, id);
	else
		e->official_s[id] = rest;
	return ;
}
