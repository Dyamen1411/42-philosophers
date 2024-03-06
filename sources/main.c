/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:30:38 by amassias          #+#    #+#             */
/*   Updated: 2024/03/06 18:17:54 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERR_NEA "%s: Not enough arguments"
#define ERR_TMA "%s: Too many arguments"
#define ERR_NNA "%s: %s: Expected numeric argument"

static bool	_parse_args(
				char *pname,
				t_settings *settings,
				char **args
				);

static bool	_initialize_context(
				t_context *ctx
				);

static void	_cleanup_context(
				t_context *ctx
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
	if (_initialize_context(&context))
		return (3);
	_cleanup_context(&context);
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

static bool	_initialize_context(
				t_context *ctx
				)
{
	size_t	i;

	memset(ctx, 0, sizeof(t_context));
	if (pthread_mutex_init(&ctx->mutexes.logging, NULL) != 0)
		return (true);
	if (pthread_mutex_init(&ctx->mutexes.simulation_running, NULL) != 0)
		return (pthread_mutex_destroy(&ctx->mutexes.logging), true);
	ctx->mutexes._are_initialized = true;
	ctx->forks = (pthread_mutex_t *)malloc(
			ctx->settings.philosopher_count * sizeof(pthread_mutex_t *));
	if (ctx->forks == NULL)
		return (_cleanup_context(ctx), true);
	i ^= i;
	while (i < ctx->settings.philosopher_count)
	{
		if (pthread_mutex_init(&ctx->forks[i++], NULL) == 0)
			continue ;
		while (i--)
			pthread_mutex_destroy(&ctx->forks[i]);
		free(ctx->forks);
		ctx->forks = NULL;
		return (_cleanup_context(ctx), true);
	}
	return (false);
}

static void	_cleanup_context(
				t_context *ctx
				)
{
	size_t	i;

	if (!ctx->mutexes._are_initialized)
		return ;
	pthread_mutex_destroy(&ctx->mutexes.logging);
	pthread_mutex_destroy(&ctx->mutexes.simulation_running);
	if (ctx->forks == NULL)
		return ;
	i ^= i;
	while (i < ctx->settings.philosopher_count)
		pthread_mutex_destroy(&ctx->forks[i++]);
	free(ctx->forks);
}
