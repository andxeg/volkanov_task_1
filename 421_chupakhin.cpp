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
#include <string.h>

#define fLines 9
#define gLines 13

//GLOBAL VARIABLES -> <FILENAME< <INPUT PARAMETERS FOR PROCEDURE F AND G> <COUNT FLAG>
std::string filename("states.txt");
int f_a, f_b, g_a, g_b;
int count = 0;
//

class State {
public:
    int f_x;
    int f_y;
    int g_x;
    int g_y;
    int c_f;
    int c_g;
    std::vector<int> init;//array for initialization control of the local variables
public:
    State(const int & x_f = 0, const int & y_f = 0, const int & x_g = 0, const int & y_g = 0,
          const int & f_c = 0, const int & g_c = 0):
    f_x(x_f), f_y(y_f), g_x(x_g), g_y(y_g), c_f(f_c), c_g(g_c)
    {
        init = std::vector<int>(4,0);
    }

    ~State(){}

    void print(){}
};

int strToInt( const char * number, int & result ) {
    char* end_ptr;
    long val = strtol(number, &end_ptr, 10);
    if (*end_ptr) {
        std::cout << "Error in the number -> " << std::string(number) << std::endl;
        return 0;
    }

    if ( ((val == LONG_MAX || val == LONG_MIN ) && errno == ERANGE) || ( val > INT_MAX || val < INT_MIN ) ) {
        std::cout << "OverFlow in number ->" << number << std::endl;
        return 0;
    }

    result = static_cast<int>(val);
    return 1;
}

int parserInputParameters( int argc, char ** argv ) {
    int a,b,c,d;
    if (argc < 5 || argc > 8)
        return 0;
    //argc = {5,6,7,8}
    //Check input parameters for procedure f and g
    if ( !strToInt(argv[1], a ) )
        return 0;
    if ( !strToInt(argv[2], b ) )
        return 0;
    if ( !strToInt(argv[3], c ) )
        return 0;
    if ( !strToInt(argv[4], d ) )
        return 0;
    //Set global variables
    f_a = a;
    f_b = b;
    g_a = c;
    g_b = d;
    //

    //Check other input parameters
    // Four variants:
    // [-file <filename>] second [-count]
    // second [-count] [-file <filename>]
    // [-file <filename>]
    // [-count]
    if ( argc == 6 ) {
        if ( strcmp(argv[5],"-count\0") == 0 ) {
            count = 1;
            std::cout << "-count parameter successful read" << std::endl;
            return 1;
        } else {
            std::cout << "Error in the 5-th parameter" << std::endl;
            return 0;
        }
    }

    if ( argc == 7 ) {
        if ( ( strcmp(argv[5],"-file\0") == 0 ) && ( strcmp(argv[6],"-count\0") != 0) ) {
            filename = std::string(argv[6]);
            std::cout << "-filename parameter successful read" << std::endl;
            return 1;
        } else {
            std::cout << "Error in the 5-th and 6-th parameters" << std::endl;
            return 0;
        }
    }

    if ( argc == 8 ) {
        if ( ( strcmp(argv[5],"-file\0") == 0 ) && ( strcmp(argv[6],"-count\0") != 0 ) && ( strcmp(argv[7],"-count\0") == 0 ) ) {
            std::cout << "-filename parameter successful read" << std::endl;
            std::cout << "-count parameter successful read" << std::endl;
            filename = std::string(argv[6]);
            count = 1;
            return 1;
        } else if ( ( strcmp(argv[5],"-count\0") == 0 ) && ( strcmp(argv[6],"-file\0") == 0 ) && ( strcmp(argv[7],"-count\0") != 0 ) ) {
            std::cout << "-filename parameter successful read" << std::endl;
            std::cout << "-count parameter successful read" << std::endl;
            filename = std::string(argv[7]);
            count = 1;
            return 1;
        } else {
            std::cout << "Error in the 5-th, 6-th, 7-th parameters" << std::endl;
            return 0;
        }
    }
    //
    std::cout << "End of parserInputParameters" << std::endl;
    return 1;
}

int main( int argc, char **argv ) {
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
    std::cout << " f_a, f_b, g_a, g_b : "  << f_a << ", "<< f_b << ", " << g_a << ", " << g_b << std::endl;
    std::cout << " Count flag -> "  << count << " Filename -> " << filename << std::endl;
    //
    return 0;
}