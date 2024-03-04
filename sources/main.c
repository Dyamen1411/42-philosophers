/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:30:38 by amassias          #+#    #+#             */
/*   Updated: 2024/03/04 17:52:12 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_NEA "%s: Not enough arguments"
#define ERR_TMA "%s: Too many arguments"
#define ERR_NNA "%s: %s: Expected numeric argument"

static bool	_parse_args(
				char *pname,
				t_settings *settings,
				char **args
				);

int	main(
		int argc,
		char **argv
		)
{
	t_context	context;

	if (argc < 5)
		return (dprintf(STDERR_FILENO, ERR_NEA "\n", *argv), 1);
	if (argc > 6)
		return (dprintf(STDERR_FILENO, ERR_TMA "\n", *argv), 1);
	if (_parse_args(argv[0], &context.settings, argv + 1))
		return (2);
	printf("philosopher_count: %u\n", context.settings.philosopher_count);
	printf("death_timer      : %lu\n", context.settings.death_timer);
	printf("eating_timer     : %lu\n", context.settings.eating_timer);
	printf("sleeping_timer   : %lu\n", context.settings.sleeping_timer);
	printf("max_eating       : %lu\n", context.settings.max_eating);
	return (EXIT_SUCCESS);
}

static bool	_parse_args(
				char *pname,
				t_settings *settings,
				char **args
				)
{
	if (read_unsinged_int(args[0], &settings->philosopher_count))
		return (dprintf(STDERR_FILENO, ERR_NNA "\n", pname, args[0]), true);
	if (read_unsigned_long(args[1], &settings->death_timer))
		return (dprintf(STDERR_FILENO, ERR_NNA "\n", pname, args[1]), true);
	if (read_unsigned_long(args[2], &settings->eating_timer))
		return (dprintf(STDERR_FILENO, ERR_NNA "\n", pname, args[2]), true);
	if (read_unsigned_long(args[3], &settings->sleeping_timer))
		return (dprintf(STDERR_FILENO, ERR_NNA "\n", pname, args[3]), true);
	if (args[4] == NULL)
		settings->max_eating = 0;
	else if (read_unsigned_long(args[4], &settings->max_eating))
		return (dprintf(STDERR_FILENO, ERR_NNA "\n", pname, args[4]), true);
	return (false);
}
