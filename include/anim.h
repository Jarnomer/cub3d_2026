/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIM_H
# define ANIM_H

# include <types.h>
# include <defs.h>

typedef struct s_game	t_game;

typedef struct s_anidef
{
	t_anim_id	id;
	t_u16		start;
	t_u16		total;
	t_u16		next;
	t_f32		duration;
	bool		is_looping;
	bool		is_reversed;
}	t_anidef;

typedef struct s_anim
{
	t_anim_id	def_id;
	t_u16		frame;
	t_f32		timer;
	bool		is_playing;
	bool		is_finished;
}	t_anim;

void	anim_init(t_anim *anim, t_anim_id def_id);
void	anim_play(t_anim *anim, t_anim_id def_id);
void	anim_stop(t_anim *anim);
void	anim_reset(t_anim *anim);

void	anim_update(t_anim *anim, const t_anidef *def, t_f32 dt);
void	anim_update_entities(t_game *game, t_f32 dt);

t_i32	anim_get_frame(t_anim *anim, const t_anidef *def);
bool	anim_is_playing(t_anim *anim);

#endif
