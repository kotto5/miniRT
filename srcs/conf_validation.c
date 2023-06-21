/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:14:07 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/21 21:35:49 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "conf_validation.h"
#include "libft.h"
#include "get_next_line_bonus.h"

static int  is_valid_file(const char *filepath)
{
    const int fd = open(filepath, O_RDONLY);

    if (fd < 0)
    {
        printf("\x1b[31m");
        perror("[Error]: miniRT");
        printf("\x1b[0m");
        return (IS_NOT_VALID);
    }
    close(fd);
    return (IS_VALID);
}

static int  get_identifier(char *line)
{
    size_t  i_line;

    i_line = 0;
    while (ft_isspace(line[i_line]) == 1)
        i_line++;
    return (line[i_line]);
}

static int  has_essental_identifers(const char *filepath)
{
    const int   fd = open(filepath, O_RDONLY);
    char        *line;
    int         identifer;
    int         has_ambient_light;
    int         has_camera;

    has_ambient_light = 0;
    has_camera = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break ;
        identifer = get_identifier(line);
        if (identifer == 'A')
            has_ambient_light = 1;
        if (identifer == 'c')
            has_camera = 1;
        free(line);
    }
    close(fd);
    if (has_ambient_light == 0 || has_camera == 0)
    {
        printf("\x1b[31m");
        printf("[Error]: miniRT: identifier A and C are essential.\n");
        printf("\x1b[0m");
        return (IS_NOT_VALID);
    }
    return (IS_VALID);
}

// static int  has_valid_format(const char *filepath)
// {
//     const int   fd = open(filepath, O_RDONLY);
//     char        *line;

//     while (1)
//     {
//         line = get_next_line(fd);
//         if (line == NULL)
//             break ;
//         if (has_only_nl(line) == IS_NOT_VALID)
//         {
//             if (is_valid_line(line) == IS_NOT_VALID)
//                 return (IS_NOT_VALID);
//         }
//     }
//     close(fd);
//     return (IS_VALID);
// }

int is_valid(char *filepath)
{
    if (is_valid_file(filepath) == IS_NOT_VALID)
        return (IS_NOT_VALID);
    if (has_essental_identifers(filepath) == IS_NOT_VALID)
        return (IS_NOT_VALID);
    // if (has_valid_format(filepath) == IS_NOT_VALID)
    //     return (IS_NOT_VALID);
    return (IS_VALID);
}
