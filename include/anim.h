/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIM_H
# define ANIM_H

# include <types.h>

typedef struct s_game	t_game;

typedef enum e_anim_id
{
	ANIM_NONE,
	ANIM_DOOR_IDLE,
	ANIM_DOOR_OPEN,
	ANIM_DOOR_CLOSE,
	ANIM_COUNT
}	t_anim_id;

/* ************************************************************************** */
/*    ANIMATION DEFINITION                                                    */
/* ************************************************************************** */
/*
** Static animation definition (loaded from config)
** - id:    Animation identifier
** - start: First frame index in sprite sheet
** - total: Number of frames in this animation
** - next:  Animation to chain after completion (0 = none)
** - time:  Duration in seconds per frame
** - loop:  Whether animation loops
*/

typedef struct s_anidef
{
	t_u16	id;
	t_u16	start;
	t_u16	total;
	t_u16	next;
	t_f32	time;
	bool	loop;
}	t_anidef;

/* ************************************************************************** */
/*    ANIMATION STRUCTURE                                                     */
/* ************************************************************************** */
/*
** Runtime animation state (per entity)
** - def_id:   Which animation definition to use
** - frame:    Current frame within animation (0 to total-1)
** - timer:    Time accumulated since last frame change
** - playing:  Is animation currently playing
** - finished: Has non-looping animation completed
*/

typedef struct s_anim
{
	t_u16	def_id;
	t_u16	frame;
	t_f32	timer;
	bool	playing;
	bool	finished;
}	t_anim;

/* ************************************************************************** */
/*    FUNCTION PROTOTYPES                                                     */
/* ************************************************************************** */
/*
** See source files for function explanations
*/

void	anim_init(t_anim *anim, t_u16 def_id);
void	anim_play(t_anim *anim, t_u16 def_id);
void	anim_stop(t_anim *anim);
void	anim_reset(t_anim *anim);

void	anim_update(t_anim *anim, const t_anidef *def, t_f32 dt);
void	anim_update_entities(t_game *game, t_f32 dt);

t_i32	anim_get_frame(t_anim *anim, const t_anidef *def);
bool	anim_is_playing(t_anim *anim);

#endif
