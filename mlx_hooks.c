/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:05:05 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 15:10:56 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>
#include <stdlib.h>

static void		phi_leave_correctly(t_env *e)
{
    int		i;

	phi_quit_mlx(&e->g);
	i = 0;
    while (i < 7)
		pthread_join(e->tid[i++], NULL);
	i = 0;
	while (i < 7)
		pthread_mutex_destroy(&e->mutex[i++]);
	exit(0);
}

int				phi_expose_hook(void *envp)
{
	phi_redraw_surface((t_env*)envp);
	return (0);
}

int				phi_loop_hook(void *envp)
{
	t_env	*e;

	e = (t_env*)envp;
	if (e->g.redraw)
	{
		e->g.redraw = 0;
		phi_redraw_surface(e);
	}
	if (!e->play)
		phi_leave_correctly(e);
	return (0);
}
