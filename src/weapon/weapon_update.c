/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	update_recoil(t_weapon *wpn, t_f32 dt)
{
	if (wpn->recoil > 0.0f)
	{
		wpn->recoil -= WEAPON_RECOIL_DECAY * dt;
		if (wpn->recoil < 0.0f)
			wpn->recoil = 0.0f;
	}
}

static void	update_reloading(t_weapon *wpn, t_game *game)
{
	if (wpn->anim.done)
	{
		wpn->ready = true;
		weapon_set_state(wpn, STATE_IDLE, game);
	}
}

static void	update_firing(t_weapon *wpn, t_game *game, t_f32 dt)
{
	t_wpndef	*def;

	def = weapon_get_def(game, wpn->id);
	if (!def)
		return ;
	wpn->fire_timer -= dt;
	if (wpn->anim.done)
	{
		wpn->ready = true;
		weapon_set_state(wpn, STATE_IDLE, game);
	}
}

void	weapon_update(t_weapon *wpn, t_game *game, t_f32 dt)
{
	t_anidef	*def;

	if (!wpn || wpn->id == WEAPON_NONE)
		return ;
	def = &game->assets.anidefs[wpn->anim.def_id];
	anim_update(&wpn->anim, def, dt);
	if (wpn->state == STATE_FIRING)
		update_firing(wpn, game, dt);
	else if (wpn->state == STATE_RELOADING)
		update_reloading(wpn, game);
	update_recoil(wpn, dt);
}
