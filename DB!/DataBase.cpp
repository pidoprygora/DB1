#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "DataBase.h"
#include "Country.hpp"
#include "Input.h"
#define _CRT_SECURE_NO_WARNINGS


void DataBase::init() {
     FILE* banks_file_m = nullptr;
    fopen_s(&banks_file_m, COUNTRY_DATA, "wb+");
    if (banks_file_m == nullptr) {
        perror("Error opening COUNTRY_DATA file");
       }
    else {
        fclose(banks_file_m);
    }

    FILE* filials_file_s = nullptr;
    fopen_s(&filials_file_s, COUNTRY_GARBAGE, "wb+");
    if (filials_file_s == nullptr) {
        perror("Error opening COUNTRY_GARBAGE file");
    }
    else {
        fclose(filials_file_s);
    }

    FILE* indexes_file_i = nullptr;
    fopen_s(&indexes_file_i, SINGER_DATA, "wb+");
    if (indexes_file_i == nullptr) {
        perror("Error opening SINGER_DATA file");
    }
    else {
        fclose(indexes_file_i);
    }

    FILE* indexes_file_ = nullptr;
    fopen_s(&indexes_file_, COUNTRY_INDEX, "wb+");
    if (indexes_file_ == nullptr) {
        perror("Error opening STUDIO_INDEX file");
    }
    else {
        fclose(indexes_file_);
    }

    FILE* indexes_fi = nullptr;
    fopen_s(&indexes_fi, SINGER_GARBAGE, "wb+");
    if (indexes_fi == nullptr) {
        perror("Error opening SINGER_GARBAGE file");
    }
    else {
        fclose(indexes_fi);
    }

    for (int i = 0; i < COUNTRY_GARBAGE_MAX_SIZE; i++) {
        countries_garbage[i] = -1;
        singers_garbage[i] = -1;
    }
}



void DataBase::load_country_garbage(bool mode) {
    FILE* collector_file = nullptr;

    if (fopen_s(&collector_file, COUNTRY_GARBAGE, mode ? "rb+" : "wb+") != 0) {
        perror("Error opening file");
        return; 
    }

    for (int i = 0; i < del_countries; i += 1) {
        if (mode) {
            fread(&countries_garbage[i], sizeof(int), 1, collector_file);
        }
        else {
            fwrite(&countries_garbage[i], sizeof(int), 1, collector_file);
        }
    }

    fclose(collector_file);
}

void DataBase::load_singer_garbage(bool mode) {
    FILE* collector_file = nullptr;
    errno_t err = fopen_s(&collector_file, SINGER_GARBAGE, mode ? "rb+" : "wb+");

    if (err != 0) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < del_singers; i += 1) {
        if (mode) {
            fread(&singers_garbage[i], sizeof(int), 1, collector_file);
        }
        else {
            fwrite(&singers_garbage[i], sizeof(int), 1, collector_file);
        }
    }

    fclose(collector_file);
}


void DataBase::load_index_table(bool mode) {
    FILE* collector_file = nullptr;
    if (fopen_s(&collector_file, COUNTRY_INDEX, mode ? "rb+" : "wb+") != 0) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < cnt_countries; i += 1) {
        mode ? fread(&country_index[i].id, sizeof(int), 1, collector_file) : fwrite(&country_index[i].id, sizeof(int),
            1,
            collector_file);
        mode ? fread(&country_index[i].language, sizeof(int), 1, collector_file) : fwrite(&country_index[i].language,
            sizeof(int),
            1, collector_file);
        mode ? fread(&country_index[i].exists, sizeof(int), 1, collector_file) : fwrite(&country_index[i].exists,
            sizeof(int),
            1, collector_file);
    }

    fclose(collector_file);
}

void DataBase::sort_index_table() {
    std::qsort(country_index,
        cnt_countries, sizeof(Index),
        [](const void* a, const void* b) {
            return (((Index*)a)->id - ((Index*)b)->id);
        }
    );
}

int DataBase::get_address(int key) {

    for (int i = 0; i < real_cnt_countries; i += 1) {
        if (country_index[i].id == key && country_index[i].exists == 1) {
            return country_index[i].language;
        }
    }

    return -1;

}

