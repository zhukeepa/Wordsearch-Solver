#ifndef LOCATIONDATA_H
#define LOCATIONDATA_H

#include <utility>

/*
 *  Despite this file having three classes, there is no implementation file for any
 *  of them. This is because these are just structs; however, some of them need some
 *  trivial operations defined on them (e.g., !=, ==, and constructors). I have
 *   hence made them classes with a few inline operations.
 */

class Coord
{
    /**
      * @brief This is simply an ordered pair of coordinates.
      */

public:
    unsigned pX;
    unsigned pY;

    Coord(unsigned x, unsigned y) : pX(x), pY(y) {}
    Coord() : pX(0), pY(0) {}

    bool operator == (Coord const& coord) const { return (pX == coord.pX &&
                                                           pY == coord.pY); }
    bool operator != (Coord const& coord) const { return !(*this == coord); }
};

class Direction
{
public:
    /**
      * @brief This class represents 8 primitive directions using pairs (dX, dY):
      *         (-1, -1) : left and up
      *         (-1, 0)  : left
      *         (-1, 1)  : left and down
      *         (0, -1)  : up
      *         (0, 0)   : no direction
      *         (0, 1)   : down
      *         (1, -1)  : right and up
      *         (1, 0)   : right
      *         (1, 1)   : right and down
      *
      *        In other words, dX represents the right direction, and dY represents
      *        the down direction. Note that dX and dY are not allowed to be -2,
      *        despite -2 being in the range of possible values of dX and dY.
      *
      *        These directions are used to represent the orientations of a word
      *        found in the array, so we know which direction the word faces when
      *        we get its coordinates. As such, we may use (0, 0) to represent the
      *        orientation of a single letter.
      */

    int dX : 2;
    int dY : 2;

    Direction(int x, int y)  : dX(x), dY(y) {}
    Direction() : dX(0), dY(0) {}
};

class LocationData
{
    /**
      * @brief A class containing coordinates and direction; this is used to
      *        represent the location of a word in the wordsearch. The coordiantes
      *        correspond to the coordinates of the first letter of the word, and
      *        the direction specifies which direction the word is in.
      */

public:
    Coord coord;
    Direction dir;

    LocationData() : coord(Coord()), dir(Direction()) {}
    LocationData(Coord aCoord, Direction aDir) : coord(aCoord), dir(aDir)
    {}
};

#endif
