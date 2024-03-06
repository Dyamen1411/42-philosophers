/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:37:17 by amassias          #+#    #+#             */
/*   Updated: 2024/03/06 18:13:04 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>

enum	e_action
{
	ACTION_TAKE,
	ACTION_EATING,
	ACTION_SLEEPING,
	ACTION_THINKING,
	ACTION_DEATH
};

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
	struct s_context	*context;
};

typedef enum e_action			t_action;

typedef struct s_settings		t_settings;

typedef struct s_philosopher	t_philosopher;

typedef struct s_context		t_context;

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