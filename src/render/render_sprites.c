/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_i32	calc_tex_y(t_proj *proj, t_i32 screen_y, t_i32 tex_h)
{
	t_i32	sprite_y;
	t_i32	tex_y;

	sprite_y = screen_y - (proj->screen.y - proj->size.y / 2);
	tex_y = sprite_y * tex_h / proj->size.y;
	return (clampi(tex_y, 0, tex_h - 1));
}

static t_i32	calc_tex_x(t_proj *proj, t_i32 screen_x, t_i32 tex_w)
{
	t_i32	sprite_x;
	t_i32	tex_x;

	sprite_x = screen_x - (proj->screen.x - proj->size.x / 2);
	tex_x = sprite_x * tex_w / proj->size.x;
	return (clampi(tex_x, 0, tex_w - 1));
}

void	render_sprite_column(t_game *game, t_proj *proj, t_i32 x)
{
	t_tex	*tex;
	t_i32	tex_x;
	t_i32	y;
	t_u32	color;

	tex = assets_get_sprite(&game->assets, proj->tex_id);
	if (!tex || !tex->pixels)
		return ;
	tex_x = calc_tex_x(proj, x, tex->width);
	y = proj->start.y;
	while (y < proj->end.y)
	{
		color = texture_sample(tex, tex_x, calc_tex_y(proj, y, tex->height));
		if ((color >> 24) > 128)
		{
			color = fog_blend(color, fog_factor(proj->dist));
			render_pixel(game->render.frame, x, y, color);
		}
		y++;
	}
}
