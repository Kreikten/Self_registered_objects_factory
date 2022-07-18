#pragma once
#include "path_utilities.h"
class Tester
{
public:
    string input_path;
    string output_path;
    Tester(string in_path, string out_path)
    {
        input_path = in_path;
        output_path = out_path;
    }

    bool test(int i)
    {
        bool all_correct = true;
        Parser parser(input_path); //, "D:\\PRACTICE\\PROGS\\PARSER\\log.txt");
        ofstream outfile(output_path);
        outfile.close();
        outfile.open(output_path, ios::app);
        for (int j = 0; j < i; j++)
        {
            string FILEPATH = input_path + "test" + to_string(j) + ".txt";
            parser.set_path(FILEPATH);
            try
            {
                parser.read_file();
                all_correct = false;
            }
            catch (invalid_argument & e)
            {
                string rrr(e.what());
                outfile << rrr+ "In file \"test" + to_string(j) + "\".\n\n";
            }
            
        }
        outfile.close();
        if (!all_correct)
        {
            cerr << "Check test_log.txt" << endl;
        }
        return all_correct;
    }
};

bool test_all(string path)
{
    Tester tester(path + "\\Examples\\", path + "\\test_log.txt");
    bool f = tester.test(13);
    return f;
}
