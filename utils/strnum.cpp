#include "strnum.h"
#include <sstream>
#include <iomanip>

#define VAL_k 1000
#define VAL_M 1000000
#define VAL_G 1000000000
#define VAL_T 1000000000000

#define MINUTE 60
#define HOUR 3600
#define DAY 86400
#define MONTH 2629800
#define YEAR 31557600

std::string Utils::bigLong2Str(long long num)
{
    std::stringstream sstr;
    if (num < 0) sstr << "-";
    num = num > 0 ? num : -num;

    if (num < VAL_k)
        sstr << num;
    else if (num < VAL_M)
        sstr << std::fixed << std::setprecision(1) << (double(num) / VAL_k) << "k";
    else if (num < VAL_G)
        sstr << std::fixed << std::setprecision(1) << (num / VAL_M) << "M";
    else if ((long long)num < VAL_T)
        sstr << std::fixed << std::setprecision(1) << (num / VAL_G) << "B";
    else
        sstr << "none";

    return sstr.str();
}

std::string Utils::secondsToTime(int sec)
{
    std::stringstream sstr;

    if (sec < MINUTE)
        sstr << sec << "s";
    else if (sec < HOUR)
        sstr << (sec / MINUTE) << "m";
    else if (sec < DAY)
        sstr << std::fixed << std::setprecision(1) << (double(sec) / HOUR) << "h";
    else if (sec < MONTH)
        sstr << std::fixed << std::setprecision(1) << (double(sec) / DAY) << "d";
    else if (sec < YEAR)
        sstr << std::fixed << std::setprecision(2) << (double(sec) / MONTH) << " months";
    else
        sstr << std::fixed << std::setprecision(2) << (double(sec) / YEAR) << " years";
    return sstr.str();

}
