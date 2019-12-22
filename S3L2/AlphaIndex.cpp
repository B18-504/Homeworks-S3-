#pragma once

#include "CmdMgr/Parser.cpp"            //to be replaced

Dict<String, int> &CreateAlphaIndex(Dict<String, int> &result, char **word_arr, int words_number, int std_page_size)
{
    int curr_page_number = 1, curr_page_cap = std_page_size/2;
    int symbols_on_page = -1;

    for(int i = 0; i < words_number; i++)
    {
        String curr_word(*word_arr);
        symbols_on_page += curr_word.len + 1;
        if(symbols_on_page > curr_page_cap)
        {
            symbols_on_page -= curr_page_cap;
            curr_page_number++;

            if(curr_page_number % 10)
            {
                curr_page_cap = std_page_size;
            }
            else
            {
                curr_page_cap = std_page_size/4 * 3;
            }
        }
        
        //printf("!\n");

        if(!(result.IsPresent(curr_word)))
        {
            result.Set(curr_word, curr_page_number);
        }

        word_arr++; 
    }
}

Dict<String, int> &CreateAlphaIndex(Dict<String, int> &result, FILE *ifstream, int std_page_size)
{
    char **words;
    int word_num;
    char err;
    finput(words, ifstream, word_num, err);
    if(err != 0)
    {
        throw BFI();
    }
    else
    {
        CreateAlphaIndex(result, words, word_num, std_page_size);
    }
}