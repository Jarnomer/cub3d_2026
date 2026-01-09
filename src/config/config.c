/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	config_load_all(t_assets *assets)
{
	config_load_textures(assets);
	config_load_sprites(assets);
	config_load_sheets(assets);
	config_load_entities(assets->entdefs);
	config_load_anims(assets->anidefs);
	config_load_weapons(assets->wpndefs);
}
