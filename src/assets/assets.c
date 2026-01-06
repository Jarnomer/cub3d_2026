/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	load_sprites(t_assets *assets)
{
	texture_load(&assets->sprites[SPRITE_BARREL], PATH_BARREL);
}

static void	load_textures(t_assets *assets, t_map *map)
{
	texture_load(&assets->textures[TEXTURE_WALL_N], map->textures[ELEM_NO]);
	texture_load(&assets->textures[TEXTURE_WALL_S], map->textures[ELEM_SO]);
	texture_load(&assets->textures[TEXTURE_WALL_E], map->textures[ELEM_WE]);
	texture_load(&assets->textures[TEXTURE_WALL_W], map->textures[ELEM_EA]);
	texture_load(&assets->textures[TEXTURE_FLOOR], PATH_FLOOR);
	texture_load(&assets->textures[TEXTURE_CEILING], PATH_CEILING);
}

void	assets_init(t_assets *assets, t_map *map)
{
	ft_bzero(assets, sizeof(t_assets));
	config_load_all(assets);
	load_textures(assets, map);
	load_sprites(assets);
	assets->loaded = true;
}

void	assets_destroy(t_assets *assets)
{
	int	i;

	if (!assets || !assets->loaded)
		return ;
	i = 0;
	while (i < MAX_TEXTURES)
	{
		texture_destroy(&assets->textures[i]);
		i++;
	}
	i = 0;
	while (i < MAX_SPRITES)
	{
		texture_destroy(&assets->sprites[i]);
		i++;
	}
	assets->loaded = false;
}
