/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	draw_weapon_row(t_game *game, t_sheet *sheet, t_vec2i pos, t_i32 y)
{
	t_i32	frame;
	t_u32	color;
	t_vec2i	dst;
	t_vec2i	src;
	t_i32	x;

	frame = weapon_get_frame(&game->player.weapon, game);
	dst.y = pos.y - (t_i32)(sheet->height * WEAPON_SCALE) + y;
	src.y = y / (t_i32)WEAPON_SCALE;
	x = 0;
	while (x < (t_i32)(sheet->width * WEAPON_SCALE))
	{
		dst.x = pos.x - (t_i32)(sheet->width * WEAPON_SCALE) / 2 + x;
		src.x = x / (t_i32)WEAPON_SCALE;
		color = sheet_sample(sheet, frame, src.x, src.y);
		if (color_is_opaque(color))
			render_pixel_safe(game->render.overlay, dst.x, dst.y, color);
		x++;
	}
}

static void	calc_weapon_pos(t_game *game, t_weapon *wpn, t_vec2i *pos)
{
	t_vec2i	base;

	base.x = game->render.width / 2 + WEAPON_OFFSET_X;
	base.y = game->render.height + WEAPON_OFFSET_Y;
	pos->x = base.x + (t_i32)(wpn->sway.x);
	pos->y = base.y + (t_i32)(wpn->sway.y - wpn->bob - wpn->recoil);
}

void	render_weapon(t_game *game)
{
	t_weapon	*wpn;
	t_wpndef	*def;
	t_sheet		*sheet;
	t_vec2i		pos;
	t_i32		y;

	wpn = &game->player.weapon;
	if (wpn->id == WEAPON_NONE)
		return ;
	def = weapon_get_def(game, wpn->id);
	if (!def)
		return ;
	sheet = assets_get_sheet(&game->assets, def->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return ;
	calc_weapon_pos(game, wpn, &pos);
	y = 0;
	while (y < (t_i32)(sheet->height * WEAPON_SCALE))
	{
		draw_weapon_row(game, sheet, pos, y);
		y++;
	}
}
