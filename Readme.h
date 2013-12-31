/*
    Hey Dave, sorry about my absence. Read through the whole readme for more
    information.

    Let me get over the trivial information before I tell you the important things.
    Set your hint column to 85 (or higher); that's what I set mine too. It'll make
    all my code a lot more readable. I'll admit that I did go past the margin a few
    times (many more, actually), due to the fact that I have knack for giving
    variables descriptive (and therefore long =/) names. Also, all my files are
    set to debug mode (when you add a file, you can check either debug or release;
    I checked debug for each one.)

    There are some things that I've changed in the code that could affect you:
      1. I've realized it would be more consistent and easier on my part to create
         a coordinate class and a direction class (called Coord and Direction,
         respectively). LocationData is therefore a struct containing a coordinate
         member (coord) and a direction member (dir). See LocationData.h for more
         information.

      2. I recall telling you that if a word had a direction of (0, 0) after wsSolve()
         was called, then it was not found. I've changed my mind; if a word is a single
         letter long, I let its direction be (0, 0). Any word longer than a single
         letter long, if found, will have a valid direction. You've got a few possible
         solutions here:
            - Set the default values of the coordinates to the bounds of the array
              (the coordinates (array.getWidth(), array.getHeight)); if the word was
              not found, that coordinate won't be replaced. In other words, check if
              a word was found by checking its coordinates rather than its direction.
            - Still check the direction, but if it's (0, 0), see if it's one letter
              long. If it is, check to see if it's at the coordinates in LocationData.
              If it is, then the character is at that position. If not, the character
              wasn't found.

         I would personally use the second solution, but it's your decision here.

      3. I refactored Array2D(). I have my reasons for the refactoring; I've made a
         list of things I want to discuss with you, and that's coding style. I've
         changed the names of Array2D's private members by suffixing them with an
         underscore. I'll provide my argument for this method later. I'm welcoming
         an argument back; I'd like to see your point of view. (If that sounded
         arrogant/sarcastic, sorry. -__- I'm serious here.)

      4. I also made another change to Array2D(); I fixed a memory leak. In the copy
         constructor, you forgot to delete[] Array2D()'s data.

      5. Forget about the Boolean template specialization for Array2D() for now. A
         Boolean array doesn't work; wee wsSolveDoc.h to see why.

    I've completed wsSolve. It turned out to be far more complex than I thought
    (434 lines o_O). I have a crapload of nested loops, two goto's that were
    virtually unavoidable, multimaps and reverse iterators... The last time we spoke,
    I said I was about 80% through. That was only partially correct; I was 80% through
    if you didn't consider the debugging. If you considered debugging, I was 40% through.
    It turned out that my logic was entirely wrong in certain places (e.g., with the
    Boolean array). The fix was extraordinarily complex; it's probably the most
    complicated part of the whole code. Not to worry, though; I've commented it
    a lot. You'll see a huge-ass bunch of comments in areAllOccupiedBySuperstring.

    My code has a main() too. Run my main() just once and see what it does. It'll
    give you an idea of how my wordsearch works. And I believe my main(), which is
    just a bunch of code I quickly piled up (didn't bother to make it consistent
    or sexy or anything), is still longer than your main(). Heheh.

    Random note: To my knowledge, "superstring" is the opposite of "substring". For
    instance, "FOOBAR" is a superstring of "FOO", and "FOO" is a substring of "FOOBAR".

    I have some todos:
        1. Make the comments clearer - I can do this myself, but if you read all my
           comments and tell me what's confusing, I'd appreciate
           it quiet a bit.
        2. Switch from vectors to other STL containers - I don't really need vectors'
           random access capabilities for the most part--I could just use a list
           and an iterator; that would speed up performance a tiny bit.
        3. Use forward iterators when I should - As of now, I only use normal iterators
           (except for in the case of the multimap), when in fact, I only need them
           to go forward.

    As you can see, these are just little optimizations. I've solved most of the problems
    myself already. While I lost contact with you, I squashed about every bug in my
    program. I honestly can't find anymore. I want you to see if you can find any.
    If you get an assertion failed on your first wordsearch, shoot me.

    Just saying, I love Code::Block's debugger interface is WAY better than Dev's. If
    I were debugging in Dev, I'd still be in development stage right now. Now that I
    think of it, I never really figured out how to get the debugger to even run.
    "Your project does not have debugging information. Enable debugging? " I pressed
    yes. The message came up again. <__<

    So this is Version 1.0 of my code. Version 1.1 will be the version with the three
    todo's up there fixed. Version 2 will be... pointless. There are, however,
    other forms of wordsearches in which words may go like this:

    F O
       O   R
        B A

    I suppose we could do that, but wordsearches like that are so rare that there's
    no real use to it. Furthermore, implementing that is, contrary to what it may
    first seem, extremely easy. My solution uses recursion. See if you can figure
    it out. =D

    Besides, this was just an exercise.

    Despite this being an exercise, there are a few things we should discuss about
    this project that may be relevant to future projects:

    1. Namespaces - We really should have a namespace for each project we make. It's
                    not anything extremely annoying or difficult to add a namespace.
                    We'll call the namespace NsBiggoronMpwProjectname (so this would
                    be NsBiggoronMpwWordsearchsolve). Then do namespace my = namespace
                    NsBiggoronMpwWordsearchsolve;. No big deal. For one thing, that's
                    just how good code should be.

    2. A new Array2D - Who knows, we may need another dynamic 2D array again. All that
                       really needs to happen is make a Boolean extension for it.
                       We may even decide to make an Arrayn-D later that takes vectors
                       as arguments to specify which members to reference. =D

    3. Coding styles
         - Private members : I suffix my private members with an underscore. This has
                             two main advantages:
                               a) In constructors, we can create a more accurate name
                                  for the argument without resorting to some weird
                                  prefix. For example, we could do coord_(coord)
                                  rather than coord(x) or coord(aCoord) (a for
                                  argument).
                               b) It's a nice reminder that these members are PRIVATE.
                                  The class user also won't ever need to be plagued by
                                  typing those underscores, so it doesn't matter to
                                  them.
         - Braces : I do this:
                    if (bbq)
                    {
                        //line 1
                        //line 2
                    }
                    or this:
                    if (bbq)
                        //line 1

                    //rest of code.

                    From what I know, when you have more than one line of code,
                    you do this:
                    if(bbq) {
                        //line 1
                        //line 2
                    }

                    You're a real sucker for preserving space, aren't you? :p Think
                    of it this way:
                          a) Putting a { at the end of the line increases the horizantal
                             space. All you do is save one line of vertical space.
                             I can understand why you might want to conserve on
                             horizantal space. Vertical space? I have no clue. Wouldn't
                             you rather boast that you have more lines? :p
                          b) Code::Blocks matches up your }'s with your {'s. The
                             pairs of openings and closings, as well as which level
                             of indentation you use, is clearer using my method.

         - Commenting : I recall that you said you only comment when other people see
                        your code. I'm going to tell you right here, right now that
                        since we're going to work as a group, I'm going to see your
                        code. Actually, I might not, since I just supply you with
                        functions and classes and have nothing to do with GUI. :D
                        Despite that fact, commenting your own code makes it more
                        readable for yourself. If I looked at wsSolve() a month from
                        today, I'd probably be lost without the comments. But they
                        always help. I know you get lazy a lot (I do too =O), but at
                        least make some notes at the more complicated sections.

         - Whitespace use: I use whitespace like this:

                           (a + b) * c
                           a & b
                           if (a || b) {}

                           Some may use it like this:

                           (a+b)*c
                           a&b
                           if(a||b) {}

                           Which one is more readable? Which one is sexier? I think
                           mine is. :p I'm pretty sure you don't code like the latter,
                           but you do do it to a certain extent. Preserving horizantal
                           space isn't that big a deal; if it takes up more space
                           but makes code more readable, make it take up more space.
                           I can, however, understand that you may sometimes exclude
                           spaces from mixes of multiplication and addition
                           (e.g., a + b*c) in order to make the order of operations
                           more explicit (that's a habit I should start adapting).
                           Am I correct?

         - Breaking up lines : I do it like this:
                               int foobar = a + b +
                                            c + d;
                                if ((a && b) ||
                                    (c && d) ||
                                    (x && y))
                                {
                                    //asdfg;
                                }
                                myFunc(abcdefghijklmnop,
                                       qrstuvwxyzzzzzlol);

                                That's just my style. I don't know how you do it.
                                I'd like some comments.

         - Function arguments : I do them like this:
                                int foo(int a,
                                        int b,
                                        int c,
                                        double d) //D9 lol
                                { return 42; }

                                It's easier to comment on the arguments that way
                                when they're unclear. Furthermore, my argument lists
                                usually exceed the margin; this preserves whitespace.

                                Comment on my style. Give me reasons for yours
                                (the more commonly-used one.)

        - Positioning of const : Between you and me, I think int const bar; is better
                                 than const int bar;. The reason is that when we deal
                                 with special cases of consts with references and
                                 pointers, the const must necessarily appear after
                                 the int. The only reason const int is used more is
                                 because... it's used more. More people are used to
                                 it. I personally think int const is better. What's
                                 your opinion?

        If you find any other discrepancies in coding styles, alert me.


    My next idea for a project is a mathematical expression evaluator. That's going
    to be mostly work on my part, so if I stay out of contact with you, I can still
    work on it just fine. Honestly, an expression evaluator by itself is pretty
    much useless (since we have Google calculator), so I'm going to make a graphing
    calculator out of that. The graphing calculator will actually be almost trivially
    easy to make. But as I've said, this is mostly work on my part. If we do work
    on this, then you'd better make the GUI look good. >=D

    And I still haven't explained my absence. =O Saving the best for last. =D
    On the day we last spoke, my mom came home early, snuck up on me, and entered
    the room with Safe Eyes disabled. She got uber pissed and took away all my
    Internet time. I was engrossed in programming, there was really no need to use
    the Internet a lot. My sister--who's been unusually nice the past few
    days--logged me in to her Safe Eyes account and supervised me, so I couldn't
    contact you. I did, however, look up a few things about STL's and iterators.

    I'd like to talk with you on Monday, July 21, 2008 at 11:00 am Eastern
    daylightsavings time. I'm not very enlightened about time-zone conversions, (from
    here to England is +6 hours I think, but I dunno about daylight savings time), and
    I don't have any Internet time as of the time I'm typing this, so I can't look
    it up. I'll be in my town library then.

    The only way I can get this sent to you is if I put it into the code. This is because
    I can only send this to you under my sister's Safe Eyes login, and she'll be
    supervising what I send. She won't see my project. However, attaching a .txt,
    .doc, or .rtf may look kind of suspicious, as is pasting a huge message into body
    and sending before anyone could read it.

    I'm going to the library every day of the week from Monday to Thursday
    (for a volunteer service; after that, I can use the computers.) I'm writing an
    essay to my mom about my rights, how taking away my Internet time was selfish
    and not well-planned, how it will do more harm than good, and how she should change
    her ways. In other ways, I'm going to fight peacefully. All the same, I'm going to
    figure out how to kill Safe Eyes. Safe Eyes works by screwing with Winsock, so all
    programs have to pass the "Safe Eyes requirements" test. Resetting the Winsock
    catalog may be too dangerous--that's how some antivirus programs work. I'll do
    some research on the Winsock catalog at the library, and force-kill Safe Eyes
    if my mom doesn't comply. I believe safe mode is still open. I'm not even going
    to bother sneaking anymore.

    I justify my actions because I'm right. I've thought it through.

    Looks like we really do need a week for this project.
*/
