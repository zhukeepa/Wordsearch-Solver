//#include "PODs.h"
#include "Array2D.h"
#include "Array2D.cpp"
#include "Globals.h"
#include <map>
#include <vector>
#include <utility>
#include <cassert>
#include <string>

//Note that all directions are represented using ordered pairs; see LocationData.h
//for more information.

bool isWordAtGivenDir(Array2D<char> const& wsArray,
                      std::string          str,
                      Coord const&         coord,
                      Direction            dir)
{
    /**
      * @brief Given the array to search in, the string to find, this function
      *        specifies whether or not the string is found at the position
      *        coord in the direction dir.
      */

    //First check if the word can be entirely contained within the wordsearch's
    //bounds.
    if ((coord.pX + (str.size() - 1) * dir.dX < 0) ||
        (coord.pX + (str.size() - 1) * dir.dX >= wsArray.getWidth()) ||
        (coord.pY + (str.size() - 1) * dir.dY < 0) ||
        (coord.pY + (str.size() - 1) * dir.dY >= wsArray.getHeight()))
        return false;

    //If you see any letter that doesn't match, you're done.
    for (unsigned i = 0; i != str.size(); ++i)
    {
        if (str[i] != wsArray(coord.pX + i * dir.dX, coord.pY + i * dir.dY))
            return false;
    }

    //One arrives here if and only if no letters that don't match are encountered,
    //i.e., the word IS found at the given coordinates and direction.
    return true;
}

void findWordAt(Array2D<char> const&    wsArray,
                std::string             str,
                Coord const&            coord,
                std::vector<Direction>& possibleDir)
{
    /**
      * @brief This function checks to see if the word str, at the coordinates coord,
      *        can be found in wsArray at some direction, e.g., up, left, or down.
      *        In other words, it calls isWordAtGivenDir for for every possible
      *        direction at the given coordinates. If the word is found at one
      *        one of the directions, this saves the direction into the vector of
      *        directions. (The user passes in an empty vector, and this functions
      *        fills it up.)
      */

    //The string clearly can't be empty...
    assert(str != "");

    //If the first character doesn't match with the position in the array, the word
    //is not a match. The else statement executes only if the first character does
    //match. In that case, if the string is only one character long, then the whole
    //word is just one letter; we therefore should return true.
    if (wsArray(coord.pX, coord.pY) != str[0])
        return;
    else if (str.size() == 1)
    {
        //Orientation of a single letter; see LocationData.h.
        possibleDir.push_back(Direction(0, 0));
        return;
    }

    //Search each direction for the word.
    for (int dX = -1; dX <= 1; ++dX)
    {
        for (int dY = -1; dY <= 1; ++dY)
        {
            //Ensures that the direction (0, 0) cannot be obtained.
            if (dX != 0 || dY != 0)
            {
                if (isWordAtGivenDir(wsArray, str, coord, Direction(dX, dY)))
                    possibleDir.push_back(Direction(dX, dY));
            }
        }
    }

    return;
}

