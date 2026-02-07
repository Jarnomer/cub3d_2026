/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/15 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	render_sheet_column(t_game *game, t_proj *proj, t_i32 x)
{
	t_sheet		*sheet;
	t_vec2i		tex;
	t_u32		color;
	t_u32		fog;
	t_i32		y;

	sheet = assets_get_sheet(&game->assets, proj->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return ;
	fog = lookup_fog(&game->lookup, proj->dist);
	tex.x = trans_sprite_tex_x(proj, x, sheet->width);
	y = proj->bounds.y;
	while (y < rect_bottom(proj->bounds))
	{
		if (!occlude_pixel(game, x, y, proj->dist))
		{
			tex.y = trans_sprite_tex_y(proj, y, sheet->height);
			color = sheet_sample(sheet, proj->frame, tex.x, tex.y);
			if (color_is_opaque(color))
				render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		}
		y++;
	}
}

void	render_sprite_column(t_game *game, t_proj *proj, t_i32 x)
{
	t_tex		*sprite;
	t_vec2i		tex;
	t_u32		color;
	t_u32		fog;
	t_i32		y;

	sprite = assets_get_sprite(&game->assets, proj->tex_id);
	if (!sprite || !sprite->pixels)
		return ;
	fog = lookup_fog(&game->lookup, proj->dist);
	tex.x = trans_sprite_tex_x(proj, x, sprite->width);
	y = proj->bounds.y;
	while (y < rect_bottom(proj->bounds))
	{
		if (!occlude_pixel(game, x, y, proj->dist))
		{
			tex.y = trans_sprite_tex_y(proj, y, sprite->height);
			color = texture_sample(sprite, tex.x, tex.y);
			if (color_is_opaque(color))
				render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		}
		y++;
	}
}
