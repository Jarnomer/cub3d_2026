/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_act.c                                       :+:      :+:    :+:   */
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

static t_entity	*find_nearest_interactable(t_game *game)
{
	t_entity	*ent;
	t_entity	*nearest;
	t_f32		dist;
	t_f32		nearest_dist;
	size_t		i;

	nearest = NULL;
	nearest_dist = INTERACT_RANGE + 1.0f;
	i = 0;
	while (i < game->entities.size)
	{
		ent = darray_get(&game->entities, i);
		if (ent->active && is_interactable(ent))
		{
			dist = vec2_len(vec2_sub(ent->pos, game->camera.pos));
			if (dist < nearest_dist && dist <= INTERACT_RANGE)
			{
				nearest = ent;
				nearest_dist = dist;
			}
		}
		i++;
	}
	return (nearest);
}

void	player_interact(t_game *game)
{
	t_entity	*target;

	target = find_nearest_interactable(game);
	if (target)
		interact_with_target(target);
}
