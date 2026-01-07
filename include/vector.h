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
/*    VECTOR STRUCTURE                                                        */
/* ************************************************************************** */
/*
** [ADD DETAILS HERE LATER]
*/

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

/* ************************************************************************** */
/*    FUNCTION PROTOTYPES                                                     */
/* ************************************************************************** */
/*
** See source files for function details
*/

t_vec2		vec2_new(t_f32 x, t_f32 y);
t_vec2		vec2_zero(void);
t_vec2		vec2_from_angle(t_f32 angle);

t_vec2		vec2_add(t_vec2 a, t_vec2 b);
t_vec2		vec2_sub(t_vec2 a, t_vec2 b);
t_f32		vec2_dot(t_vec2 a, t_vec2 b);
t_vec2		vec2_mul(t_vec2 v, t_f32 scalar);
t_vec2		vec2_div(t_vec2 v, t_f32 scalar);

t_f32		vec2_len(t_vec2 v);
t_vec2		vec2_normalize(t_vec2 v);
t_vec2		vec2_perp(t_vec2 v);

t_vec2i		vec2i_new(t_i32 x, t_i32 y);
t_vec2i		vec2i_from_vec2(t_vec2 v);
t_vec2		vec2_from_vec2i(t_vec2i v);

#endif
