/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:47:27 by amassias          #+#    #+#             */
/*   Updated: 2024/03/04 17:21:43 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>

const char	*g_messages[] = {
[ACTION_TAKE] = "has taken a fork",
[ACTION_EATING] = "is eating",
[ACTION_SLEEPING] = "is sleeping",
[ACTION_THINKING] = "is thinking",
[ACTION_DEATH] = "died"
};

void	log_action(
			t_context *ctx,
			t_philosopher *philosopher,
			unsigned long timestamp
			)
{
	const unsigned int	id = philosopher->id;
	const t_action		status = philosopher->status;

	pthread_mutex_lock(&ctx->mutexes.logging);
	printf("%lu %u %s\n", timestamp, id, g_messages[status]);
	pthread_mutex_unlock(&ctx->mutexes.logging);
}
