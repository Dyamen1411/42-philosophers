/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:32:20 by amassias          #+#    #+#             */
/*   Updated: 2024/03/19 17:13:25 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file philo_life.c
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

#include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	*philo_life(
			void *p
			)
{
	t_philo *const		philo = p;
	t_philo_ctx *const	ctx = philo->ctx;

	if (philo->id % 2)
		custom_sleep(philo, 4);
	while (philo_is_running(ctx))
	{
		philo_eat(philo);
		if (!philo_is_running(philo->ctx))
			break ;
		philo_log(ctx, philo->id, ACTION_SLEEPING);
		custom_sleep(philo, ctx->timers.sleep);
		philo_log(ctx, philo->id, ACTION_THINKING);
	}
	return (NULL);
}
