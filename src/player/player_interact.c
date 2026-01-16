/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	interact_with_target(t_entity *ent)
{
	if (ent->type == ENTITY_DOOR)
		door_interact(ent);
}

static bool	is_interactable(t_entity *ent)
{
	if (ent->type == ENTITY_DOOR)
		return (door_can_interact(ent));
	return (false);
}

static t_entity	*find_interactable(t_game *game)
{
	t_entity	*ent;
	t_entity	*object;
	t_f32		dist;
	t_f32		nearest;
	size_t		i;

	object = NULL;
	nearest = INTERACT_RANGE + 1.0f;
	i = 0;
	while (i < game->entities.size)
	{
		ent = darray_get(&game->entities, i);
		if (ent->is_active && is_interactable(ent))
		{
			dist = vec2_len(vec2_sub(
				vec2_from_vec3(ent->pos), game->camera.pos));
			if (dist < nearest && dist <= INTERACT_RANGE)
			{
				object = ent;
				nearest = dist;
			}
		}
		i++;
	}
	return (object);
}

void	player_interact(t_game *game)
{
	t_entity	*target;

	target = find_interactable(game);
	if (target)
		interact_with_target(target);
}
