/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include <vector.h>

/* ************************************************************************** */
/*    LOOKUP TABLE                                                            */
/* ************************************************************************** */

# define TRIG_TABLE_SIZE	3600
# define TRIG_TABLE_SCALE	10.0f

typedef struct s_lookup
{
	t_f32	sin_table[TRIG_TABLE_SIZE];
	t_f32	cos_table[TRIG_TABLE_SIZE];
	t_f32	tan_table[TRIG_TABLE_SIZE];
	bool	initialized;
}	t_lookup;

void	lookup_init(t_lookup *lut);
t_f32	lookup_sin(t_lookup *lut, t_f32 angle);
t_f32	lookup_cos(t_lookup *lut, t_f32 angle);
t_f32	lookup_tan(t_lookup *lut, t_f32 angle);

/* ************************************************************************** */
/*    RANDOM                                                                  */
/* ************************************************************************** */

void	rand_seed(t_u32 seed);
t_u32	rand_next(void);
t_f32	rand_float(void);
t_f32	rand_range(t_f32 lo, t_f32 hi);
t_i32	rand_rangei(t_i32 lo, t_i32 hi);
t_vec2	rand_unit_vec2(void);
t_vec2	rand_in_circle(t_f32 radius);

/* ************************************************************************** */
/*    COLOR                                                                   */
/* ************************************************************************** */

t_color	color_new(t_u8 r, t_u8 g, t_u8 b, t_u8 a);
t_color	color_from_u32(t_u32 val);
t_u32	color_to_u32(t_color c);
t_color	color_mul(t_color c, t_f32 factor);
t_color	color_lerp(t_color a, t_color b, t_f32 t);
t_color	color_add(t_color a, t_color b);
t_color	color_blend(t_color dst, t_color src);

/* ************************************************************************** */
/*    ANGLE                                                                   */
/* ************************************************************************** */

t_f32	angle_normalize(t_f32 angle);
t_f32	angle_diff(t_f32 from, t_f32 to);
t_f32	angle_lerp(t_f32 from, t_f32 to, t_f32 t);
t_f32	deg_to_rad(t_f32 deg);
t_f32	rad_to_deg(t_f32 rad);

/* ************************************************************************** */
/*    RECTANGLE                                                               */
/* ************************************************************************** */

t_rect	rect_new(t_i32 x, t_i32 y, t_i32 w, t_i32 h);
bool	rect_contains(t_rect r, t_vec2i point);
bool	rect_overlaps(t_rect a, t_rect b);
t_rect	rect_intersect(t_rect a, t_rect b);

/* ************************************************************************** */
/*    SCALAR FLOAT                                                            */
/* ************************************************************************** */

t_f32	minf(t_f32 a, t_f32 b);
t_f32	maxf(t_f32 a, t_f32 b);
t_f32	clampf(t_f32 val, t_f32 lo, t_f32 hi);
t_f32	absf(t_f32 val);
t_f32	inv_absf(t_f32 val);

/* ************************************************************************** */
/*    SCALAR INT                                                              */
/* ************************************************************************** */

t_i32	mini(t_i32 a, t_i32 b);
t_i32	maxi(t_i32 a, t_i32 b);
t_i32	clampi(t_i32 val, t_i32 lo, t_i32 hi);
t_i32	absi(t_i32 val);

/* ************************************************************************** */
/*    SCALAR OPS                                                              */
/* ************************************************************************** */

t_f32	lerpf(t_f32 a, t_f32 b, t_f32 t);
t_f32	signf(t_f32 val);
t_f32	wrapf(t_f32 val, t_f32 lo, t_f32 hi);
t_f32	smoothstep(t_f32 edge0, t_f32 edge1, t_f32 x);

#endif
