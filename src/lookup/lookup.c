/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_u32	fog_gradient_color(t_f32 t)
{
	t_blend	color;
	t_u8	alpha;

	color.start = color_rgba(FOG_START_R, FOG_START_G, FOG_START_B, 0);
	color.end = color_rgba(FOG_END_R, FOG_END_G, FOG_END_B, COLOR_CHANNEL_MAX);
	alpha = (t_u8)(clampf(t, 0.0f, 1.0f) * COLOR_CHANNEL_MAX);
	return (color_lerp(color.start, color.end, alpha));
}

static void	init_fog_table(t_lookup *lut)
{
	t_u32	color;
	t_f32	dist;
	t_f32	base;
	t_f32	t;
	t_i32	i;

	base = FOG_START + (FOG_END - FOG_START);
	i = 0;
	while (i < FOG_TABLE_SIZE)
	{
		dist = base * i / (FOG_TABLE_SIZE - 1);
		if (dist <= FOG_START)
			t = 0.0f;
		else if (dist >= FOG_END)
			t = 1.0f;
		else
		{
			t = (dist - FOG_START) / (FOG_END - FOG_START);
			t = 1.0f - expf(-FOG_INTENSITY * t * 3.0f);
		}
		color = fog_gradient_color(t);
		lut->fog_table[i] = color;
		i++;
	}
}

static void	init_trig_tables(t_lookup *lut)
{
	t_i32	i;
	t_f32	angle;

	i = 0;
	while (i < TRIG_TABLE_SIZE)
	{
		angle = (t_f32)i / TRIG_TABLE_SCALE * DEG2RAD;
		lut->sin_table[i] = sinf(angle);
		lut->cos_table[i] = cosf(angle);
		i++;
	}
}

void	lookup_init(t_lookup *lut)
{
	*lut = (t_lookup){0};
	init_trig_tables(lut);
	init_fog_table(lut);
	lut->initialized = true;
}
