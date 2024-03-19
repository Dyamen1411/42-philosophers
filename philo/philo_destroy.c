/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:35:28 by amassias          #+#    #+#             */
/*   Updated: 2024/03/19 17:23:12 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file philo_destroy.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-01-13
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
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	philo_destroy(
			t_philo_ctx *ctx
			)
{
	size_t	i;

	pthread_mutex_destroy(&ctx->mutex_is_running);
	if (ctx->forks == NULL)
		return ;
	i = 0;
	while (i < ctx->philo_count)
		pthread_mutex_destroy(&ctx->forks[i++]);
	free(ctx->forks);
	if (ctx->philos == NULL)
		return ;
	i = 0;
	while (i < ctx->philo_count)
	{
		pthread_mutex_destroy(&ctx->philos[i].mutex_eating);
		pthread_mutex_destroy(&ctx->philos[i].mutex_eaten);
		++i;
	}
	free(ctx->philos);
}