void DataBase::insert_m(Country* country) {
    FILE* country_file = nullptr;
    if (fopen_s(&country_file, COUNTRY_DATA, "r+b") != 0) {
        perror("Error opening file");
        return;  
    }

    DataBase::load_index_table(true);
    country_index[real_cnt_countries].id = country->id;
    real_cnt_countries++;
    cnt_countries++;

    if (countries_garbage[0] == -1) {
        country_index[real_cnt_countries - 1].language = (real_cnt_countries - 1) * sizeof(Country);
        fseek(country_file, (real_cnt_countries - 1) * sizeof(Country), SEEK_SET);

        fwrite(&country->id, sizeof(int), 1, country_file);
        fwrite(&country->name, sizeof(country->name), 1, country_file);
        fwrite(&country->population, sizeof(int), 1, country_file);
        fwrite(&country->language, sizeof(country->language), 1, country_file);
        fwrite(&country->isPresent, sizeof(int), 1, country_file);
        fwrite(&country->firstSinger, sizeof(int), 1, country_file);

        sort_index_table();
        load_index_table(false);
        fclose(country_file);
    }
    else {
        country_index[real_cnt_countries - 1].language = countries_garbage[0];
        fseek(country_file, countries_garbage[0], SEEK_SET);

        fwrite(&country->id, sizeof(int), 1, country_file);
        fwrite(&country->name, sizeof(country->name), 1, country_file);
        fwrite(&country->population, sizeof(int), 1, country_file);
        fwrite(&country->language, sizeof(country->language), 1, country_file);
        fwrite(&country->isPresent, sizeof(int), 1, country_file);
        fwrite(&country->firstSinger, sizeof(int), 1, country_file);

        shift_country_garbage();
        sort_index_table();
        load_index_table(false);
        fclose(country_file);
    }

}

bool DataBase::get_m(int id, struct Country* country) {
    int skip = get_address(id);
    if (skip == -1) {
        printf("Studio with this id doesn't exist!  \n");
        return false;
    }

    FILE* studio_file = nullptr;
    if (fopen_s(&studio_file, COUNTRY_DATA, "r+b") != 0) {
        perror("Error opening file");
        return -1;  
    }


    bool isPresent = true;
    fread(&country->id, sizeof(int), 1, studio_file);
    fread(&country->name, 20, 1, studio_file);
    fread(&country->population, sizeof(int), 1, studio_file);
    fread(&country->language, 20, 1, studio_file);
    fread(&country->isPresent, sizeof(int), 1, studio_file);
    fread(&country->firstSinger, sizeof(int), 1, studio_file);
    fclose(studio_file);
    return true;
}

void DataBase::delete_m(int id) {
    int tmp = get_address(id);
    int tmpIndex = get_index(id);
    if (tmp == -1) {
        printf("Country with this id doesn't exist! \n");
        return;
    }

    country_index[tmpIndex].exists = 0;
    add_country_garbage_address(tmp);
    load_country_garbage(false);

    FILE* country_file = nullptr;
    if (fopen_s(&country_file, COUNTRY_DATA, "rb+") != 0) {
        perror("Error opening file");
        return;
    }

    fseek(country_file, tmp + 48, SEEK_SET);
    int result = 0;
    fwrite(&result, sizeof(int), 1, country_file);
    cnt_countries--;
    del_countries++;
    fclose(country_file);
    load_index_table(false);
}


void DataBase::update_m(Country country) {
    int skip = get_address(country.id);
    if (skip == -1) {
        printf("Country with this id doesn't exist! \n");
        return;
    }

    FILE* country_file = nullptr;
    if (fopen_s(&country_file, COUNTRY_DATA, "r+b") != 0) {
        perror("Error opening file");
        return;
    }

    fseek(country_file, skip, SEEK_SET);
    fwrite(&country.id, sizeof(int), 1, country_file);
    fwrite(&country.name, 20, 1, country_file);
    fwrite(&country.population, sizeof(int), 1, country_file);
    fwrite(&country.language, 20, 1, country_file);

    fclose(country_file);
}

