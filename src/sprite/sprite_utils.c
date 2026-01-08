/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	sort_sprites(t_proj *projs, t_u32 count)
{
	t_proj	temp;
	t_u32	i;
	t_u32	j;

	i = 1;
	while (i < count)
	{
		temp = projs[i];
		j = i;
		while (j > 0 && projs[j - 1].dist < temp.dist)
		{
			projs[j] = projs[j - 1];
			j--;
		}
		projs[j] = temp;
		i++;
	}
}

t_u32	collect_sprites(t_game *game, t_proj *projs)
{
	t_entity	*ent;
	t_u32		count;
	size_t		i;

	count = 0;
	i = 0;
	while (i < game->entities.size && count < MAX_ENTITIES)
	{
		ent = darray_get(&game->entities, i);
		if (!ent->active || ent->type == ENTITY_DOOR)
		{
			i++;
			continue ;
		}
		if (project_sprite(game, ent, &projs[count]))
			count++;
		i++;
	}
	return (count);
}
