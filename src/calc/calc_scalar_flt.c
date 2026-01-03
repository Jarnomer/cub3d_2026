/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_scalar_flt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_f32	minf(t_f32 a, t_f32 b)
{
	if (a < b)
		return (a);
	return (b);
}

t_f32	maxf(t_f32 a, t_f32 b)
{
	if (a > b)
		return (a);
	return (b);
}

t_f32	clampf(t_f32 val, t_f32 lo, t_f32 hi)
{
	if (val < lo)
		return (lo);
	if (val > hi)
		return (hi);
	return (val);
}

t_f32	absf(t_f32 val)
{
	if (val < 0.0f)
		return (-val);
	return (val);
}

t_f32	inv_absf(t_f32 v)
{
	if (v == 0.0f)
		return (FLOAT_LARGE);
	return (absf(1.0f / v));
}