void DataBase::insert_s(Singer singer) {
    Country country;
    this->get_m(singer.countryId, &country);

    FILE* singer_file;
    if (fopen_s(&singer_file, SINGER_DATA, "rb+") != 0) {
        perror("Error opening file");
        return;
    }


    if (country.firstSinger == -1) {
        country.firstSinger = (cnt_singers + del_singers) * (int)sizeof(Singer);
        int skip = get_address(country.id);
        if (skip == -1) {
            printf("Country with this id doesn't exist! \n");
            return;
        }

        FILE* country_file = nullptr;
        if (fopen_s(&country_file, COUNTRY_DATA, "r+b") != 0) {
            perror("Error opening file");
            return;  
        }
        fseek(country_file, skip + 52, SEEK_SET);
        fwrite(&country.firstSinger, 4, 1, country_file);
        fclose(country_file);

        fseek(singer_file, 0, SEEK_END);
        fwrite(&singer, sizeof(Singer), 1, singer_file);
    }
    else {
        Singer tempPartition;
        fseek(singer_file, country.firstSinger, SEEK_SET);
        fread(&tempPartition, sizeof(Singer), 1, singer_file);
        if (tempPartition.isPresent == 0) {
            fseek(singer_file, country.firstSinger, SEEK_SET);
            fwrite(&singer.id, sizeof(int), 1, singer_file);
            fwrite(&singer.name, 20, 1, singer_file);
            fwrite(&singer.genre, 20, 1, singer_file);
            fwrite(&singer.numberOfListeners, sizeof(int), 1, singer_file);
            fwrite(&singer.countryId, sizeof(int), 1, singer_file);
            fseek(singer_file, 4, SEEK_CUR);
            fwrite(&singer.isPresent, sizeof(int), 1, singer_file);
            fclose(singer_file);
            del_singers--;
            cnt_singers++;
            return;
        }
        int language = tempPartition.nextSingerAddress;
        while (tempPartition.nextSingerAddress != -1) {
            fseek(singer_file, tempPartition.nextSingerAddress, SEEK_SET);
            fread(&tempPartition, sizeof(Singer), 1, singer_file);
            if (tempPartition.isPresent == 0) {
                fseek(singer_file, language, SEEK_SET);
                fwrite(&singer.id, sizeof(int), 1, singer_file);
                fwrite(&singer.name, 20, 1, singer_file);
                fwrite(&singer.genre, 20, 1, singer_file);
                fwrite(&singer.numberOfListeners, sizeof(int), 1, singer_file);
                fwrite(&singer.countryId, sizeof(int), 1, singer_file);
                fseek(singer_file, 4, SEEK_CUR);
                fwrite(&singer.isPresent, sizeof(int), 1, singer_file);
                fclose(singer_file);
                del_singers--;
                cnt_singers++;
                return;

            }
            language = tempPartition.nextSingerAddress;
        }
        tempPartition.nextSingerAddress = (cnt_singers + del_singers) * (int)sizeof(Singer);
        this->update_s_with_address(tempPartition);

        fseek(singer_file, 0, SEEK_END);
        fwrite(&singer, sizeof(Singer), 1, singer_file);
    }
    cnt_singers++;
    fclose(singer_file);
}

bool DataBase::get_s(int parent_id, int child_id, struct Singer* singer) {
    Country studio;
    this->get_m(parent_id, &studio);

    if (studio.firstSinger == -1) {
        printf("Country doesn't have singers. \n");
        return false;
    }
    else {
        FILE* singer_file;
        if (fopen_s(&singer_file, SINGER_DATA, "rb+") != 0) {
            perror("Error opening file");
            return true;
        }
        fseek(singer_file, studio.firstSinger, SEEK_SET);
        fread(singer, sizeof(Singer), 1, singer_file);
        if (singer->id == child_id) {
            fclose(singer_file);
            return true;
        }
        while (singer->nextSingerAddress != -1) {
            fseek(singer_file, singer->nextSingerAddress, SEEK_SET);
            fread(singer, sizeof(Singer), 1, singer_file);
            if (singer->id == child_id) {
                fclose(singer_file);
                return true;
            }
        }
        printf("No such singer \n");
        return false;
    }
}

