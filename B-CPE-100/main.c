#include <unistd.h>
#include <stdlib.h>

/// Determines the width of the star using the found formula and taking in 
/// considerations the exception of size 1.
int det_width(unsigned int size)
{
    return (size > 1) ? (size * 6 - 1) : 7;
}

void tail(unsigned int h, unsigned int w, int b_h)
{
    int current_h;
    unsigned int current_pad;
    unsigned int up_tail;

    current_h = b_h;
    up_tail = b_h == 0;
    while ((current_h < h && up_tail) || (current_h >= 0 && !up_tail)) 
    {
        current_pad = w / 2 - current_h;
        while (current_pad > 0)
        {
            write(1, " ", 1);
            current_pad--;
        }
        write(1, "*", 1);
        if (current_h > 0) 
        {
            current_pad = current_h * 2 - 1;
            while (current_pad > 0)
            {
                write(1, " ", 1);
                current_pad--;
            }
            write(1, "*", 1);
        }
        write(1, "\n", 1);
        if (up_tail)
            current_h++;
        else
            current_h--;
    }
}

void straight_l(unsigned int w, int size)
{
    int l_part_w;
    int l_part_ptr;
    int l_pad_w;

    l_part_ptr = 0;
    l_part_w = size * 2 + 1;
    l_pad_w = size * 2 - 3;
    if (size == 1)
        l_pad_w = 1;
    while (l_part_ptr < l_part_w) 
    {
        write(1, "*", 1);
        l_part_ptr++;
    }
    while (l_pad_w > 0)
    {
        write(1, " ", 1);
        l_pad_w--;
    }
    l_part_ptr = 0;
    while (l_part_ptr < l_part_w)
    {
        write(1, "*", 1);
        l_part_ptr++;
    }
    write(1, "\n", 1);
}

void body(unsigned int w, int size, int b_pad)
{
    int pad;
    int upper_body;
    int pad_ptr;
    int mid_pad;

    pad = b_pad;
    pad_ptr = 0;
    upper_body = 0;
    if (b_pad == 1)
        upper_body = 1;
    if (size == 1)
        size = 2;
    while ((pad < size && upper_body) || (pad > 0 && !upper_body))
    {
        while (pad_ptr < pad)
        {
            write(1, " ", 1);
            pad_ptr++;
        }
        write(1, "*", 1);
        mid_pad = w - pad * 2 - 2;
        while (mid_pad > 0)
        {
            write(1, " ", 1);
            mid_pad--;
        }
        write(1, "*\n", 2);
        pad_ptr = 0;
        if (upper_body)
            pad++;
        else
            pad--;
    }
}

/// The first loop will be writing the upper branch
void star(unsigned int size) 
{
    unsigned int w;
    unsigned int current_h;
    unsigned int current_pad;

    w = det_width(size);
    tail(size, w, 0);
    straight_l(w, size);
    body(w, size, 1);
    if (size > 1)
        body(w, size, size);
    straight_l(w, size);
    tail(size, w, size - 1);
}

int main(int argc, char** argv) 
{
    star(atoi(argv[1]));
}

