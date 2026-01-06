/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include <vector.h>
# include <types.h>

# include <render.h>

typedef struct s_game	t_game;
typedef struct s_entity	t_entity;

typedef struct s_sheet
{
	t_tex	tex;
	t_i32	width;
	t_i32	height;
	t_i32	cols;
	t_i32	rows;
	t_i32	count;
}	t_sheet;

typedef struct s_proj
{
	t_vec2		trans;
	t_vec2i		screen;
	t_vec2i		size;
	t_vec2i		start;
	t_vec2i		end;
	t_u32		tex_id;
	t_f32		dist;
}	t_proj;

bool	sprite_project(t_game *game, t_entity *ent, t_proj *proj);
t_u32	collect_sprites(t_game *game, t_proj *projs);
void	sort_sprites(t_proj *projs, t_u32 count);

#endif
