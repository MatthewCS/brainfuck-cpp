#include "Tape.h"


std::istream & operator>>(std::istream & in, const Tape & t)
{
    t.input(in);
    return in;
}

std::ostream & operator<<(std::ostream & out, const Tape & t)
{
    t.output(out);
    return out;
}
