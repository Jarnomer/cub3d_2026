/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

// static t_u32	fog_color(void)
// {
// 	return (color_rgba(FOG_COLOR_R, FOG_COLOR_G, FOG_COLOR_B, COLOR_MAX));
// }

t_u32	fog_apply(t_u32 color, t_u32 fog)
{
	return (color_blend(fog, color, color_a(fog)));
}

void	fog_fill_row(t_game *game, t_i32 y)
{
	t_u32	*pixels;
	t_u32	color;
	t_i32	offset;
	t_i32	x;

	color = game->lookup.fog_table[FOG_TABLE_SIZE - 1];
	pixels = (t_u32 *)game->render.frame->pixels;
	offset = y * game->render.width;
	x = 0;
	while (x < game->render.width)
	{
		pixels[offset + x] = color;
		x++;
	}
}

void	fog_fill_column(t_game *game, t_i32 x, t_i32 start, t_i32 end)
{
	t_u32	*pixels;
	t_u32	color;
	t_i32	y;

	color = game->lookup.fog_table[FOG_TABLE_SIZE - 1];
	pixels = (t_u32 *)game->render.frame->pixels;
	y = start;
	while (y <= end)
	{
		pixels[y * game->render.width + x] = color;
		y++;
	}
}
