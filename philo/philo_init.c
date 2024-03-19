/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:00:24 by amassias          #+#    #+#             */
/*   Updated: 2024/03/19 17:56:56 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file philo_init.c
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
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define ERR_NAT_INT "must be a natural integer"
#define ERR_NULL "cannot be null"
#define ERR_MUTEX "mutex initialization error"
#define ERR_ALLOC "Bad allocation"

/* ************************************************************************** */
/*                                                                            */
/* Helper prototypes                                                          */
/*                                                                            */
/* ************************************************************************** */

static void	_philo_init_philos(
				t_philo_ctx *ctx
				);

static void	_philo_init_forks(
				t_philo_ctx *ctx
				);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	philo_init_args(
			t_philo_ctx *ctx,
			int argc,
			char **argv
			)
{
	unsigned int *const	each_ptr = &ctx->timers.each;

	ctx->program_name = argv[PROG_NAME];
	ctx->philos = NULL;
	ctx->is_running = false;
	ctx->forks = NULL;
	if (!ft_atoui(argv[PROG_PHILO_COUNT], &ctx->philo_count))
		error(ctx, ARG1 " " ERR_NAT_INT);
	if (!ft_atot(argv[PROG_DEATH_TIMER], &ctx->timers.death))
		error(ctx, ARG2 " " ERR_NAT_INT);
	if (!ft_atot(argv[PROG_EAT_TIMER], &ctx->timers.eat))
		error(ctx, ARG3 " " ERR_NAT_INT);
	if (!ft_atot(argv[PROG_SLEEP_TIMER], &ctx->timers.sleep))
		error(ctx, ARG4 " " ERR_NAT_INT);
	if (argc == PROG__MAX && !ft_atoui(argv[PROG_EACHP_TIMER], each_ptr))
		error(ctx, ARG5 " " ERR_NAT_INT);
	if (argc != PROG__MAX)
		*each_ptr = __INT_MAX__;
	if (ctx->philo_count == 0)
		error(ctx, ARG1 " " ERR_NULL);
	if (pthread_mutex_init(&ctx->mutex_is_running, NULL))
		error(ctx, ERR_MUTEX);
}

void	philo_init(
			t_philo_ctx *ctx
			)
{
	ctx->forks = malloc(sizeof(*ctx->forks) * ctx->philo_count);
	if (ctx->forks == NULL)
		error(ctx, ERR_ALLOC);
	_philo_init_forks(ctx);
	ctx->philos = malloc(sizeof(*ctx->philos) * ctx->philo_count);
	if (ctx->philos == NULL)
		error(ctx, ERR_ALLOC);
	_philo_init_philos(ctx);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static void	_philo_init_philos(
				t_philo_ctx *ctx
				)
{
	size_t	i;

	i = 0;
	while (i < ctx->philo_count)
	{
		ctx->philos[i].r_fork = &ctx->forks[(i + 1) % ctx->philo_count];
		ctx->philos[i].l_fork = &ctx->forks[i];
		ctx->philos[i].id = i;
		ctx->philos[i].last_time_eaten = 0;
		ctx->philos[i].times_eaten = 0;
		ctx->philos[i].ctx = ctx;
		ctx->philos[i].thread_id = 0;
		if (pthread_mutex_init(&ctx->philos[i].mutex_eating, NULL)
			|| pthread_mutex_init(&ctx->philos[i].mutex_eaten, NULL))
			error(ctx, ERR_MUTEX);
		ctx->philos[i++].is_dead = 0;
	}
}

static void	_philo_init_forks(
				t_philo_ctx *ctx
				)
{
	size_t	i;

	i = 0;
	while (i < ctx->philo_count)
		if (pthread_mutex_init(&ctx->forks[i++], NULL))
			break ;
	if (i == ctx->philo_count)
		return ;
	while (i--)
		pthread_mutex_destroy(&ctx->forks[i]);
}
