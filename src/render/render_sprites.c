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

/*
** Calculates texture Y coordinate from screen Y position
**
** Maps screen pixel to texture pixel using sprite's projected size
*/
static t_i32	calc_tex_y(t_proj *proj, t_i32 screen_y, t_i32 tex_h)
{
	t_i32	sprite_y;

	sprite_y = screen_y - (proj->screen.y - proj->size.y / 2);
	return (clampi(sprite_y * tex_h / proj->size.y, 0, tex_h - 1));
}

/*
** Calculates texture X coordinate from screen X position
*/
static t_i32	calc_tex_x(t_proj *proj, t_i32 screen_x, t_i32 tex_w)
{
	t_i32	sprite_x;

	sprite_x = screen_x - (proj->screen.x - proj->size.x / 2);
	return (clampi(sprite_x * tex_w / proj->size.x, 0, tex_w - 1));
}

/*
** Checks if sprite pixel should be rendered
**
** A pixel is visible if:
**   1. Sprite alpha is above threshold (not transparent)
**   2. Not occluded by wall (z-buffer check done by caller)
**   3. Not occluded by opaque door pixel (animated occlusion)
**
** The door occlusion check samples the door's current animation frame
** to determine if this specific pixel is blocked, allowing sprites
** to gradually appear through transparent parts of opening doors.
*/

static bool	pixel_visible(t_game *game, t_i32 x, t_i32 y,
		t_f32 dist)
{
	if (occlude_check_door(game, x, y, dist))
		return (false);
	return (true);
}

/*
** Renders a single vertical column of a static sprite
**
** For each pixel in column:
**   1. Sample texture at mapped coordinates
**   2. Skip if transparent (alpha < threshold)
**   3. Skip if occluded by door pixel
**   4. Apply distance fog
**   5. Write to framebuffer
*/

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
