/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static bool	is_exposed(char **grid, int x, int y, t_parse *ctx)
{
	int	row_len;

	if (x < 0 || y < 0 || y >= ctx->map->height)
		return (true);
	row_len = ft_strlen(grid[y]);
	if (x >= row_len)
		return (true);
	if (grid[y][x] == CHAR_SPACE)
		return (true);
	return (false);
}

static void	floodfill(char **grid, int x, int y, t_parse *ctx)
{
	if (is_exposed(grid, x, y, ctx))
		err_exit_msg(MSG_MAP_WALL);
	if (grid[y][x] == CHAR_WALL || grid[y][x] == 'V')
		return ;
	grid[y][x] = 'V';
	floodfill(grid, x + 1, y, ctx);
	floodfill(grid, x - 1, y, ctx);
	floodfill(grid, x, y + 1, ctx);
	floodfill(grid, x, y - 1, ctx);
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
	int		start_x;
	int		start_y;

	dup = duplicate_grid(ctx);
	start_x = (int)ctx->map->spawn_pos.x;
	start_y = (int)ctx->map->spawn_pos.y;
	floodfill(dup, start_x, start_y, ctx);
	ft_free_double((void ***)&dup);
}
