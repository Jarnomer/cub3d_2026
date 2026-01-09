/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	render_sheet_column(t_game *game, t_proj *proj, t_i32 x)
{
	t_sheet	*sheet;
	t_vec2i	tex_uv;
	t_u32	color;
	t_u8	fog;
	t_i32	y;

	sheet = assets_get_sheet(&game->assets, proj->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return ;
	fog = lookup_fog(&game->lookup, proj->dist);
	tex_uv.x = trans_sprite_tex_x(proj, x, sheet->width);
	y = proj->start.y;
	while (y < proj->end.y)
	{
		if (!occlude_pixel(game, x, y, proj->dist))
		{
			tex_uv.y = trans_sprite_tex_y(proj, y, sheet->height);
			color = sheet_sample(sheet, proj->frame, tex_uv.x, tex_uv.y);
			if (color_a(color) >= ALPHA_THRESHOLD)
				render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		}
		y++;
	}
}

void	render_sprite_column(t_game *game, t_proj *proj, t_i32 x)
{
	t_tex	*tex;
	t_vec2i	tex_uv;
	t_u32	color;
	t_u8	fog;
	t_i32	y;

	tex = assets_get_sprite(&game->assets, proj->tex_id);
	if (!tex || !tex->pixels)
		return ;
	fog = lookup_fog(&game->lookup, proj->dist);
	tex_uv.x = trans_sprite_tex_x(proj, x, tex->width);
	y = proj->start.y;
	while (y < proj->end.y)
	{
		if (!occlude_pixel(game, x, y, proj->dist))
		{
			tex_uv.y = trans_sprite_tex_y(proj, y, tex->height);
			color = texture_sample(tex, tex_uv.x, tex_uv.y);
			if (color_a(color) >= ALPHA_THRESHOLD)
				render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		}
		y++;
	}
}
