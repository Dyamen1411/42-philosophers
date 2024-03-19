/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:35:28 by amassias          #+#    #+#             */
/*   Updated: 2024/01/13 22:02:08 by amassias         ###   ########.fr       */
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
	size_t	k;

	if (ctx->forks != NULL)
	{
		k = 0;
		while (k < ctx->nb)
			pthread_mutex_destroy(&ctx->forks[k++]);
		free(ctx->forks);
	}
	if (ctx->philos != NULL)
	{
		k = 0;
		while (k < ctx->nb)
		{
			pthread_mutex_destroy(&ctx->philos[k].eating);
			pthread_mutex_destroy(&ctx->philos[k].eaten);
			++k;
		}
		free(ctx->philos);
	}
	pthread_mutex_destroy(&ctx->mis_running);
}
