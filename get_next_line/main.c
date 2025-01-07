/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:36:56 by mpoesy            #+#    #+#             */
/*   Updated: 2024/10/29 17:54:51 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"  // Include your get_next_line header

#define FILENAME "test1.txt"

int main() {
    int fd1 = open(FILENAME, O_RDONLY);
    if (fd1 == -1) {
        perror("Error opening file");
        return 1;
    }
    /*
    int fd2 = open("test2.txt", O_RDONLY);
    if (fd2 == -1) {
        perror("Error opening file");
        return 1;
    }
    int fd3 = open("test3.txt", O_RDONLY);
    if (fd3 == -1) {
        perror("Error opening file");
        return 1;
    }
    */


    char *line;
    for (int i = 0; i < 5; i++)
    {
        line = get_next_line(fd1);
	if (line == NULL) {
            break;  // Break if EOF or error occurs
        }
	/*
        printf("%s", i + 1, line);
	line = get_next_line(fd2);
        if (line == NULL) {
            break;  // Break if EOF or error occurs
        }
        printf("Line %d: %s\n", i + 1, line);
	line = get_next_line(fd1);
        if (line == NULL) {
            break;  // Break if EOF or error occurs
        }*/
        printf("%s", line);

        free(line);  // Don't forget to free the memory allocated for the line
    }

    close(fd1);
    /*
  close(fd2);
close(fd3);  // Close the file descriptor
	     // */
    return 0;
}

