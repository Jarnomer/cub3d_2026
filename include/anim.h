/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIM_H
# define ANIM_H

# include <types.h>

typedef struct s_anidef
{
	t_u16	id;
	t_u16	start;
	t_u16	total;
	t_u16	next;
	t_f32	time;
	bool	loop;
}	t_anidef;

typedef struct s_anim
{
	t_u16	def_id;
	t_u16	frame;
	t_f32	timer;
	bool	playing;
	bool	finished;
}	t_anim;

#endif
