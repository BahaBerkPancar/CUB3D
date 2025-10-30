#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static char	*read_into_buffer(int fd, char *buf)
{
	char temp[BUFFER_SIZE + 1];
	ssize_t bytes;

	if (!buf) buf = ft_strdup("");
	while (!ft_strchr(buf, '\n'))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes <= 0) break;
		temp[bytes] = '\0';
		buf = ft_strjoin(buf, temp);
		if (!buf) return NULL;
	}
	if (buf[0] == '\0')
	{
		free(buf);
		return NULL;
	}
	return buf;
}

char	*get_next_line(int fd)
{
	static char *buffer[1024];
	char *line;
	char *tmp;
	size_t i = 0;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return NULL;

	buffer[fd] = read_into_buffer(fd, buffer[fd]);
	if (!buffer[fd]) return NULL;

	while (buffer[fd][i] && buffer[fd][i] != '\n')
		i++;

	if (buffer[fd][i] == '\n') i++;
	line = ft_substr(buffer[fd], 0, i);
	tmp = ft_strdup(buffer[fd] + i);
	free(buffer[fd]);
	buffer[fd] = tmp;

	return line;
}