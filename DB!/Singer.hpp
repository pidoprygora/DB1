#pragma once

struct Singer {
    int id;
    char name[20];
    char genre[20] = {};
    int numberOfListeners;
    int countryId;

    int nextSingerAddress = -1;
    int isPresent = true;
};
