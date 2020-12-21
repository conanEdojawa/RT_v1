#include "../header/rt.h"

int     ft_valid_data_camera(char *str)
{
    int i;

    i = 0;
    if (ft_strlen(str) != 3)
       return (-1);    
    if (str[0] > '9' || str[0] < '0')
        return (-1);
    if (str[1] != '.')
        return (-1);
    if (str[2] > '9' || str[2] < '0')
        return (-1);
    return (0);
}
int   camera(char **table, int i)
{
    int j;
    int k;
    char **str;
    j = 0;
    while (table[i] && j < 2)
    {
        k = 0;
        str = ft_strsplit(table[i],' ');
        while (str[k])
        {
            ft_putendl(str[k]);
            if (ft_valid_data_camera(str[k]))
                return(-1);
            k++;
        }
        j++;
        i++;
    }
    return (0);
}
int     ft_checker(char **table)
{
    int i;

    i = 0;
    while (table[i])
    {
        if (ft_strcmp("camera",table[i]) == 0)
            if (camera(table, i + 1) < 0)
                return (-1);
        i++;
    }
    return (0);
}

int     ft_lines_in_file(char *str)
{
    int     fd;
    int     count;
    char    *line;
    

    count = 0;
    if ((fd = open(str, O_RDONLY)) < 0)
		return (-1);
     while (get_next_line(fd,&line))
        {
            count++;
            free(line);
        }
    if (close(fd) < 0)
        return (-1);
    return (count);
}
int     file_checker(char *str)
{
    int fd;
    int lines;
    int i;
    char **table;

    i = 0;
    lines = ft_lines_in_file(str);
    table = (char **)malloc(sizeof(char*) * (lines + 1));
    if ((fd = open(str, O_RDONLY)) < 0)
		return (-1);
    while (get_next_line(fd,&table[i]))
    {
        i++;
    }
    table[i] = NULL;
    while (table[i])
    {
        ft_putendl(table[i]);
        if (ft_strcmp("camera",table[i]) == 0)
            if (camera(table,i) < 0)
                return (-1);
        i++;
    }
    if (ft_checker(table) < 0)
        {
            ft_strdel(table);
            return (-1);
        }
    return (1);
}