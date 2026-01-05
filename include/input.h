/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <config.h>
# include <vector.h>
# include <types.h>

typedef struct s_game	t_game;

typedef struct s_input
{
	bool	keys[MAX_KEYS];
	bool	keys_prev[MAX_KEYS];
	t_vec2	mouse_pos;
	t_vec2	mouse_delta;
	bool	mouse_captured;
}	t_input;

void	input_init(t_input *input);
void	input_update(t_game *game);
void	input_mouse_init(t_game *game);

void	input_mouse_capture(t_game *game);
void	input_mouse_release(t_game *game);
void	input_mouse_center(t_game *game);

bool	input_key_down(t_input *input, int key);
bool	input_key_pressed(t_input *input, int key);
bool	input_key_released(t_input *input, int key);

#endif
