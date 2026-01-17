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

# include <calc.h>
# include <defs.h>

typedef struct s_game	t_game;
typedef struct s_hit	t_hit;

typedef struct s_partdef
{
	t_part_id	id;
	t_rangeu	color;
	t_range		speed;
	t_range		life;
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
	t_rangei	count;
}	t_surfdef;

typedef struct s_particle
{
	t_vec3		pos;
	t_vec3		vel;
	t_range		life;
	t_part_id	type;
	bool		is_active;
}	t_particle;

typedef struct s_prtclmgr
{
	t_particle	*particles;
	t_partdef	partdefs[PARTICLE_COUNT];
	t_surfdef	surfdefs[SURFACE_COUNT];
	t_u32		capacity;
	t_u32		active;
}	t_prtclmgr;

void		particle_init(t_prtclmgr *mgr, size_t capacity);
void		particle_destroy(t_prtclmgr *mgr);
void		particle_clear(t_prtclmgr *mgr);
void		particle_update_all(t_prtclmgr *mgr, t_f32 dt);

void		particle_emit_impact(t_game *game, t_hit *hit);
void		particle_spawn(t_prtclmgr *mgr,
				t_part_id type, t_vec3 pos, t_vec3 dir);

void		render_particles(t_game *game);

t_particle	*particle_get_inactive(t_prtclmgr *mgr);
t_surfdef	*surface_get_def(t_prtclmgr *mgr, t_hit *hit);

#endif
