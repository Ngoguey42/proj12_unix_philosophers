/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpix_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/22 08:55:14 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 15:21:02 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>
#include <mlx.h>

int phi_put_string(const t_graph *e, t_cooi coo, t_co c, char *str)
{
	return (mlx_string_put(e->serv, e->win, coo.x, coo.y, c.i, str));
}

int phi_puts_pix(const t_graph *e, t_cooi coo, t_co c)
{
	const int	dst = e->s.lsz * coo.y + coo.x * (e->s.bpp / 8);
	int			i;

	i = -1;
	while (++i < (e->s.bpp / 8))
	{
		e->s.dat[dst + i] = (char)c.s.b;
		c.i >>= 8;
	}
	return (0);
}

int	phi_puts_dst(const t_img *s, int dst, t_co c)
{
	int				i;

	i = -1;
	while (++i < (s->bpp / 8))
	{
		s->dat[dst + i] = (char)c.s.b;
		c.i >>= 8;
	}
	return (0);
}
