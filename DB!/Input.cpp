

#include <cstdio>
#include <cstring>
#include "Country.hpp"
#include "Singer.hpp"
#include <memory>

void inputSinger(struct Singer* singer) {
    int id;
    char name[20];
    char genre[20];
    int numberOfListeners;
    int countryId;

    printf("Enter singer ID: ");
    scanf_s("%d", &id);
    singer->id = id;

    name[0] = '\0';
    printf("Enter singer's name: ");
    scanf_s("%s", name, (unsigned)_countof(name));
    strcpy_s(singer->name, sizeof(singer->name), name);

    genre[0] = '\0';
    printf("Enter singer's genre: ");
    scanf_s("%s", genre, (unsigned)_countof(genre));
    strcpy_s(singer->genre, sizeof(singer->genre), genre);

    printf("Enter singer\'s number of listeners: ");
    scanf_s("%d", &numberOfListeners);
    singer->numberOfListeners = numberOfListeners;

    printf("Enter country ID: ");
    scanf_s("%d", &countryId);
    singer->countryId = countryId;
}

void inputCountry(struct Country* country) {
    int id;
    char name[20];
    int population;
    char language[20];

    printf("Enter country ID: ");
    scanf_s("%d", &id);
    country->id = id;

    printf("Enter country's name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';  
    strcpy_s(country->name, sizeof(country->name), name);

    printf("Enter country's population: ");
    scanf_s("%d", &population);
    country->population = population;

    printf("Enter country's language: ");
    fgets(language, sizeof(language), stdin);
    language[strcspn(language, "\n")] = '\0';
    strcpy_s(country->language, sizeof(country->language), language);
}

void printCountry(struct Country studio) {
    printf("Country\'s id: %d\n", studio.id);
    printf("Country\'s name: %s\n", studio.name);
    printf("Country\'s population: %d\n", studio.population);
    printf("Country\'s language: %s\n", studio.language);
    printf("Country\'s isPresent: %d\n", studio.isPresent);
    printf("Country\'s first order name: %d\n", studio.firstSinger);
}

void printSinger(struct Singer partition) {
    printf("Singer id: %d \n", partition.id);
    printf("Singer name: %s\n", partition.name);
    printf("Singer genre: %s\n", partition.genre);
    printf("Singer number of listeners: %d\n", partition.numberOfListeners);
    printf("Singer countryId: %d\n", partition.countryId);
    printf("Singer nextLogicalAddress: %d\n", partition.nextSingerAddress);
    printf("Singer isPresent: %d\n", partition.isPresent);
    printf("-------------------------\n");
}