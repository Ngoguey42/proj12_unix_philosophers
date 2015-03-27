/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 10:12:28 by ngoguey           #+#    #+#             */
/*   Updated: 2015/03/27 09:19:19 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHI_H
# define PHI_H

# include <libft.h>
# include <ft_math.h>
# include <pthread.h>
# include <time.h>

/*
** nm philo | grep -v _phi_ | grep -v " L_" | grep -v "EH_fr" | grep -v "mlx" |
** grep -v "__stack_" | grep -v "_ft_" | grep -v "OBJC_CLASS" | grep -v "_ptf" |
** grep -v "_gl" | grep -v "_build_nb" | grep -v "OBJC" | grep -v "Win" |
** grep -v "_store_op"
*/

# define MAX_LIFE 50
# define EAT_T 7
# define REST_T 5
# define THINK_T 3
# define TIMEOUT 300

# define CAN_WAIT_TO_EAT 0

# define LEAVE_MSG "Now, it is time... To DAAAAAAAANCE ! ! !\n"
# define TIMEFAIL_MSG "Could not retrieve time\n"
# define CONNECTION_FAIL "Could not establish connection to X-Window server.\n"
# define WINDOW_FAIL "Could not create new window.\n"
# define IMAGE_FAIL "Could not create new image.\n"
# define IMAGE_DATA_FAIL "Could not retrieve image's data.\n"

/*
** *****************************************************************************
** *********************************GRAPH PART**********************************
** *****************************************************************************
** 'struct s_grap' Graphical datas. (1 instance, inside main's t_env)
** 		'redraw'	bool, screen (t_img) + text overlay redraw
** 		'redrawt'	bool, text overlay redraw
**		'serv'		mlx's serv pointer
**		'win'		mlx's window pointer
**		's'			screen image datas.
*/

typedef struct	s_graph
{
	int			redraw;
	int			redrawt;
	void		*serv;
	void		*win;
	t_img		s;
}				t_graph;

/*
** 'enum e_sdir' Sticks on screen direction.
** 'struct s_stick' Sticks Graph datas (21 instances, 7 Sticks * 3 Positions)
** 		Contant datas.
*/
typedef enum	e_sdir
{
	h,
	v,
}				t_sdir;

typedef struct	s_stick
{
	t_cooi		coo;
	int			stick_id;
	int			owner;
	t_sdir		direction;
}				t_stick;

# define WINX	1200
# define RATIO	(4. / 3.)
# define WIN_X	(int)(WINX)
# define WIN_Y	(int)((double)WIN_X / RATIO)

# define TABLE_LEFTPAD 400
# define TABLE_TOPPAD 250
# define TABLE_RADIUS 200

# define PHILO_RADIUS 30
# define PHILO_TABLEPAD 10

# define STICK_LEN 25

# ifndef POSITIONS_ABREVIATIONS
#  define POSITIONS_ABREVIATIONS

#  define LP TABLE_LEFTPAD
#  define TP TABLE_TOPPAD
#  define TR TABLE_RADIUS
#  define TR2 TABLE_RADIUS * 2
#  define HTR TABLE_RADIUS / 2

#  define PR PHILO_RADIUS
#  define PR2 PHILO_RADIUS * 2
#  define PTP PHILO_TABLEPAD

#  define SL STICK_LEN
# endif

# ifndef PHILO_COORD_MACROS
#  define PHILO_COORD_MACROS
#  define P_ICOOADD(A, B) ACOOTOI((A).x + (B).x, (A).y + (B).y, 0)
#  define P_ACOOADD(A, X, Y) ACOOTOI((A).x + (X), (A).y + (Y), 0)
# endif

# define P0_POS (t_cooi){LP + TR - PR,			TP - PTP - PR2, 0}
# define P1_POS (t_cooi){LP + TR2 + PTP,		TP + 10, 0}
# define P2_POS (t_cooi){LP + TR2 + PTP,		TP + 215, 0}
# define P3_POS (t_cooi){LP + TR + 110 - PR,	TP + TR2 + PTP, 0}
# define P4_POS (t_cooi){LP + TR - 110 - PR,	TP + TR2 + PTP, 0}
# define P5_POS (t_cooi){LP - PTP - PR2,		TP + 215, 0}
# define P6_POS (t_cooi){LP - PTP - PR2,		TP + 10, 0}

/*
** *****************************************************************************
** **********************************GAME PART**********************************
** *****************************************************************************
** 'enum e_pstat' Philosopher official status.
*/
typedef enum	e_pstat
{
	start = 0,
	rest = 1,
	think = 2,
	eat = 3,
	wthink = 4,
	weat = 5,
}				t_pstat;
/*
** 'enum e_owntype'	Type of ownership for a Stick
*/
typedef enum	e_owntype
{
	available = 0,
	soft_locked = 1,
	hard_locked = 2,
}				t_owntype;
/*
** 'enum e_philock' Philosopher's lock status toward one mutex.
*/
typedef enum	e_philock
{
	ignored = 0,
	waited = 1,
	think_with = 2,
	stolen = 3,
	eat_with = 4,
}				t_philock;
/*
** 'struct s_env' (1 instance, inside 'main' function)
**		'g'				mlx vars + bool redraw
**		'play'			stop game @ 0
**		'stick_state_change'	strings redraw
**		'init_time'		game start time
**		'last_time'		last game's update
**		'end_time'		game end time
** ** sticks (mutexes)
**		'mutex'			mutexes
**		'own_type'		type of ownership
**		'owner'			owner id (-1 of none)
** ** philosophers (threads)
**		'tid'			threads id (set by main thread)
**		'phi_hp'		phi hp (set by main thread)
**		'official_s'	official status, set by the philosopher himself
**		'act_end_time'	end time of current action
**		'eating_delta'	delta hp to gain each sec, while eating
**		'llock'			philosopher's status toward left stick
**		'rlock'			philosopher's status toward right stick
**		'r_asked'		(set by right neighbor) when he requires the stick
**		'l_asked'		(set by left neighbor) when he requires the stick
**		'think_stick'	stick id when thinking
*/
typedef pthread_mutex_t		t_mutex;
typedef struct	s_env
{
	t_graph		g;
	int			play;
	int			stick_state_change;
	time_t		init_time;
	time_t		last_time;
	time_t		end_time;
	t_ui64		t;

	t_mutex		mutex[7];
	t_owntype	own_type[7];
	int			owner[7];

	pthread_t	tid[7];
	int			phi_hp[7];
	t_pstat		official_s[7];
	time_t		act_end_time[7];
	int			eating_delta[7];
	t_philock	llock[7];
	t_philock	rlock[7];
	int			r_asked[7];
	int			l_asked[7];
	int			think_stick[7];
}				t_env;
# define CS_ENV const struct s_env

