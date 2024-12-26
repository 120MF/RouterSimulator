#include "data_structure/Graph.cpp"
#include "data_structure/ConcurrentHashmap.cpp"
#include "data_structure/Hashmap.cpp"
#include "RouterContainer.h"

template class Graph<std::shared_ptr<RouterNode>, uint16_t>;
template class ConcurrentHashmap<std::shared_ptr<RouterNode>,uint16_t>;
template class ConcurrentHashmap<std::shared_ptr<RouterNode>, ConcurrentHashmap<std::shared_ptr<RouterNode>,uint16_t>*>;
template class Hashmap<Glib::ustring, std::shared_ptr<RouterNode>>;