/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	entity_apply_def(t_entity *ent, const t_entdef *def)
{
	ent->tex_id = def->spr_id;
	ent->scale = def->scale;
	ent->z_offset = def->z_offset;
	ent->health = def->health;
	ent->solid = def->solid;
}

t_entity	*entity_get(t_game *game, t_u32 index)
{
	return ((t_entity *)darray_get(&game->entities, index));
}