typedef CS_ENV	t_cenv;

/*
** P_RSID, Right hand Stick ID. (from philo)
** P_LSID, Left hand Stick ID. (from philo)
** *
** S_RPID, Right hand Philo ID. (from stick)
** S_LPID, Left hand Philo ID. (from stick)
** *
** P_RPID, Right hand Philo ID. (from philo)
** P_LPID, Left hand Philo ID. (from philo)
*/
# define P_RSID(pid) (pid == 0 ? 6 : pid - 1)
# define P_LSID(pid) (pid)
# define S_RPID(sid) (sid)
# define S_LPID(sid) (sid == 6 ? 0 : sid + 1)
# define P_RPID(pid) (pid == 0 ? 6 : pid - 1)
# define P_LPID(pid) (pid == 6 ? 0 : pid + 1)

/*
** ISLPICK, Is left philosopher picking.
** ISRPICK, Is right philosopher picking.
** *
** ISLAVAILABLE, Is left stick available.
** ISRAVAILABLE, Is right stick available.
** *
** LS_TIME_LEFT, Left stick time left.
** RS_TIME_LEFT, Right stick time left.
** *
** P_HP, Left stick time left.
** P_LPHP, Left stick time left.
** P_RPHP, Left stick time left.
** P_ACT, Official status for .
** *
** S_LP_RLOCK, Left philosopher's right lock status (from stick)
** S_RP_LLOCK, Right philosopher's left lock status (from stick)
*/

# define ISLPICKNG			(e->act_end_time[P_LPID(id)] <= e->last_time)
# define ISRPICKNG			(e->act_end_time[P_RPID(id)] <= e->last_time)
# define ISLAVAILABLE		(e->own_type[P_LSID(id)] == 0)
# define ISRAVAILABLE		(e->own_type[P_RSID(id)] == 0)
# define P_HP				(e->phi_hp[id])
# define P_LPHP				(e->phi_hp[P_LPID(id)])
# define P_RPHP				(e->phi_hp[P_RPID(id)])
# define P_ACT				(e->official_s[id])
# define S_LP_RLOCK(sid)	(e->rlock[S_LPID(sid)])
# define S_RP_LLOCK(sid)	(e->llock[S_RPID(sid)])
# define P_LP_RLOCK(pid)	(e->rlock[P_LPID(pid)])
# define P_RP_LLOCK(pid)	(e->llock[P_RPID(pid)])
# define P_LLOCK(pid)		(e->llock[pid])
# define P_RLOCK(pid)		(e->rlock[pid])
# define ISLASKED			(e->l_asked[id])
# define ISRASKED			(e->r_asked[id])

/*
** *****************************************************************************
*/
typedef struct	s_thread
{
	t_env		*e;
	int			id;
}				t_thread;

/*
** *****************************************************************************
** *********************************PROTOTYPES**********************************
** *****************************************************************************
*/

int				phi_init_env(t_env *e, t_thread tid[7]);
void			*phi_thread_split(void *ptr);
void			phi_leave_correctly(t_env *e, int nthrd, int nmutx, char *msg);
/*
** Phi action
*/
void			phi_start_end_event(t_env *e, int id);
void			phi_eat_start_event(t_env *e, int id);
void			phi_eat_end_event(t_env *e, int id);
void			phi_rest_end_event(t_env *e, int id);
void			phi_rest_start_event(t_env *e, int id);
void			phi_think_start_event(t_env *e, int id);
void			phi_think_stolen_event(t_env *e, int id, int isright);
void			phi_think_end_event(t_env *e, int id);
void			phi_waiteat_start_event(t_env *e, int id);
void			phi_waiteat_end_event(t_env *e, int id);
void			phi_waitthink_start_event(t_env *e, int id);
void			phi_waitthink_end_event(t_env *e, int id);
void			phi_can_wait_to_eat_pick(t_env *e, int id);
void			phi_cant_wait_to_eat_pick(t_env *e, int id);

/*
**Mlx
*/
int				phi_init_mlx(t_env *e);
void			phi_pause_mlx(t_env *e);
int				phi_loop_hook(void *envp);
int				phi_redraw_surface(t_env *e);
int				phi_quit_mlx(t_graph *g);
int				phi_puts_pix(const t_graph *e, t_cooi coo, t_co c);
int				phi_put_string(const t_graph *e, t_cooi coo, t_co c, char *str);
/*
** Redraw
*/
void			phi_redraw_image(t_cenv *e);
void			phi_putphilo(const t_graph *g);
void			phi_puttable(const t_graph *g);
void			phi_put_strings(t_cenv *e);
void			phi_put_sticks(t_cenv *e);

/*
** *****************************************************************************
*/

#endif
