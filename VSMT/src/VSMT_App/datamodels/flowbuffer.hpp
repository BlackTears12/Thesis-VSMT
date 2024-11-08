#ifndef FLOWBUFFER_HPP
#define FLOWBUFFER_HPP

#include <array>
#include <cstddef>
#include <QObject>

namespace datamodels::flowbuffer
{

struct SignalHandler : public QObject
{
    Q_OBJECT
signals:
    void dataChanged();
};

template <typename T,size_t N>
class FlowBuffer
{
public:
    FlowBuffer();
    T operator[](size_t index) const;

    void push(double value);
    constexpr size_t size() const { return N; }
    SignalHandler signalHandler;
private:
    std::array<T,N> container;
    size_t offset;
};

template <typename T,size_t N>
inline FlowBuffer<T,N>::FlowBuffer():
    container{0},offset(0) {}

template <typename T,size_t N>
inline void FlowBuffer<T,N>::push(double value)
{
    container[offset] = value;
    offset = (offset+1)%N;
    emit signalHandler.dataChanged();
}

template <typename T,size_t N>
inline T FlowBuffer<T,N>::operator[](size_t index) const
{
    return container[(index+offset)%N];
}

}
#endif // FLOWBUFFER_HPP
