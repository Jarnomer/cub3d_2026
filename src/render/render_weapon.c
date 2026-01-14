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

static t_vec2i	calc_weapon_base(t_render *render)
{
	t_vec2i	base;

	base.x = render->width / 2 + WEAPON_OFFSET_X;
	base.y = render->height + WEAPON_OFFSET_Y;
	return (base);
}

static t_vec2i	calc_weapon_offset(t_player *player)
{
	t_vec2i	offset;
	t_vec2	sway;
	t_vec2	inertia;
	t_vec2	sprint;

	sway = player->weapon.sway.current;
	inertia = player->weapon.sway.inertia;
	sprint = sprint_get_offset(&player->weapon.sway, &player->motion.bob);
	offset.x = (t_i32)(sway.x + inertia.x + sprint.x);
	offset.y = (t_i32)(-sway.y - inertia.y + sprint.y - player->weapon.bob);
	offset.y -= (t_i32)(player->weapon.recoil);
	return (offset);
}

void	render_weapon(t_game *game)
{
	t_weapon	*wpn;
	t_wpndef	*def;
	t_sheet		*sheet;
	t_i32		frame;
	t_blit		blit;

	wpn = &game->player.weapon;
	if (wpn->id == WEAPON_NONE)
		return ;
	def = weapon_get_def(game, wpn->id);
	if (!def)
		return ;
	sheet = assets_get_sheet(&game->assets, def->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return ;
	frame = weapon_get_frame(wpn, game);
	blit_from_sheet(&blit, sheet, frame, WEAPON_SCALE);
	blit_set_centered(&blit, calc_weapon_base(&game->render));
	blit_apply_offset(&blit, calc_weapon_offset(&game->player));
	blit_clip_bounds(&blit, game->render.width, game->render.height);
	blit_render(&blit, game->render.overlay);
}
