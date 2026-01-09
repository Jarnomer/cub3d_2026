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

# define CELL_VOID		-1
# define ENTITY_VOID	-1

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

typedef enum e_cell
{
	CELL_EMPTY,
	CELL_WALL,
	CELL_DOOR
}	t_cell;

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
	STATE_FIRING,
	STATE_RELOADING,
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
	SHEET_BARREL,
	SHEET_SHOTGUN,
	SHEET_COUNT
}	t_sht_id;

typedef enum e_anim_id
{
	ANIM_NONE,
	ANIM_DOOR_IDLE,
	ANIM_DOOR_OPEN,
	ANIM_DOOR_CLOSE,
	ANIM_BARREL_IDLE,
	ANIM_BARREL_EXPLODE,
	ANIM_SHOTGUN_IDLE,
	ANIM_SHOTGUN_FIRE,
	ANIM_SHOTGUN_RELOAD,
	ANIM_COUNT
}	t_anim_id;

typedef enum e_wpn_id
{
	WEAPON_NONE,
	WEAPON_SHOTGUN,
	WEAPON_PISTOL,
	WEAPON_COUNT
}	t_wpn_id;

typedef enum e_ammo
{
	AMMO_SHELL,
	AMMO_BULLET,
	AMMO_CELL,
	AMMO_EXP,
	AMMO_COUNT
}	t_ammo;

#endif
