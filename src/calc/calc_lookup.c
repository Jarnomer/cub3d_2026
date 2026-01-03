/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_lookup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <calc.h>

void	lookup_init(t_lookup *lut)
{
	t_i32	i;
	t_f32	angle;

	i = 0;
	while (i < TRIG_TABLE_SIZE)
	{
		angle = (t_f32)i / TRIG_TABLE_SCALE * DEG2RAD;
		lut->sin_table[i] = sinf(angle);
		lut->cos_table[i] = cosf(angle);
		lut->tan_table[i] = tanf(angle);
		i++;
	}
	lut->initialized = true;
}

static t_i32	angle_to_index(t_f32 angle)
{
	t_f32	deg;
	t_i32	idx;

	deg = rad_to_deg(angle_normalize(angle));
	idx = (t_i32)(deg * TRIG_TABLE_SCALE);
	if (idx < 0)
		idx = 0;
	if (idx >= TRIG_TABLE_SIZE)
		idx = TRIG_TABLE_SIZE - 1;
	return (idx);
}

t_f32	lookup_sin(t_lookup *lut, t_f32 angle)
{
	if (!lut->initialized)
		return (sinf(angle));
	return (lut->sin_table[angle_to_index(angle)]);
}

t_f32	lookup_cos(t_lookup *lut, t_f32 angle)
{
	if (!lut->initialized)
		return (cosf(angle));
	return (lut->cos_table[angle_to_index(angle)]);
}

t_f32	lookup_tan(t_lookup *lut, t_f32 angle)
{
	if (!lut->initialized)
		return (tanf(angle));
	return (lut->tan_table[angle_to_index(angle)]);
}
