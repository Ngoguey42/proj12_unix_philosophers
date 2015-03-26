/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pick_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/26 08:08:26 by ngoguey           #+#    #+#             */
/*   Updated: 2015/03/26 08:12:35 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

void						phi_can_wait_to_eat_pick(t_env *e, int id)
{
	if ((P_LPHP >= P_HP || P_LP_RLOCK(id) == eat_with)
		&& (P_RPHP > P_HP || P_RP_LLOCK(id) == eat_with))
		phi_waiteat_start_event(e, id);
	else
		phi_rest_start_event(e, id);
	return ;
}

void						phi_cant_wait_to_eat_pick(t_env *e, int id)
{
	if ((P_LPHP >= P_HP || P_LP_RLOCK(id) == eat_with)
		&& (P_RPHP > P_HP || P_RP_LLOCK(id) == eat_with))
		phi_waiteat_start_event(e, id);
	else
		phi_rest_start_event(e, id);
	(void)e;
	(void)id;
	return ;
}

