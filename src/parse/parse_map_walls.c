/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static bool	is_barrier(char c)
{
	return (c == CHAR_WALL || c == CHAR_SPACE);
}

static int	flood_fill(char **grid, int y, int x)
{
	int	result;

	if (y < 0 || x < 0 || !grid[y] || !grid[y][x])
		return (1);
	if (is_barrier(grid[y][x]))
		return (0);
	grid[y][x] = CHAR_WALL;
	result = 0;
	result += flood_fill(grid, y - 1, x);
	result += flood_fill(grid, y + 1, x);
	result += flood_fill(grid, y, x - 1);
	result += flood_fill(grid, y, x + 1);
	return (result);
}

static void	check_walls(char **grid)
{
	int	y;
	int	x;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (!is_barrier(grid[y][x]))
			{
				if (flood_fill(grid, y, x))
					err_exit_msg(MSG_MAP_WALL);
			}
			x++;
		}
		y++;
	}
}

static char	**duplicate_grid(t_parse *ctx)
{
	char	**dup;
	int		i;

	dup = safe_calloc(sizeof(char *) * (ctx->map->height + 1));
	i = 0;
	while (i < ctx->map->height)
	{
		dup[i] = safe_strdup(ctx->map->grid[i]);
		i++;
	}
	return (dup);
}

void	parse_map_walls(t_parse *ctx)
{
	char	**dup;

	dup = duplicate_grid(ctx);
	check_walls(dup);
	free_arr(dup);
}
