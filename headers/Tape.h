#ifndef _TAPE_H_

#define _TAPE_H_


#include <iostream>
#include "Exceptions.h"


#define _DEFAULT_SIZE_ 30000 // 30,000 segnemts of tape


class Tape
{
private:
    int _size;
    int * _tape;
    int _current;

public:
    friend std::istream & operator>>(std::istream & in, const Tape & t);
    friend std::ostream & operator<<(std::ostream & out, const Tape & t);

    Tape() : Tape(_DEFAULT_SIZE_) {}
    Tape(int n);

    // ~Tape() { delete _tape; }

    void increment() const;
    void decrement() const;
    void move_right();
    void move_left();
    void input(std::istream & in) const;
    void output(std::ostream & out) const;
    // void jump(int n) { _current = n; };
    bool is_zero() const { return _tape[_current] == 0; };

    const int & operator[](int i) const { return _tape[i]; }
};

inline Tape::Tape(int n)
{
    if(n < 1)
        throw BadTapeLength(n);

    _size = n;
    _tape = new int[n]{};
    _current = 0;
}

inline void Tape::increment() const
{
    ++_tape[_current];
    if(_tape[_current] == 256)
        _tape[_current] = 0;
}

inline void Tape::decrement() const
{
    --_tape[_current];
    if(_tape[_current] == -1)
        _tape[_current] = 255;
}

inline void Tape::move_right()
{
    ++_current;
    if(_current == _size)
        _current = 0;
}

inline void Tape::move_left()
{
    --_current;
    if(_current == -1)
        _current = _size - 1;
}

inline void Tape::input(std::istream & in) const
{
    char c;
    in >> c;
    _tape[_current] = (int)c;
}

inline void Tape::output(std::ostream & out) const
{
    out << (char)_tape[_current];
}


#endif
