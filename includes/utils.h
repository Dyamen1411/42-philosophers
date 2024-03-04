/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:34:28 by amassias          #+#    #+#             */
/*   Updated: 2024/03/04 17:49:59 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

int		is_space(int c);
int		is_digit(int c);

bool	read_unsinged_int(
			char *str,
			unsigned int *v
			);

bool	read_unsigned_long(
			char *str,
			unsigned long *v
			);

#endif