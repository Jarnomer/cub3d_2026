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

static void	handle_death(t_entity *ent)
{
	ent->health = 0;
	if (ent->type == ENTITY_BARREL)
		barrel_explode(ent);
	else
		ent->state = STATE_DEAD;
}

void	entity_damage(t_game *game, t_i32 idx, t_i32 amount)
{
	t_entity	*ent;

	if (idx < 0 || (size_t)idx >= game->entities.size)
		return ;
	ent = darray_get(&game->entities, idx);
	if (!ent || !ent->is_active)
		return ;
	if (ent->health <= 0)
		return ;
	ent->health -= amount;
	if (ent->health <= 0)
		handle_death(ent);
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
