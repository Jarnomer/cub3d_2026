/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_scalar_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_f32	lerpf(t_f32 a, t_f32 b, t_f32 t)
{
	return (a + (b - a) * t);
}

t_f32	wrapf(t_f32 val, t_f32 lo, t_f32 hi)
{
	t_f32	range;

	range = hi - lo;
	while (val < lo)
		val += range;
	while (val >= hi)
		val -= range;
	return (val);
}

t_f32	signf(t_f32 val)
{
	if (val > 0)
		return (1.0f);
	if (val < 0)
		return (-1.0f);
	return (0.0f);
}

t_f32	smoothstep(t_f32 edge0, t_f32 edge1, t_f32 x)
{
	t_f32	t;

	t = clampf((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
	return (t * t * (3.0f - 2.0f * t));
}
