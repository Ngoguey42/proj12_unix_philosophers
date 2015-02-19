/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 10:12:28 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 12:48:00 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHI_H
# define PHI_H

# include <libft.h>
# include <ft_math.h>
#include <ft_debug.h> //debug

# define MAX_LIFE 100
# define EAT_T 5
# define REST_T 3
# define THINK_T 2
# define TIMEOUT 30

typedef enum	s_pstat
{
	rest = 0,
	think = 1,
	eat = 2,
	waiteat = 3,
	waitthink = 4,
}				t_pstat;

typedef enum	s_sstat
{
	free = 0,
	left = 2,
	right = 3,
}				t_sstat;

/*
** *****************************************************************************
** 'struct s_grap' Graphical datas. (1 instance, inside main's t_env)
**		'serv'		mlx's serv pointer
**		'win'		mlx's window pointer
**		's'			screen image datas.
*/

# define WINX	1600
# define RATIO	(4. / 3.)
# define WIN_X	(int)(WINX)
# define WIN_Y	(int)((double)WIN_X / RATIO)

typedef struct	s_graph
{	
	void		*serv;
	void		*win;
	t_img		s;
}				t_graph;

/*
** *****************************************************************************
** 'struct s_env' (1 instance, inside 'main' function)
**		'serv'		...
**		'var1'		...
**		'var1'		...
** *
** 't_cenv'	== const struct s_env
**		(use const t_env as soon as possible)
*/

# define CS_ENV const struct s_env

typedef struct	s_env
{
	t_graph		g;
	t_sstat		stick_s[7];
	int			mutex[7];
	t_pstat		phi_s[7];
	int			phi_hp[7];	

}				t_env;
typedef CS_ENV	t_cenv;

/*
** *****************************************************************************
*/


/*
** *****************************************************************************
*/

int				phi_init_env(t_env *e);
int				phi_init_mlx(t_env *e);
int				phi_redraw_surface(t_cenv *e);
int				phi_mlx_quit(t_graph *g);
void			phi_redraw_image(t_cenv *e);

/*
** *****************************************************************************
*/

#endif
