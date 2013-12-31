#include "Array2D.h"
#include "WordsearchExceptions.h"

template <typename T>
Array2D<T>::Array2D(unsigned width, unsigned height) : width_(width),
                                                       height_(height),
                                                       data_(new T[width * height])
{
}

template <typename T>
Array2D<T>::Array2D(Array2D<T> const& copy) : width_(copy.width_),
                                              height_(copy.height_)
{
    delete[] data_;
    data_(new T[width_ * height_]);

    if (copy.data)
    {
        for (unsigned i=0; i < width_ * height_; ++i)
            data_[i] = copy.data_[i];
    }
}

template <typename T>
Array2D<T>::~Array2D()
{
    delete[] data_;
}

template <typename T>
T& Array2D<T>::operator() (unsigned x, unsigned y)
{
    if (inRange(x, y))
        return data_[x + y * width_];
    else
        throw OutOfRange();
}

template <typename T>
T const& Array2D<T>::operator() (unsigned x, unsigned y) const
{
    if (inRange(x, y))
        return data_[x + y * width_];
    else
        throw OutOfRange();
}

template <typename T>
bool Array2D<T>::inRange(unsigned x, unsigned y) const
{
    return (x < width_ && y < height_);
}
