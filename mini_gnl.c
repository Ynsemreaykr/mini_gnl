#include <unistd.h>   
#include <stdlib.h>   

static char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

static char *append_char_to_line(char *line, int line_size, char c)
{
	char *new_line;

	new_line = malloc(line_size + 2);
	if (!new_line)
	{
		if (line)
			free(line);
		return (NULL);
	}
	if (line)
	{
		ft_strncpy(new_line, line, line_size);
		free(line);
	}
	else
		new_line[0] = '\0';
	new_line[line_size] = c;
	new_line[line_size + 1] = '\0';
	return (new_line);
}

static char *read_file_content(int fd)
{
	char    *line;
	int     line_size;
	char    buffer[1];
	ssize_t bytes_read;

	line = NULL;
	line_size = 0;
	bytes_read = read(fd, buffer, 1);
	while (bytes_read > 0)
	{
		if (buffer[0] == '\n')
			break;
		line = append_char_to_line(line, line_size, buffer[0]);
		if (!line)
			return (NULL);
		line_size++;
		bytes_read = read(fd, buffer, 1);
	}
	if (bytes_read == 0 && line_size == 0)
		return (NULL);
	if (line_size == 0)
		return (ft_strdup(""));
	return (line);
}

static char *append_line_to_content(char *content, int content_size, char *line)
{
	char *new_content;
	int   line_len;
	int   i;

	line_len = ft_strlen(line);
	new_content = malloc(content_size + line_len + 2);
	if (!new_content)
	{
		if (content)
			free(content);
		return (NULL);
	}
	i = 0;
	while (i < content_size)
	{
		new_content[i] = content[i];
		i++;
	}
	i = 0;
	while (i < line_len)
	{
		new_content[content_size + i] = line[i];
		i++;
	}
	new_content[content_size + line_len] = '\n';
	new_content[content_size + line_len + 1] = '\0';
	if (content)
		free(content);
	return (new_content);
}

char *get_next_line(int fd)
{
	char *content;
	char *line;
	int   content_size;

	content = NULL;
	content_size = 0;
	line = read_file_content(fd);
	while (line != NULL)
	{
		content = append_line_to_content(content, content_size, line);
		if (!content)
			return (NULL);
		content_size += ft_strlen(line) + 1;
		free(line);
		line = read_file_content(fd);
	}
	return (content);
}
