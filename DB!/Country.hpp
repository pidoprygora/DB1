#pragma once

struct Country {
    int id;

    char name[20] = {};
    int population;
    char language[20];

    int isPresent = 1;
    int firstSinger = -1;
};