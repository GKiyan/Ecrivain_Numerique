//
// Created by gelin on 11/06/2025.
//

#include <fcntl.h>    // pour open
#include <unistd.h>   // pour write, close
#include <stdio.h>    // pour perror
#include <string.h>   // pour strlen
#include "sauvegarde.h"

void saveText(string path, string text) {
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }
    if (text == NULL) {
        return;
    }
    ssize_t n = write(fd, text, strlen(text));
    if (n == -1) {
        perror("write");
    }
    close(fd);;
}

int openFileConcat(string path) {
    return open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void addText(int fd, string text) {
    if (text == NULL) {
        return;
    }
    ssize_t n = write(fd, text, strlen(text));
    if (n == -1) {
        perror("write");
    }
}
