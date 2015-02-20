/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:05:05 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/20 16:58:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>
#include <time.h>

int				phi_expose_hook(void *envp)
{
	phi_redraw_surface((t_env*)envp);
	return (0);
}

static void		tick(t_env *e, time_t elapsedtime)
{
	int		i;

	i = 0;
	while (i < 7)
	{
		if (e->official_s[i] == eat)
		{
			e->phi_hp[i] += e->eating_delta[i] * elapsedtime;
			e->phi_hp[i] = MIN(e->phi_hp[i], MAX_LIFE);
		}
		else
		{
			e->phi_hp[i] -= 1 * elapsedtime;
			e->phi_hp[i] = MAX(e->phi_hp[i], 0);
		}
		i++;
	}
	return ;
}

int				phi_loop_hook(void *envp)
{
	t_env	*e;
	time_t	curtime;

	e = (t_env*)envp;
	if (e->g.redraw)
	{
		qprintf("ici1\n");
		e->g.redraw = 0;
		phi_redraw_surface(e);
	}
	if (!e->play)
		phi_leave_correctly(e, 7, 7, "");
	if (time(&curtime) == (time_t)-1)
		phi_leave_correctly(e, 7, 7, "Could not retrieve time\n");
	if (curtime >= e->end_time)
		phi_leave_correctly(e, 7, 7, LEAVE_MSG);
	else if (curtime != e->last_time)
		tick(e, curtime - e->last_time);
	return (0);
}
