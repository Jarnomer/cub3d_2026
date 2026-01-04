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

typedef struct s_game	t_game;

typedef struct s_thd
{
	t_game	*game;
	t_i32	start;
	t_i32	end;
	t_i32	id;
}	t_thd;

void	render_walls(t_game *game);
void	render_floor(t_game *game);

#endif
