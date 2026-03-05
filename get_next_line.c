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
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	s = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	i = 0;
	d = (unsigned char *)dest;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
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
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len_s1);
	ft_memcpy(str + len_s1, s2, len_s2);
	str[len_s1 + len_s2] = '\0';
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
char *new_remainder(char *remainder)
{
	int i = 0;
	int j = 0;
	//printf("%s\n", remainder);
	while(remainder[i] && remainder[i] != '\n')
		i++;
	if(!remainder[i])
		return(NULL);
	i++;
	while(remainder[i])
	{
		remainder[j] = remainder[i];
		i++;
		j++;
	}
	remainder[j] = '\0';
	printf("%s\n", remainder);
	return(remainder);
}

char *find_first_newline(char *remainder)
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
char *get_next_line(int fd)
{
    static char *remainder;
    char *buffer;
    int b_read;
	char *line;

    if(fd < 0 || BUFFER_SIZE <= 0)
        return(NULL);
	remainder = ft_strdup("");
    buffer = malloc(BUFFER_SIZE + 1);
    while(!(ft_strchr(remainder, '\n')) && BUFFER_SIZE > 0)
    {
        b_read = read (fd, buffer, BUFFER_SIZE);
        if(b_read < 0)
        {
            free(buffer);
            return(NULL);
        }
        else
            buffer[b_read] = '\0';
        remainder = ft_strjoin(remainder, buffer);
    }
	//printf("%s", remainder);
	line = find_first_newline(remainder);
	//printf("%s\n", line);
	remainder = new_remainder(remainder);
	//printf("%s\n", remainder);
	free(buffer);
	return(line);

} 
int main()
{
	int fd = open("deneme.txt", O_RDONLY, 0777);
	//get_next_line(fd);
	 printf("%s\n", get_next_line(fd));
	 printf("%s\n", get_next_line(fd));
	 //printf("%s\n", get_next_line(fd));
}