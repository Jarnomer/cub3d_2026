/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <calc.h>

static t_u8	lerp_u8(t_u8 a, t_u8 b, t_f32 t)
{
	return ((t_u8)(a + (b - a) * t));
}

t_color	color_lerp(t_color a, t_color b, t_f32 t)
{
	t_color	result;

	t = clampf(t, 0.0f, 1.0f);
	result.r = lerp_u8(a.r, b.r, t);
	result.g = lerp_u8(a.g, b.g, t);
	result.b = lerp_u8(a.b, b.b, t);
	result.a = lerp_u8(a.a, b.a, t);
	return (result);
}

static t_u8	add_clamped(t_u8 a, t_u8 b)
{
	t_i32	sum;

	sum = (t_i32)a + (t_i32)b;
	if (sum > 255)
		return (255);
	return ((t_u8)sum);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	result;

	result.r = add_clamped(a.r, b.r);
	result.g = add_clamped(a.g, b.g);
	result.b = add_clamped(a.b, b.b);
	result.a = add_clamped(a.a, b.a);
	return (result);
}

t_color	color_blend(t_color dst, t_color src)
{
	t_color	result;
	t_f32	sa;
	t_f32	da;
	t_f32	inv_sa;

	if (src.a == 0)
		return (dst);
	if (src.a == 255)
		return (src);
	sa = src.a / 255.0f;
	da = dst.a / 255.0f;
	inv_sa = 1.0f - sa;
	result.r = (t_u8)(src.r * sa + dst.r * da * inv_sa);
	result.g = (t_u8)(src.g * sa + dst.g * da * inv_sa);
	result.b = (t_u8)(src.b * sa + dst.b * da * inv_sa);
	result.a = (t_u8)((sa + da * inv_sa) * 255.0f);
	return (result);
}
