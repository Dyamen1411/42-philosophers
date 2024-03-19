/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:21:18 by amassias          #+#    #+#             */
/*   Updated: 2024/01/13 22:11:42 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file philo.h
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-01-09
 * @copyright Copyright (c) 2024
 */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdnoreturn.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

# define ERR_BAD_ALLOC 1

# define ARG1 "number_of_philosophers"
# define ARG2 "time_to_die"
# define ARG3 "time_to_eat"
# define ARG4 "time_to_sleep"
# define ARG5 "number_of_times_each_philosopher_must_eat"

/* ************************************************************************** */
/*                                                                            */
/* Enumerations                                                               */
/*                                                                            */
/* ************************************************************************** */

enum e_args
{
	PROG_NAME,
	PROG_NBPHILO,
	PROG_TTODIE,
	PROG_TTOEAT,
	PROG_TTOSLEEP,
	PROG_TTOEACHP,
	PROG__MIN=PROG_TTOSLEEP + 1,
	PROG__MAX=PROG_TTOEACHP + 1,
};

enum e_action
{
	ACTION_FORK_TAKEN,
	ACTION_EATING,
	ACTION_SLEEPING,
	ACTION_THINKING,
	ACTION_DIED
};

/* ************************************************************************** */
/*                                                                            */
/* Structures                                                                 */
/*                                                                            */
/* ************************************************************************** */

struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				dead;
	unsigned int	nb_ate;
	void			*ctx;
	time_t			last_eat;
	pthread_mutex_t	eating;
	pthread_mutex_t	eaten;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
};

struct s_philo_ctx
{
	char			*pn;
	unsigned int	nb;
	int				is_running;
	pthread_mutex_t	mis_running;
	time_t			t_todie;
	time_t			t_toeat;
	time_t			t_tosleep;
	unsigned int	t_toeach;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
};

/* ************************************************************************** */
/*                                                                            */
/* Types                                                                      */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_args			t_args;

typedef enum e_action		t_action;

typedef struct s_philo		t_philo;

typedef struct s_philo_ctx	t_philo_ctx;

/* ************************************************************************** */
/*                                                                            */
/* Header prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

void			philo_init_args(
					t_philo_ctx *ctx,
					int argc,
					char **argv
					);

void			philo_init(
					t_philo_ctx *ctx
					);

void			philo_start(
					t_philo_ctx *ctx
					);

void			philo_destroy(
					t_philo_ctx *ctx
					);

void			*philo_life(
					void *p
					);

void			philo_eat(
					t_philo *philo
					);

int				philo_is_running(
					t_philo_ctx *ctx
					);

void			philo_set_running(
					t_philo_ctx *ctx,
					int running
					);

noreturn void	error(
					t_philo_ctx *ctx,
					const char *message
					);

void			custom_sleep(
					t_philo *philo,
					time_t duration
					);

void			philo_log(
					t_philo_ctx *ctx,
					int id,
					t_action action
					);

int				ft_atot(
					const char *s,
					time_t *t
					);

int				ft_atoui(
					const char *s,
					unsigned int *n
					);

time_t			ft_time_ms(void);

#endif
