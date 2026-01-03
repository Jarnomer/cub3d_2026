/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <types.h>

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
/*    VEC2 CONSTRUCTORS                                                       */
/* ************************************************************************** */

t_vec2		vec2_new(t_f32 x, t_f32 y);
t_vec2		vec2_zero(void);
t_vec2		vec2_one(void);
t_vec2		vec2_from_angle(t_f32 angle);

/* ************************************************************************** */
/*    VEC2 ARITHMETIC                                                         */
/* ************************************************************************** */

t_vec2		vec2_add(t_vec2 a, t_vec2 b);
t_vec2		vec2_sub(t_vec2 a, t_vec2 b);
t_vec2		vec2_mul(t_vec2 v, t_f32 scalar);
t_vec2		vec2_div(t_vec2 v, t_f32 scalar);
t_vec2		vec2_negate(t_vec2 v);

/* ************************************************************************** */
/*    VEC2 PRODUCTS                                                           */
/* ************************************************************************** */

t_vec2		vec2_hadamard(t_vec2 a, t_vec2 b);
t_f32		vec2_dot(t_vec2 a, t_vec2 b);
t_f32		vec2_cross(t_vec2 a, t_vec2 b);
t_f32		vec2_len(t_vec2 v);
t_f32		vec2_len_sq(t_vec2 v);

/* ************************************************************************** */
/*    VEC2 DISTANCE                                                           */
/* ************************************************************************** */

t_f32		vec2_dist(t_vec2 a, t_vec2 b);
t_f32		vec2_dist_sq(t_vec2 a, t_vec2 b);
t_f32		vec2_angle(t_vec2 v);
t_f32		vec2_angle_to(t_vec2 from, t_vec2 to);

/* ************************************************************************** */
/*    VEC2 TRANSFORMATIONS                                                    */
/* ************************************************************************** */

t_vec2		vec2_normalize(t_vec2 v);
t_vec2		vec2_rotate(t_vec2 v, t_f32 angle);
t_vec2		vec2_perp(t_vec2 v);
t_vec2		vec2_perp_ccw(t_vec2 v);
t_vec2		vec2_reflect(t_vec2 v, t_vec2 normal);

/* ************************************************************************** */
/*    VEC2 MOVEMENT                                                           */
/* ************************************************************************** */

t_vec2		vec2_lerp(t_vec2 a, t_vec2 b, t_f32 t);
t_vec2		vec2_clamp_len(t_vec2 v, t_f32 max_len);
t_vec2		vec2_move_toward(t_vec2 from, t_vec2 to, t_f32 max_dist);

/* ************************************************************************** */
/*    VEC2I OPERATIONS                                                        */
/* ************************************************************************** */

t_vec2i		vec2i_new(t_i32 x, t_i32 y);
t_vec2i		vec2i_from_vec2(t_vec2 v);
t_vec2		vec2_from_vec2i(t_vec2i v);
bool		vec2i_eq(t_vec2i a, t_vec2i b);
t_vec2i		vec2i_add(t_vec2i a, t_vec2i b);
t_vec2i		vec2i_sub(t_vec2i a, t_vec2i b);

#endif
