#ifndef MY_DYNAMIC_BITSET_HPP
#define MY_DYNAMIC_BITSET_HPP

#include <boost/dynamic_bitset.hpp>

template <typename Block, typename Allocator>
class my_dynamic_bitset : public boost::dynamic_bitset<Block, Allocator>
{
        using boost::dynamic_bitset<Block, Allocator>::dynamic_bitset;
        using size_type = typename boost::dynamic_bitset<Block, Allocator>::size_type;

    public:
        void crop(size_type first, size_type last);
        void reverse();
};

template <typename Block = unsigned long,
          typename Allocator = std::allocator<Block>>
class my_dynamic_bitset;

template <typename Block, typename Allocator>
void my_dynamic_bitset<Block, Allocator>::crop(size_type first, size_type last)
{
    ((*this <<= this->size() - last) >>= this->size() - first).resize(last - first);
}

template <typename Block, typename Allocator>
void my_dynamic_bitset<Block, Allocator>::reverse()
{
    size_type i = 0, j = this->size() - 1;
    while (i < j) {
        std::swap((*this)[i], (*this)[j]);
        ++i;
        --j;
    }
}

#endif // MY_DYNAMIC_BITSET_HPP
