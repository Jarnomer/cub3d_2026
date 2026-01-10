/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_overlay.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	blend_pixel(t_u32 *dst, t_u32 src)
{
	t_u8	src_a;
	t_u8	inv_a;
	t_u32	r;
	t_u32	g;
	t_u32	b;

	src_a = color_a(src);
	if (src_a == 0)
		return ;
	inv_a = 255 - src_a;
	r = (color_r(src) * src_a + color_r(*dst) * inv_a) / 255;
	g = (color_g(src) * src_a + color_g(*dst) * inv_a) / 255;
	b = (color_b(src) * src_a + color_b(*dst) * inv_a) / 255;
	*dst = color_pack(r, g, b, 255);
}

void	overlay_fill_color(t_render *render, t_u32 color)
{
	t_u32	*pixels;
	t_i32	total;
	t_i32	i;

	if (!render->overlay || color_a(color) == 0)
		return ;
	pixels = (t_u32 *)render->overlay->pixels;
	total = render->width * render->height;
	i = 0;
	while (i < total)
	{
		blend_pixel(&pixels[i], color);
		i++;
	}
}

void	overlay_apply(t_render *render)
{
	t_u32	*frame;
	t_u32	*overlay;
	t_i32	total;
	t_i32	i;

	if (!render->frame || !render->overlay)
		return ;
	frame = (t_u32 *)render->frame->pixels;
	overlay = (t_u32 *)render->overlay->pixels;
	total = render->width * render->height;
	i = 0;
	while (i < total)
	{
		blend_pixel(&frame[i], overlay[i]);
		i++;
	}
}

void	overlay_clear(t_render *render)
{
	t_u32	*pixels;
	t_i32	total;
	t_i32	i;

	if (!render->overlay)
		return ;
	pixels = (t_u32 *)render->overlay->pixels;
	total = render->width * render->height;
	i = 0;
	while (i < total)
	{
		pixels[i] = 0x00000000;
		i++;
	}
}
