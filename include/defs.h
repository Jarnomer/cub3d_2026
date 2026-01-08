/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

/* ************************************************************************** */
/*    AXIS ENUM                                                               */
/* ************************************************************************** */
/*
** Orientation of a door in the map
**
** - AXIS_X: Ray crossed a vertical (X) grid line
** - AXIS_Y: Ray crossed a horizontal (Y) grid line
** - AXIS_NS: Door faces North/South (wall segments to N and S)
** - AXIS_EW: Door faces East/West (wall segments to E and W)
*/

typedef enum e_axis
{
	AXIS_X,
	AXIS_Y,
	AXIS_NS,
	AXIS_EW
}	t_axis;

typedef enum e_dir
{
	WALL_NORTH,
	WALL_SOUTH,
	WALL_EAST,
	WALL_WEST
}	t_dir;

typedef enum e_type
{
	ENTITY_NONE,
	ENTITY_BARREL,
	ENTITY_DOOR,
	ENTITY_HEALTH,
	ENTITY_ARMOR,
	ENTITY_AMMO,
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
	STATE_OPEN,
	STATE_DYING,
	STATE_DEAD,
	STATE_COUNT
}	t_state;

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

typedef enum e_spr_id
{
	SPRITE_BARREL,
	SPRITE_DOOR,
	SPRITE_HEALTH,
	SPRITE_ARMOR,
	SPRITE_AMMO,
	SPRITE_COUNT
}	t_spr_id;

typedef enum e_sht_id
{
	SHEET_DOOR,
	SHEET_COUNT
}	t_sht_id;

typedef enum e_anim_id
{
	ANIM_NONE,
	ANIM_DOOR_IDLE,
	ANIM_DOOR_OPEN,
	ANIM_DOOR_CLOSE,
	ANIM_COUNT
}	t_anim_id;

#endif
