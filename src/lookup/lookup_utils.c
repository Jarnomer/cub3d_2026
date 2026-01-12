/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

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

t_u32	lookup_fog(t_lookup *lut, t_f32 dist)
{
	t_i32	idx;
	t_f32	val;

	if (!FOG_ENABLED || !lut->initialized)
		return (color_rgba(0, 0, 0, 0));
	if (dist <= FOG_START)
		return (color_rgba(0, 0, 0, 0));
	if (dist >= FOG_END)
		return (lut->fog_table[FOG_TABLE_SIZE - 1]);
	val = (dist - FOG_START) / (FOG_END - FOG_START);
	idx = (t_i32)(val * (FOG_TABLE_SIZE - 1));
	idx = clampi(idx, 0, FOG_TABLE_SIZE - 1);
	return (lut->fog_table[idx]);
}
