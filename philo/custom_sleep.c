/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:54:20 by amassias          #+#    #+#             */
/*   Updated: 2024/03/19 16:48:40 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file custom_sleep.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-01-13
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	custom_sleep(
			t_philo *philo,
			time_t duration
			)
{
	time_t	now;

	now = ft_time_ms();
	while (now + duration > ft_time_ms())
	{
		if (!philo_is_running(philo->ctx))
			break ;
		usleep(((t_philo_ctx *)philo->ctx)->philo_count * 2);
	}
}
