#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <cstdlib>

template <typename T>
class Array2D
{
public:
    Array2D(unsigned, unsigned);
    Array2D(const Array2D&);
    ~Array2D();

    T& operator() (unsigned, unsigned);
    T const& operator() (unsigned, unsigned) const;

    bool inRange(unsigned, unsigned) const;

    unsigned getWidth() const { return width_; }
    unsigned getHeight() const { return height_; }

private:
    unsigned width_;
    unsigned height_;
    T* data_;
};

#endif
