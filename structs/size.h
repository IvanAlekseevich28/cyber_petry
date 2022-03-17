#pragma once

struct TSize
{
    unsigned w;
    unsigned h;

    explicit TSize(unsigned w, unsigned h) :
        w(w), h(h) {}
    explicit TSize(unsigned s) :
        w(s), h(s) {}
};
