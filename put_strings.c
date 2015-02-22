/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_strings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:27:27 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/20 16:58:10 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phi.h>

#define TOP_PAD ACOOTOI(10, -5, 0)
#define BOT_PAD ACOOTOI(10, PHILO_RADIUS * 2 + 15, 0)
#define MID_PAD ACOOTOI(27, PHILO_RADIUS + 4, 0)

#define HP_TOP(P) P_ICOOADD((P), TOP_PAD)
#define HP_BOT(P) P_ICOOADD((P), BOT_PAD)
#define ID_MID(P) P_ICOOADD((P), MID_PAD)

#define P_VCOTOI(R, G, B, A) (t_co){{B, G, R, A}}
#define HP_COLOR P_VCOTOI(255, 255, 255, 0)
#define ID_COLOR P_VCOTOI(255, 255, 255, 0)

static void	put_one_hp(const t_graph *g, int hp, t_cooi coo)
{
	char	buf[128];

	buf[0] = '\0';
	buf[127] = '\0';
	ft_sprintf(buf, "%03d/%-3d", hp, MAX_LIFE);
	phi_put_string(g, coo, HP_COLOR, buf);
	return ;
}

static void	put_one_id(const t_graph *g, int id, t_cooi coo)
{
	char	buf[16];

	buf[0] = '\0';
	buf[15] = '\0';
	ft_itoa_c(id, buf, 10);
	phi_put_string(g, coo, ID_COLOR, buf);
	return ;
}

void		phi_put_strings(t_cenv *e)
{
	put_one_hp(&e->g, e->phi_hp[0], HP_TOP(P0_POS));
	put_one_hp(&e->g, e->phi_hp[1], HP_TOP(P1_POS));
	put_one_hp(&e->g, e->phi_hp[2], HP_TOP(P2_POS));
	put_one_hp(&e->g, e->phi_hp[3], HP_BOT(P3_POS));
	put_one_hp(&e->g, e->phi_hp[4], HP_BOT(P4_POS));
	put_one_hp(&e->g, e->phi_hp[5], HP_TOP(P5_POS));
	put_one_hp(&e->g, e->phi_hp[6], HP_TOP(P6_POS));
	put_one_id(&e->g, 0, ID_MID(P0_POS));
	put_one_id(&e->g, 1, ID_MID(P1_POS));
	put_one_id(&e->g, 2, ID_MID(P2_POS));
	put_one_id(&e->g, 3, ID_MID(P3_POS));
	put_one_id(&e->g, 4, ID_MID(P4_POS));
	put_one_id(&e->g, 5, ID_MID(P5_POS));
	put_one_id(&e->g, 6, ID_MID(P6_POS));
	return ;
}
