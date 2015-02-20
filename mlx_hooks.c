/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:05:05 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/20 12:06:51 by wide-aze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>
#include <time.h>

int				phi_expose_hook(void *envp)
{
	phi_redraw_surface((t_env*)envp);
	return (0);
}

int				phi_loop_hook(void *envp)
{
	t_env	*e;
	time_t	tmp;

	e = (t_env*)envp;
	if (e->g.redraw)
	{
		e->g.redraw = 0;
		phi_redraw_surface(e);
	}
	if (!e->play)
		phi_leave_correctly(e, 7, 7, "");
	time(&tmp);
	if (tmp - e->saved_time >= TIMEOUT)
		phi_leave_correctly(e, 7, 7, "Now, it is time... To DAAAAAAAANCE ! ! !\n");
	return (0);
}
