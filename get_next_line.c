#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char *ft_strdup(char *str);
int ft_check(char *str);
int ft_strlen(char *str);
char *ft_strjoin(char *s1, char *s2);

int ft_check(char *str)
{
    if(!str)
        return (0);
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

int ft_strlen(char *str)
{
    if (!str)
        return (0);
    int i;

    i = 0;
    while (str[i])
        i++;
    return(i);
}

char *ft_strjoin(char *s1, char *s2)
{
    if (!s1)
        return(ft_strdup(s2));
    int i;
    int j;
    char *cpy;

    cpy = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    i = 0;
    j = 0;
    while (s1[i])
    {
        cpy[j] = s1[i];
        j++;
        i++;
    }
    i = 0;
    while (s2[i])
    {
        cpy[j] = s2[i];
        j++;
        i++;
    }
    cpy[j] = '\0';
    return(cpy);
}

char *ft_strdup(char *str)
{
    char *cpy;
    int i;

    i = 0;
    cpy = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!cpy)
        return (NULL);
    while (str[i])
    {
        cpy[i] = str[i];
        i++;
    }
    cpy[i] = '\0';
    return (cpy);
}

char *ft_strndup(char *str, int n)
{
    char *cpy;
    int i;

    i = 0;
    cpy = malloc(sizeof(char) * (n + 1));
    if (!cpy)
        return (NULL);
    while (str[i] && i <= n)
    {
        cpy[i] = str[i];
        i++;
    }
    cpy[i] = '\0';
    return (cpy);
}

int ft_cut(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            break;
        i++;
    }
    return(i);
}

char *get_next_line(int fd)
{
    char *buffer;
    char *tmp;
    static char *position = NULL;
    char *line;
    ssize_t i;

    i = 1;
    if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    while (!ft_check(position) && i != 0)
    {
        i = read(fd, buffer, BUFFER_SIZE);
        buffer[i + 1] = '\0';
        // if (i == -1 || i == 0 || i == 1)
        //     break;
        tmp = position;
        position = ft_strjoin(tmp, buffer);
        free(tmp);
    }
    line = ft_strndup(position, (ft_cut(position)));
    tmp = position;
    position = ft_strdup(tmp + (ft_cut(tmp) + 1));
    free(tmp);
    return(line);
}

#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    // int fd = open("test.txt", O_RDONLY);
    // char *str;
    // char *str2;
    // char *str3;
    // char *str4;
    // str = get_next_line(fd);
    // printf("%s", str);
    // str2 = get_next_line(fd);
    // printf("%s", str2);
    // str3 = get_next_line(fd);
    // printf("%s", str3);
    // str4 = get_next_line(fd);
    // printf("%s", str4);

    int fd;
    char *s;
    int count;

    (void)argc;
    count = atoi(argv[1]);
    fd = open("odysee", O_RDONLY);
    while (count--)
    {
        s = get_next_line(fd);
        printf("GNL : %s", s);
        free(s);
    }
    close(fd);
    
}