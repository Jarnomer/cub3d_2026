/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_u32	color_lerp(t_u32 c1, t_u32 c2, t_u8 factor)
{
	t_u32	inv;
	t_u32	r;
	t_u32	g;
	t_u32	b;
	t_u32	a;

	if (factor == 0)
		return (c1);
	if (factor == COLOR_MAX)
		return (c2);
	inv = COLOR_MAX - factor;
	r = (color_r(c1) * inv + color_r(c2) * factor) / COLOR_MAX;
	g = (color_g(c1) * inv + color_g(c2) * factor) / COLOR_MAX;
	b = (color_b(c1) * inv + color_b(c2) * factor) / COLOR_MAX;
	a = (color_a(c1) * inv + color_a(c2) * factor) / COLOR_MAX;
	return (color_rgba(r, g, b, a));
}

t_u32	color_blend(t_u32 src, t_u32 dst, t_u8 alpha)
{
	t_u32	inv;
	t_u32	r;
	t_u32	g;
	t_u32	b;

	if (alpha == 0)
		return (dst);
	if (alpha == COLOR_MAX)
		return (src);
	inv = COLOR_MAX - alpha;
	r = (color_r(src) * alpha + color_r(dst) * inv) / COLOR_MAX;
	g = (color_g(src) * alpha + color_g(dst) * inv) / COLOR_MAX;
	b = (color_b(src) * alpha + color_b(dst) * inv) / COLOR_MAX;
	return (color_rgba(r, g, b, COLOR_MAX));
}

bool	color_is_opaque(t_u32 color)
{
	return (color_a(color) >= ALPHA_THRESHOLD);
}

bool	color_is_solid(t_u32 color)
{
	return (color_a(color) >= ALPHA_OPAQUE);
}
