#pragma once
#include <fstream>
#include <map>
#include <exception>
#include <set>
////////// CMAKE использовать для сборки
#include "lexem_methods.h"
#include "ELEMENT_TYPE_DESCRIPTION.h"

using namespace std;


class Parser
{
public:
    Parser() : current_elem_data_index(-1)
    {
        //fill_elem_number_and_userIDs_maps();
    }
    Parser(string input_p) : current_elem_data_index(-1)
    {
        input_path = input_p;
        //fill_elem_number_and_userIDs_maps();
    }
    void set_path(string p)
    {
        input_path = p;
    }

    bool read_file()
    {
        m_data = "";
        fill_elem_number_and_userIDs_maps();
        lexems.clear();
        get_file_data();
        get_lexems();
        filter_lexems();
        check_correct_syntaxys();
        return true;
    }

    int get_elems_count()
    {
        return std::count(lexems.begin(), lexems.end(), "data");
    }

    int get_unic_id()
    {
        std::vector<std::string>::iterator itr = std::find(lexems.begin() + current_elem_data_index, lexems.end(), "data");
        return (std::count(lexems.begin(), itr, "data") + 1);
    }

    string get_elem_typename()
    {
        get_lexems_ind_of_curr_elem();
        return to_upper(get_element_type(lexems[current_elem_data_index + 1]));
    }

    int get_elem_user_id()
    {
        return stoi(get_element_num(lexems[current_elem_data_index + 1]));
    }

    int get_elem_number()
    {
        obj_count.find(to_upper(get_element_type(lexems[current_elem_data_index + 1])))->second++;
        return obj_count.find(to_upper(get_element_type(lexems[current_elem_data_index + 1])))->second;
    }

    int get_keys_count()
    {
        current_key_index = current_elem_data_index;
        int i = current_elem_data_index;
        int key_count = 0;
        while (lexems[i] != "end")
        {
            if (lexems[i] == "=")
            {
                key_count++;
            }
            i++;
        }
        return key_count;
    }

    pair<string, string> get_key_pair()
    {
        while (lexems[current_key_index - 1] != "=")
        {
            current_key_index++;
        }
        pair<string, string> key_pair;
        key_pair.first = to_upper(lexems[current_key_index - 2]);
        key_pair.second = lexems[current_key_index];
        return key_pair;
    }

private:
    enum STEPS
    {
        CHECK_DATA_FOUND = 0,
        CHECK_ELEMENT_NAME_EXIST = 1,
        CHECK_END_LINE_SEMICOLON_FOUND = 2,
        CHECK_KEY_NAME_EXIST = 3,
        CHECK_EQUALITY_SIGN_FOUND = 4,
        CHECK_KEY_VALUE_EXIST = 5
    };

    set<char> DELIMITERS{' ', '\n', '+', '.', ';', '*', '/', '-', '!', '(', ')', '[', ']', '='};
    set<string> KEYWORDS{"data", "end"};

    map<string, int> obj_count;
    map<string, set<int>> elems_user_id;
    vector<string> lexems;
    string input_path;
    string m_data;
    int current_elem_data_index;
    int current_key_index;
    void get_file_data()
    {
        ifstream file(input_path);
        string s;
        m_data = "";
        while (getline(file, s))
        {
            m_data = m_data + s + "\n";
        }
    }

    void get_lexems()
    {
        string lexem = "";
        for (int i = 0; i < static_cast<int>(m_data.length()); i++)
        {
            if (DELIMITERS.count(m_data[i]))
            {
                if ((m_data[i] != ' '))
                {
                    if (lexem != "")
                    {
                        lexems.push_back(lexem);
                    }
                    lexem = m_data[i];
                    lexems.push_back(lexem);
                    lexem = "";
                }
                else
                {
                    if (lexem != "")
                    {
                        lexems.push_back(lexem);
                    }
                    lexem = "";
                }
            }
            else
            {
                lexem.insert(lexem.end(), m_data[i]);
            }
        }
    }

    void filter_lexems()
    {
        int i = 0;
        while (i < static_cast<int>(lexems.size()) - 1)
        {
            int j = i;
            if (lexems[i] == "!")
            {
                string s;
                while ((lexems[j + 1] != "\n") && (i < static_cast<int>(lexems.size())))
                {
                    s = s + lexems[j + 1] + " ";
                    lexems.erase(lexems.begin() + j + 1);
                }
                s.pop_back();
                lexems.insert(lexems.begin() + j + 1, s);
                lexems.erase(lexems.begin() + j + 1);
                lexems.erase(lexems.begin() + j);
            }

            if (lexems[i] == "=")
            {
                string s;
                while ((lexems[j + 1] != ";") && (i < static_cast<int>(lexems.size())) && (lexems[j + 1] != "!"))
                {
                    s = s + lexems[j + 1];
                    lexems.erase(lexems.begin() + j + 1);
                }
                lexems.insert(lexems.begin() + j + 1, s);
                j++;
            }
            i = j;
            i++;
        }
    }

