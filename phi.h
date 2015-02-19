s/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 10:12:28 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/19 11:41:10 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHI_H
# define PHI_H

# include <libft.h>
#include <ft_debug.h> //debug


typedef enum	s_state
{
	rest = 0,
	think = 1,
	eat = 2;
}				t_state;


/*
** *****************************************************************************
** 'struct s_grap' Graphical datas. (1 instance, inside main's t_env)
**		'serv'		mlx's serv pointer
**		'win'		mlx's window pointer
**		's'			screen image datas.
*/

#define WINX	1600
#define RATIO	(4. / 3.)

#define WIN_X	(int)(WIN_X)
#define WIN_Y	(int)((double)WIN_X / ratio)

typedef struct	s_grap
{	
	void		*serv;
	void		*win;
	t_img		s;
}				t_grap;


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
}				t_env;
typedef CS_ENV	t_cenv;

/*
** *****************************************************************************
*/


/*
** *****************************************************************************
*/

void			phi_init_env(t_env *e);

/*
** *****************************************************************************
*/

#endif
