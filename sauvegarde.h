//
// Created by gelin on 11/06/2025.
//

#ifndef ECRIVAIN_NUMERIQUE_SAUVEGARDE_H
#define ECRIVAIN_NUMERIQUE_SAUVEGARDE_H

#include "hachage.h"

void saveText(string path, string text);

int openFileConcat(string path);

void addText(int fd, string text);

#endif //ECRIVAIN_NUMERIQUE_SAUVEGARDE_H
