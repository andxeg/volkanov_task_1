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
#include <vector>

#define fLines 9
#define gLines 13

//GLOBAL VARIABLES -> <FILENAME< <INPUT PARAMETERS FOR PROCEDURE F AND G> <COUNT FLAG>
//F_Procedure lines - {0}, G_Procedure lines - {1}
//Implementation of the program is represented by the binary vector
//Weight of the vector is a constant. Weight == gLines
std::string filename("states.txt");
int f_a, f_b, g_a, g_b;
int count = 0;
uint START_PATH;// 0000000001111111111111
uint END_PATH;  // 1111111111111000000000
//

void initPathes() {
    START_PATH = 1;
    for (int i = 0; i < gLines-1; ++i ) {
        START_PATH = START_PATH << 1;
        START_PATH |= 1;
    }
    END_PATH = START_PATH << fLines;
}

int correctTrace( const uint & trace ) {
    //Trace is correct if weight == gLines and length == (fLines + gLines)
    return 1;
}

class F {
public:
    int ip;//instruction pointer
public:
    void execute(State & curr_state) {
        //execute operation in ip -> change State and change ip
        // curr_state -> execute command -> new_state and new valure in ip
    }
};

class G {
public:
    int ip;//instruction pointer
public:
    void execute(State &) {

    }
};

class State {
public:
    int f_x;
    int f_y;
    int g_x;
    int g_y;
    int h;
    int c_f;
    int c_g;
    std::vector<int> init;//array for initialization control of the local variables { h, f_x, f_y, g_x, g_y }
public:
    State( const int & x_f = 0, const int & y_f = 0, const int & x_g = 0, const int & y_g = 0, const int & h_fg = 0,
          const int & f_c = 0, const int & g_c = 0 ):
    f_x(x_f), f_y(y_f), g_x(x_g), g_y(y_g), h(h_fg), c_f(f_c), c_g(g_c)
    {
        init = std::vector<int>(5,0);
    }

    ~State(){}

    void print() {
        std::cout <<
        c_f << "  " <<
        c_g << "  ";
        if (init[0])
            std::cout << h << "  ";
        else
            std::cout << "#" << "  ";

        if (init[1])
            std::cout << f_x << "  ";
        else
            std::cout << "#" << "  ";

        if (init[2])
            std::cout << f_y << "  ";
        else
            std::cout << "#" << "  ";

        if (init[3])
            std::cout << g_x << "  ";
        else
            std::cout << "#" << "  ";

        if (init[4])
            std::cout << g_y;
        else
            std::cout << "#";

        std::cout << std::endl;
    }
};

void implementTrace(const uint & trace, std::vector<State> & states) {
    //Passing nulles and ones while implement trace
    char one_count = 0;
    char null_count = 0;
    //
    //create new procedures F and G
    F f; // {3}
    G g; // {4}
    //
    //Init state. All variables have unknown values. Only c_f == 0 and c_g == 0
    State initState;
    //
    while ( g.ip < gLines || f.ip < fLines ) {
        //take bit with number == ( one_count + null_count)
        //if bit == 0 then f.execute
        //if bit == 1 then g.execute
        //print new state
    }

}

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

    //Main Algorithm
    //For input parameters look through all the routes of Program implementation
    //Initialize start and end path
    initPathes();
    std::cout << " START_PATH -> "  << START_PATH << " END_PATH -> " << END_PATH << std::endl;
    //
    //Set of states
    std::vector<State> states;
    //
    for ( uint trace = START_PATH; trace <= END_PATH; trace++ ) {
        if ( !correctTrace(trace) ) // {1}
            continue;
        implementTrace(trace, states); // {2}
    }
    //
    return 0;
}