/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <calc.h>

t_color	color_new(t_u8 r, t_u8 g, t_u8 b, t_u8 a)
{
	return ((t_color){r, g, b, a});
}

t_color	color_from_u32(t_u32 val)
{
	t_color	c;

	c.r = (val >> 24) & 0xFF;
	c.g = (val >> 16) & 0xFF;
	c.b = (val >> 8) & 0xFF;
	c.a = val & 0xFF;
	return (c);
}

t_u32	color_to_u32(t_color c)
{
	return ((t_u32)c.r << 24 | (t_u32)c.g << 16 | (t_u32)c.b << 8 | c.a);
}

t_color	color_mul(t_color c, t_f32 factor)
{
	t_color	result;

	factor = clampf(factor, 0.0f, 1.0f);
	result.r = (t_u8)(c.r * factor);
	result.g = (t_u8)(c.g * factor);
	result.b = (t_u8)(c.b * factor);
	result.a = c.a;
	return (result);
}
