/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 10:12:28 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/20 12:39:27 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHI_H
# define PHI_H

# include <libft.h>
# include <ft_math.h>
# include <pthread.h>
# include <time.h>
#include <ft_debug.h> //debug

# define MAX_LIFE 100
# define EAT_T 5
# define REST_T 3
# define THINK_T 2
# define TIMEOUT 100

typedef pthread_mutex_t		t_mutex;

typedef enum	e_pstat
{
	rest = 0,
	think = 1,
	eat = 2,
	waiteat = 3,
	waitthink = 4,
}				t_pstat;

typedef enum	e_sstat
{
	available = 0,
	left = 1,
	right = 2,
}				t_sstat;

/*
** *****************************************************************************
** 'struct s_grap' Graphical datas. (1 instance, inside main's t_env)
**		'serv'		mlx's serv pointer
**		'win'		mlx's window pointer
**		's'			screen image datas.
*/

# define WINX	1200
# define RATIO	(4. / 3.)
# define WIN_X	(int)(WINX)
# define WIN_Y	(int)((double)WIN_X / RATIO)

# define TABLE_LEFTPAD 400
# define TABLE_TOPPAD 250
# define TABLE_RADIUS 200

# define PHILO_RADIUS 30

# define P0_POS (t_cooi){600 - PHILO_RADIUS, 240 - PHILO_RADIUS * 2, 0}
# define P1_POS (t_cooi){810, 260, 0}
# define P2_POS (t_cooi){810, 455, 0}
# define P3_POS (t_cooi){740 - PHILO_RADIUS, 660, 0}
# define P4_POS (t_cooi){460 - PHILO_RADIUS, 660, 0}
# define P5_POS (t_cooi){390 - PHILO_RADIUS * 2 , 455, 0}
# define P6_POS (t_cooi){390 - PHILO_RADIUS * 2, 260, 0}

typedef struct	s_graph
{
	int			redraw;
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
	t_mutex		mutex[7];
	t_pstat		phi_s[7];
	int			phi_hp[7];
	pthread_t	tid[7];
	int			play;
	time_t		saved_time;
	time_t		act_time[7];
}				t_env;
typedef CS_ENV	t_cenv;

/*
** *****************************************************************************
*/

typedef struct	s_thread
{
	t_env		*e;
	int			id;
}				t_thread;

typedef struct	s_stick
{
	t_cooi		coo;
	int			stick_id;
	t_sstat		stick_status;
}				t_stick;


/*
** *****************************************************************************
*/

int				phi_init_env(t_env *e, t_thread tid[7]);
int				phi_init_mlx(t_env *e);
void			phi_pause_mlx(t_env *e);
int				phi_redraw_surface(t_cenv *e);
int				phi_quit_mlx(t_graph *g);
void			phi_redraw_image(t_cenv *e);
int				phi_loop_hook(void *envp);
void			*phi_thread_split(void *ptr);
int				phi_puts_pix(const t_graph *e, t_cooi coo, t_co c);
int				phi_put_string(const t_graph *e, t_cooi coo, t_co c, char *str);
void			phi_puttable(const t_graph *g);
void			phi_putphilo(const t_graph *g);
void			phi_leave_correctly(t_env *e, int nthrd, int nmutx, char *msg);
void        phi_put_strings(t_cenv *e);

/*
** *****************************************************************************
*/

#endif
