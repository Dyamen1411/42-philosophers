/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:47:27 by amassias          #+#    #+#             */
/*   Updated: 2024/03/02 17:53:24 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

const char	*g_messages[] = {
[ACTION_TAKE] = "has taken a fork",
[ACTION_EATING] = "is eating",
[ACTION_SLEEPING] = "is sleeping",
[ACTION_THINKING] = "is thinking",
[ACTION_DEATH] = "died"
};

void	log_action(
			unsigned int philo_id,
			unsigned long timestamp,
			t_action action
			)
{
	printf("%lu %u %s\n", timestamp, philo_id, g_messages[action]);
}
