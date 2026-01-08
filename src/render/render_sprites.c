/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_i32	calc_tex_y(t_proj *proj, t_i32 screen_y, t_i32 tex_h)
{
	t_i32	sprite_y;

	sprite_y = screen_y - (proj->screen.y - proj->size.y / 2);
	return (clampi(sprite_y * tex_h / proj->size.y, 0, tex_h - 1));
}

static t_i32	calc_tex_x(t_proj *proj, t_i32 screen_x, t_i32 tex_w)
{
	t_i32	sprite_x;

	sprite_x = screen_x - (proj->screen.x - proj->size.x / 2);
	return (clampi(sprite_x * tex_w / proj->size.x, 0, tex_w - 1));
}

static bool	pixel_visible(t_game *game, t_i32 x, t_i32 y,
		t_f32 dist)
{
	if (occlude_check_door(game, x, y, dist))
		return (false);
	return (true);
}

void	render_sprite_column(t_game *game, t_proj *proj, t_i32 x)
{
	t_tex	*tex;
	t_i32	tex_x;
	t_i32	y;
	t_u32	color;
	t_u8	fog;

	tex = assets_get_sprite(&game->assets, proj->tex_id);
	if (!tex || !tex->pixels)
		return ;
	fog = lookup_fog(&game->lookup, proj->dist);
	tex_x = calc_tex_x(proj, x, tex->width);
	y = proj->start.y;
	while (y < proj->end.y)
	{
		color = texture_sample(tex, tex_x, calc_tex_y(proj, y, tex->height));
		if (color_a(color) > ALPHA_THRESHOLD)
		{
			if (pixel_visible(game, x, y, proj->dist))
				render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		}
		y++;
	}
}
