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

static t_u32	fog_color(void)
{
	return (color_rgba(FOG_COLOR_R, FOG_COLOR_G, FOG_COLOR_B, 255));
}

t_u32	fog_apply(t_u32 color, t_u8 fog_alpha)
{
	t_u32	r;
	t_u32	g;
	t_u32	b;
	t_u32	inv;

	inv = 255 - fog_alpha;
	r = (color_r(color) * inv + FOG_COLOR_R * fog_alpha) / 255;
	g = (color_g(color) * inv + FOG_COLOR_G * fog_alpha) / 255;
	b = (color_b(color) * inv + FOG_COLOR_B * fog_alpha) / 255;
	return (color_rgba(r, g, b, color_a(color)));
}

void	fog_fill_row(t_game *game, t_i32 y)
{
	t_u32	color;
	t_i32	x;

	color = fog_color();
	x = 0;
	while (x < game->render.width)
	{
		render_pixel(game->render.frame, x, y, color);
		x++;
	}
}

void	fog_fill_column(t_game *game, t_i32 x, t_i32 start, t_i32 end)
{
	t_u32	color;
	t_i32	y;

	color = fog_color();
	y = start;
	while (y <= end)
	{
		render_pixel(game->render.frame, x, y, color);
		y++;
	}
}
