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

typedef struct s_game	t_game;
typedef struct s_assets	t_assets;

typedef struct s_entdef
{
	t_type		type;
	t_spr_id	spr_id;
	t_sheet_id	sheet_id;
	t_anim_id	anim_id;
	t_f32		scale;
	t_f32		offset;
	t_i32		health;
	bool		is_solid;
	bool		use_sheet;
}	t_entdef;

typedef struct s_entity
{
	t_vec3		pos;
	t_type		type;
	t_state		state;
	t_anim		anim;
	t_f32		scale;
	t_i32		health;
	t_f32		cooldown;
	t_sheet_id	sheet_id;
	t_spr_id	spr_id;
	bool		is_active;
	bool		is_solid;
	bool		has_anim;
	bool		use_sheet;
}	t_entity;

void		entity_load_spawns(t_game *game);
void		entity_update_all(t_game *game, t_f32 dt);

void		entity_damage(t_game *game, t_i32 entity_idx, t_i32 amount);
void		entity_death(t_entity *ent);

void		door_init(t_entity *ent);
void		door_update(t_entity *ent, t_f32 dt);
void		door_interact(t_entity *ent);

void		door_start_opening(t_entity *ent);
void		door_start_closing(t_entity *ent);
void		door_update_open(t_entity *ent, t_f32 dt);
void		door_set_open(t_entity *ent);
void		door_set_closed(t_entity *ent);

bool		door_can_interact(t_entity *ent);
bool		door_is_animating(t_entity *ent);
bool		door_is_blocking(t_entity *ent);
t_i32		door_get_frame(t_entity *ent, t_assets *assets);

void		barrel_init(t_entity *ent);
void		barrel_explode(t_entity *ent);
void		barrel_death(t_entity *ent);

#endif
