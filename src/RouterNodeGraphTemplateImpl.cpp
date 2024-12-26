#include "data_structure/Graph.cpp"
#include "data_structure/ConcurrentHashmap.cpp"
#include "RouterContainer.h"

template<>
uint32_t ConcurrentHashCompute(const RouterNode& key) {
    return std::hash<RouterNode>()(key);
}
template class Graph<RouterNode, uint16_t>;
template class ConcurrentHashmap<RouterNode,uint16_t>;
template class ConcurrentHashmap<RouterNode, ConcurrentHashmap<RouterNode,uint16_t>*>;