bool areAllOccupiedBySuperstring(Array2D<VecStr> const& occupied,
                                 std::string            str,
                                 Coord const&           coord,
                                 Direction const&       dir)
{
    /**
      * @brief Given the array of squares in the wordsearch that are occupied,
      *        we check to see if the word str is "allowed" to be at the coord
      *        of ld and have direction dir. See wsSolveDoc.h for more information
      *        on what's "allowed" and what's not.
      */

    //Assert that you remain in the bounds; this is a "private" function, and
    //you should never leave the bounds when wsSolve() is called.
    assert((coord.pX + (str.size() - 1) * dir.dX >= 0) &&
           (coord.pX + (str.size() - 1) * dir.dX < occupied.getWidth()) &&
           (coord.pY + (str.size() - 1) * dir.dY >= 0) &&
           (coord.pY + (str.size() - 1) * dir.dY < occupied.getHeight()));

    //The string's length can't be 0.
    assert(str.size() != 0);

    //First check if the square that the first letter of str occupies is occupied
    //by any superstring of str. If not, exit; if so, make a list of them.
    VecStr firstVecStr = occupied(coord.pX, coord.pY);
    if (firstVecStr.size() == 0)
        return false;

    //Executes iff above code didn't return false.
    VecStr possibleSuperstrList;

    for (unsigned i = 0; i != firstVecStr.size(); ++i)
    {
        //The below statement is equivalent to "if str is not a substring of
        //firstVecStr[i].
        if (firstVecStr[i].find(str) == std::string::npos)
            return false;
        else
            possibleSuperstrList.push_back(firstVecStr[i]);
    }

    //If the string is only one letter long, and we didn't return false yet, it means
    //that the string is on a spot occupied by one of its superstrings. Hence, we
    //return true.
    if (str.size() == 1)
        return true;

    //Something important to note is that str can only be a substring of any
    //superstring of str if its first is contained by a superstring of str.
    //Therefore, the set of all possible superstrings of str that overlap with str
    //entirely has already been determined. In the following code, we either find a
    //square which is empty or does not contain a superstring of str (and therefore
    //we return false) or find a square in which some element of possibleSuperstrList
    //is not found on the square (implying that that element is not a superstring of
    //str that overlaps with str entirely; make sure you see why); we therefore
    //remove that element from possibleSuperStrList. In the end, any remaining elements
    //in possibleSuperstrList is definitely a superstring of str that overlaps with
    //str entirely; hence, if it is empty by the end, this function returns false,
    //and if it isn't empty, this function returns true.

    for (unsigned i = 1; i < str.size(); ++i)
    {
        //Vector obtained at the current position in the array.
        VecStr vecStrCurrent = occupied(coord.pX + i * dir.dX, coord.pY + i * dir.dY);

        //List of superstrings of str on the current square.
        VecStr superstrListCurrent;

        //If the vector is empty, the position is unoccupied.
        if (vecStrCurrent.size() == 0)
            return false;

        //See if str is a substring of any strings currently held in vecStrCurrent.
        for (unsigned j = 0; j != vecStrCurrent.size(); ++j)
        {
            //The below statement is equivalent to "if str is not a substring of
            //vecStrCurrent[i].
            if (vecStrCurrent[j].find(str) == std::string::npos)
                return false;
            else
                superstrListCurrent.push_back(vecStrCurrent[j]);
        }

        //Get rid of all the elements of possibleSuperstrList that don't appear in
        //vecSuperStrListCurrent. We do this by creating a new vector containing all
        //elements that DO appear in vecSuperStrListCurrent, and then copy
        //possibleSuperstrList to the new one.
        VecStr newPossibleSuperstrList;
        for (unsigned j = 0; j != possibleSuperstrList.size(); ++j)
        {
            for (unsigned k = 0; k != superstrListCurrent.size(); ++k)
            {
                if (possibleSuperstrList[j] == superstrListCurrent[k])
                {
                    newPossibleSuperstrList.push_back(possibleSuperstrList[j]);
                    break;
                }
            }
        }
        possibleSuperstrList = newPossibleSuperstrList;

        //If it's empty, you're done.
        if (possibleSuperstrList.size() == 0)
            return false;
    }

    //Reached if and only if the above code doesn't execute.
    return true;
}

void setOccupied(Array2D<VecStr>& occupied,
                 std::string      str,
                 Coord const&     coord,
                 Direction const& dir)
{
    //Assert that you remain in the bounds; this is a "private" function, and
    //you should never leave the bounds when wsSolve() is called.
    assert((coord.pX + (str.size() - 1) * dir.dX >= 0) &&
           (coord.pX + (str.size() - 1) * dir.dX < occupied.getWidth()) &&
           (coord.pY + (str.size() - 1) * dir.dY >= 0) &&
           (coord.pY + (str.size() - 1) * dir.dY < occupied.getHeight()));

    //For each block that this string occupies, show that the block is occupied by
    //the string.
    for (unsigned i = 0; i < str.size(); ++i)
        occupied(coord.pX + i * dir.dX, coord.pY + i * dir.dY).push_back(str);
}

Coord searchForLetter(Array2D<char> const& wsArray,
                      char                 c,
                      Coord const&         start)
{
    /**
      * @brief This function searches each row starting at the point start for the
      *        letter c. When it reaches the end of the row, it sets the x-coordinate
      *        to search for and goes down another row.
      */

    unsigned x = start.pX;
    for (unsigned y = start.pY; y < wsArray.getHeight(); ++y)
    {
        while (x < wsArray.getWidth())
        {
            //If the first character matches, check the word out.
            if (wsArray(x, y) == c)
                return Coord(x, y);

            ++x;
        }

        x = 0;
    }

    return Coord(wsArray.getWidth(), wsArray.getHeight());
}



