/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_scalar_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_i32	mini(t_i32 a, t_i32 b)
{
	if (a < b)
		return (a);
	return (b);
}

t_i32	maxi(t_i32 a, t_i32 b)
{
	if (a > b)
		return (a);
	return (b);
}

t_i32	clampi(t_i32 val, t_i32 lo, t_i32 hi)
{
	if (val < lo)
		return (lo);
	if (val > hi)
		return (hi);
	return (val);
}
