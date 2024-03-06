#pragma once

#include <stdio.h>
#include <string.h>
#include "Singer.hpp"
#include "Country.hpp"

void inputSinger(struct Singer* singer);

void inputCountry(struct Country* country);

void printCountry(struct Country country);

void printSinger(struct Singer singer);
