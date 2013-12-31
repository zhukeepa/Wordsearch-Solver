#ifndef GLOBALS_H
#define GLOBALS_H

#include "LocationData.h"
#include "WordsearchExceptions.h"
#include "Array2D.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, LocationData> StrLocMap;
typedef std::vector<std::string> VecStr;

void wsSolve(Array2D<char> const&, StrLocMap&);


#endif
