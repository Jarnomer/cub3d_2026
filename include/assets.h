/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include <render.h>
# include <entity.h>
# include <anim.h>
# include <defs.h>

/* ************************************************************************** */
/*    TEXTURE STRUCTURE                                                       */
/* ************************************************************************** */
/*
** Texture data loaded from PNG file
**
** - mlx_tex: MLX42 texture handle (for cleanup)
** - pixels:  Raw pixel data pointer (RGBA format)
** - width:   Texture width in pixels
** - height:  Texture height in pixels
*/

typedef struct s_texture
{
	t_mlxt	*mlx_tex;
	t_u32	*pixels;
	t_i32	width;
	t_i32	height;
}	t_tex;

/* ************************************************************************** */
/*    SHEET STRUCTURE                                                         */
/* ************************************************************************** */
/*
** Sprite sheet - single texture with multiple frames
**
** - tex:    The full texture containing all frames
** - width:  Width of a single frame in pixels
** - height: Height of a single frame in pixels
** - cols:   Number of columns in the sheet
** - rows:   Number of rows in the sheet
** - count:  Total number of frames (cols * rows)
*/

typedef struct s_sheet
{
	t_tex	tex;
	t_i32	width;
	t_i32	height;
	t_i32	cols;
	t_i32	rows;
	t_i32	count;
}	t_sheet;

/* ************************************************************************** */
/*    ASSETS STRUCTURE                                                        */
/* ************************************************************************** */
/*
** Central asset storage for all game resources
**
** - textures: Wall, floor, ceiling textures
** - sprites:  Static sprite images (barrel, pickups)
** - sheets:   Animated sprite sheets (door, enemies)
** - anidefs:  Animation definitions
** - entdefs:  Entity definitions
** - loaded:   Flag to prevent double-free
*/

typedef struct s_assets
{
	t_tex		textures[MAX_TEXTURES];
	t_tex		sprites[MAX_SPRITES];
	t_sheet		sheets[MAX_SHEETS];
	t_anidef	anidefs[MAX_ANIMS];
	t_entdef	entdefs[MAX_ENTITIES];
	bool		loaded;
}	t_assets;

/* ************************************************************************** */
/*    FUNCTION PROTOTYPES                                                     */
/* ************************************************************************** */
/*
** See source files for function details
*/

void	assets_init(t_assets *assets, t_map *map);
void	assets_destroy(t_assets *assets);

void	texture_load(t_tex *tex, const char *path);
void	texture_destroy(t_tex *tex);
t_u32	texture_sample(t_tex *tex, t_i32 x, t_i32 y);

void	sheet_load(t_sheet *sheet, const char *path, t_i32 cols, t_i32 rows);
void	sheet_destroy(t_sheet *sheet);
t_u32	sheet_sample(t_sheet *sheet, t_i32 frame, t_i32 x, t_i32 y);

t_tex	*assets_get_texture(t_assets *assets, t_tex_id id);
t_tex	*assets_get_sprite(t_assets *assets, t_spr_id id);
t_sheet	*assets_get_sheet(t_assets *assets, t_sht_id id);

#endif
