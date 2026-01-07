/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_type	char_to_entity(char c)
{
	if (c == CHAR_BARREL)
		return (ENTITY_BARREL);
	if (c == CHAR_DOOR)
		return (ENTITY_DOOR);
	if (c == CHAR_HEALTH)
		return (ENTITY_HEALTH);
	if (c == CHAR_ARMOR)
		return (ENTITY_ARMOR);
	if (c == CHAR_AMMO)
		return (ENTITY_AMMO);
	return (ENTITY_NONE);
}

void	parse_save_spawn(t_parse *ctx, int x, int y, char c)
{
	t_spawn	*spawn;

	if (ctx->map->spawn_count >= MAX_ENTITIES)
		err_exit_msg(MSG_MAP_ENTITY);
	spawn = &ctx->map->spawns[ctx->map->spawn_count];
	spawn->pos.x = (t_f32)x + 0.5f;
	spawn->pos.y = (t_f32)y + 0.5f;
	spawn->type = char_to_entity(c);
	ctx->map->grid[y][x] = CHAR_EMPTY;
	ctx->map->spawn_count++;
}
