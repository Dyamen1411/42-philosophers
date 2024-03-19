/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:00:24 by amassias          #+#    #+#             */
/*   Updated: 2024/01/13 21:41:14 by amassias         ###   ########.fr       */
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
	ctx->pn = argv[PROG_NAME];
	ctx->philos = NULL;
	ctx->is_running = 0;
	ctx->forks = NULL;
	if (!ft_atoui(argv[PROG_NBPHILO], &ctx->nb))
		error(ctx, ARG1 " " ERR_NAT_INT);
	if (!ft_atot(argv[PROG_TTODIE], &ctx->t_todie))
		error(ctx, ARG2 " " ERR_NAT_INT);
	if (!ft_atot(argv[PROG_TTOEAT], &ctx->t_toeat))
		error(ctx, ARG3 " " ERR_NAT_INT);
	if (!ft_atot(argv[PROG_TTOSLEEP], &ctx->t_tosleep))
		error(ctx, ARG4 " " ERR_NAT_INT);
	if (argc == PROG__MAX && !ft_atoui(argv[PROG_TTOEACHP], &ctx->t_toeach))
		error(ctx, ARG5 " " ERR_NAT_INT);
	if (argc != PROG__MAX)
		ctx->t_toeach = __INT_MAX__;
	if (ctx->nb == 0)
		error(ctx, ARG1 " " ERR_NULL);
	if (pthread_mutex_init(&ctx->mis_running, NULL))
		error(ctx, ERR_MUTEX);
}

void	philo_init(
			t_philo_ctx *ctx
			)
{
	ctx->forks = malloc(sizeof(*ctx->forks) * ctx->nb);
	if (ctx->forks == NULL)
		error(ctx, ERR_ALLOC);
	_philo_init_forks(ctx);
	ctx->philos = malloc(sizeof(*ctx->philos) * ctx->nb);
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
	size_t	k;

	k = 0;
	while (k < ctx->nb)
	{
		ctx->philos[k].r_fork = &ctx->forks[(k + 1) % ctx->nb];
		ctx->philos[k].l_fork = &ctx->forks[k];
		ctx->philos[k].id = k;
		ctx->philos[k].last_eat = 0;
		ctx->philos[k].nb_ate = 0;
		ctx->philos[k].ctx = ctx;
		ctx->philos[k].thread_id = 0;
		if (pthread_mutex_init(&ctx->philos[k].eating, NULL)
			|| pthread_mutex_init(&ctx->philos[k].eaten, NULL))
			error(ctx, ERR_MUTEX);
		ctx->philos[k++].dead = 0;
	}
}

static void	_philo_init_forks(
				t_philo_ctx *ctx
				)
{
	size_t	k;

	k = 0;
	while (k < ctx->nb)
		if (pthread_mutex_init(&ctx->forks[k++], NULL))
			break ;
	if (k != ctx->nb)
		while (k-- != 0)
			pthread_mutex_destroy(&ctx->forks[k]);
}
