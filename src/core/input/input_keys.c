/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

bool	input_key_down(t_input *input, int key)
{
	if (key < 0 || key >= MAX_KEYS)
		return (false);
	return (input->keys[key]);
}

bool	input_key_pressed(t_input *input, int key)
{
	if (key < 0 || key >= MAX_KEYS)
		return (false);
	return (input->keys[key] && !input->keys_prev[key]);
}

bool	input_key_released(t_input *input, int key)
{
	if (key < 0 || key >= MAX_KEYS)
		return (false);
	return (!input->keys[key] && input->keys_prev[key]);
}
