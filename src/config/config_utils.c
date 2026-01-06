/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_f32	ft_atof(const char *str)
{
	t_f32	result;
	t_f32	decimal;
	int		sign;

	result = 0.0f;
	sign = 1;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		result = result * 10.0f + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		decimal = 0.1f;
		while (*str >= '0' && *str <= '9')
		{
			result += (*str++ - '0') * decimal;
			decimal *= 0.1f;
		}
	}
	return (result * sign);
}
