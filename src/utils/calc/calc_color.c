/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_u8	color_r(t_u32 c)
{
	return (c & 0xFF);
}

t_u8	color_g(t_u32 c)
{
	return ((c >> 8) & 0xFF);
}

t_u8	color_b(t_u32 c)
{
	return ((c >> 16) & 0xFF);
}

t_u8	color_a(t_u32 c)
{
	return ((c >> 24) & 0xFF);
}

t_u32	color_rgba(t_u8 r, t_u8 g, t_u8 b, t_u8 a)
{
	return ((t_u32)a << 24 | (t_u32)b << 16 | (t_u32)g << 8 | (t_u32)r);
}
