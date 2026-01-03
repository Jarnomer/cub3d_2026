/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <cub3d.h>

# define MAP_MIN_SIZE		3
# define MAP_MAX_SIZE		256

# define CHAR_EMPTY			'0'
# define CHAR_WALL			'1'
# define CHAR_SPACE			' '
# define CHAR_PLAYER_N		'N'
# define CHAR_PLAYER_S		'S'
# define CHAR_PLAYER_E		'E'
# define CHAR_PLAYER_W		'W'
# define CHARSET_VALID		"01 NSEW"
# define CHARSET_PLAYER		"NSEW"

# define ID_NORTH			"NO "
# define ID_SOUTH			"SO "
# define ID_WEST			"WE "
# define ID_EAST			"EA "
# define ID_FLOOR			"F "
# define ID_CEILING			"C "

typedef enum e_elem
{
	ELEM_NO,
	ELEM_SO,
	ELEM_WE,
	ELEM_EA,
	ELEM_F,
	ELEM_C,
	ELEM_COUNT
}	t_elem;

typedef struct s_parse
{
	int			fd;
	char		*line;
	char		*filename;
	bool		elements[ELEM_COUNT];
	int			elem_count;
	t_map		*map;
}	t_parse;

t_map	*parse(const char *filepath);

int		parse_file_open(const char *filepath);
void	parse_file_validate(const char *filepath, const char *ext);

void	parse_elements(t_parse *ctx);
void	parse_texture(t_parse *ctx, t_elem type);
void	parse_color(t_parse *ctx, t_elem type);

void	parse_map(t_parse *ctx);
void	parse_map_validate(t_parse *ctx);
void	parse_map_walls(t_parse *ctx);

char	*parse_skip_spaces(char *str);
bool	parse_is_empty_line(const char *line);
void	parse_remove_newline(char *str);
void	parse_cleanup(t_parse *ctx);

#endif
