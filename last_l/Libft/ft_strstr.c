
#include "libft.h"

char    *ft_strstr(char *str, char *to_find)
{
    char    *p2;
    char    *p1;

    if (to_find[0] == '\0')
        return (str);
    while (*str)
    {
        p2 = to_find;
        p1 = str;
        while (*p2 && *p1 && *p1 == *p2)
        {
            p1++;
            p2++;
        }
        if (!*p2)
            return (str);
        str++;
    }
    return (0);
}
