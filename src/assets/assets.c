/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	load_walls(t_assets *assets, t_map *map)
{
	texture_load(&assets->textures[TEXTURE_WALL_N], map->textures[ELEM_NO]);
	texture_load(&assets->textures[TEXTURE_WALL_S], map->textures[ELEM_SO]);
	texture_load(&assets->textures[TEXTURE_WALL_E], map->textures[ELEM_WE]);
	texture_load(&assets->textures[TEXTURE_WALL_W], map->textures[ELEM_EA]);
}

void	assets_init(t_assets *assets, t_map *map)
{
	*assets = (t_assets){0};
	config_load_all(assets);
	load_walls(assets, map);
	assets->loaded = true;
}

void	assets_destroy(t_assets *assets)
{
	int	i;

	if (!assets || !assets->loaded)
		return ;
	i = 0;
	while (i < TEXTURE_COUNT)
		texture_destroy(&assets->textures[i++]);
	i = 0;
	while (i < SPRITE_COUNT)
		texture_destroy(&assets->sprites[i++]);
	i = 0;
	while (i < SHEET_COUNT)
		sheet_destroy(&assets->sheets[i++]);
	assets->loaded = false;
}
