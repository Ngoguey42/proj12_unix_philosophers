/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 11:06:03 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 14:09:54 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

int			phi_init_env(t_env *e)
{
	ft_bzero(e, sizeof(t_env));

	e->play = 1;
	D(int, e->play);
	if (phi_init_mlx(e))
		return (0);
	return (0);
}
