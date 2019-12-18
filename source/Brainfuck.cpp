#include "Brainfuck.h"


using namespace std;


//                                   { add, substract, move right, move left,
//                                     output, input, loop begin, loop end  }
const std::unordered_set<char> _TOKENS_ = {'+', '-', '>', '<', '.', ',', '[', ']'};


// helper function for _preprocess
int end_of_loop(istream & in)
{
    char c;
    int count = 1;
    int between = 0;

    while(in >> c)
    {
        if(c == '[')        // are we at the start of a new loop?
        {
            ++between;
            ++count;
        }
        else if(c == ']')   // are we at the end of a loop?
        {
            if(between == 0)
                return count;

            --between;
            ++count;
        }
        else if(_TOKENS_.find(c) != _TOKENS_.end()) // c is a token
            ++count;
    }

    return -1;
}

void Brainfuck::_preprocess(istream & in)
{
    char c;
    int stream_index = 0;
    int instructions_index = 0;

    while(in >> c)
    {
        if(c == '[')    // start of a loop
        {
            // where is the loop?
            int pos = in.tellg();
            int until_next = end_of_loop(in);

            // error checking
            if(until_next == -1)
                throw UnterminatedLoop(stream_index);

            // go back to where we came from
            in.seekg(pos, ios::beg);

            // tell the interpreter where the loops shold go,
            // then push the current token to the back of the instructions.
            _loops.push_back( {instructions_index,
                               instructions_index + until_next} );
            _instructions.push_back(c);

            ++instructions_index;
        }
        else if(_TOKENS_.find(c) != _TOKENS_.end()) // c is any others token
        {
            _instructions.push_back(c);
            instructions_index;
            ++instructions_index;
        }

        ++stream_index;
    }
}


void Brainfuck::run()
{
    int index = 0;
    std::stack<Position> current_jumps;

    while(index < _instructions.size())
    {
        switch(_instructions[index])
        {
        case '+':
            _tape.increment();
            break;
        case '-':
            _tape.decrement();
            break;
        case '>':
            _tape.move_right();
            break;
        case '<':
            _tape.move_left();
            break;
        case '.':
            _tape.output(cout);
            break;
        case ',':
            _tape.input(cin);
            break;
        case '[':
        {
            Position jump = _jump_at(index);
            // only begin the loop if our current position is not zero
            if(! _tape.is_zero())
                current_jumps.push(_jump_at(index));
            // skip to the end of the loop if otherwise
            else
                index = jump.end;
            break;
        }
        case ']':
        {
            Position jump = current_jumps.top();
            current_jumps.pop();
            if(! _tape.is_zero())   // end of loop
            {
                index = jump.start;
                current_jumps.push(jump);
            }
            break;
        }
        default:
            break;
        }
        ++index;
    }
}
