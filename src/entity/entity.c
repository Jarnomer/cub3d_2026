/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	entity_init(t_entity *ent)
{
	ft_bzero(ent, sizeof(t_entity));
	ent->scale = 1.0f;
	ent->state = STATE_IDLE;
	ent->type = ENTITY_NONE;
}

static void	setup_barrel(t_entity *ent)
{
	ent->tex_id = SPRITE_BARREL;
	ent->scale = 0.7f;
	ent->health = 20;
	ent->solid = true;
}

t_entity	entity_create(t_type type, t_vec2 pos)
{
	t_entity	ent;

	entity_init(&ent);
	ent.type = type;
	ent.pos = pos;
	ent.active = true;
	if (type == ENTITY_BARREL)
		setup_barrel(&ent);
	return (ent);
}
