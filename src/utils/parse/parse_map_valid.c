/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	save_spawn(t_parse *ctx, int x, int y, char c)
{
	t_spawn	*spawn;

	if (ctx->map->entities >= MAX_ENTITIES)
		err_exit_msg(MSG_MAP_ENTITY);
	spawn = &ctx->map->spawns[ctx->map->entities];
	spawn->pos.x = (t_f32)x + CELL_CENTER;
	spawn->pos.y = (t_f32)y + CELL_CENTER;
	spawn->pos.z = 0.0f;
	spawn->type = charmap_to_entity(c);
	ctx->map->grid[y][x] = CHAR_EMPTY;
	ctx->map->entities++;
}

static void	save_player(t_parse *ctx, int x, int y, char c)
{
	ctx->map->position.x = (t_f32)x + CELL_CENTER;
	ctx->map->position.y = (t_f32)y + CELL_CENTER;
	if (c == PLAYER_DIR_N)
		ctx->map->angle = 3.0f * PI / 2.0f;
	else if (c == PLAYER_DIR_S)
		ctx->map->angle = PI / 2.0f;
	else if (c == PLAYER_DIR_E)
		ctx->map->angle = 0.0f;
	else
		ctx->map->angle = PI;
	ctx->map->grid[y][x] = CHAR_EMPTY;
	ctx->map->players++;
}

static void	validate_characters(t_parse *ctx)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (ctx->map->grid[y])
	{
		x = 0;
		while (ctx->map->grid[y][x])
		{
			c = ctx->map->grid[y][x];
			if (!charmap_is_valid(c))
				err_exit_msg(MSG_MAP_CHAR);
			else if (charmap_is_player(c))
				save_player(ctx, x, y, c);
			else if (charmap_is_spawn(c))
				save_spawn(ctx, x, y, c);
			x++;
		}
		y++;
	}
}

static void	calculate_dimensions(t_parse *ctx)
{
	int		i;
	size_t	len;

	ctx->map->height = 0;
	ctx->map->width = 0;
	i = 0;
	while (ctx->map->grid[i])
	{
		len = ft_strlen(ctx->map->grid[i]);
		if ((int)len > ctx->map->width)
			ctx->map->width = (int)len;
		ctx->map->height++;
		i++;
	}
	if (ctx->map->height < MAP_MIN_SIZE
		|| ctx->map->width < MAP_MIN_SIZE)
		err_exit_msg(MSG_MAP_SIZE);
	if (ctx->map->height > MAP_MAX_SIZE
		|| ctx->map->width > MAP_MAX_SIZE)
		err_exit_msg(MSG_MAP_SIZE);
}

void	parse_map_validate(t_parse *ctx)
{
	calculate_dimensions(ctx);
	validate_characters(ctx);
	if (ctx->map->players != 1)
		err_exit_msg(MSG_MAP_PLAYER);
	parse_map_walls(ctx);
}
