# include "get_next_line.h"

static char	*fill_storage(int fd, char *storage)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free_both(storage, NULL));
	bytes = 1;
	while (bytes > 0 && !ft_strchr(storage, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_free_both(storage, buffer));
		buffer[bytes] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (ft_free_both(NULL, buffer));
	}
	free(buffer);
	return (storage);
}

static char	*cut_line(char *storage)
{
	char	*string;
	int	i;
	int	j;

	i = 0;
	if (!storage || !storage[0])
		return(NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	string = malloc(i + 1);
	if (!string)
		return(NULL);
	j = 0;
	while (j < i)
	{
		string[j] = storage[j];
		j++;
	}
	string[j] = '\0';
	return(string);
}

static char	*copy_string(char *storage, int i)
{
	char	*string;
	int		j;

	string = malloc(ft_strlen(storage) - i + 1);
	if (!string)
		return (NULL);
	j = 0;
	while (storage[i])
		string[j++] = storage[i++];
	string[j] = '\0';
	return (string);
}

static char	*clean_stash(char *storage)
{
	char	*string;
	int		i;

	if (!storage)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i] || !storage[i + 1])
	{
		free(storage);
		return (NULL);
	}
	string = copy_string(storage, i + 1);
	free(storage);
	return (string);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = fill_storage(fd, storage);
	if (!storage)
		return (NULL);
	line = cut_line(storage);
	if (!line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = clean_stash(storage);
	return (line);
}