/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wide-aze <wide-aze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 09:29:06 by wide-aze          #+#    #+#             */
/*   Updated: 2015/02/24 09:31:16 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

/*
** les fonctions start doivent etre betes, 
** les fonctions end prennent les decisions,
*/

void			phi_rest_start_event(t_env *e, int id)//callable en next
{
	//set self->hp to HP_MAX
	(void)e; (void)id;
}

void			phi_rest_end_event(t_env *e, int id)//callable depuis W
{
	(void)e; (void)id;
}
