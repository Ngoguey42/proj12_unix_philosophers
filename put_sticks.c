/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sticks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 12:37:38 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/20 15:30:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

#ifndef POSITIONS_ABREVIATIONS
# define POSITIONS_ABREVIATIONS

# define LP TABLE_LEFTPAD
# define TP TABLE_TOPPAD
# define TR TABLE_RADIUS
# define TR2 TABLE_RADIUS * 2
# define HTR TABLE_RADIUS / 2

# define PR PHILO_RADIUS
# define PR2 PHILO_RADIUS * 2
# define PTP PHILO_TABLEPAD

# define SL STICK_LEN
#endif

/*
** SS: Space between two used sticks
** HSS: Half Space between two used sticks
** SPU: Stick Pad from table's border, when used
** SPA: Stick Pad from table's border, when available
*/
#define SS 16
#define HSS SS / 2
#define SPU 20
#define SPA 40

#define P_VCOTOI(R, G, B, A) (t_co){{B, G, R, A}}

const t_stick	s[21]
{
	{P_ACOOADD(P0_POS, PR + HSS, PR2 + PTP + SPU), 0, 0, vert},
	{(t_cooi){LP + TR + HTR, TP + SPA, 0}, 0, -1, vert},
	{P_ACOOADD(P1_POS, - PTP - SPU - SL, PR - HSS), 0, 1, horiz},
	
	{P_ACOOADD(P1_POS, - PTP - SPU - SL, PR + HSS), 1, 1, horiz},
	{(t_cooi){LP + TR2 - SPA - SL, TP + HTR, 0}, 1, -1, horiz},
	{P_ACOOADD(P2_POS, - PTP - SPU - SL, PR - HSS), 1, 2, horiz},
	
	{P_ACOOADD(P2_POS, - PTP - SPU - SL, PR + HSS), 2, 2, horiz},
	{(t_cooi){LP + TR2 - SPA - SL, TP + TR + HTR, 0}, 2, -1, horiz},
	{P_ACOOADD(P3_POS, PR + HSS, - PTP - SPU - SL), 2, 3, vert},
	
	{P_ACOOADD(P3_POS, PR - HSS, - PTP - SPU - SL), 3, 3, vert},
	{(t_cooi){LP + TR, TP + TR2 - SPA - SL, 0}, 3, -1, vert},
	{P_ACOOADD(P4_POS, PR + HSS, - PTP - SPU - SL), 3, 4, vert},
	
	{P_ACOOADD(P4_POS, PR - HSS, - PTP - SPU - SL), 4, 4, vert},
	{(t_cooi){LP + SPA, TP + TR + HTR, 0}, 4, -1, horiz},
	{P_ACOOADD(P5_POS, PR2 + PTP + SPU, PR + HSS), 4, 5, horiz},
	
	{P_ACOOADD(P5_POS, PR2 + PTP + SPU, PR - HSS), 5, 5, horiz},
	{(t_cooi){LP + SPA, TP + HTR, 0}, 5, -1, horiz},
	{P_ACOOADD(P6_POS, PR2 + PTP + SPU, PR + HSS), 5, 6, horiz},
	
	{P_ACOOADD(P6_POS, PR2 + PTP + SPU, PR - HSS), 6, 6, horiz},
	{(t_cooi){LP + HTR, TP + SPA, 0}, 6, -1, vert},
	{P_ACOOADD(P0_POS, PR - HSS, PR2 + PTP + SPU), 6, 0, vert}
};

static void	put_horiz(const t_graph *g, t_cooi coo)
{
	int		i;

	i = 0;
	while (i < STICK_LEN)
	{
		phi_puts_pix(g, coo, P_VCOTOI(210, 210, 30, 0));
		coo.x++;
		i++;
	}
	return ;
}

static void	put_vert(const t_graph *g, t_cooi coo)
{
	int		i;

	i = 0;
	while (i < STICK_LEN)
	{
		phi_puts_pix(g, coo, P_VCOTOI(210, 210, 30, 0));
		coo.y++;
		i++;
	}
	return ;
}

void		phi_put_sticks(t_cenv *e)
{
	int		i;

	while (i < 21)
	{
		if (e->owner[s[i].stick_id] == s[i].owner)
		{
			if (s[i].direction == horiz)
				put_horiz(&e->g, s[i].coo);
			else
				put_vert(&e->g, s[i].coo);
		}
		i++
	}
	return ;
}
