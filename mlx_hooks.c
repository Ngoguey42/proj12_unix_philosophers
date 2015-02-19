/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:05:05 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 14:11:14 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>
#include <stdlib.h>

int			phi_expose_hook(void *envp)
{

	(void)envp;
	return (0);
}


int			phi_loop_hook(void *envp)
{
	t_env	*e;

	e = (t_env*)envp;
	if (e->g.redraw)
		phi_redraw_surface(e);
	if (!e->play)
		exit(0);
		/* phi_leave_correctly(); */
	return (0);
}
