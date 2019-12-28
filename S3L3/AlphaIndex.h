#pragma once

#include "Dict.h"
#include "String.h"

Dict<String, int> &CreateAlphaIndex(char **word_arr, int words_number, int std_page_size);

Dict<String, int> &CreateAlphaIndex(FILE *ifstream, int std_page_size);

#include "AlphaIndex.cpp"