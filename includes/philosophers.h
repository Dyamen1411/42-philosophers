/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:37:17 by amassias          #+#    #+#             */
/*   Updated: 2024/03/02 17:47:18 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

enum	e_action
{
	ACTION_TAKE,
	ACTION_EATING,
	ACTION_SLEEPING,
	ACTION_THINKING,
	ACTION_DEATH
};

struct	s_settings
{
	unsigned int	philosopher_count;
	unsigned long	death_timer;
	unsigned long	eating_timer;
	unsigned long	sleeping_timer;
	signed long		max_eating;
};

typedef enum e_action		t_action;

typedef struct s_settings	t_settings;

void	log_action(
			unsigned int philo_id,
			unsigned long timestamp,
			t_action action
			);

#endif