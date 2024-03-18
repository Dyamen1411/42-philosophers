/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:30:38 by amassias          #+#    #+#             */
/*   Updated: 2024/03/18 19:57:31 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-03-02
 * @copyright Copyright (c) 2024
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define ERR_NEA "%s: Not enough arguments"
#define ERR_TMA "%s: Too many arguments"
#define ERR_NNA "%s: %s: Expected numeric argument"

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

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

void		*_philo(
				t_philosopher *philosopher
				);

/* ************************************************************************** */
/*                                                                            */
/* Main                                                                       */
/*                                                                            */
/* ************************************************************************** */

int	main(
		int argc,
		char **argv
		)
{
	static t_context	context = {0};
	t_philosopher		*philosophers;
	size_t				i;
	size_t				j;
	struct timeval		tv;
	unsigned long		t;

	if (argc < 5)
		return (dprintf(STDERR_FILENO, ERR_NEA "\n", *argv), 1);
	if (argc > 6)
		return (dprintf(STDERR_FILENO, ERR_TMA "\n", *argv), 1);
	if (_parse_args(argv[0], &context.settings, argv + 1))
		return (1);
	printf("philosopher_count: %u\n", context.settings.philosopher_count);
	printf("death_timer      : %lu\n", context.settings.death_timer);
	printf("eating_timer     : %lu\n", context.settings.eating_timer);
	printf("sleeping_timer   : %lu\n", context.settings.sleeping_timer);
	printf("max_eating       : %lu\n", context.settings.max_eating);
	if (_initialize_context(&context))
		return (1);
	philosophers = (t_philosopher *)calloc(context.settings.philosopher_count,
			sizeof(t_philosopher));
	if (philosophers == NULL)
		return (_cleanup_context(&context), 1);
	i = 0;
	while (i < context.settings.philosopher_count)
	{
		philosophers[i].id = i;
		philosophers[i].context = &context;
		philosophers[i].status = ACTION_TAKE;
		philosophers[i].left_fork = &context.forks[i];
		philosophers[i].right_fork = &context.forks[(i + 1) % context.settings.philosopher_count];
		gettimeofday(&tv, NULL);
		philosophers[i].last_time_eaten = tv.tv_usec;
		if (pthread_mutex_init(&philosophers[i].last_time_eaten_mutex, NULL) == 0)
		{
			if (pthread_create(&philosophers[i].thread, NULL, (void *(*)(void *))_philo, &philosophers[i]) == 0)
			{
				++i;
				continue ;
			}
			pthread_mutex_destroy(&philosophers[i].last_time_eaten_mutex);
		}
		while (i--)
		{
			pthread_join(philosophers[i].thread, NULL);
			pthread_mutex_destroy(&philosophers[i].last_time_eaten_mutex);
		}
		return (_cleanup_context(&context), 1);
	}
	printf("checker\n");
	while (context_is_running(&context))
	{
		j = 0;
		while (j < context.settings.philosopher_count)
		{
			pthread_mutex_lock(&philosophers[j].last_time_eaten_mutex);
			t = philosophers[j].last_time_eaten;
			pthread_mutex_unlock(&philosophers[j++].last_time_eaten_mutex);
			gettimeofday(&tv, NULL);
			tv.tv_usec -= t;
			if (tv.tv_usec < (suseconds_t)context.settings.death_timer)
				continue ;
			context_kill_simulation(&context);
			break ;
		}
	}
	while (i--)
		pthread_join(philosophers[i].thread, NULL);
	return (_cleanup_context(&context), EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

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

	if (pthread_mutex_init(&ctx->mutexes.logging, NULL) != 0)
		return (true);
	if (pthread_mutex_init(&ctx->mutexes.simulation_running, NULL) != 0)
		return (pthread_mutex_destroy(&ctx->mutexes.logging), true);
	ctx->mutexes._are_initialized = true;
	ctx->forks = (pthread_mutex_t *)malloc(
			ctx->settings.philosopher_count * sizeof(pthread_mutex_t));
	if (ctx->forks == NULL)
		return (_cleanup_context(ctx), true);
	i = 0;
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
	ctx->is_simulation_running = true;
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
	i = 0;
	while (i < ctx->settings.philosopher_count)
		pthread_mutex_destroy(&ctx->forks[i++]);
	free(ctx->forks);
}

unsigned long	_philo_get_last_time_eaten(
					t_philosopher *philo
					)
{
	unsigned long	t;

	pthread_mutex_lock(&philo->last_time_eaten_mutex);
	t = philo->last_time_eaten;
	pthread_mutex_unlock(&philo->last_time_eaten_mutex);
	return (t);
}

int	_wait(
		t_philosopher *philo,
		suseconds_t time
		)
{
	t_context	*ctx;

	ctx = philo->context;
	while (time > 10)
	{
		usleep(10);
		if (!context_is_running(ctx))
			return (1);
		if (_philo_get_last_time_eaten(philo) >= ctx->settings.eating_timer)
			return (context_kill_simulation(ctx), 1);
		time -= 10;
	}
	if (time > 0)
	{
		usleep(time);
		if (!context_is_running(ctx))
			return (1);
		if (_philo_get_last_time_eaten(philo) >= ctx->settings.eating_timer)
			return (context_kill_simulation(ctx), 1);
	}
	return (0);
}

void	*_philo(
			t_philosopher *philosopher
			)
{
	struct timeval	tv;
	int				status;

	while (context_is_running(philosopher->context))
	{
		gettimeofday(&tv, NULL);
		if (philosopher->status == ACTION_SLEEPING)
		{
			log_action(philosopher->context, philosopher, tv.tv_usec);
			if (_wait(philosopher, philosopher->context->settings.sleeping_timer))
				break ;
			philosopher->status = ACTION_THINKING;
		}
		else if (philosopher->status == ACTION_THINKING)
		{
			log_action(philosopher->context, philosopher, tv.tv_usec);
			philosopher->status = ACTION_TAKE;
		}
		else if (philosopher->status == ACTION_TAKE)
		{
			pthread_mutex_lock(philosopher->left_fork);
			if (!context_is_running(philosopher->context))
				break ;
			pthread_mutex_lock(philosopher->right_fork);
			if (!context_is_running(philosopher->context))
				break ;
			gettimeofday(&tv, NULL);
			log_action(philosopher->context, philosopher, tv.tv_usec);
			philosopher->status = ACTION_EATING;
			pthread_mutex_lock(&philosopher->last_time_eaten_mutex);
			gettimeofday(&tv, NULL);
			philosopher->last_time_eaten = tv.tv_usec;
			pthread_mutex_unlock(&philosopher->last_time_eaten_mutex);
			log_action(philosopher->context, philosopher, tv.tv_usec);
			status = _wait(philosopher, philosopher->context->settings.eating_timer);
			pthread_mutex_unlock(philosopher->right_fork);
			pthread_mutex_unlock(philosopher->left_fork);
			if (status)
				break ;
		}
	}
	philosopher->status = ACTION_DEATH;
	gettimeofday(&tv, NULL);
	log_action(philosopher->context, philosopher, tv.tv_usec);
	printf("%u exit\n", philosopher->id);
	return (NULL);
}
