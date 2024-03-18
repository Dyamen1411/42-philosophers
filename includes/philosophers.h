/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:37:17 by amassias          #+#    #+#             */
/*   Updated: 2024/03/18 19:28:20 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file philosophers.h
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-02
 * @copyright Copyright (c) 2024
 */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdbool.h>

/* ************************************************************************** */
/*                                                                            */
/* Enums                                                                      */
/*                                                                            */
/* ************************************************************************** */

enum	e_action
{
	ACTION_TAKE,
	ACTION_EATING,
	ACTION_SLEEPING,
	ACTION_THINKING,
	ACTION_DEATH
};

/* ************************************************************************** */
/*                                                                            */
/* Structures                                                                 */
/*                                                                            */
/* ************************************************************************** */

struct	s_settings
{
	unsigned int	philosopher_count;
	unsigned long	death_timer;
	unsigned long	eating_timer;
	unsigned long	sleeping_timer;
	unsigned long	max_eating;
};

struct	s_context
{
	struct s_settings		settings;
	pthread_mutex_t			*forks;
	bool					is_simulation_running;
	struct s_mutexes
	{
		pthread_mutex_t			logging;
		pthread_mutex_t			simulation_running;
		bool					_are_initialized;
	}						mutexes;
};

struct	s_philosopher
{
	unsigned int		id;
	enum e_action		status;
	unsigned long		last_time_eaten;
	pthread_t			thread;
	pthread_mutex_t		last_time_eaten_mutex;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_context	*context;
};

/* ************************************************************************** */
/*                                                                            */
/* Types                                                                      */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_action			t_action;

typedef struct s_settings		t_settings;

typedef struct s_philosopher	t_philosopher;

typedef struct s_context		t_context;

/* ************************************************************************** */
/*                                                                            */
/* Header protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

void	log_action(
			t_context *ctx,
			t_philosopher *philosopher,
			unsigned long timestamp
			);

bool	context_is_running(
			t_context *ctx
			);

void	context_kill_simulation(
			t_context *ctx
			);

#endif