void DataBase::delete_s(int parent_id, int child_id) {
    Country country;
    this->get_m(parent_id, &country);

    if (country.firstSinger == -1) {
        printf("Studio doesn't have partitions. \n");
        return;
    }
    else {
        Singer singer;
        FILE* singer_file;
        if (fopen_s(&singer_file, SINGER_DATA, "rb+") != 0) {
            perror("Error opening file");
            return;
        }
        fseek(singer_file, country.firstSinger, SEEK_SET);
        fread(&singer, sizeof(Singer), 1, singer_file);
        int isPresent = 0;
        if (singer.id == child_id) {
            fseek(singer_file, country.firstSinger + 56, SEEK_SET);
            fwrite(&isPresent, sizeof(int), 1, singer_file);
            fclose(singer_file);
            return;
        }
        while (singer.nextSingerAddress != -1) {
            Singer prevSingers = singer;
            fseek(singer_file, singer.nextSingerAddress, SEEK_SET);
            fread(&singer, sizeof(Singer), 1, singer_file);
            if (singer.id == child_id) {
                fseek(singer_file, prevSingers.nextSingerAddress + 56, SEEK_SET);
                fwrite(&isPresent, sizeof(int), 1, singer_file);
                fclose(singer_file);
                return;
            }

        }
        printf("No such singer \n");
    }
    del_singers++;
    cnt_singers--;
}

void DataBase::ut_m() {
    FILE* country_file_m = nullptr;
    if (fopen_s(&country_file_m, COUNTRY_DATA, "rb+") != 0) {
        perror("Error opening file");
        return;  
    }
    printf("ut_m:\n");
    int id;

    char name[20];
    int population;
    char language[20];

    int isPresent = true;
    int firstSinger = -1;


    for (int i = 0; i < real_cnt_countries; i++) {
        if (country_index[i].exists == 1) {
            fseek(country_file_m, get_address(country_index[i].id), SEEK_SET);
            fread(&id, sizeof(int), 1, country_file_m);
            fread(&name, sizeof(name), 1, country_file_m);
            fread(&population, sizeof(int), 1, country_file_m);
            fread(&language, sizeof(language), 1, country_file_m);
            fread(&isPresent, sizeof(int), 1, country_file_m);
            fread(&firstSinger, sizeof(int), 1, country_file_m);
            printf("Id: %d, Name: %s, population: %d, name: %s , isPresent: %d, firstSinger: %d \n", id, name,
                population, language, isPresent, firstSinger);
        }
    }

    fclose(country_file_m);
}

void DataBase::update_s_with_address(Singer newSinger) {
    Country country;
    this->get_m(newSinger.countryId, &country);

    if (country.firstSinger == -1) {
        printf("Country doesn't have partitions. \n");
        return;
    }
    else {
        Singer singer;
        FILE* singer_file = nullptr;
        if (fopen_s(&singer_file, SINGER_DATA, "rb+") != 0) {
            perror("Error opening file");
            return;  
        }
        fseek(singer_file, country.firstSinger, SEEK_SET);
        fread(&singer, sizeof(Singer), 1, singer_file);
        if (singer.id == newSinger.id) {
            fseek(singer_file, country.firstSinger, SEEK_SET);
            fwrite(&newSinger.id, sizeof(int), 1, singer_file);
            fwrite(&newSinger.name, 20, 1, singer_file);
            fwrite(&newSinger.genre, 20, 1, singer_file);
            fwrite(&newSinger.numberOfListeners, sizeof(int), 1, singer_file);
            fwrite(&newSinger.countryId, sizeof(int), 1, singer_file);
            fwrite(&newSinger.nextSingerAddress, sizeof(int), 1, singer_file);
            fclose(singer_file);
            return;
        }
        while (singer.nextSingerAddress != -1) {
            Singer prevSinger = singer;
            fseek(singer_file, singer.nextSingerAddress, SEEK_SET);
            fread(&singer, sizeof(Singer), 1, singer_file);
            if (singer.id == newSinger.id) {
                fseek(singer_file, prevSinger.nextSingerAddress, SEEK_SET);
                fwrite(&newSinger.id, sizeof(int), 1, singer_file);
                fwrite(&newSinger.name, 20, 1, singer_file);
                fwrite(&newSinger.genre, 20, 1, singer_file);
                fwrite(&newSinger.numberOfListeners, sizeof(int), 1, singer_file);
                fwrite(&newSinger.countryId, sizeof(int), 1, singer_file);
                fwrite(&newSinger.nextSingerAddress, sizeof(int), 1, singer_file);
                fclose(singer_file);
                return;
            }

        }
        printf("No such singer \n");
    }
}

