#include "node.h"

// node is a structure
node::node(int _dist, int _max_dist, node *_prev)
    : dist(_dist), max_dist(_max_dist), prev(_prev)
{
}

node::node() : dist{-1}, max_dist{0}, prev{}, player{-1}
{
}