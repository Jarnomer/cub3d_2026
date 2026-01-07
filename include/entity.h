/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include <anim.h>
# include <types.h>
# include <defs.h>

/* ************************************************************************** */
/*    FORWARD DECLARATIONS                                                    */
/* ************************************************************************** */

typedef struct s_game	t_game;
typedef struct s_assets	t_assets;
typedef struct s_proj	t_proj;

/* ************************************************************************** */
/*    ENTITY DEFINITION                                                       */
/* ************************************************************************** */
/*
** Static entity definition data loaded from config
** - [ADD EXPLANATIONS HERE LATER]
*/

typedef struct s_entdef
{
	t_type		type;
	t_u32		sprite_id;
	t_u32		sheet_id;
	t_u32		anim_id;
	t_f32		scale;
	t_f32		z_offset;
	t_i32		health;
	bool		solid;
	bool		use_sheet;
}	t_entdef;

/* ************************************************************************** */
/*    ENTITY STRUCTURE                                                        */
/* ************************************************************************** */
/*
** Entity instance - runtime data
** - [ADD EXPLANATIONS HERE LATER]
*/

typedef struct s_entity
{
	t_vec2		pos;
	t_f32		z;
	t_type		type;
	t_state		state;
	t_anim		anim;
	t_u32		tex_id;
	t_u32		sheet_id;
	t_f32		scale;
	t_f32		z_offset;
	t_i32		health;
	bool		active;
	bool		solid;
	bool		has_anim;
	bool		use_sheet;
}	t_entity;

/* ************************************************************************** */
/*    FUNCTION PROTOTYPES                                                     */
/* ************************************************************************** */
/*
** See source files for function details
*/

void		entity_load_spawns(t_game *game);

void		entity_apply_entdef(t_entity *ent, const t_entdef *def);

t_entity	*entity_get(t_game *game, t_u32 index);
t_u32		entity_count(t_game *game);

void		door_init(t_entity *ent);
bool		entity_is_door(t_entity *ent);
t_i32		door_get_frame(t_entity *ent, t_assets *assets);

#endif
