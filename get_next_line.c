#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	char	*arr;

	i = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen((char *)s);
	if (start >= len_s)
		len = 0;
	else if (len > len_s - start)
		len = len_s - start;
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
char *ft_new_remainder(char *remainder)
{
	int i = 0;
	int j = 0;
	//printf("%s\n", remainder);
	while(remainder[i] && remainder[i] != '\n')
		i++;
	if(!remainder[i])
	{
		free(remainder);
		return(NULL);
	}
	i++;
	while(remainder[i])
	{
		remainder[j] = remainder[i];
		i++;
		j++;
	}
	remainder[j] = '\0';
	//printf("%s\n", remainder);
	return(remainder);
}

char *ft_find_first_newline(char *remainder)
{
	char *line;
	char *newline;
	int len= 0;
	
	
	if(!remainder)
		return(NULL);
	newline = ft_strchr(remainder, '\n');
	if(!newline)
		return(ft_strdup(remainder));
	len = (newline - remainder) + 1;
	line = ft_substr(remainder, 0, len);
	//printf("%s", line);
	return(line);

}
char	*ft_free_and_join(char *rem, char *buf)
{
	char	*temp;

	temp = ft_strjoin(rem, buf);
	free(rem); // Eski remainder'ı burada siliyoruz
	return (temp);
}
char	*ft_extract_and_save(char **rem)
{
	char	*line;
	char	*temp;

	if (!*rem || **rem == '\0')
	{
		free(*rem);
		*rem = NULL;
		return (NULL);
	}
	line = ft_find_first_newline(*rem);
	temp = ft_new_remainder(*rem);
	*rem = temp;
	return (line);
}

char *get_next_line(int fd)
{
    static char *remainder;
    char *buffer;
    int b_read = 1;
	char *line;

    if(fd < 0 || BUFFER_SIZE <= 0)
        return(NULL);
	if(!remainder)
		remainder = ft_strdup("");
    buffer = malloc(BUFFER_SIZE + 1);
    while(!(ft_strchr(remainder, '\n')) && b_read != 0)
    {
        b_read = read (fd, buffer, BUFFER_SIZE);
        if(b_read < 0)
        {
            free(buffer);
			free(remainder);
			remainder = NULL;
            return(NULL);
        }
        buffer[b_read] = '\0';
        remainder = ft_free_and_join(remainder, buffer);
    }
	free(buffer);
	return (ft_extract_and_save(&remainder));
} 
int main()
{
    int     fd;
    char    *line;

    fd = open("deneme.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}