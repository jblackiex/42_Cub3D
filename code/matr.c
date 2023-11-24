#include "Cub3d.h"

void	ft_free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	**get_map(char *mapy)
{
	char	**result;
	char	*holder;
	char	*old_address;
	char	*map;
	int		fd;

	fd = open(mapy, O_RDONLY);
	if (fd == -1)
		print_error(fd, NULL);
	map = ft_strdup("");
	old_address = "test";
	while (1)
	{
		holder = get_next_line(fd);
		if (!holder)
			break ;
		old_address = map;
		map = ft_strjoin(old_address, holder);
		ft_free_ptr((void *)&old_address);
		ft_free_ptr((void *)&holder);
	}
	if (old_address)
		print_error(fd, NULL);
	result = ft_split_mod(map, '\n');
	ft_free_ptr((void *)&map);
	return (close(fd), result);
}

