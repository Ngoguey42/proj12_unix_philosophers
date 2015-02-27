/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:29:06 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/27 15:45:00 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

void			phi_rest_start_event(t_env *e, int id)
{
	e->official_s[id] = rest;
	e->act_end_time[id] = e->last_time + REST_T;
	return ;
}

void			phi_rest_end_event(t_env *e, int id)
{
	if ((P_LPHP >= P_HP || P_LP_RLOCK(id) == eat_with)
	&& (P_RPHP > P_HP || P_RP_LLOCK(id) == eat_with))
		phi_waiteat_start_event(e, id);
	else
		phi_rest_start_event(e, id);
	return ;
}
