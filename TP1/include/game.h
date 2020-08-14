#if !defined(GAME_H_ALG1)
#define GAME_H_ALG1
#include "node.h"
#include <fstream>
#include <tuple>
#include <queue>
#include <vector>

/**
 * @brief Exception for bad board sizes.
 * 
 */
struct BoardSizeException : public std::exception
{
    const char *what() const throw()
    {
        return "invalid board size";
    }
};

/**
 * @brief Exception for when the file doesn't exist.
 * 
 */
struct FileNotFoundException : public std::exception
{
    char *file;
    FileNotFoundException(char *filename)
    {
        file = filename;
    }
    const char *what() const throw()
    {
        return file;
    }
};

/**
 * @brief Represents a game described in the "description.pdf" file.
 * 
 */
class Game
{
private:
    /**
     * @brief represents the board on which the game will be played.
     * 
     */
    node **board;

    /**
     * @brief Width of the board.
     * 
     */
    int n;

    /**
     * @brief Height of the board
     * 
     */
    int m;

    /**
     * @brief reads a game board from a file.
     * 
     * @param file stream from which the board will be read.
     */
    void read_board(std::ifstream &file);

    /**
     * @brief Priority queue that represents the currently unexpanded
     * but up for expantion nodes. The construction represents the number
     * of steps taken to get to the given node as the first part and the coordinates
     * of the second node in the second.
     * This construction makes sure the nodes are ordered in a way that every
     * node that had to be explored in a given play has been explored.
     * 
     */
    std::priority_queue<std::pair<int, std::pair<int, int>>> edge;

    /**
     * @brief Gets the nodes that are accessible from a given board
     * coordinate. The accessible are determined by the position and
     * number of moves (in manhattan coordinates) that can be made from
     * the given square.
     * 
     * @param i the 'y' coordinate
     * @param j the 'x' coordinate
     * @return std::vector<std::pair<int, int>> Vector containing coordinates for all nodes
     * accessible from the node in the coordinate (i, j) of the board. 
     */
    std::vector<std::pair<int, int>> accessible_from(int i, int j);

public:
    /**
     * @brief Construct a new Game object
     * 
     * @param filepath path of the file from which the game will be built.
     */
    Game(char *filepath);

    /**
     * @brief Plays the game that was initialized in the constructor.
     * 
     * @return std::pair<char, int> A pair with the winning player and the
     * number of rounds it took for the player to win.
     */
    std::pair<char, int> Play();
    ~Game();
};

#endif // GAME_H_ALG1
