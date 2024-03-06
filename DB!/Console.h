#pragma 
#ifndef UNTITLED3_CONSOLEMENU_H
#define UNTITLED3_CONSOLEMENU_H

#include <cstdio>
#include "Singer.hpp"
#include "Country.hpp"
#include "Input.h"
#include "DataBase.h"

class ConsoleMenu {
    DataBase db;

    void dbInit() {
        db.init();

        Country country;
        country.id = 1;
        strcpy_s(country.name, "Ukrain");
        country.population = 41167335;
        strcpy_s(country.language, "ukrainian");
        db.insert_m(&country);

        country.id = 2;
        strcpy_s(country.name, "Sweden");
        country.population = 9801345;
        strcpy_s(country.language, "swedish");
        db.insert_m(&country);

        country.id = 3;
        strcpy_s(country.name, "Germany");
        country.population = 84482267;
        strcpy_s(country.language, "german");
        db.insert_m(&country);

        country.id = 4;
        strcpy_s(country.name, "France");
        country.population = 65470981;
        strcpy_s(country.language, "french");
        db.insert_m(&country);


        country.id = 5;
        strcpy_s(country.name, "Italy");
        country.population = 60461826;
        strcpy_s(country.language, "italian");
        db.insert_m(&country);



        Singer singer;
        singer.id = 1;
        strcpy_s(singer.name, "Ziferblat");
        singer.numberOfListeners = 25765;
        strcpy_s(singer.genre, "pop, rock");
        singer.countryId = 1;
        db.insert_s(singer);

        singer.id = 2;
        strcpy_s(singer.name, "Zhadan i sobaki");
        singer.numberOfListeners = 34560;
        strcpy_s(singer.genre, "pank rock");
        singer.countryId = 1;
        db.insert_s(singer);

        singer.id = 3;
        strcpy_s(singer.name, "Go_a");
        singer.numberOfListeners = 146783;
        strcpy_s(singer.genre, "folk");
        singer.countryId = 1;
        db.insert_s(singer);

        singer.id = 4;
        strcpy_s(singer.name, "Loreen");
        singer.numberOfListeners = 237893;
        strcpy_s(singer.genre, "pop");
        singer.countryId = 2;
        db.insert_s(singer);

        singer.id = 5;
        strcpy_s(singer.name, "Maria Sur");
        singer.numberOfListeners = 45673;
        strcpy_s(singer.genre, "pop-rock");
        singer.countryId = 2;
        db.insert_s(singer);

        singer.id = 10;
        strcpy_s(singer.name, "Maneskin");
        singer.numberOfListeners = 24567983;
        strcpy_s(singer.genre, "glam-rock");
        singer.countryId = 5;
        db.insert_s(singer);

        singer.id = 11;
        strcpy_s(singer.name, "Mahmood");
        singer.numberOfListeners = 4678320;
        strcpy_s(singer.genre, "r&b");
        singer.countryId = 5;
        db.insert_s(singer);

        singer.id = 12;
        strcpy_s(singer.name, "Annalisa");
        singer.numberOfListeners = 2567480;
        strcpy_s(singer.genre, "neo soul");
        singer.countryId = 5;
        db.insert_s(singer);

        singer.id = 13;
        strcpy_s(singer.name, "Angelina Mango");
        singer.numberOfListeners = 3492780;
        strcpy_s(singer.genre, "pop-folk");
        singer.countryId = 5;
        db.insert_s(singer);

    }

public:
    void run() {
       
        struct Country country;
        struct Singer singer;
        printf("==============================================\n");
        printf("Acceptable Options:\n0 Exit\n1 Insert country\n2 Get country\n3 Update country\n4 Delete country\n5 Insert singer\n6 Get singer\n7 Update singer\n8 Delete singer\n9 General Info\n10 General info about partitions \n");
        printf("==============================================\n");
        while (1) {
            int choice;
            int id;
            char error[51]{};
           
            printf("Your choice: ");
            scanf_s("%d", &choice);
            switch (choice) {
            case 0:
                return;
            case 1:
                inputCountry(&country);
                db.insert_m(&country);
                break;
            case 2:
                printf("Enter country ID: ");
                scanf_s("%d", &id);
                if (db.get_m(id, &country)) printCountry(country);
                break;
            case 3:
                inputCountry(&country);
                db.update_m(country);
                printf("Updated successfully\n");
                break;
            case 4:
                printf("Enter country ID: ");
                int countryId;
                scanf_s("%d", &countryId);
                db.delete_m(countryId);
                break;
            case 5:
                inputSinger(&singer);
                db.insert_s(singer);
                break;
            case 6:
                printf("Enter country ID: ");
                scanf_s("%d", &countryId);
                printf("Enter singer ID: ");
                int singerId;
                scanf_s("%d", &singerId);
                if (db.get_s(countryId, singerId, &singer)) printSinger(singer);
                break;
            case 7:
                inputSinger(&singer);
                db.update_s(singer);
                break;
            case 8:
                printf("Enter country ID: ");
                countryId;
                scanf_s("%d", &countryId);
                printf("Enter singer ID: ");
                singerId;
                scanf_s("%d", &singerId);
                db.delete_s(countryId, singerId);
                break;
            case 9:
                db.ut_m();
                break;
            case 10:
                printf("Enter country ID: ");
                countryId;
                scanf_s("%d", &countryId);
                db.ut_s(countryId);
                break;
            default:
                printf("Invalid input, Try again!\n");

            }
        }
    }
};

#endif 