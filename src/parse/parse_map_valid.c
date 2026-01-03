/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static float	get_spawn_angle(char c)
{
	if (c == CHAR_PLAYER_N)
		return (3.0f * PI / 2.0f);
	if (c == CHAR_PLAYER_S)
		return (PI / 2.0f);
	if (c == CHAR_PLAYER_E)
		return (0.0f);
	return (PI);
}

static void	save_player(t_parse *ctx, int x, int y, char c)
{
	ctx->map->spawn_pos.x = (float)x + 0.5f;
	ctx->map->spawn_pos.y = (float)y + 0.5f;
	ctx->map->spawn_angle = get_spawn_angle(c);
	ctx->map->grid[y][x] = CHAR_EMPTY;
}

static void	validate_characters(t_parse *ctx, int *player_count)
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
			if (!ft_strchr(CHARSET_VALID, c))
				err_exit_msg(MSG_MAP_CHAR);
			if (ft_strchr(CHARSET_PLAYER, c))
			{
				save_player(ctx, x, y, c);
				(*player_count)++;
			}
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
	if (ctx->map->height < MAP_MIN_SIZE || ctx->map->width < MAP_MIN_SIZE)
		err_exit_msg(MSG_MAP_SIZE);
	if (ctx->map->height > MAP_MAX_SIZE || ctx->map->width > MAP_MAX_SIZE)
		err_exit_msg(MSG_MAP_SIZE);
}

void	parse_map_validate(t_parse *ctx)
{
	int	player_count;

	calculate_dimensions(ctx);
	player_count = 0;
	validate_characters(ctx, &player_count);
	if (player_count != 1)
		err_exit_msg(MSG_MAP_PLAYER);
	parse_map_walls(ctx);
}
