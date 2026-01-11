/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_damage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	entity_damage(t_game *game, t_i32 entity_idx, t_i32 amount)
{
	t_entity	*ent;

	if (entity_idx < 0 || (size_t)entity_idx >= game->entities.size)
		return ;
	ent = darray_get(&game->entities, entity_idx);
	if (!ent || !ent->is_active)
		return ;
	if (ent->health <= 0)
		return ;
	ent->health -= amount;
	if (ent->health <= 0)
	{
		ent->health = 0;
		if (ent->type == ENTITY_BARREL)
			barrel_explode(ent);
		else
			ent->state = STATE_DEAD;
	}
}

void	entity_death(t_entity *ent)
{
	if (ent->state != STATE_DYING)
		return ;
	if (!ent->anim.is_finished)
		return ;
	if (ent->type == ENTITY_BARREL)
		barrel_death(ent);
}
