/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:34:20 by amassias          #+#    #+#             */
/*   Updated: 2024/03/18 16:33:39 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file readers.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-04
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

bool	read_unsinged_int(
			char *str,
			unsigned int *v
			)
{
	bool			ok;
	unsigned int	tmp;
	unsigned int	digit;

	ok = false;
	while (is_space(*str))
		++str;
	*v = 0;
	while (is_digit(*str))
	{
		digit = *str++ - '0';
		tmp = 10 * *v + digit;
		if (tmp < *v || (tmp - digit) / 10 != *v)
			return (true);
		*v = tmp;
		ok = true;
	}
	while (is_space(*str))
		++str;
	return (*str != '\0' || !ok);
}

bool	read_unsigned_long(
			char *str,
			unsigned long *v
			)
{
	bool			ok;
	unsigned long	tmp;
	unsigned int	digit;

	ok = false;
	while (is_space(*str))
		++str;
	*v = 0;
	while (is_digit(*str))
	{
		digit = *str++ - '0';
		tmp = 10 * *v + digit;
		if (tmp < *v || (tmp - digit) / 10 != *v)
			return (true);
		*v = tmp;
		ok = true;
	}
	while (is_space(*str))
		++str;
	return (*str != '\0' || !ok);
}
