#ifndef WORDSEARCHEXCEPTIONS_H
#define WORDSEARCHEXCEPTIONS_H

#include <iostream>

class WordsearchException
{
public:
    const char* what()        const { return errMsg_; }
    const char* getFileName() const { return fileName_; }
    unsigned getLineNo()      const { return lineNo_; }

    WordsearchException() {}
    WordsearchException(const char* errMsg) : errMsg_(errMsg) {}
    WordsearchException(const char* errMsg,
                        const char* fileName,
                        unsigned lineNo) :
                        errMsg_(errMsg), fileName_(fileName), lineNo_(lineNo) {}

private:
    const char* errMsg_;     //Error message.
    const char* fileName_;   //File in which error occurred.
    unsigned    lineNo_;     //Line on which error occurred.
};

class OutOfRange : public WordsearchException {};

#endif
