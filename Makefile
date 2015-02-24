#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/04 11:28:17 by ngoguey           #+#    #+#              #
#    Updated: 2015/02/24 09:28:05 by wide-aze         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = philo

# LIBFT
LFTPATH = libft/
LFTIPATH = -I $(LFTPATH)includes/
LFT = -L $(LFTPATH) -lft

OBJPATH = obj
SRCPATH = .
INCLUDE = -I ./

CC = gcc

LIBS = $(LFT) -L/usr/X11/lib
INCLUDES = $(INCLUDE) $(LFTIPATH)

BASEFLAGS = -Wall -Wextra -lmlx -lXext -lX11
CFLAGS = $(BASEFLAGS) -Werror -O2
DEBUGFLAGS = $(BASEFLAGS) -g

LFTCALL = all
LFTRE = re
LFTG = g
LFTGRE = gre

# Put new sources here / Mettre les nouvelles sources ici.
SRCSFILES = main.c init_env.c com_mlx.c redraw.c\
mlx_hooks.c philo.c putpix_mlx.c put_objects.c put_sticks.c put_strings.c\
 philo_eat.c philo_rest.c philo_think.c philo_wait.c

SRC = $(addprefix $(SRCPATH)/,$(SRCSFILES))
OBJECTS = $(SRC:$(SRCPATH)/%.c=$(OBJPATH)/%.o)

RM = rm -rf

Y = \033[0;33m
R = \033[0;31m
G = \033[0;32m
E = \033[39m

W = 0

all: l $(NAME)

$(NAME): $(OBJECTS)
	@echo -e "$(Y)[COMPILING SH] $(G) $(CC) -o $@ $(CFLAGS) objs.o $(LIBS) $(E)"
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIBS)
	@echo -e "$(Y)[COMPILING SH]$(E)"

$(OBJECTS): $(OBJPATH)/%.o : $(SRCPATH)/%.c
	@if [ $(W) -eq 0 ] ; then printf "$(R)%-10s$(E): %s\n$(R)%-10s$(E): %s\n$(R)%-10s$(E): %s\n$(R)%-10s$(E): %s\n"\
		"=>COMPILER"\
		"$(CC)"\
		"=>CFLAGS"\
		"$(CFLAGS)"\
		"=>INCLUDES"\
		"$(INCLUDES)"\
		"=>LIBS"\
		"$(LIBS)" ;\
	fi
	$(eval W = 1)
	@mkdir -p $(dir $@)
	@echo -e "$(R)COMPILER$(E) -o $@ $(R)CFLAGS INCLUDES LIBS$(E) -c [...].c"
	@$(CC) -o $@ $(CFLAGS) $(INCLUDES) $(LIBS) -c $<

clean:
	$(RM) $(OBJPATH)

fclean: clean
	$(RM) $(NAME)

l:
	@echo -e "$(Y)[COMPILING LIBFT] $(G) make -C $(LFTPATH) $(LFTCALL) $(E)"
	@$(MAKE) -C $(LFTPATH) $(LFTCALL)
	@echo -e "$(Y)[COMPILING LIBFT DONE]$(E)"

g: _g _gft all

# re rules
re: fclean all
rel: _relft l
rea: _relft re

# gre rules
gre: _g re
grel: _greft l
grea: _g _greft re

# eval rules
_g:
	$(eval CFLAGS = $(DEBUGFLAGS))
_relft:
	$(eval LFTCALL = $(LFTRE))
_gft:
	$(eval LFTCALL = $(LFTG))
_greft:
	$(eval LFTCALL = $(LFTGRE))
