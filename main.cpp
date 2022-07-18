#include <iostream>
#include <filesystem>
#include "Elements\\PROVIDER.h"
#include "ELEMENT_STORAGE.h"
#include "Elements\\PROVIDER.h"
#include "tester.h"
#include "path_utilities.h"
using namespace std;

int main(int argc, char *argv[])
{
    string path(get_dir_path(argv[0]));
    if (test_all(path))
    {
        return 1;
    }

    Parser parser;
    Logger logger(path);
    parser.set_path(path + "\\Examples\\test.txt");

    try
    {
        parser.read_file();
        ElementStorage::getInstance().createElements(parser);
    }
    catch (invalid_argument &e)
    {
        logger.write(e.what());
    }
    ElementStorage::getInstance().printAllElements();
    ElementStorage::getInstance().emptyStorage();
    return 0;
}