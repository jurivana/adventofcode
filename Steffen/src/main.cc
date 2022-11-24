#include "01.h"
#include "02.h"
#include "03.h"
#include "04.h"
#include "05.h"
#include "06.h"
#include "07.h"
#include "08.h"
#include "09.h"
#include "10.h"
#include "11.h"
#include "12.h"
#include "13.h"
#include "14.h"
#include "15.h"
#include "16.h"
#include "17.h"
#include "18.h"
#include "19.h"
#include "20.h"
#include "21.h"
#include "22.h"
#include "23.h"
#include "24.h"
#include "25.h"

int main(int argc, char** argv) {
    int day;
    if (argc > 1) {
        day = std::stoi(argv[1]);
    }
    switch (day) {
    case 1:
        aoc01();
        break;
    case 2:
        aoc02();
        break;
    case 3:
        aoc03();
        break;
    case 4:
        aoc04();
        break;
    case 5:
        aoc05();
        break;
    case 6:
        aoc06();
        break;
    case 7:
        aoc07();
        break;
    case 8:
        aoc08();
        break;
    case 9:
        aoc09();
        break;
    case 10:
        aoc10();
        break;
    case 11:
        aoc11();
        break;
    case 12:
        aoc12();
        break;
    case 13:
        aoc13();
        break;
    case 14:
        aoc14();
        break;
    case 15:
        aoc15();
        break;
    case 16:
        aoc16();
        break;
    case 17:
        aoc17();
        break;
    case 18:
        aoc18();
        break;
    case 19:
        aoc19();
        break;
    case 20:
        aoc20();
        break;
    case 21:
        aoc21();
        break;
    case 22:
        aoc22();
        break;
    case 23:
        aoc23();
        break;
    case 24:
        aoc24();
        break;
    case 25:
        aoc25();
        break;
    }
}
