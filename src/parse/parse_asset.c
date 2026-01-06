/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static int	parse_color_value(char *str)
{
	int	value;

	str = parse_skip_spaces(str);
	if (!ft_isdigit(*str))
		err_exit_msg(MSG_COLOR_FMT);
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		err_exit_msg(MSG_COLOR_VAL);
	return (value);
}

static t_color	extract_rgb(char **parts)
{
	t_color	color;
	int		count;

	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
		err_exit_msg(MSG_COLOR_CNT);
	color.r = parse_color_value(parts[0]);
	color.g = parse_color_value(parts[1]);
	color.b = parse_color_value(parts[2]);
	color.a = 255;
	return (color);
}

static void	validate_color_format(char *str)
{
	int		i;
	char	*trimmed;

	if (!str || *str == '\0')
		err_exit_msg(MSG_COLOR_FMT);
	trimmed = parse_skip_spaces(str);
	if (*trimmed == ',')
		err_exit_msg(MSG_COLOR_FMT);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != ',')
			err_exit_msg(MSG_COLOR_FMT);
		if (str[i] == ',' && str[i + 1] == ',')
			err_exit_msg(MSG_COLOR_FMT);
		i++;
	}
}

void	parse_color(t_parse *ctx, t_elem type)
{
	char	*value;
	char	**parts;
	t_color	color;

	value = parse_skip_spaces(ctx->line + 2);
	parse_remove_newline(value);
	validate_color_format(value);
	parts = safe_split(value, ',');
	color = extract_rgb(parts);
	free_arr(parts);
	if (type == ELEM_F)
		ctx->map->floor_col = color;
	else
		ctx->map->ciel_col = color;
}

void	parse_texture(t_parse *ctx, t_elem type)
{
	char	*value;
	char	*path;

	value = parse_skip_spaces(ctx->line + 3);
	path = safe_strdup(value);
	parse_remove_newline(path);
	parse_file_validate(path, ".png");
	ctx->map->textures[type] = path;
}
