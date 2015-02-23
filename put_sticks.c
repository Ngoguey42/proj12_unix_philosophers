/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sticks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 12:37:38 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/23 11:13:49 by wide-aze         ###   ########.fr       */
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

#define T_S t_stick
#define P_VCOTOI(R, G, B, A) (t_co){{B, G, R, A}}

static void		put_horiz(const t_graph *g, t_cooi coo)
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

static void		put_vert(const t_graph *g, t_cooi coo)
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

static t_stick	tstick(int i)
{
	const t_stick		s[21] = {

	(const T_S){P_ACOOADD(P0_POS, PR + HSS, PR2 + PTP + SPU), 0, 0, v},
	(const T_S){(t_cooi){LP + TR + HTR, TP + SPA, 0}, 0, -1, v},
	(const T_S){P_ACOOADD(P1_POS, -PTP - SPU - SL, PR - HSS), 0, 1, h},
	(const T_S){P_ACOOADD(P1_POS, -PTP - SPU - SL, PR + HSS), 1, 1, h},
	(const T_S){(t_cooi){LP + TR2 - SPA - SL, TP + TR - 70, 0}, 1, -1, h},
	(const T_S){P_ACOOADD(P2_POS, -PTP - SPU - SL, PR - HSS), 1, 2, h},
	(const T_S){P_ACOOADD(P2_POS, -PTP - SPU - SL, PR + HSS), 2, 2, h},
	(const T_S){(t_cooi){LP + TR2 - SPA - SL, TP + TR + HTR + 25, 0}, 2, -1, h},
	(const T_S){P_ACOOADD(P3_POS, PR + HSS, -PTP - SPU - SL), 2, 3, v},
	(const T_S){P_ACOOADD(P3_POS, PR - HSS, -PTP - SPU - SL), 3, 3, v},
	(const T_S){(t_cooi){LP + TR, TP + TR2 - SPA - SL, 0}, 3, -1, v},
	(const T_S){P_ACOOADD(P4_POS, PR + HSS, -PTP - SPU - SL), 3, 4, v},
	(const T_S){P_ACOOADD(P4_POS, PR - HSS, -PTP - SPU - SL), 4, 4, v},
	(const T_S){(t_cooi){LP + SPA, TP + TR + HTR + 25, 0}, 4, -1, h},
	(const T_S){P_ACOOADD(P5_POS, PR2 + PTP + SPU, PR + HSS), 4, 5, h},
	(const T_S){P_ACOOADD(P5_POS, PR2 + PTP + SPU, PR - HSS), 5, 5, h},
	(const T_S){(t_cooi){LP + SPA, TP + TR - 70, 0}, 5, -1, h},
	(const T_S){P_ACOOADD(P6_POS, PR2 + PTP + SPU, PR + HSS), 5, 6, h},
	(const T_S){P_ACOOADD(P6_POS, PR2 + PTP + SPU, PR - HSS), 6, 6, h},
	(const T_S){(t_cooi){LP + HTR, TP + SPA, 0}, 6, -1, v},
	(const T_S){P_ACOOADD(P0_POS, PR - HSS, PR2 + PTP + SPU), 6, 0, v}
	};
	return ((t_stick)s[i]);
}

void			phi_put_sticks(t_cenv *e)
{
	int		i;

	i = 0;
	while (i < 21)
	{
		if (e->owner[tstick(i).stick_id] == tstick(i).owner)
		{
			if (tstick(i).direction == h)
				put_horiz(&e->g, tstick(i).coo);
			else
				put_vert(&e->g, tstick(i).coo);
		}
		i++;
	}
	return ;
}
