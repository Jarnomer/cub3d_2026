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
		pixels[i] = color_blend(color, pixels[i], color_a(color));
		i++;
	}
}

void	overlay_apply(t_render *render)
{
	t_u32	*frame;
	t_u32	*overlay;
	t_i32	total;
	t_u8	alpha;
	t_i32	i;

	if (!render->frame || !render->overlay)
		return ;
	frame = (t_u32 *)render->frame->pixels;
	overlay = (t_u32 *)render->overlay->pixels;
	total = render->width * render->height;
	i = 0;
	while (i < total)
	{
		alpha = color_a(overlay[i]);
		frame[i] = color_blend(overlay[i], frame[i], alpha);
		i++;
	}
}

void	overlay_clear(t_render *render)
{
	size_t	bytes;

	if (!render->overlay)
		return ;
	bytes = render->width * render->height * sizeof(t_u32);
	ft_bzero(render->overlay->pixels, bytes);
}
