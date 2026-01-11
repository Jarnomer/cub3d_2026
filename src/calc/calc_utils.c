/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_f32	parse_integer(const char **str)
{
	t_f32	result;

	result = 0.0f;
	while (ft_isdigit(**str))
	{
		result = result * 10.0f + (**str - '0');
		(*str)++;
	}
	return (result);
}

static t_f32	parse_decimal(const char **str)
{
	t_f32	result;
	t_f32	factor;

	result = 0.0f;
	factor = 0.1f;
	while (ft_isdigit(**str))
	{
		result += (**str - '0') * factor;
		factor *= 0.1f;
		(*str)++;
	}
	return (result);
}

static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (sign);
}

t_f32	ft_atof(const char *str)
{
	t_f32	result;
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = parse_sign(&str);
	result = parse_integer(&str);
	if (*str == '.')
	{
		str++;
		result += parse_decimal(&str);
	}
	return (result * sign);
}
