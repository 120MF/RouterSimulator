#include "data_structure/Graph.cpp"
#include "data_structure/ConcurrentHashmap.cpp"
#include "RouterContainer.h"

template<>
uint32_t ConcurrentHashCompute(const std::shared_ptr<RouterNode>& key) {
    return std::hash<RouterNode>()(*key);
}
template class Graph<std::shared_ptr<RouterNode>, uint16_t>;
template class ConcurrentHashmap<std::shared_ptr<RouterNode>,uint16_t>;
template class ConcurrentHashmap<std::shared_ptr<RouterNode>, ConcurrentHashmap<std::shared_ptr<RouterNode>,uint16_t>*>;