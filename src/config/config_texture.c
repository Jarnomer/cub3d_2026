/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_tex_id	str_to_tex_id(const char *str)
{
	if (ft_strcmp(str, "TEXTURE_FLOOR") == 0)
		return (TEXTURE_FLOOR);
	if (ft_strcmp(str, "TEXTURE_CEILING") == 0)
		return (TEXTURE_CEILING);
	return (TEXTURE_COUNT);
}

static void	load_texture_entry(char **parts, t_assets *assets)
{
	t_tex_id	id;

	id = str_to_tex_id(parts[1]);
	if (id < TEXTURE_COUNT)
		texture_load(&assets->textures[id], parts[2]);
}

static void	process_line(char *line, t_assets *assets)
{
	char	**parts;

	parts = safe_split(line, ' ');
	if (parse_count_parts(parts) < TEXDEF_FIELD_COUNT)
		err_exit_msg(MSG_CONF_FMT);
	parse_remove_newline(parts[2]);
	if (ft_strcmp(parts[0], "TEXTURE") == 0)
		load_texture_entry(parts, assets);
	free_arr(parts);
}

void	config_load_textures(t_assets *assets)
{
	int		fd;
	char	*line;

	fd = parse_file_open(PATH_CONFIG_TEXTURE, ".def");
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_skip_line(line))
			process_line(line, assets);
		free_str(line);
		line = get_next_line(fd);
	}
	close(fd);
}
