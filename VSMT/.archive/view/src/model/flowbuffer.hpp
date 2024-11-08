#ifndef FLOWBUFFER_HPP
#define FLOWBUFFER_HPP

#include <array>
#include <cstddef>
#include "dataprovider.hpp"
using datamodels::DataProvider;

template <size_t N>
class FlowBuffer
{
public:
    FlowBuffer();
    double operator[](size_t index) const;

    void push(double value);
    constexpr size_t size() const { return N; }
private:
    std::array<double,N> container;
    size_t offset;
};

template<size_t N>
inline FlowBuffer<N>::FlowBuffer():
    container{0},offset(0) {}

template<size_t N>
inline void FlowBuffer<N>::push(double value)
{
    container[offset] = value;
    offset = (offset+1)%N;
}

template<size_t N>
inline double FlowBuffer<N>::operator[](size_t index) const
{
    return container[(index+offset)%N];
}

#endif // FLOWBUFFER_HPP
