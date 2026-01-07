/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include <render.h>
# include <sprite.h>
# include <entity.h>
# include <anim.h>
# include <defs.h>

// NEED TO GET RID OF THIS STYLE...
# define PATH_FLOOR			"assets/textures/floor.png"
# define PATH_CEILING		"assets/textures/ceiling.png"
# define PATH_BARREL		"assets/sprites/barrel.png"
# define PATH_SHEET_DOOR	"assets/sheets/door.png"

/* ************************************************************************** */
/*    TEXTURE STRUCTURE                                                       */
/* ************************************************************************** */
/*
** [ADD DETAILS HERE LATER]
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
** [ADD DETAILS HERE LATER]
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

t_tex	*assets_get_texture(t_assets *assets, t_tex_id id);
t_tex	*assets_get_sprite(t_assets *assets, t_spr_id id);
t_sheet	*assets_get_sheet(t_assets *assets, t_sht_id id);

#endif
