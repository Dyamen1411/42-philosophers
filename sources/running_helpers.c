/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:15:28 by amassias          #+#    #+#             */
/*   Updated: 2024/03/18 16:32:57 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file running_helpers.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-04
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	context_is_running(
			t_context *ctx
			)
{
	bool	running;

	pthread_mutex_lock(&ctx->mutexes.simulation_running);
	running = ctx->is_simulation_running;
	pthread_mutex_unlock(&ctx->mutexes.simulation_running);
	return (running);
}

void	context_kill_simulation(
			t_context *ctx
			)
{
	pthread_mutex_lock(&ctx->mutexes.simulation_running);
	ctx->is_simulation_running = false;
	pthread_mutex_unlock(&ctx->mutexes.simulation_running);
}
