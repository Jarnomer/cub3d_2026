/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_color	g_fog_color = {FOG_COLOR_R, FOG_COLOR_G, FOG_COLOR_B, 255};

t_f32	fog_factor(t_f32 dist)
{
	t_f32	t;

	if (!FOG_ENABLED || dist <= FOG_START)
		return (0.0f);
	if (dist >= FOG_END)
		return (1.0f);
	t = (dist - FOG_START) / (FOG_END - FOG_START);
	t = 1.0f - expf(-FOG_INTENSITY * t * 3.0f);
	return (clampf(t, 0.0f, 1.0f));
}

t_u32	fog_blend(t_u32 color, t_f32 factor)
{
	t_color	src;
	t_color	result;

	if (factor <= 0.0f)
		return (color);
	if (factor >= 1.0f)
		return (color_to_u32(g_fog_color));
	src = color_from_u32(color);
	result = color_lerp(src, g_fog_color, factor);
	return (color_to_u32(result));
}