void wsSolve(Array2D<char> const& wsArray,       //Wordsearch array to solve.
             StrLocMap&           matchMap)      //List of words and their locations
{
    /**
      * @brief Given the array (wsArray) and the list of words to find (domain of
      *        matchMap), wsSolve will fill the range of matchMap with the locations
      *        of the words to find. For instance, if matchMap contains
      *        (string1, locationData), wsSolve() fills in locationData
      *        with the location of the string. If the word is not found,
      *        locationData will remain unmodified.
      *
      *        The algorithm itself is quite complex. See wsSolveDoc.h for more
      *        information.
      *
      * @author MPW
      * @date 7/19/2008
      * @version 1
      *
      */

   typedef std::vector<Coord> CoordVec;

   //Declare the array of vectors of strings and set them all to empty vectors.
   Array2D<VecStr> occupied(wsArray.getWidth(), wsArray.getHeight());

   for (unsigned y = 0; y != wsArray.getHeight(); ++y)
   {
       for (unsigned x = 0; x != wsArray.getWidth(); ++x)
           occupied(x, y) = std::vector<std::string>();
   }

    //Find the list of letters to make a location list for, and for each letter,
    //pair the letter with a vector containing the coordinates of each occurrence
    //of that letter.

    //We go through the list, finding each letter to cache.
    std::map<char, CoordVec> cacheList;
    char prevChar = 0;
    char currentChar = 0;
    for (StrLocMap::iterator itr = matchMap.begin(); itr != matchMap.end();)
    {
        //currentChar is still from the previous loop! Hence, we set prevChar to
        //currentChar and update currentChar.
        prevChar = currentChar;
        currentChar = itr->first[0];

        //If the letter here is the same as the one before, it repeats (since
        //maps sort their elements in alphabetical order) (if this is
        //the first loop, this will never happen; prevChar will be nul, and no first
        //letter of a string can be nul; therefore, we don't count the first element
        //as appearing twice).
        if (currentChar == prevChar)
        {
            cacheList.insert(std::make_pair(currentChar, CoordVec()));

            //This trasverses the map until we get to a different character.
            while ((++itr != matchMap.end()) && (itr->first[0] == currentChar));

            //This is so the ++itr below does not execute.
            continue;
        }

        ++itr;
    }

    //Copy each of the strings into a multimap; this will sort the strings by
    //length.
    std::multimap<unsigned, std::string> strList;
    for (StrLocMap::iterator itr = matchMap.begin(); itr != matchMap.end(); ++itr)
        strList.insert(std::make_pair(itr->first.size(), itr->first));

    //Start the find.
    for (std::multimap<unsigned, std::string>::reverse_iterator itr = strList.rbegin();
         itr != strList.rend(); ++itr)
    {
        std::string& str = itr->second;
        bool isCached = !(cacheList.find(str[0]) == cacheList.end()); //Whether or not
                                                                      //the first letter
                                                                      //of the current
                                                                      //string is
                                                                      //cached.

        Coord startLocation(0, 0); //Location to start searching at; if the first
                                   //letter of the word's locations have been cached,
                                   //and none of the cached positions are the
                                   //location where str is found, startLocation is
                                   //set to the spot one after the last cached
                                   //position.
        if (isCached)
        {
            CoordVec& coordVec = cacheList[str[0]];
            if (coordVec.size() != 0)
            {
                //We assert here that the cached locations are in "ascending order";
                //see wsSolveDoc.h for more information.

                for (unsigned i = 0; i != coordVec.size(); ++i)
                {
                    //Contains the list of all possible directions the word can have
                    //at the given coordinates; see wsSolveDoc.h for more information.
                    std::vector<Direction> possibleDirList;
                    findWordAt(wsArray, str, coordVec[i], possibleDirList);

                    //Go through the vector, either until we find a valid direction
                    //the word can have, or until there are no possible directions
                    //the word can have left. (There's a chance possibleDir.empty() is
                    //already true, so in that case, just skip over that part.)
                    for (std::vector<Direction>::iterator itr2 = possibleDirList.begin();
                         itr2 != possibleDirList.end(); ++itr2)
                    {
                        if (!areAllOccupiedBySuperstring(occupied, str, coordVec[i], *itr2))
                        {
                            //You found the word!
                            matchMap[str] = LocationData(coordVec[i], *itr2);
                            setOccupied(occupied, str, coordVec[i], *itr2);

                            goto lblContinue;
                        }
                    }
                }
            }
        }

        //If the word was found in a cache, we skip over to lblContinue; however, we
        //would then be skipping over some variable declarations in the current
        //scope. This is banned by C++ syntax, so we wrap the following code in
        //another block.
        {
            Coord const endLocation(wsArray.getWidth(), wsArray.getHeight());
            Coord       location(startLocation);

            //Find the next occurrence of the character you're searching for.
            while ((location = searchForLetter(wsArray, str[0], location)) != endLocation)
            {
                //Cache this position (if relevant).
                if (isCached)
                    cacheList[str[0]].push_back(location);

                //Contains the list of all possible directions the word can have
                //at the given coordinates; see wsSolveDoc.h for more information.
                std::vector<Direction> possibleDirList;
                findWordAt(wsArray, str, location, possibleDirList);

                for (std::vector<Direction>::iterator itr2 = possibleDirList.begin();
                     itr2 != possibleDirList.end(); ++itr2)
                {
                    if (!areAllOccupiedBySuperstring(occupied, str, location, *itr2))
                    {
                        //You found the word!
                        matchMap[str] = LocationData(location, *itr2);
                        setOccupied(occupied, str, location, *itr2);

                        //You're done with this loop; you then enter the next loop
                        //(i.e., you search for the next string.)
                        goto lblContinue;
                    }
                }
                //Increase the location's position by 1; if it goes past the end of
                //the row, go down another row.
                if (location.pX < wsArray.getWidth())
                    ++location.pX;
                else
                {
                    if (location.pY < wsArray.getHeight())
                    {
                        //This code executes if you're on the last position on the
                        //last row; in that case, you're done.
                        ++location.pY;
                        location.pX = 0;
                    }
                    else
                        break;
                }
            }
        }

        lblContinue:
        continue;
    }
}
