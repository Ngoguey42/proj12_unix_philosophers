/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 10:12:28 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/20 16:59:37 by ngoguey          ###   ########.fr       */
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
# define TIMEOUT 5

# define STEP 1
# define USTEP (STEP * 100000)

# define LEAVE_MSG "Now, it is time... To DAAAAAAAANCE ! ! !\n"
# define TIMEFAIL_MSG "Could not retrieve time\n"

/*
** RSID, Right hand Stick ID.
** LSID, Left hand Stick ID.
*/
# define RSID(pid) (pid == 0 ? 6 : pid - 1)
# define LSID(pid) (pid)


typedef pthread_mutex_t		t_mutex;

typedef enum	e_pstat
{
	start = 0,
	rest = 1,
	think = 2,
	eat = 3,
	await = 4,
}				t_pstat;

typedef enum	e_owntype
{
	available = 0,
	soft_lock = 1,
	hard_lock = 2,
}				t_owntype;

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
**		'g'				mlx vars + bool redraw
**		'stick_s'		stick state (0 free/1 left/2 right)
**		'mutex'			mutex lock for each thread
**		'phi_s'			phi state
**		'phi_hp'		phi hp
**		'tid'			threads id
**		'play'			boolean
**		'saved_time'	time saved at init
**		'act_time'		last action time left
** *
** 't_cenv'	== const struct s_env
**		(use const t_env as soon as possible)
*/

# define CS_ENV const struct s_env

typedef struct	s_env
{
	t_graph		g;
	int			play;
	time_t		init_time;
	time_t		last_time;
	time_t		end_time;
	
//sticks
	t_mutex		mutex[7];
	t_owntype	own_type[7];
	int			owner[7];

	
	//philos
	int			phi_hp[7];
	int			eating_delta[7];
	pthread_t	tid[7];
	
	time_t		act_end_time[7];



	/* time_t		act_time[7]; */
	
	t_pstat		official_s[7];
	t_pstat		wished_s[7];
	
	/* t_	left_relationship[7]; //mon status vis a vis de la G */
	/* t_	right_relationship[7];//mon status vis a vis de la D */
	
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

/* typedef struct	s_stick */
/* { */
/* 	t_cooi		coo; */
/* 	int			stick_id; */
/* 	t_sstat		stick_status; */
/* }				t_stick; */


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
void			phi_put_strings(t_cenv *e);

/*
** *****************************************************************************
*/

#endif
