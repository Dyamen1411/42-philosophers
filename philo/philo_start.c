/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:29:32 by amassias          #+#    #+#             */
/*   Updated: 2024/02/16 17:07:41 by amassias         ###   ########.fr       */
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
	size_t	k;

	ctx->is_running = 1;
	k = 0;
	while (k < ctx->nb)
	{
		ctx->philos[k].last_eat = ft_time_ms();
		if (pthread_create(&ctx->philos[k].thread_id, NULL,
				philo_life, &ctx->philos[k]))
		{
			philo_set_running(ctx, 0);
			_philo_wait_thread(ctx);
			error(ctx, ERR_THREAD_INIT);
		}
		usleep(500);
		++k;
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
	size_t	k;

	k = 0;
	while (k < ctx->nb)
	{
		if (ctx->philos[k].thread_id != 0)
			pthread_join(ctx->philos[k].thread_id, NULL);
		++k;
	}
}

static void	_philo_check_each(
				t_philo_ctx *ctx
				)
{
	size_t			k;
	unsigned int	nb_ate;

	k = 0;
	while (k < ctx->nb && ctx->t_toeach != __INT_MAX__)
	{
		pthread_mutex_lock(&ctx->philos[k].eaten);
		nb_ate = ctx->philos[k].nb_ate;
		pthread_mutex_unlock(&ctx->philos[k].eaten);
		if (nb_ate < (unsigned int) ctx->t_toeach)
			break ;
		++k;
	}
	if (k == ctx->nb)
		philo_set_running(ctx, 0);
}

static void	_philo_died(
				t_philo_ctx *ctx
				)
{
	size_t	k;

	while (philo_is_running(ctx))
	{
		k = 0;
		while (k < ctx->nb)
		{
			pthread_mutex_lock(&ctx->philos[k].eating);
			if (ft_time_ms() - ctx->philos[k].last_eat >= ctx->t_todie)
			{
				philo_set_running(ctx, 0);
				philo_log(ctx, k, ACTION_DIED);
				pthread_mutex_unlock(&ctx->philos[k].eating);
				break ;
			}
			pthread_mutex_unlock(&ctx->philos[k].eating);
			++k;
		}
		_philo_check_each(ctx);
	}
}
