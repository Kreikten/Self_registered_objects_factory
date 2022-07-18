#pragma once
#include <string>
#include <algorithm>
#include <vector>
bool is_word(std::string word)
{
    bool flag = true;
    for (int i = 0; i < static_cast<int>(word.length()); i++)
    {
        if (!isalpha(word[i]))
        {
            flag = false;
            break;
        }
    }
    return flag;
}

std::string to_upper(std::string str)
{
    std::string s = "";
    for (int i = 0; i < static_cast<int>(str.length()); i++)
    {
        s.insert(s.end(), toupper(str[i]));
    }
    return s;
}

int get_line(int in_cur_ind, std::vector<std::string> lexems)
{
    int cur_elem_index = 0;
    int i_n = 0;  
    bool flag_n = false;
    while (!flag_n)
    {
        std::vector<std::string>::iterator itr = std::find(lexems.begin() + cur_elem_index, lexems.end(), "\n");
        cur_elem_index = std::distance(lexems.begin(), itr) + 1;
        i_n++;
        if (cur_elem_index > in_cur_ind)
        {
            flag_n = true;
        }
    }
    return (i_n);
}

std::string get_element_type(std::string user_element)
{
    std::string element_type = "";
    for (int i = 0; i < static_cast<int>(user_element.size()); i++)
    {
        if (!isdigit(user_element[i]))
        {
            element_type.insert(element_type.end(), toupper(user_element[i]));
        }
        else
        {
            break;
        }
    }
    return element_type;
}

std::string get_element_num(std::string user_element)
{
    std::string element_type = "";
    for (int i = 0; i < static_cast<int>(user_element.size()); i++)
    {
        if (isdigit(user_element[i]))
        {
            element_type.insert(element_type.end(), toupper(user_element[i]));
        }
    }
    return element_type;
}
