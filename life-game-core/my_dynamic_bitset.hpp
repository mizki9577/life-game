#ifndef MY_DYNAMIC_BITSET_HPP
#define MY_DYNAMIC_BITSET_HPP

#include <cstddef>
#include <boost/dynamic_bitset.hpp>

template <typename Block, typename Allocator>
class my_dynamic_bitset : public boost::dynamic_bitset<Block, Allocator>
{
        using boost::dynamic_bitset<Block, Allocator>::dynamic_bitset;
        using size_type = typename boost::dynamic_bitset<Block, Allocator>::size_type;

    public:
        my_dynamic_bitset<Block, Allocator> crop(size_type first, size_type last);
        my_dynamic_bitset<Block, Allocator> reverse();
        my_dynamic_bitset<Block, Allocator> copy_to(size_type first, size_type last,
                                                    my_dynamic_bitset<Block, Allocator>& dest, size_type result);
        my_dynamic_bitset<Block, Allocator> copy_to(my_dynamic_bitset<Block, Allocator>& dest, size_type result = 0);
};

template <typename Block = unsigned long,
          typename Allocator = std::allocator<Block>>
class my_dynamic_bitset;

template <typename Block, typename Allocator>
my_dynamic_bitset<Block, Allocator> my_dynamic_bitset<Block, Allocator>::crop(size_type first, size_type last)
{
    ((*this <<= this->size() - last) >>= this->size() - first).resize(last - first);
    return *this;
}

template <typename Block, typename Allocator>
my_dynamic_bitset<Block, Allocator> my_dynamic_bitset<Block, Allocator>::reverse()
{
    size_type i = 0, j = this->size() - 1;
    while (i < j) {
        std::swap((*this)[i], (*this)[j]);
        ++i;
        --j;
    }
    return *this;
}

template <typename Block, typename Allocator>
my_dynamic_bitset<Block, Allocator>
my_dynamic_bitset<Block, Allocator>::copy_to(size_type first, size_type last,
                                             my_dynamic_bitset<Block, Allocator>& dest, size_type result)
{
    while (first < last) {
        dest[result] = (*this)[first];
        ++first;
        ++result;
    }
    return *this;
}

template <typename Block, typename Allocator>
my_dynamic_bitset<Block, Allocator>
my_dynamic_bitset<Block, Allocator>::copy_to(my_dynamic_bitset<Block, Allocator>& dest, size_type result)
{
    return copy_to(0, this->size() - 1, dest, result);
}

#endif // MY_DYNAMIC_BITSET_HPP
