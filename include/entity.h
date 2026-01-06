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

# include <types.h>

typedef struct s_game	t_game;

typedef enum e_type
{
	ENTITY_NONE,
	ENTITY_BARREL,
	ENTITY_DOOR,
	ENTITY_PICKUP_HP,
	ENTITY_PICKUP_AMMO,
	ENTITY_ENEMY,
	ENTITY_PLAYER,
	ENTITY_COUNT
}	t_type;

typedef enum e_state
{
	STATE_IDLE,
	STATE_ACTIVE,
	STATE_OPENING,
	STATE_CLOSING,
	STATE_DYING,
	STATE_DEAD,
	STATE_COUNT
}	t_state;

typedef struct s_entdef
{
	t_type		type;
	t_u32		sprite_id;
	t_f32		scale;
	t_i32		health;
	bool		solid;
}	t_entdef;

typedef struct s_entity
{
	t_vec2		pos;
	t_f32		z;
	t_type		type;
	t_state		state;
	t_u32		tex_id;
	t_f32		scale;
	t_i32		health;
	bool		active;
	bool		solid;
}	t_entity;

void			entity_load_spawns(t_game *game);
const t_entdef	*entity_get_def(t_type type);
void			entity_apply_def(t_entity *ent, const t_entdef *def);
t_entity		*entity_get(t_game *game, t_u32 index);
t_u32			entity_count(t_game *game);

#endif