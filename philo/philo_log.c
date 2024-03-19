/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:03:50 by amassias          #+#    #+#             */
/*   Updated: 2024/03/19 16:49:06 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file philo_log.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-01-09
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ************************************************************************** */
/*                                                                            */
/* Global variables                                                           */
/*                                                                            */
/* ************************************************************************** */

static const char	*g_messages[] = {
[ACTION_FORK_TAKEN] = "has taken a fork",
[ACTION_EATING] = "is eating",
[ACTION_SLEEPING] = "is sleeping",
[ACTION_THINKING] = "is thinking",
[ACTION_DIED] = "died",
};

/* ************************************************************************** */
/*                                                                            */
/* Helper prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

void	philo_log(
			t_philo_ctx *ctx,
			int id,
			t_action action
			)
{
	static pthread_mutex_t	mut = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mut);
	if (philo_is_running(ctx) || action == ACTION_DIED)
		printf("%-8ld%d %s\n", ft_time_ms(), id, g_messages[action]);
	pthread_mutex_unlock(&mut);
}

int	philo_is_running(
		t_philo_ctx *ctx
		)
{
	int	is_running;

	pthread_mutex_lock(&ctx->mutex_is_running);
	is_running = ctx->is_running;
	pthread_mutex_unlock(&ctx->mutex_is_running);
	return (is_running);
}

void	philo_set_running(
			t_philo_ctx *ctx,
			int running
			)
{
	pthread_mutex_lock(&ctx->mutex_is_running);
	ctx->is_running = running;
	pthread_mutex_unlock(&ctx->mutex_is_running);
}
