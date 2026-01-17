/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decal.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/17 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECAL_H
# define DECAL_H

# include <pool.h>
# include <calc.h>
# include <defs.h>

typedef struct s_game	t_game;
typedef struct s_hit	t_hit;

typedef struct s_decaldef
{
	t_decal_id	id;
	t_sheet_id	sheet_id;
	t_anim_id	anim_id;
	t_i32		decal_frame;
	t_f32		scale;
	t_f32		lifespan;
	t_f32		fade_time;
}	t_decaldef;

typedef struct s_impactdef
{
	t_ammo		ammo;
	t_type		target;
	t_decal_id	decal;
}	t_impactdef;

typedef struct s_decal
{
	t_vec3		pos;
	t_dir		dir;
	t_f32		wall_x;
	t_f32		dist;
	t_f32		life;
	t_f32		max_life;
	t_f32		opacity;
	t_decal_id	type;
	t_i32		frame;
	bool		is_animating;
	bool		is_active;
}	t_decal;

typedef struct s_decalmgr
{
	t_pool		pool;
	t_decaldef	defs[DECAL_COUNT];
	t_impactdef	*impacts;
	t_u32		impact_count;
	t_u32		active;
}	t_decalmgr;

void		decal_init(t_decalmgr *mgr, t_u32 capacity);
void		decal_destroy(t_decalmgr *mgr);
void		decal_clear(t_decalmgr *mgr);

// void		decal_spawn(t_game *game, t_hit *hit, t_ammo ammo);
// void		decal_update_all(t_decalmgr *mgr, t_f32 dt);

// void		render_decals(t_game *game);

// t_decal_id	decal_lookup_impact(t_decalmgr *mgr, t_ammo ammo, t_type target);

t_decal		*decal_get(t_decalmgr *mgr, t_u32 index);
t_decaldef	*decal_get_def(t_decalmgr *mgr, t_decal_id id);


#endif
