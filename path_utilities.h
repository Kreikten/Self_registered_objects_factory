#pragma once
#include <iostream>
#include <string>

using namespace std;

string get_dir_path(char *p)
{
    string path(p);
    for (int i = static_cast<int>(path.length()); i > 2; i--)
    {
        path.pop_back();
        if (path[i - 2] == '\\')
        {
            break;
        }
    }
    return path;
}

class Logger
{
public:
    Logger(string path)
    {
        m_path = path + +"\\log.txt";
        m_file.open(m_path);
        m_file.close();
    }

    void write(string txt)
    {
        m_file.open(m_path, ios::app);
        m_file << txt;
        m_file.close();
    }

private:
    ofstream m_file;
    string m_path;
};
