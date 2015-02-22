/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 10:12:28 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/20 17:45:08 by wide-aze         ###   ########.fr       */
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

# define STEP 1 //don't use for now
# define USTEP (STEP * 100000) //don't use for now

# define LEAVE_MSG "Now, it is time... To DAAAAAAAANCE ! ! !\n"
# define TIMEFAIL_MSG "Could not retrieve time\n"
# define CONNECTION_FAIL "Could not establish connection to X-Window server.\n"
# define WINDOW_FAIL "Could not create new window.\n"
# define IMAGE_FAIL "Could not create new image.\n"
# define IMAGE_DATA_FAIL "Could not retrieve image's data.\n"
# define ERR_INIT_MUTEXES "Could not init mutexes.\n"
# define ERR_CREATE_THREADS "Could not create threads.\n"

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
	horiz,
	vert,
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

# define P0_POS (t_cooi){LP + TR - PR,		TP - PTP - PR2, 0}
# define P1_POS (t_cooi){LP + TR2 + PTP,	TP + 10, 0}
# define P2_POS (t_cooi){LP + TR2 + PTP,	TP + 255, 0}
# define P3_POS (t_cooi){TR + 140 - PR,		TP + TR2 + PTP, 0}
# define P4_POS (t_cooi){TR - 140 - PR,		TP + TR2 + PTP, 0}
# define P5_POS (t_cooi){LP - PTP - PR2,	TP + 255, 0}
# define P6_POS (t_cooi){LP - PTP - PR2,	TP + 10, 0}

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
	await = 4,
}				t_pstat;
/*
** 'enum e_owntype'	Type of ownership for a Stick
*/
typedef enum	e_owntype
{
	available = 0,
	soft_lock = 1,
	hard_lock = 2,
}				t_owntype;
/*
** 'enum e_philock' Philosopher's lock status toward one mutex.
*/
typedef enum	e_philock
{
	ignoring = 0,
	waiting = 1,
	locking = 2,
}				t_philock;
/*
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
typedef pthread_mutex_t		t_mutex;
typedef struct	s_env
{
	t_graph		g;
	int			play;		//set par emulateur, update apres HPupdate
	time_t		init_time;
	time_t		last_time; //game time, used to update HP
	time_t		end_time;
//** **************************************************************************
//** **************************************************************************
//** **************************************************************************
	t_mutex		mutex[7]; //RESSOURCE PARTAGEE
	t_owntype	own_type[7]; //RESSOURCE PARTAGEE
	/*
		own_type:
			By Main:	Game_start			=> available
			By philo: 	After mutex_lock	=> hard_lock
			By philo: 	After mutex_unlock	=> available

			est-ce qu'on ignore totalement le thinking ?
			c'est problematique a mettre ici vu que c'est de la ressource partagee
			sinon on laisse le travail sur set cette variable au main-thread.
	*/
	int			owner[7]; //RESSOURCE PARTAGEE
	//initialiser à -1, reset à -1 quand dispo (pour le redraw)
	/*
		own_type: Edition seulement quand posession du mutex
			By Main:	Game_start			=> -1
			By philo:	After mutex_lock	=> Philo id
			By philo:	After mutex_unlock	=> -1
	*/
//** **************************************************************************
//** **************************************************************************
//** **************************************************************************
	pthread_t	tid[7];
	int			phi_hp[7];//set par l'emulateur
	t_pstat		official_s[7];//set par le philo
	/*
		official_s:
			Game_start		=> start
			on_rest_start	=> rest
			on_wait_start	=> wait
			on_wait_end		=> eat/think
	*/
	time_t		act_end_time[7];//set par philo, on_action_start
	int			eating_delta[7];//set par le philo, on_eat_start

	t_philock	llock[7];
	t_philock	rlock[7];
	/*
		'llock' / 'rlock'
			Game_start		=> 0
			Before lock		=> waiting
			After lock		=> locking
			After unlock	=> ignoring
	*/
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
# define P_LPID(pid) (pid == 6 ? 0 pid + 1)
/*
** ISLPICK, Is left philosopher picking.
** ISRPICK, Is right philosopher picking.
*/
# define ISLPICKNG(pid) (e->act_end_time[P_LPID(pid)] <= curtime)
# define ISRPICKNG(pid) (e->act_end_time[P_RPID(pid)] <= curtime)

/*
** *****************************************************************************
*/
typedef struct	s_thread
{
	t_env		*e;
	int			id;
}				t_thread;

// typedef enum	e_spos
// {
	// right,
	// available,
	// left,
// }				t_spos;

/*
** *****************************************************************************
** *********************************PROTOTYPES**********************************
** *****************************************************************************
*/

int				phi_init_env(t_env *e, t_thread tid[7]);
void			*phi_thread_split(void *ptr);
void			phi_leave_correctly(t_env *e, int nthrd, int nmutx, char *msg);
/*
**Mlx
*/
int				phi_init_mlx(t_env *e);
void			phi_pause_mlx(t_env *e);
int				phi_loop_hook(void *envp);
int				phi_redraw_surface(t_cenv *e);
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

/*
** *****************************************************************************
*/

#endif
