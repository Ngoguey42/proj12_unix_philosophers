/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sticks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 12:37:38 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/27 17:24:32 by wide-aze         ###   ########.fr       */
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
#define SS 40
#define HSS SS / 2
#define SPU -15
#define SPA 20

#define T_S t_stick
#define P_VCOTOI(R, G, B, A) (t_co){{B, G, R, A}}

static t_stick	tstick(int i) //ACO fait fail la nm
{
	const t_stick		s[21] = {

	(const T_S){P_ACOOADD(P0_POS, PR + HSS, PR2 + PTP + SPU), 0, 0, v},
	(const T_S){(t_cooi){LP + TR + HTR, TP + SPA, 0}, 0, -1, v},
	(const T_S){P_ACOOADD(P1_POS, -PTP - SPU - SL, PR - HSS), 0, 1, h},
	(const T_S){P_ACOOADD(P1_POS, -PTP - SPU - SL, PR + HSS), 1, 1, h},
	(const T_S){(t_cooi){LP + TR2 - SPA - SL, TP + TR - 69, 0}, 1, -1, h},
	(const T_S){P_ACOOADD(P2_POS, -PTP - SPU - SL, PR - HSS), 1, 2, h},
	(const T_S){P_ACOOADD(P2_POS, -PTP - SPU - SL, PR + HSS), 2, 2, h},
	(const T_S){(t_cooi){LP + TR2 - SPA - SL, TP + TR + HTR + 20, 0}, 2, -1, h},
	(const T_S){P_ACOOADD(P3_POS, PR + HSS, -PTP - SPU - SL), 2, 3, v},
	(const T_S){P_ACOOADD(P3_POS, PR - HSS, -PTP - SPU - SL), 3, 3, v},
	(const T_S){(t_cooi){LP + TR, TP + TR2 - SPA - SL, 0}, 3, -1, v},
	(const T_S){P_ACOOADD(P4_POS, PR + HSS, -PTP - SPU - SL), 3, 4, v},
	(const T_S){P_ACOOADD(P4_POS, PR - HSS, -PTP - SPU - SL), 4, 4, v},
	(const T_S){(t_cooi){LP + SPA, TP + TR + HTR + 20, 0}, 4, -1, h},
	(const T_S){P_ACOOADD(P5_POS, PR2 + PTP + SPU, PR + HSS), 4, 5, h},
	(const T_S){P_ACOOADD(P5_POS, PR2 + PTP + SPU, PR - HSS), 5, 5, h},
	(const T_S){(t_cooi){LP + SPA, TP + TR - 69, 0}, 5, -1, h},
	(const T_S){P_ACOOADD(P6_POS, PR2 + PTP + SPU, PR + HSS), 5, 6, h},
	(const T_S){P_ACOOADD(P6_POS, PR2 + PTP + SPU, PR - HSS), 6, 6, h},
	(const T_S){(t_cooi){LP + HTR, TP + SPA, 0}, 6, -1, v},
	(const T_S){P_ACOOADD(P0_POS, PR - HSS, PR2 + PTP + SPU), 6, 0, v}
	};
	return ((t_stick)s[i]);
}

static void		put_it(const t_graph *g, t_cooi coo, t_co c, int index)
{
	int		i;

	i = 0;
	while (i < STICK_LEN)
	{
		phi_puts_pix(g, coo, c);
		if (tstick(index).direction == h)
			coo.x++;
		else
			coo.y++;
		i++;
	}
	return ;
}

void			phi_put_sticks(t_cenv *e)
{
	int			i;
	t_stick		s;

	i = 0;
	while (i < 21)
	{
		s = tstick(i);
		if (i % 3 == 0)
		{
			if (e->llock[s.owner] == think_with || e->llock[s.owner] == eat_with)
				put_it(&e->g, tstick(i).coo, P_VCOTOI(210, 210, 30, 0), i);
			else if (e->llock[s.owner] == stolen)
				put_it(&e->g, tstick(i).coo, P_VCOTOI(210, 50, 30, 0), i);
			else if (e->llock[s.owner] == waited)
				put_it(&e->g, tstick(i).coo, P_VCOTOI(0x66, 0xCC, 0xCC, 0), i);
		}
		else if (i % 3 == 2)
		{
			if (e->rlock[s.owner] == think_with || e->rlock[s.owner] == eat_with)
				put_it(&e->g, tstick(i).coo, P_VCOTOI(210, 210, 30, 0), i);
			else if (e->rlock[s.owner] == stolen)
				put_it(&e->g, tstick(i).coo, P_VCOTOI(210, 50, 30, 0), i);
			else if (e->rlock[s.owner] == waited)
				put_it(&e->g, tstick(i).coo, P_VCOTOI(0x66, 0xCC, 0xCC, 0), i);
		}
		else
		{
			if (e->owner[s.stick_id] == s.owner)
				put_it(&e->g, tstick(i).coo, P_VCOTOI(210, 210, 30, 0), i);
		}
		i++;
	}
	return ;
}

