/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	weapon_set_state(t_weapon *wpn, t_state state, t_game *game)
{
	t_wpndef	*def;

	def = weapon_get_def(game, wpn->id);
	if (!def)
		return ;
	wpn->state = state;
	if (state == STATE_IDLE)
		anim_play(&wpn->anim, def->anim_idle);
	else if (state == STATE_FIRING)
		anim_play(&wpn->anim, def->anim_fire);
	else if (state == STATE_RELOADING)
		anim_play(&wpn->anim, def->anim_reload);
}

bool	weapon_can_fire(t_weapon *wpn, t_game *game)
{
	t_wpndef	*def;

	if (wpn->state != STATE_IDLE || !wpn->ready)
		return (false);
	def = weapon_get_def(game, wpn->id);
	if (!def)
		return (false);
	return (player_has_ammo(&game->player, def->ammo_type));
}

bool	weapon_can_reload(t_weapon *wpn, t_game *game)
{
	t_wpndef	*def;

	if (wpn->state != STATE_IDLE)
		return (false);
	def = weapon_get_def(game, wpn->id);
	if (!def)
		return (false);
	return (player_has_ammo(&game->player, def->ammo_type));
}
