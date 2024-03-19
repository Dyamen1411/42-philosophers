/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:29:32 by amassias          #+#    #+#             */
/*   Updated: 2024/03/19 17:29:36 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file philo_start
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-01-16
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
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define ERR_THREAD_INIT "Thread initialization error"

/* ************************************************************************** */
/*                                                                            */
/* Helper prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

static void	_philo_wait_thread(
				t_philo_ctx *ctx
				);

static void	_philo_check_each(
				t_philo_ctx *ctx
				);

static void	_philo_died(
				t_philo_ctx *ctx
				);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	philo_start(
			t_philo_ctx *ctx
			)
{
	size_t	i;

	ctx->is_running = 1;
	i = 0;
	while (i < ctx->philo_count)
	{
		ctx->philos[i].last_time_eaten = ft_time_ms();
		if (pthread_create(&ctx->philos[i].thread_id, NULL,
				philo_life, &ctx->philos[i]))
		{
			philo_set_running(ctx, 0);
			_philo_wait_thread(ctx);
			error(ctx, ERR_THREAD_INIT);
		}
		usleep(500);
		++i;
	}
	_philo_died(ctx);
	_philo_wait_thread(ctx);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static void	_philo_wait_thread(
				t_philo_ctx *ctx
				)
{
	size_t	i;

	i = 0;
	while (i < ctx->philo_count)
	{
		if (ctx->philos[i].thread_id != 0)
			pthread_join(ctx->philos[i].thread_id, NULL);
		++i;
	}
}

static void	_philo_check_each(
				t_philo_ctx *ctx
				)
{
	size_t			i;
	unsigned int	nb_ate;

	i = 0;
	while (i < ctx->philo_count && ctx->timers.each != __INT_MAX__)
	{
		pthread_mutex_lock(&ctx->philos[i].mutex_eaten);
		nb_ate = ctx->philos[i].times_eaten;
		pthread_mutex_unlock(&ctx->philos[i].mutex_eaten);
		if (nb_ate < (unsigned int) ctx->timers.each)
			break ;
		++i;
	}
	if (i == ctx->philo_count)
		philo_set_running(ctx, 0);
}

static void	_philo_died(
				t_philo_ctx *ctx
				)
{
	size_t	i;
	time_t	time_since_eaten;

	while (philo_is_running(ctx))
	{
		i = 0;
		while (i < ctx->philo_count)
		{
			pthread_mutex_lock(&ctx->philos[i].mutex_eating);
			time_since_eaten = ft_time_ms() - ctx->philos[i].last_time_eaten;
			if (time_since_eaten >= ctx->timers.death)
			{
				philo_set_running(ctx, 0);
				philo_log(ctx, i, ACTION_DIED);
				pthread_mutex_unlock(&ctx->philos[i].mutex_eating);
				break ;
			}
			pthread_mutex_unlock(&ctx->philos[i].mutex_eating);
			++i;
		}
		_philo_check_each(ctx);
	}
}
