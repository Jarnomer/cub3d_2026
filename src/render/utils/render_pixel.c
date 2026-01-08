/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

bool	pixel_in_bounds(t_mlxi *frame, t_i32 x, t_i32 y)
{
	if (x < 0 || x >= (t_i32)frame->width)
		return (false);
	if (y < 0 || y >= (t_i32)frame->height)
		return (false);
	return (true);
}

void	pixel_put_safe(t_mlxi *frame, t_i32 x, t_i32 y, t_u32 color)
{
	if (!pixel_in_bounds(frame, x, y))
		return ;
	((t_u32 *)frame->pixels)[y * frame->width + x] = color;
}

t_u32	pixel_get(t_mlxi *frame, t_i32 x, t_i32 y)
{
	if (!pixel_in_bounds(frame, x, y))
		return (0);
	return (((t_u32 *)frame->pixels)[y * frame->width + x]);
}

void	pixel_blend(t_mlxi *frame, t_i32 x, t_i32 y, t_u32 color)
{
	t_u32	dst;
	t_u8	alpha;

	if (!pixel_in_bounds(frame, x, y))
		return ;
	alpha = color_a(color);
	if (alpha == 0)
		return ;
	if (alpha == ALPHA_OPAQUE)
	{
		((t_u32 *)frame->pixels)[y * frame->width + x] = color;
		return ;
	}
	dst = ((t_u32 *)frame->pixels)[y * frame->width + x];
	((t_u32 *)frame->pixels)[y * frame->width + x] =
            color_blend(color, dst, alpha);
}

void	pixel_fill_rect(t_mlxi *frame, t_vec2i pos, t_vec2i size, t_u32 color)
{
	t_i32	x;
	t_i32	y;
	t_i32	x_end;
	t_i32	y_end;

	x_end = mini(pos.x + size.x, (t_i32)frame->width);
	y_end = mini(pos.y + size.y, (t_i32)frame->height);
	y = maxi(pos.y, 0);
	while (y < y_end)
	{
		x = maxi(pos.x, 0);
		while (x < x_end)
		{
			((t_u32 *)frame->pixels)[y * frame->width + x] = color;
			x++;
		}
		y++;
	}
}
