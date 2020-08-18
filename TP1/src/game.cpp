#include "game.hpp"
#include <fstream>
#include <iostream>
#define min(x, y) x > y ? y : x
#define max(x, y) x > y ? x : y

AccessibleFrom::reference AccessibleFrom::operator*()
{
    return value;
}

AccessibleFrom::pointer AccessibleFrom::operator->() { return &value; }

AccessibleFrom::AccessibleFrom(int _i, int _j, node **_board, int X, int Y) : i(_i),
                                                                              j(_j),
                                                                              done(false),
                                                                              board(_board)

{
    max_dist = board[i][j].max_dist;
    x_upper_limit = min(max_dist, X - i - 1);

    current_x = max(-max_dist, -i);
    y_upper_limit = min(max_dist, Y - j - 1);
    y_lower_limit = current_y = max(-max_dist, -j);
    ++*this;
}

AccessibleFrom &AccessibleFrom::operator++()
{
    for (; current_x <= x_upper_limit; current_x++, current_y = y_lower_limit)
    {
        for (; current_y <= y_upper_limit; current_y++)
        {
            int absolute_sum = abs(current_x) + abs(current_y);
            // if the sum of the movements is bigger than the radius,
            // skip the current movement
            if (absolute_sum > max_dist)
                continue;
            // the movement is valid if it has the same parity as the
            // maximum distance, otherwise the square is unreachable
            if (absolute_sum % 2 == max_dist % 2)
            {
                value = {i + current_x, j + current_y};
                current_y++;
                return *this;
            }
        }
    }
    done = true;
    return *this;
}

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

    file >> X;
    file >> Y;
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
    auto &fin = board[X - 1][Y - 1];
    while (!edge.empty())
    {
        // getting the top priority node's address
        auto current_address = edge.front();
        // removing it from the 'to be explored' list
        edge.pop();

        // getting the node itself
        auto &current_node = board[current_address.first][current_address.second];
        // if (fin.dist != -1 && fin.dist == current_node.dist)
        // {
        //     break;
        // }

        // for each node accessible from the current node
        for (auto address = AccessibleFrom(
                 current_address.first,
                 current_address.second,
                 board,
                 X,
                 Y);
             bool(address); ++address)
        {

            auto &nd = board[address->first][address->second];

            // if the reachable node has never been seen or if the priority of the node that got to
            // it is lesser than the priority of the current node (this priority is
            // given by the maximum distance that can be travelled from the node, in reverse)
            if (nd.dist == -1 || (nd.dist > current_node.dist && nd.prev->max_dist > current_node.max_dist))
            {

                if (nd.dist == -1)
                {
                    // if the node hasn't been explored, explore it
                    edge.push(*address);
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
    return {board[X - 1][Y - 1].player + 'A', board[X - 1][Y - 1].dist};
}

Game::~Game()
{
    for (size_t i = 0; i < X; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}

void Game::read_board(std::ifstream &file)
{
    if (X <= 0 || Y <= 0)
    {
        throw BoardSizeException();
    }
    board = new node *[X];
    for (size_t i = 0; i < X; i++)
    {
        board[i] = new node[Y];
    }

    for (size_t i = 0; i < X; i++)
    {
        for (size_t j = 0; j < Y; j++)
        {
            board[i][j].dist = -1;
            file >> board[i][j].max_dist;
            board[i][j].prev = NULL;
        }
    }
}
