/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICLE_H
# define PARTICLE_H

# include <vector.h>
# include <types.h>
# include <defs.h>

typedef struct s_game	t_game;
typedef struct s_hit	t_hit;

typedef struct s_partdef
{
	t_part_id	id;
	t_u32		color_start;
	t_u32		color_end;
	t_f32		speed_min;
	t_f32		speed_max;
	t_f32		life_min;
	t_f32		life_max;
	t_f32		gravity;
	t_f32		spread;
	t_f32		size;
	t_f32		bounce;
	bool		is_faded;
}	t_partdef;

typedef struct s_surfdef
{
	t_surface	type;
	t_part_id	particle;
	t_i32		count_min;
	t_i32		count_max;
}	t_surfdef;

typedef struct s_particle
{
	t_vec3		pos;
	t_vec3		vel;
	t_f32		life;
	t_f32		lifespan;
	t_part_id	type;
	bool		is_active;
}	t_particle;

typedef struct s_emitter
{
	t_particle	*particles;
	t_partdef	partdefs[PARTICLE_COUNT];
	t_surfdef	surfdefs[SURFACE_COUNT];
	t_u32		capacity;
	t_u32		active_count;
}	t_emitter;

void		particle_init(t_emitter *emitter, size_t capacity);
void		particle_destroy(t_emitter *emitter);
void		particle_clear(t_emitter *emitter);
void		particle_update_all(t_emitter *emitter, t_f32 dt);

void		particle_emit_impact(t_game *game, t_hit *hit);
void		particle_spawn(t_emitter *emitter,
				t_part_id type, t_vec3 pos, t_vec3 dir);

void		render_particles(t_game *game);

t_particle	*particle_get_inactive(t_emitter *emitter);
t_surfdef	*surface_get_def(t_emitter *emitter, t_type type);

#endif
