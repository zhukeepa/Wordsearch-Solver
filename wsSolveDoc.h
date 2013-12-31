/**
  *  wsSolveDoc.h
  *
  *  Here, we document the algorithm used to solve wsSolve().
  *
  *  ======  THE IDEA ======
  *
  *  Suppose we wish to find the word "SCATTER". The basic idea of thealgorithm
  *  is this:
  *       1. We have a point to start at, called startAt. By default, it is set to
  *          (0, 0).
  *       2. Starting at the point startAt, we go right until we find the letter "S".
  *          If we cannot find the letter "S" in the whole row, we go down a row and
  *          place the x-coordinate at 0 again. For example, if we have a 5x5 array,
  *          at the point (4, 3), we would go down to (0, 4). If we go through the
  *          whole array and cannot find "S", then we are done.
  *       3. If "S" is found, say at the point "location", we consider the letter
  *          one square up and to the left of location. If that square has the letter
  *          "C", we continue going one square up and to the left. This repeats until
  *          either:
  *              - We found the whole word "SCATTER".
  *              - There's a letter that doesn't match, e.g., if we encounter "SCE",
  *                we stop searching in that direction.
  *              - We step out of the bounds of the array, e.g., if the S is at (0, 0),
  *                and we search up and left, "SCATTER" won't be found.
  *       4. Repeat step 3 for each other direction (up, up and right, etc.).
  *       5. If "SCATTER" is found, we are finished. If not, we set startAt to
  *          the point right after location (one square to the right; if location's
  *          x-coordinate is at the far right side of the array, we set the
  *          x-coordinate to 0 and go down one ro).
  *       6. Repeat step 2.
  *
  *   Loosely speaking, we scan the array for "S"'s, and for each "S" we find, we
  *   search the block of letters around it; if "SCATTER" isn't found, we continue
  *   scanning the array.
  *
  *
  *   ===== A PROBLEM (AND ITS SOLUTION) =====
  *
  *   We overlooked a problem. Suppose "CAT" were on our list of words to
  *   find, as well as "SCATTER". We may find that the location of "CAT" is the
  *   substring "CAT" of "SCATTER". For instance, if "SCATTER" were at (3, 2) and
  *   is found going down and right, there is a possibility that "CAT" may be found at
  *   (4, 3) going down and right. We know this is not allowed to happen.
  *
  *   In order to remedy this problem, we create a 2D-array storing a vector of strings
  *   that occupy each square. We will call this array "occupy". For example, in
  *   occupy, the points (3, 2), (4, 3), ..., (10, 9) will each contain a vector
  *   containing the string "SCATTER". Then, at the points (4, 3), (5, 4), and (6, 5)
  *   in the array occupy, since "SCATTER" occupies all of those points, and "CAT" is a
  *   substring of "SCATTER", "CAT" is not allowed to be placed at the given location.
  *
  *   As a sidenote, an array of Boolean values stating whether or not a given point is
  *   occupied or not will not suffice; consider this wordsearch:
  *
  *   APPLE
  *   BLAST
  *   CREAK
  *
  *   We want to find the words "APPLE", "BLAST", "CREAK", and "ABC". However, after
  *   "APPLE", "BLAST", and "CREAK" are found, every point on the wordsearch will
  *   be occupied. However, "ABC" does not overlap entirely with any of the three
  *   words and therefore should be found.
  *
  *   We note that there is another more problem; what if we find "CAT" before we find
  *   "SCATTER"? As "SCATTER" is not a substring of "CAT", our current algorithm allows
  *   them to overlap. To prevent this from happening, we go through the list by order
  *   of length (from longest to shortest).
  *
  *   As a note, we cannot stop once we find a single instance of "CAT". Consider this
  *   possibility:
  *
  *   S
  *    C A T
  *     A
  *      T
  *       T
  *        E
  *         R
  *
  *   In this instance, suppose we find the diagonal "CAT" in "SCATTER" first. Since
  *   "CAT" is not allowed to be placed there, we would incorrectly mark "CAT" as not
  *   being found in the wordsearch. We must therefore search every direction for "CAT",
  *   even after we found a direction that one instance of the word "CAT" points in.
  *
  *
  *   ===== INCREASING PERFORMANCE =====
  *
  *   Suppose we're looking for the word "SCATTER". We note that the most
  *   time-consuming part of this algorithm is finding the "S"'s in the wordsearch.
  *   Therefore, when there is more than one "S" in the list of words to find, e.g.,
  *   if our list contains "SNOWBALL" as well, we create a vector containing the
  *   locations of every "S" that is found in the wordsearch. For example, since
  *   "SNOWBALL" is longer than "SCATTER", we search for "SNOWBALL" first. During our
  *   search, we stop once we find the "S" that "SNOWBALL" starts with in the
  *   wordsearch. But by that "S", it is very probable that other "S"'s have been found;
  *   it is also probably that "SCATTER" starts with one of those "S"'s. We therefore
  *   make a vector that caches that location of every "S" that we find when we searched
  *   for "SNOWBALL". Then, when searching for "SCATTER", we first go through the list
  *   of all "S"'s encountered by "SNOWBALL". If "SCATTER" doesn't start with any of
  *   those "S"'s, we continue searching for "SCATTER" from the spot right after "S"
  *   (one spot to the right if possible, one spot down with x-coordinate set to 0 if
  *   not), and again caching every "S" we encounter until we find "SCATTER".
  *
  *   Note that by this method, no position will be cached twice; for example, while
  *   searching for "SCATTER", we won't cache any "S" that "SNOWBALL" already found.
  *   This is because "SCATTER" only starts to cache "S"'s AFTER it goes through the
  *   list of all "S"'s that "SNOWBALL" found.
  *
  *   Also note that by this method, the cached positions will be stored in "ascending
  *   order", e.g., (3, 0), (7, 0), (3, 1), (1, 3), (6, 4), i.e., (a, b) < (c, d) if
  *   and only if b = d and a < c or b < d. In other words, if (a, b) is in the same
  *   row as (c, d), (a, b) < (c, d) if and only if b < d, and if (c, d) is on a row
  *   below the row (a, b), (a, b) < (c, d). This is because the positions are cached
  *   in "ascending order"; this is due to how wsSolve() searches for letters. It calls
  *   searchForLetter(), which scans the list in "ascending order"; see the function
  *   for more details.
  */
