//Author: Chupakhin Andrey
//Year: September, 2015
/* Данная программа вычисляет и записывает в текстовой файл states.txt множество достижимых состояний
 * заданной программы для заданных значений параметров функций, а также выводит в стандартный
 * поток вывода количество достижимых состояний.
*/


#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits.h>

#define fLines 9
#define gLines 13

std::string filename("states.txt");
int f_a, f_b, g_a, g_b;
int f_x, f_y, g_x, g_y;
std::vector<int> init(4,0);//array for initialization control of the local variables
int c_f = 0, c_g = 0;
int count = 0;


int parserInputParameters( int argc, char ** argv) {
//    int a,b,c,d;
//    if (argc < 5 || argc > 8)
//        return 0;
    return 1;
}

int main(int argc, char **argv) {
    /*имя_программы <f_a> <f_b> <g_a> <g_b>
            -file имя_файла - запись состояний в указанный файл,
    -count - вывод общего количества состояний программы в стандартный поток вывода.
            При запуске без параметров (либо с недостаточным количеством параметров)
    программа должна выводить информацию о программе, авторе, годе написания и параметрах запуска.
     формат вывода в файл c_f, c_g, h, f.x, f.y, g.x, g.y.
     */
    if (!parserInputParameters(argc, argv)) {
        std::cerr << "Error in the input parameters" << std::endl;
        std::cout << "This program computes the set of reachable states "
            "for the program from the file task.txt" << std::endl <<
            "Author: Chupakhin Andrey" << std::endl <<
            "Year: September, 2015" << std::endl <<
            "usage: prog_name <f_a> <f_b> <g_a> <g_b> [-file <filename>] [-count]" << std::endl;
        return 1;
    }
    //If parsing true therefore all variables f_a, f_b, g_a, g_b was initialized

    //Print input parameters for check

    //

    //Check convertation
    int i,result;
    const char * number = "    -2147483648\0";
    char* end_ptr;
    long val = strtol(number, &end_ptr, 10);
    if (*end_ptr) {
        std::cout << *end_ptr << std::endl;
        std::cout << "Error in the string" << std::endl;
        return 1;
    }

    if ((val == LONG_MAX || val == LONG_MIN ) && errno == ERANGE || ( val > INT_MAX || val < INT_MIN ) ) {
        std::cout << "OverFlow" << std::endl;
        return 1;
    }
    result = (int)val;
    std::cout << "LONG_Number -> " << val << " INT_Number -> " << number << std::endl;
    std::cout << LONG_MAX << " " << LONG_MIN << std::endl;
    std::cout << INT_MAX << " " << INT_MIN << std::endl;
    //

    return 0;
}