void DataBase::update_s(Singer newSinger) {
    Country country;
    this->get_m(newSinger.countryId, &country);

    if (country.firstSinger == -1) {
        printf("Country doesn't have singers. \n");
        return;
    }
    else {
        Singer singer;
        FILE* siger_file = nullptr;
        if (fopen_s(&siger_file, SINGER_DATA, "rb+") != 0) {
            perror("Error opening file");
            return;
        }
        fseek(siger_file, country.firstSinger, SEEK_SET);
        fread(&singer, sizeof(Singer), 1, siger_file);
        if (singer.id == newSinger.id) {
            fseek(siger_file, country.firstSinger, SEEK_SET);
            fwrite(&newSinger.id, sizeof(int), 1, siger_file);
            fwrite(&newSinger.name, 20, 1, siger_file);
            fwrite(&newSinger.genre, 20, 1, siger_file);
            fwrite(&newSinger.numberOfListeners, sizeof(int), 1, siger_file);
            fwrite(&newSinger.countryId, sizeof(int), 1, siger_file);
            fclose(siger_file);
            return;
        }
        while (singer.nextSingerAddress != -1) {
            Singer prevSinger = singer;
            fseek(siger_file, singer.nextSingerAddress, SEEK_SET);
            fread(&singer, sizeof(Singer), 1, siger_file);
            if (singer.id == newSinger.id) {
                fseek(siger_file, prevSinger.nextSingerAddress, SEEK_SET);
                fwrite(&newSinger.id, sizeof(int), 1, siger_file);
                fwrite(&newSinger.name, 20, 1, siger_file);
                fwrite(&newSinger.genre, 20, 1, siger_file);
                fwrite(&newSinger.numberOfListeners, sizeof(int), 1, siger_file);
                fwrite(&newSinger.countryId, sizeof(int), 1, siger_file);
                fclose(siger_file);
                return;
            }

        }
        printf("No such singer \n");
    }
}

void DataBase::ut_s(int countryId) {
    Country country;
    this->get_m(countryId, &country);
    Singer singer;

    if (country.firstSinger == -1) {
        printf("Country doesn't have singers. \n");
        return;
    }
    else {
        FILE* singer_file = nullptr;
        if (fopen_s(&singer_file, SINGER_DATA, "rb+") != 0) {
            perror("Error opening file");
            return;
        }

        fseek(singer_file, country.firstSinger, SEEK_SET);
        fread(&singer, sizeof(Singer), 1, singer_file);
        printSinger(singer);
        while (singer.nextSingerAddress != -1) {
            fseek(singer_file, singer.nextSingerAddress, SEEK_SET);
            fread(&singer, sizeof(Singer), 1, singer_file);
            if (singer.isPresent) printSinger(singer);
        }
    }
}

int DataBase::get_index(int key) {
    for (int i = 0; i < real_cnt_countries; i += 1) { // can be faster --> log(cnt_banks)
        if (country_index[i].id == key && country_index[i].exists == 1) {
            return i;
        }
    }
    return -1;
}

void DataBase::shift_country_garbage() {
    int i = 0;
    while (countries_garbage[i] != -1) {
        countries_garbage[i] = countries_garbage[i + 1];
        i++;
    }
}

void DataBase::shift_singer_garbage() {
    int i = 0;
    while (singers_garbage[i] != -1) {
        singers_garbage[i] = singers_garbage[i + 1];
        i++;
    }
}

void DataBase::add_country_garbage_address(int language) {
    int i = 0;
    while (countries_garbage[i] != -1) {
        i++;
    }
    countries_garbage[i] = language;
}

void DataBase::add_singer_garbage_address(int language) {
    int i = 0;
    while (singers_garbage[i] != -1) {
        i++;
    }
    singers_garbage[i] = language;
}

