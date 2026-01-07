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

t_u32	color_lerp(t_u32 a, t_u32 b, t_u8 t)
{
	t_u32	inv;
	t_u32	r;
	t_u32	g;
	t_u32	bl;

	if (t == 0)
		return (a);
	if (t == 255)
		return (b);
	inv = 255 - t;
	r = (color_r(a) * inv + color_r(b) * t) / 255;
	g = (color_g(a) * inv + color_g(b) * t) / 255;
	bl = (color_b(a) * inv + color_b(b) * t) / 255;
	return (color_pack(r, g, bl, color_a(a)));
}

t_u32	color_blend(t_u32 src, t_u32 dst, t_u8 alpha)
{
	t_u32	inv;
	t_u32	r;
	t_u32	g;
	t_u32	b;

	if (alpha == 0)
		return (dst);
	if (alpha == 255)
		return (src);
	inv = 255 - alpha;
	r = (color_r(src) * alpha + color_r(dst) * inv) / 255;
	g = (color_g(src) * alpha + color_g(dst) * inv) / 255;
	b = (color_b(src) * alpha + color_b(dst) * inv) / 255;
	return (color_pack(r, g, b, 255));
}
