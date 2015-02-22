/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:15:24 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/20 12:37:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

static void	draw_row(const t_graph *g, int row, int pad, int rad)
{
	int	i;

	i = 0;
	while (i < rad * 2)
	{
		/* qprintf("%d %d\n", i + TABLE_LEFTPAD, row); */
		phi_puts_pix(g, ACOOTOI(i++ + pad, row, 0),
			(t_co){{0, 0, 75, 150}});
	}
	return ;
}

void		phi_puttable(const t_graph *g)
{
	int		i;

	i = TABLE_TOPPAD;//attention a pas avoir de libmath dans les macros
	while (i < TABLE_TOPPAD + TABLE_RADIUS * 2)
		draw_row(g, i++, TABLE_LEFTPAD, TABLE_RADIUS);
	return ;
}

void		phi_putphilo(const t_graph *g)
{
	int				i;
	int				j;
	const t_cooi	pos[7] = {

	P0_POS, P1_POS, P2_POS, P3_POS, P4_POS, P5_POS, P6_POS};
	i = 0;
	while (i < 7)
	{
		j = 0;
		while (j < PHILO_RADIUS * 2)
			draw_row(g, pos[i].y + j++, pos[i].x, PHILO_RADIUS);
		i++;
	}
	
	return ;
}
