/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_tex	*assets_get_texture(t_assets *assets, t_tex_id id)
{
	if (id < 0 || id >= TEXTURE_COUNT)
		return (NULL);
	return (&assets->textures[id]);
}

t_tex	*assets_get_sprite(t_assets *assets, t_spr_id id)
{
	if (id < 0 || id >= SPRITE_COUNT)
		return (NULL);
	return (&assets->sprites[id]);
}

t_sheet	*assets_get_sheet(t_assets *assets, t_sht_id id)
{
	if (id < 0 || id >= SHEET_COUNT)
		return (NULL);
	return (&assets->sheets[id]);
}
