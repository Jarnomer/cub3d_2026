/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mouse_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

bool	input_mouse_down(t_input *input, int button)
{
	if (button < 0 || button >= MAX_MOUSE_KEYS)
		return (false);
	return (input->mouse[button]);
}

bool	input_mouse_pressed(t_input *input, int button)
{
	if (button < 0 || button >= MAX_MOUSE_KEYS)
		return (false);
	return (input->mouse[button] && !input->mouse_prev[button]);
}

bool	input_mouse_released(t_input *input, int button)
{
	if (button < 0 || button >= MAX_MOUSE_KEYS)
		return (false);
	return (!input->mouse[button] && input->mouse_prev[button]);
}
