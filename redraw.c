/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 11:24:58 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 15:31:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

void		phi_redraw_image(t_cenv *e)
{
	ft_bzero(e->g.s.dat, WIN_X * WIN_Y * 4);
	phi_puttable(&e->g);
	phi_putphilo(&e->g);
	(void)e;

}
