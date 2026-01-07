/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include <render.h>
# include <vector.h>
# include <types.h>

/* ************************************************************************** */
/*    FORWARD DECLARATIONS                                                    */
/* ************************************************************************** */

typedef struct s_game	t_game;
typedef struct s_entity	t_entity;

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

/*
** Sprite projection data for rendering
** - trans:     Camera-space coordinates (x = lateral, y = depth)
** - screen:    Screen position (center of sprite)
** - size:      Rendered size in pixels
** - start/end: Clipped draw bounds
** - tex_id:    Texture ID for single-texture sprites
** - sheet_id:  Sheet ID for animated sprites
** - frame:     Current frame index (for sheets)
** - dist:      Distance for z-buffer/fog
** - use_sheet: Whether to use sheet or single texture
*/
typedef struct s_proj
{
	t_vec2		trans;
	t_vec2i		screen;
	t_vec2i		size;
	t_vec2i		start;
	t_vec2i		end;
	t_u32		tex_id;
	t_u32		sheet_id;
	t_i32		frame;
	t_f32		dist;
	bool		use_sheet;
}	t_proj;

bool	project_sprite(t_game *game, t_entity *ent, t_proj *proj);
t_u32	collect_sprites(t_game *game, t_proj *projs);
void	sort_sprites(t_proj *projs, t_u32 count);

void	sheet_load(t_sheet *sheet, const char *path, t_i32 cols, t_i32 rows);
void	sheet_destroy(t_sheet *sheet);
t_vec2i	sheet_frame_offset(t_sheet *sheet, t_i32 frame);
t_u32	sheet_sample(t_sheet *sheet, t_i32 frame, t_i32 x, t_i32 y);

#endif
