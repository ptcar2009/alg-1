#if !defined(NODE_H_ALG1)
#define NODE_H_ALG1

/**
 * @brief Struct representing a node in the game board.
 * 
 */
struct node
{
    /**
     * @brief Construct a new node object   
     * 
     * @param _dist number of that were spent to get here
     * @param _max_dist maximum manhattan distance that can be travelled from the node
     * @param _prev previous node in the chain
     */
    node(int _dist, int _max_dist, node *_prev);
    /**
     * @brief Construct a new node object with non conflicting values.
     * 
     * 
     */
    node();

    /**
     * @brief Previous node in the chain.
     * 
     */
    node *prev;

    /**
     * @brief Distance (in jumps) from the beggining of the chain.
     * 
     */
    int dist;

    /**
     * @brief Maximum manhattan distance that can be travelled from 
     * the node.
     * 
     */
    int max_dist;

    /**
     * @brief Player which got to the node.
     * 
     */
    int player;
};

#endif // NODE_H_ALG1
