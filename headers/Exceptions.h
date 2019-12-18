#ifndef _EXCEPTIONS_H_

#define _EXCEPTIONS_H_


#include <exception>
#include <string>


class UnterminatedLoop: public std::exception
{
private:
    std::string _msg;
public:
    UnterminatedLoop(int i) :
        _msg("ERROR: UNTERMINATED LOOP"
             "\nLoop instantiated at index " + std::to_string(i) +
             " left without an end.")
    {};
    virtual const char* what() const throw()
    {
        return _msg.c_str();
    }
};

class BadTapeLength: public std::exception
{
private:
    std::string _msg;
public:
    BadTapeLength(int n) :
        _msg("ERROR: BAD TAPE"
             "\nTape length (" + std::to_string(n) + ") less than 1.")
    {};
    virtual const char* what() const throw()
    {
        return _msg.c_str();
    }
};

class NoInputFile: public std::exception
{
private:
    std::string _msg;
public:
    NoInputFile(std::string filepath) :
        _msg("ERROR: NO INPUT FILE"
             "\nNo file found at path \"" + filepath + "\".")
    {};
    virtual const char* what() const throw()
    {
        return _msg.c_str();
    }
};

#endif
