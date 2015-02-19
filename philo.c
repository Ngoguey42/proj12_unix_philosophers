/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:30:02 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 15:58:14 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>


static void	philo(t_env *e, int id)
{
	(void)e;
	(void)id;
	qprintf("%d \n", id);
	while (e->play)
	{

	}
	return ;
}


void		*phi_thread_split(void	*ptr)
{
	philo(((t_thread*)ptr)->e, ((t_thread*)ptr)->id);
	return (NULL);
}
