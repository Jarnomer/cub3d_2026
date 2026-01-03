/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <cub3d.h>

# define MAX_KEYS	512

/* ************************************************************************** */
/*    NUMERIC TYPES                                                           */
/* ************************************************************************** */

typedef uint8_t		t_u8;
typedef uint16_t	t_u16;
typedef uint32_t	t_u32;
typedef uint64_t	t_u64;
typedef int8_t		t_i8;
typedef int16_t		t_i16;
typedef int32_t		t_i32;
typedef int64_t		t_i64;
typedef float		t_f32;
typedef double		t_f64;

/* ************************************************************************** */
/*    VECTOR TYPES                                                            */
/* ************************************************************************** */

typedef struct s_vec2
{
	t_f32	x;
	t_f32	y;
}	t_vec2;

typedef struct s_vec2i
{
	t_i32	x;
	t_i32	y;
}	t_vec2i;

typedef struct s_vec3
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
}	t_vec3;

typedef struct s_vec4
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
	t_f32	w;
}	t_vec4;

/* ************************************************************************** */
/*    COLOR TYPES                                                             */
/* ************************************************************************** */

typedef struct s_color
{
	t_u8	r;
	t_u8	g;
	t_u8	b;
	t_u8	a;
}	t_color;

typedef union u_pixel
{
	t_u32	value;
	t_color	rgba;
}	t_pixel;

/* ************************************************************************** */
/*    RECTANGLE TYPES                                                         */
/* ************************************************************************** */

typedef struct s_rect
{
	t_i32	x;
	t_i32	y;
	t_i32	w;
	t_i32	h;
}	t_rect;

typedef struct s_rectf
{
	t_f32	x;
	t_f32	y;
	t_f32	w;
	t_f32	h;
}	t_rectf;

/* ************************************************************************** */
/*    DIRECTION TYPES                                                         */
/* ************************************************************************** */

typedef enum e_dir4
{
	DIR4_NORTH = 0,
	DIR4_SOUTH = 1,
	DIR4_EAST = 2,
	DIR4_WEST = 3,
	DIR4_COUNT = 4
}	t_dir4;

typedef enum e_dir8
{
	DIR8_N = 0,
	DIR8_NE = 1,
	DIR8_E = 2,
	DIR8_SE = 3,
	DIR8_S = 4,
	DIR8_SW = 5,
	DIR8_W = 6,
	DIR8_NW = 7,
	DIR8_COUNT = 8
}	t_dir8;

/* ************************************************************************** */
/*    COLLISION LAYERS                                                        */
/* ************************************************************************** */

typedef enum e_layer
{
	LAYER_NONE = 0,
	LAYER_PLAYER = 1 << 0,
	LAYER_ENEMY = 1 << 1,
	LAYER_PROJ_PLAYER = 1 << 2,
	LAYER_PROJ_ENEMY = 1 << 3,
	LAYER_PICKUP = 1 << 4,
	LAYER_WALL = 1 << 5,
	LAYER_TRIGGER = 1 << 6,
	LAYER_CORPSE = 1 << 7,
	LAYER_DOOR = 1 << 8,
	LAYER_HAZARD = 1 << 9
}	t_layer;

/* ************************************************************************** */
/*    ENTITY COMPONENTS                                                       */
/* ************************************************************************** */

typedef enum e_comp
{
	COMP_NONE = 0,
	COMP_TRANSFORM = 1 << 0,
	COMP_VELOCITY = 1 << 1,
	COMP_COLLIDER = 1 << 2,
	COMP_SPRITE = 1 << 3,
	COMP_HEALTH = 1 << 4,
	COMP_AI = 1 << 5,
	COMP_PLAYER = 1 << 6,
	COMP_WEAPON = 1 << 7,
	COMP_PICKUP = 1 << 8,
	COMP_PARTICLE = 1 << 9,
	COMP_ANIM = 1 << 10,
	COMP_DAMAGE = 1 << 11,
	COMP_DOOR = 1 << 12,
	COMP_TRIGGER = 1 << 13,
	COMP_LIGHT = 1 << 14
}	t_comp;

typedef enum e_axis
{
	AXIS_X = 0,
	AXIS_Y = 1
}	t_axis;

#endif
