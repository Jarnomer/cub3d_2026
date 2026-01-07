/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_sheet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_sht_id	str_to_sheet_id(const char *str)
{
	if (ft_strcmp(str, "SHEET_DOOR") == 0)
		return (SHEET_DOOR);
	return (SHEET_COUNT);
}

static void	parse_sheet_line(char **p, t_assets *assets)
{
	t_sht_id	id;
	const char	*path;
	t_i32		cols;
	t_i32		rows;

	id = str_to_sheet_id(p[0]);
	if (id >= SHEET_COUNT)
		return ;
	path = p[1];
	cols = ft_atoi(p[2]);
	rows = ft_atoi(p[3]);
	sheet_load(&assets->sheets[id], path, cols, rows);
}

static void	process_line(char *line, t_assets *assets)
{
	char	**parts;

	parts = safe_split(line, ' ');
	if (parse_count_parts(parts) < SHTDEF_FIELD_COUNT)
		err_exit_msg(MSG_CONF_FMT);
	parse_sheet_line(parts, assets);
	free_arr(parts);
}

void	config_load_sheets(t_assets *assets)
{
	int		fd;
	char	*line;

	fd = parse_file_open(PATH_CONFIG_SHEET, ".def");
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
