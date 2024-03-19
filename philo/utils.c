/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:53:55 by amassias          #+#    #+#             */
/*   Updated: 2024/01/13 19:11:37 by amassias         ###   ########.fr       */
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
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

int	ft_atot(
		const char *s,
		time_t *t
		)
{
	time_t	k;

	if (*s == '\0')
		return (0);
	k = 0;
	while (*s >= '0' && *s <= '9')
	{
		k *= 10;
		k += *s - '0';
		++s;
	}
	*t = k;
	return (*s == '\0');
}

int	ft_atoui(
		const char *s,
		unsigned int *n
		)
{
	unsigned int	k;

	if (*s == '\0')
		return (0);
	k = 0;
	while (*s >= '0' && *s <= '9')
	{
		k *= 10;
		k += *s - '0';
		++s;
	}
	*n = k;
	return (*s == '\0');
}

time_t	ft_time_ms(void)
{
	static time_t	initime = -1;
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (initime == -1)
		initime = (t.tv_sec * 1000 + t.tv_usec / 1000);
	return ((t.tv_sec * 1000 + t.tv_usec / 1000) - initime);
}
