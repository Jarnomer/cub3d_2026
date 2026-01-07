/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	advance_frame(t_anim *anim, const t_anidef *def)
{
	anim->frame++;
	if (anim->frame >= def->total)
	{
		if (def->loop)
			anim->frame = 0;
		else
		{
			anim->frame = def->total - 1;
			anim->finished = true;
			anim->playing = false;
		}
	}
}

void	anim_update(t_anim *anim, const t_anidef *def, t_f32 dt)
{
	if (!anim->playing || anim->finished)
		return ;
	if (!def || def->time <= 0.0f)
		return ;
	anim->timer += dt;
	while (anim->timer >= def->time)
	{
		anim->timer -= def->time;
		advance_frame(anim, def);
		if (anim->finished)
			break ;
	}
}

void	anim_update_entities(t_game *game, t_f32 dt)
{
	t_entity	*ent;
	t_anidef	*def;
	size_t		i;

	i = 0;
	while (i < game->entities.size)
	{
		ent = darray_get(&game->entities, i);
		if (ent->active && ent->has_anim)
		{
			def = &game->assets.anidefs[ent->anim.def_id];
			anim_update(&ent->anim, def, dt);
		}
		i++;
	}
}
