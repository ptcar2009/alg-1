#include "game.hpp"
#include <fstream>
#include <iostream>

Game::Game(char *filepath)
{
    // Initializing the priority queue for nodes on the 'edge', as described
    // in the report.
    edge = std::queue<std::pair<int, int>>();

    std::ifstream file;
    try
    {
        file.open(filepath);
    }
    catch (const std::exception &e)
    {
        throw FileNotFoundException(filepath);
    }

    file >> m;
    file >> n;
    int n_players;
    file >> n_players;

    // reading the board and initializing the board's values
    read_board(file);

    // setting the spots where the players start and adding them to the edge
    for (size_t i = 0; i < n_players; i++)
    {
        int x, y;
        file >> x;
        file >> y;
        board[x][y].player = i;
        board[x][y].dist = 0;
        edge.push({x, y});
    }

    file.close();
}

std::pair<char, int> Game::Play()
{
    // while there are still nodes to be explored
    while (!edge.empty() /* && board[n - 1][m - 1].dist == -1 */)
    {
        // getting the top priority node's address
        auto current_address = edge.front();
        // removing it from the 'to be explored' list
        edge.pop();

        // getting the node itself
        auto current_node = board[current_address.first][current_address.second];

        // for each node accessible from the current node
        for (auto address : accessible_from(current_address.first, current_address.second))
        {

            auto &nd = board[address.first][address.second];

            // if the reachable node has never been seen or if the priority of the node that got to
            // it is lesser than the priority of the current node (this priority is)
            // given by the maximum distance that can be travelled from the node, in reverse)
            if (nd.dist == -1 || (nd.dist > current_node.dist && nd.prev->max_dist > current_node.max_dist))
            {

                if (nd.dist == -1)
                {
                    // if the node hasn't been explored, explore it
                    edge.push(address);
                }

                // update the node in relation to the current node
                nd.dist = current_node.dist + 1;
                nd.player = current_node.player;
                nd.prev = &current_node;
            }
        }
    }
    // when there's no more nodes to be explored, either the solution has been
    // reached, or the solution is unreachable. if the solution is unreachable,
    // then the target node will have distance -1, if it is reachable, the target
    // node will have another distance and the player that reached it first.
    return {board[n - 1][m - 1].player + 'A', board[n - 1][m - 1].dist};
}

Game::~Game()
{
    for (size_t i = 0; i < n; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}

void Game::read_board(std::ifstream &file)
{
    if (n < 0 || m < 0)
    {
        throw BoardSizeException();
    }
    board = new node *[n];
    for (size_t i = 0; i < n; i++)
    {
        board[i] = new node[m];
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            board[i][j].dist = -1;
            file >> board[i][j].max_dist;
            board[i][j].prev = NULL;
        }
    }
}

std::vector<std::pair<int, int>> Game::accessible_from(int i, int j)
{
    auto max_dist = board[i][j].max_dist;
    auto ret = std::vector<std::pair<int, int>>();
    int x, y;

    // getting a manhattan radius for x and y in relation to the maximum
    // distance
    for (x = -max_dist; x <= max_dist; x++)
    {
        // if the current movement is out of bounds, skip it
        if (x + i < 0 || x + i >= n)
            continue;
        for (y = -max_dist; y <= max_dist; y++)
        {
            if (y + j < 0 || y + j >= m)
                continue;
            // if the sum of the movements is bigger than the radius,
            // skip the current movement
            if (abs(x) + abs(y) > max_dist)
                continue;
            // the movement is valid if it has the same parity as the
            // maximum distance, otherwise the square is unreachable
            if (abs(x) + abs(y) % 2 == max_dist % 2)
            {
                ret.push_back({i + x, j + y});
            }
        }
    }
    return ret;
}