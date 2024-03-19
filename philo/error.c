/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:36:02 by amassias          #+#    #+#             */
/*   Updated: 2024/03/19 16:48:09 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file error.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2024-01-10
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

noreturn
void	error(
			t_philo_ctx *ctx,
			const char *message
			)
{
	dprintf(STDERR_FILENO, "%s: %s\n", ctx->program_name, message);
	philo_destroy(ctx);
	exit(EXIT_FAILURE);
}
