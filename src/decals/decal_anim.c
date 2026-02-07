/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decal_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/17 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	decal_start_anim(t_decal *decal, t_decaldef *def, t_game *game)
{
	t_anidef	*anidef;

	if (def->anim_id <= ANIM_NONE || def->anim_id >= ANIM_COUNT)
		return ;
	anim_play(&decal->anim, def->anim_id);
	anidef = &game->assets.anidefs[def->anim_id];
	decal->frame = anim_get_frame(&decal->anim, anidef);
}

void	decal_update_anim(t_decal *decal, t_decaldef *def,
	t_game *game, t_f32 dt)
{
	t_anidef	*anidef;

	if (!anim_is_playing(&decal->anim))
		return ;
	anidef = &game->assets.anidefs[decal->anim.def_id];
	anim_update(&decal->anim, anidef, dt);
	decal->frame = anim_get_frame(&decal->anim, anidef);
	if (decal->anim.is_finished)
		decal->frame = def->decal_frame;
}
