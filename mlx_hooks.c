/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:05:05 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/27 15:27:39 by wide-aze         ###   ########.fr       */
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
			if (e->phi_hp[i] <= 0)
				e->play = 0;
			e->phi_hp[i] = MAX(e->phi_hp[i], 0);
		}
		i++;
	}
	e->g.redrawt = 1;
	return ;
}

static void		update_sticks_off_stats(t_env *e)
{
	int		i;
//on peut en delete la moitier
	//verifier les valeurs de retour des pthread partout sauf
	i = 0;
	while (i < 7)
	{
		if (S_RP_LLOCK(i) == eat_with || S_LP_RLOCK(i) == eat_with)
		{
			e->own_type[i] = hard_locked;
			e->owner[i] = (S_RP_LLOCK(i) == eat_with) ? S_RPID(i) : S_LPID(i);
		}
		else if (S_RP_LLOCK(i) == think_with || S_LP_RLOCK(i) == think_with)
		{
			e->own_type[i] = soft_locked;
			e->owner[i] = (S_RP_LLOCK(i) == think_with) ? S_RPID(i) : S_LPID(i);
		}
		else
		{
			e->own_type[i] = available;
			e->owner[i] = -1;
		}
		i++;
	}
	e->g.redraw = 1;
	return ;
}

int				phi_loop_hook(void *envp)
{
	t_env	*e;
	time_t	curtime;

	e = (t_env*)envp;
	if (!e->play)
		phi_leave_correctly(e, 7, 7, "");
	if (time(&curtime) == (time_t)-1)
		phi_leave_correctly(e, 7, 7, TIMEFAIL_MSG);
	if (curtime >= e->end_time)
		phi_leave_correctly(e, 7, 7, LEAVE_MSG);
	else if (curtime != e->last_time)
	{
		tick(e, curtime - e->last_time);
		e->last_time = curtime;
	}
	e->g.redraw = 1;
	e->g.redrawt = 1;
	update_sticks_off_stats(e);
	if (e->g.redraw || e->g.redrawt)
		phi_redraw_surface(e);
	return (0);
}
