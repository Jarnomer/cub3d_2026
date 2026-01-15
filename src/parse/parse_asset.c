/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
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
	if (value < 0 || value > COLOR_CHANNEL_MAX)
		err_exit_msg(MSG_COLOR_VAL);
	return (value);
}

static t_u32	extract_rgb(char **parts)
{
	int		count;
	t_u8	r;
	t_u8	g;
	t_u8	b;

	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
		err_exit_msg(MSG_COLOR_CNT);
	r = parse_color_value(parts[0]);
	g = parse_color_value(parts[1]);
	b = parse_color_value(parts[2]);
	return (color_rgba(r, g, b, COLOR_CHANNEL_MAX));
}

static void	validate_color_format(char *str)
{
	char	*end;

	if (!str || *str == '\0')
		err_exit_msg(MSG_COLOR_FMT);
	str = parse_skip_spaces(str);
	if (*str == ',')
		err_exit_msg(MSG_COLOR_FMT);
	end = str + ft_strlen(str) - 1;
	while (end > str && *end == ' ')
		end--;
	if (*end == ',')
		err_exit_msg(MSG_COLOR_FMT);
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ' ' && *str != ',')
			err_exit_msg(MSG_COLOR_FMT);
		if (*str == ',' && *(str + 1) == ',')
			err_exit_msg(MSG_COLOR_FMT);
		str++;
	}
}

void	parse_color(t_parse *ctx, t_elem type)
{
	char	*value;
	char	**parts;
	t_u32	color;

	value = parse_skip_spaces(ctx->line + ID_LEN_COLOR);
	parse_remove_newline(value);
	validate_color_format(value);
	parts = safe_split(value, ',');
	color = extract_rgb(parts);
	free_arr(parts);
	if (type == ELEM_F)
		ctx->map->floor_col = color;
	else
		ctx->map->ceil_col = color;
}

void	parse_texture(t_parse *ctx, t_elem type)
{
	char	*value;
	char	*path;

	value = parse_skip_spaces(ctx->line + ID_LEN_TEXTURE);
	path = safe_strdup(value);
	parse_remove_newline(path);
	parse_file_validate(path, ".png");
	ctx->map->textures[type] = path;
}
