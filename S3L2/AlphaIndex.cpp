#pragma once

#include "CmdMgr/Parser.cpp"            //to be replaced

Dict<String, int> &CreateAlphaIndex(char **word_arr, int words_number, int std_page_size)
{
    Dict<String, int> *result = new BPlusDict<String, int>(50);

    //std::string curr_word;
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

        if(!(result->IsPresent(curr_word)))
        {
            result->Set(curr_word, curr_page_number);
        }   

        word_arr++; 
    }

    return *result;
}

Dict<String, int> &CreateAlphaIndex(FILE *ifstream, int std_page_size)
{
    char **words;
    int word_num;
    char err;
    finput(words, ifstream, word_num, err);
    if(err > 0)
    {
        throw BFI();
    }
    else
    {
        return CreateAlphaIndex(words, word_num, std_page_size);
    }
}

