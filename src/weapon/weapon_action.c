/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	weapon_fire(t_weapon *wpn, t_game *game)
{
	t_wpndef	*def;
	t_player	*player;
	t_f32		recoil;

	if (!weapon_can_fire(wpn, game))
		return ;
	def = weapon_get_def(game, wpn->id);
	player = &game->player;
	if (!player_use_ammo(player, def->ammo_type, 1))
		return ;
	weapon_set_state(wpn, STATE_FIRING, game);
	recoil = wpn->recoil + WEAPON_RECOIL_MAX;
	wpn->recoil = minf(recoil, WEAPON_RECOIL_MAX);
	wpn->timer = def->fire_rate;
	wpn->ready = false;
	weapon_fire_pellets(game, def);
}

void	weapon_reload(t_weapon *wpn, t_game *game)
{
	if (!weapon_can_reload(wpn, game))
		return ;
	weapon_set_state(wpn, STATE_RELOADING, game);
	wpn->ready = false;
}
