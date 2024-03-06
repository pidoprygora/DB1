#pragma once
//#pragma once
#pragma once

#ifndef UNTITLED3_DATABASE_H
#define UNTITLED3_DATABASE_H

#include "Index.hpp"
#include "Const.h"
#include "Country.hpp"
#include "Singer.hpp"

class DataBase {
private:
    Index country_index[INDEX_MAX_SIZE]{};
    int countries_garbage[COUNTRY_GARBAGE_MAX_SIZE]{};
    int singers_garbage[SINGER_GARBAGE_MAX_SIZE]{};


    int cnt_singers = 0;
    int del_singers = 0;

    int real_cnt_countries = 0;
    int cnt_countries = 0;
    int del_countries = 0;
public:
    int get_index(int id);

    void update_s(Singer newSinger);

    void ut_s(int studioId);

    void ut_m();

    void update_s_with_address(Singer newSinger);

    void delete_s(int parent_id, int child_id);

    bool get_s(int parent_id, int child_id, struct Singer* singer);

    void insert_s(Singer singer);

    void update_m(Country country);

    bool get_m(int id, struct Country* country);

    void delete_m(int id);

    void init();

    void load_country_garbage(bool mode);

    void load_singer_garbage(bool mode);

    void load_index_table(bool mode);

    void sort_index_table();

    int get_address(int id);

    void insert_m(Country* country);

    void shift_country_garbage();

    void shift_singer_garbage();

    void add_country_garbage_address(int language);

    void add_singer_garbage_address(int language);
};

#endif //UNTITLED3_DATABASE_H
