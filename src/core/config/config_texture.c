/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/10 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	process_texture(char **fields, void *ctx)
{
	t_assets	*assets;
	t_i32		id;

	assets = (t_assets *)ctx;
	parse_remove_newline(fields[2]);
	id = config_str_to_id(fields[1]);
	if (ft_strcmp(fields[0], "TEXTURE") == 0 && id >= 0 && id < TEXTURE_COUNT)
		texture_load(&assets->textures[id], fields[2]);
	if (ft_strcmp(fields[0], "SPRITE") == 0 && id >= 0 && id < SPRITE_COUNT)
		texture_load(&assets->sprites[id], fields[2]);
}

void	config_load_textures(t_assets *assets)
{
	t_cfgload	cfg;

	cfg = (t_cfgload){
		.path = PATH_CONFIG_TEXTURE,
		.fields = TEXDEF_FIELD_COUNT,
		.process = process_texture,
		.ctx = assets
	};
	config_parse_file(&cfg);
}

static void	process_sheet(char **fields, void *ctx)
{
	t_assets	*assets;
	t_i32		cols;
	t_i32		rows;
	t_i32		id;

	assets = (t_assets *)ctx;
	id = config_str_to_id(fields[0]);
	if (id < 0 || id >= SHEET_COUNT)
		return ;
	cols = ft_atoi(fields[2]);
	rows = ft_atoi(fields[3]);
	sheet_load(&assets->sheets[id], fields[1], cols, rows);
}

void	config_load_sheets(t_assets *assets)
{
	t_cfgload	cfg;

	cfg = (t_cfgload){
		.path = PATH_CONFIG_SHEET,
		.fields = SHEETDEF_FIELD_COUNT,
		.process = process_sheet,
		.ctx = assets
	};
	config_parse_file(&cfg);
}
