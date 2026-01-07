/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <pthread.h>
# include <types.h>

/* ************************************************************************** */
/*    FORWARD DECLARATIONS                                                    */
/* ************************************************************************** */

typedef struct s_game	t_game;
typedef struct s_proj	t_proj;

/* ************************************************************************** */
/*    THREAD STRUCTURE                                                        */
/* ************************************************************************** */
/*
** [ADD DETAILS HERE LATER]
*/

typedef struct s_thd
{
	t_game	*game;
	t_proj	*projs;
	t_u32	count;
	t_i32	start;
	t_i32	end;
	t_i32	id;
}	t_thd;

/* ************************************************************************** */
/*    FUNCTION PROTOTYPES                                                     */
/* ************************************************************************** */
/*
** See source files for function details
*/

void	render_walls(t_game *game);
void	render_floor(t_game *game);
void	render_sprites(t_game *game);

#endif
