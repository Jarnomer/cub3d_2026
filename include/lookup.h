/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOKUP_H
# define LOOKUP_H

# include <types.h>
# include <config.h>

/* ************************************************************************** */
/*    CONSTANTS                                                               */
/* ************************************************************************** */

# define TRIG_TABLE_SIZE	3600
# define TRIG_TABLE_SCALE	10.0f
# define FOG_TABLE_SIZE		256

/* ************************************************************************** */
/*    LOOKUP STRUCTURE                                                        */
/* ************************************************************************** */
/*
** Unified lookup tables for precomputed values
** Eliminates expensive math operations on render
*/

typedef struct s_lookup
{
	t_f32	sin_table[TRIG_TABLE_SIZE];
	t_f32	cos_table[TRIG_TABLE_SIZE];
	t_u8	fog_table[FOG_TABLE_SIZE];
	bool	initialized;
}	t_lookup;

/* ************************************************************************** */
/*    FUNCTION PROTOTYPES                                                     */
/* ************************************************************************** */
/*
** See source files for function details
*/

void	lookup_init(t_lookup *lut);

t_f32	lookup_sin(t_lookup *lut, t_f32 angle);
t_f32	lookup_cos(t_lookup *lut, t_f32 angle);
t_u8	lookup_fog(t_lookup *lut, t_f32 dist);

#endif
