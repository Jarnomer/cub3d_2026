/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	weapon_init(t_weapon *wpn, t_wpn_id id, t_game *game)
{
	t_wpndef	*def;

	*wpn = (t_weapon){.id = id, .state = STATE_IDLE, .ready = true};
	def = weapon_get_def(game, id);
	if (def)
		anim_init(&wpn->anim, def->anim_idle);
	sway_init(&wpn->sway);
}

t_i32	weapon_get_frame(t_weapon *wpn, t_game *game)
{
	t_anidef	*def;

	if (!wpn || wpn->id == WEAPON_NONE)
		return (0);
	def = &game->assets.anidefs[wpn->anim.def_id];
	return (anim_get_frame(&wpn->anim, def));
}

t_wpndef	*weapon_get_def(t_game *game, t_wpn_id id)
{
	if (id <= WEAPON_NONE || id >= WEAPON_COUNT)
		return (NULL);
	return (&game->assets.wpndefs[id]);
}
