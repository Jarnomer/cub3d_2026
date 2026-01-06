/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include <render.h>
# include <sprite.h>
# include <entity.h>
# include <anim.h>

typedef enum e_spr_id
{
	SPRITE_BARREL,
	SPRITE_DOOR,
	SPRITE_LAMP,
	SPRITE_PICKUP_HP,
	SPRITE_PICKUP_AMMO,
	SPRITE_COUNT
}	t_spr_id;

typedef enum e_tex_id
{
	TEXTURE_WALL_N,
	TEXTURE_WALL_S,
	TEXTURE_WALL_E,
	TEXTURE_WALL_W,
	TEXTURE_FLOOR,
	TEXTURE_CEILING,
	TEXTURE_COUNT
}	t_tex_id;

# define PATH_FLOOR		"assets/textures/floor.png"
# define PATH_CEILING	"assets/textures/ceiling.png"
# define PATH_BARREL	"assets/sprites/barrel.png"
# define PATH_DOOR		"assets/sprites/door.png"

/* ************************************************************************** */
/*    ASSETS STRUCTURE                                                        */
/* ************************************************************************** */

typedef struct s_assets
{
	t_tex		textures[MAX_TEXTURES];
	t_tex		sprites[MAX_SPRITES];
	t_sheet		sheets[MAX_SHEETS];
	t_anidef	anidefs[MAX_ANIMS];
	t_entdef	entdefs[MAX_ENTITIES];
	bool		loaded;
}	t_assets;

void	assets_init(t_assets *assets, t_map *map);
void	assets_destroy(t_assets *assets);

t_tex	*assets_get_sprite(t_assets *assets, t_spr_id id);
t_tex	*assets_get_texture(t_assets *assets, t_tex_id id);

#endif