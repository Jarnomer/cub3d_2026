/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	init_entity_ctx(t_entity *ent, t_type type)
{
	if (type == ENTITY_DOOR)
		door_init(ent);
}

static t_entity	entity_create(t_assets *assets, t_type type, t_vec2 pos)
{
	const t_entdef	*def;
	t_entity		ent;

	ent = (t_entity){.pos = pos, .type = type, .active = true};
	def = &assets->entdefs[type];
	entity_apply_entdef(&ent, def);
	init_entity_ctx(&ent, type);
	return (ent);
}

void	entity_load_spawns(t_game *game)
{
	t_spawn		*spawn;
	t_entity	ent;
	t_u32		i;

	i = 0;
	while (i < game->map->spawn_count)
	{
		spawn = &game->map->spawns[i];
		ent = entity_create(&game->assets, spawn->type, spawn->pos);
		darray_push(&game->entities, &ent);
		i++;
	}
}
