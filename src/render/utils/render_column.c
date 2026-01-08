/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_column_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

bool	column_is_visible(t_i32 x, t_i32 width)
{
	return (x >= 0 && x < width);
}

void	column_clamp_bounds(t_i32 height, t_i32 *start, t_i32 *end)
{
	if (*start < 0)
		*start = 0;
	if (*end >= height)
		*end = height - 1;
}

void	column_fill(t_mlxi *frame, t_i32 x, t_i32 y1, t_i32 y2, t_u32 color)
{
	t_i32	y;

	y = y1;
	while (y <= y2)
	{
		((t_u32 *)frame->pixels)[y * frame->width + x] = color;
		y++;
	}
}

void	column_fill_fog(t_mlxi *frame, t_i32 x, t_i32 y1, t_i32 y2)
{
	column_fill(frame, x, y1, y2, fog_color(ALPHA_OPAQUE));
}

void	column_clear(t_mlxi *frame, t_i32 x, t_i32 height)
{
	t_i32	y;

	y = 0;
	while (y < height)
	{
		((t_u32 *)frame->pixels)[y * frame->width + x] = 0;
		y++;
	}
}
