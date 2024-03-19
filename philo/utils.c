/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:53:55 by amassias          #+#    #+#             */
/*   Updated: 2024/03/19 17:39:11 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.c
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
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

time_t	_get_current_time(void);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

int	ft_atot(
		const char *str,
		time_t *time_ptr
		)
{
	time_t	_time;

	if (*str == '\0')
		return (0);
	_time = 0;
	while (*str >= '0' && *str <= '9')
	{
		_time *= 10;
		_time += *str - '0';
		++str;
	}
	*time_ptr = _time;
	return (*str == '\0');
}

int	ft_atoui(
		const char *str,
		unsigned int *value_ptr
		)
{
	unsigned int	_value;

	if (*str == '\0')
		return (0);
	_value = 0;
	while (*str >= '0' && *str <= '9')
	{
		_value *= 10;
		_value += *str - '0';
		++str;
	}
	*value_ptr = _value;
	return (*str == '\0');
}

time_t	ft_time_ms(void)
{
	static time_t	initial_time = -1;
	const time_t	current_time = _get_current_time();

	if (initial_time == -1)
		initial_time = current_time;
	return (current_time - initial_time);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

time_t	_get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}
