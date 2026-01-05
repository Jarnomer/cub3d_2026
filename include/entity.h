/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include <types.h>

typedef enum e_type
{
	ENTITY_NONE,
	ENTITY_DOOR,
	ENTITY_ENEMY,
	ENTITY_PLAYER,
	ENTITY_PICKUP_HP,
	ENTITY_PICKUP_AMMO,
	ENTITY_BARREL,
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

void		entity_init(t_entity *ent);
t_entity	entity_create(t_type type, t_vec2 pos);

#endif