    void check_correct_syntaxys()
    {
        int state = 0;
        bool data_found;
        bool type_elem_def;
        string error = "";
        vector<string> keylist = {};
        for (int i = 0; i < static_cast<int>(lexems.size()); i++)
        {
            if ((lexems[i] != "\n"))
            {
                switch (state)
                {
                case STEPS::CHECK_DATA_FOUND:
                {
                    if (to_upper(lexems[i]) != "DATA")
                    {
                        error = "Expected \"data\" but found \"" + lexems[i] + "\" at line " + to_string(get_line(i, lexems)) + "\n";
                        invalid_argument e(error);
                        throw e;
                    }
                    else
                    {
                        data_found = true;
                        state = 1;
                    }
                    break;
                }
                case STEPS::CHECK_ELEMENT_NAME_EXIST:
                {
                    string type = to_upper(get_element_type(lexems[i]));
                    keylist = ElementTypeDescription::getInstance().getKeyDescription(type);
                    if (keylist.empty() || get_element_num(lexems[i]) == "")
                    {
                        if (ElementTypeDescription::getInstance().getKeyDescription(type).empty())
                        {
                            error = type + " is wrong type element: " + to_string(get_line(i, lexems)) + "\n";
                        }
                        else
                        {
                            error = "Missed user id in element name at line " + to_string(get_line(i, lexems)) + "\n";
                        }
                        invalid_argument e(error);
                        throw e;
                    }
                    else
                    {
                        if (elems_user_id.find(type)->second.count(stoi(get_element_num(lexems[i]))))
                        {
                            error = "User ID " + get_element_num(lexems[i]) + " already exists, use another ID at line " + to_string(get_line(i, lexems)) + "\n";
                            invalid_argument e(error);
                            throw e;
                        }
                        else
                        {
                            elems_user_id.find(type)->second.insert(stoi(get_element_num(lexems[i])));
                            type_elem_def = true;
                            state = 2;
                        }
                    }
                    break;
                }
                case STEPS::CHECK_END_LINE_SEMICOLON_FOUND:
                {
                    if (lexems[i] != ";" || lexems[i + 1] != "\n")
                    {
                        if (lexems[i] != ";")
                        {
                            if (type_elem_def == true)
                            {
                                error = "Can't initialize more than one element at once at line ";
                            }
                            else
                            {
                                error = "Missed ; at the end at line at line ";
                            }
                        }
                        else
                        {
                            error = "You should jump to another line: writing after ; isn't allowed at line ";
                        }
                        error = error + to_string(get_line(i, lexems)) + "\n";
                        invalid_argument e(error);
                        throw e;
                    }
                    else
                    {
                        if (data_found == false)
                        {
                            state = 0;
                        }
                        else
                        {
                            type_elem_def = false;
                            state = 3;
                        }
                    }
                    break;
                }
                case STEPS::CHECK_KEY_NAME_EXIST:
                {
                    vector<string>::iterator itr = find(keylist.begin(), keylist.end(), to_upper(lexems[i]));
                    if (itr == keylist.end() && (lexems[i] != "end") && lexems[i] != "data")
                    {
                        error = "Element key \"" + lexems[i] + "\" incorrect name at line " + to_string(get_line(i, lexems)) + ": this key doesn't exist or already have been initialized\n";
                        invalid_argument e(error);
                        throw e;
                    }
                    else
                    {
                        if (lexems[i] == "end")
                        {
                            data_found = false;
                            state = 2;
                        }
                        else if (lexems[i] == "data")
                        {
                            if (data_found == true)
                            {
                                error = "Block of current element isn't completed: key word \"end\" haven't found - you can't use \"data\" at line " +
                                        to_string(get_line(i, lexems)) + "\n";
                                invalid_argument e(error);
                                throw e;
                            }
                            else
                            {
                                state = 1;
                            }
                        }
                        else
                        {
                            keylist.erase(itr);
                            state = 4;
                        }
                    }
                    break;
                }
                case STEPS::CHECK_EQUALITY_SIGN_FOUND:
                {
                    if (lexems[i] != "=")
                    {
                        error = "Expected = but found \"" + lexems[i] + "\" at line " + to_string(get_line(i, lexems)) + "\n";
                        invalid_argument e(error);
                        throw e;
                    }
                    else
                    {
                        state = 5;
                    }
                    break;
                }
                case STEPS::CHECK_KEY_VALUE_EXIST:
                {
                    if (DELIMITERS.count(lexems[i][0]) != 0 || lexems[i] == "")
                    {
                        string del = "";
                        del.insert(del.end(), lexems[i][0]);
                        error = "Expected definition of key by word(s) or number but found \"" + del + "\" at line " + to_string(get_line(i, lexems)) + "\n";
                        invalid_argument e(error);
                        throw e;
                    }
                    else
                    {
                        state = 2;
                    }
                    break;
                }
                }
            }
            else if (i != 0)
            {
                if (lexems[i - 1] != "\n")
                {
                    if (lexems[i - 1] != ";")
                    {
                        error = "Missed ; at the end at line " + to_string(get_line(i, lexems)) + "\n";
                        invalid_argument e(error);
                        throw e;
                    }
                }
            }
        }
    }

    void fill_elem_number_and_userIDs_maps()
    {
        for (unsigned int i = 0; i < ElementTypeDescription::getInstance().getVector().size(); i++)
        {
            obj_count[ElementTypeDescription::getInstance().getVector()[i]] = 0;
            set<int> user_IDs;
            elems_user_id[ElementTypeDescription::getInstance().getVector()[i]] = user_IDs;
        }
    }

    void get_lexems_ind_of_curr_elem()
    {
        std::vector<std::string>::iterator itr = std::find(lexems.begin() + current_elem_data_index + 1, lexems.end(), "data");
        current_elem_data_index = std::distance(lexems.begin(), itr);
    }
};