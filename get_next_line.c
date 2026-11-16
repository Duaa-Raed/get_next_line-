# include "get_next_line.h"
static char	*fill_storage(int fd, char *storage)
{

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

}