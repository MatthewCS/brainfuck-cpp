#ifndef _BRAINFUCK_H_

#define _BRAINFUCK_H_


#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include "Tape.h"
#include "Exceptions.h"


struct Position
{
    int start;
    int end;

    Position(int s, int e) : start(s), end(e) {};
};


class Brainfuck
{
private:
    std::vector<Position> _loops;
    std::vector<char> _instructions;
    Tape _tape;

    std::ifstream _get_stream(const std::string & filepath);
    void _preprocess(std::istream & in);
    inline Position _jump_at(int i) const;

public:
    Brainfuck() {};
    Brainfuck(const std::string & path);
    Brainfuck(const std::string & path, int tape_length);
    Brainfuck(std::istream & in);
    Brainfuck(std::istream & in, int tape_length);

    void run();
};

inline std::ifstream Brainfuck::_get_stream(const std::string & filepath)
{
    std::ifstream in(filepath);

    if(! in.good())
        throw NoInputFile(filepath);

    return in;
}


inline Brainfuck::Brainfuck(const std::string & path)
{
    std::ifstream in = _get_stream(path);
    _preprocess(in);
}

inline Brainfuck::Brainfuck(const std::string & path, int tape_length)
{
    _tape = Tape(tape_length);
    std::ifstream in = _get_stream(path);
    _preprocess(in);
}

inline Brainfuck::Brainfuck(std::istream & in)
{
    _preprocess(in);
}

inline Brainfuck::Brainfuck(std::istream & in, int tape_length)
{
    _tape = Tape(tape_length);
    _preprocess(in);
}

// helper function for run
inline Position Brainfuck::_jump_at(int i) const
{
    for(const Position & p: _loops)
        if(p.start == i)
            return p;

    return Position(-1, -1);
}

#endif
