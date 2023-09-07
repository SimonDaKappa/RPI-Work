#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <cassert>
#include <list>

#include "tile.h"
#include "location.h"
#include "board.h"

// this global variable is set in main.cpp and is adjustable from the command line
// (you are not allowed to make your own global variables)
int GLOBAL_TILE_SIZE = 11;

// ==========================================================================
// Helper function that is called when an error in the command line
// arguments is detected.
void usage(int /*argc*/, char *argv[])
{
    std::cerr << "USAGE: " << std::endl;
    std::cerr << "  " << argv[0] << " <filename>  --board_dimensions <h> <w>" << std::endl;
    std::cerr << "  " << argv[0] << " <filename>  --board_dimensions <h> <w>  --all_solutions" << std::endl;
    std::cerr << "  " << argv[0] << " <filename>  --board_dimensions <h> <w>  --allow_rotations" << std::endl;
    std::cerr << "  " << argv[0] << " <filename>  --all_solutions  --allow_rotations" << std::endl;
    std::cerr << "  " << argv[0] << " <filename>  --tile_size <odd # >= 11>" << std::endl;
    exit(1);
}

// ==========================================================================
// To get you started, this function places tiles on the board and
// randomly and outputs the results (in all likelihood *not* a
// solution!) in the required format
void RandomlyPlaceTiles(Board &board, const std::vector<Tile *> &tiles,
                        std::vector<Location> &locations)
{

    for (unsigned int t = 0; t < tiles.size(); t++)
    {
        // loop generates random locations until we (eventually) find one
        // that is not occupied
        int i, j;
        do
        {
            // generate a random coordinate within the range 0,0 -> rows-1,cols-1
            i = std::rand() % (board.numRows() - 1);
            j = std::rand() % (board.numColumns() - 1);
        } while (board.getTile(i, j) != NULL);

        // rotation is always 0 (for now)
        locations.push_back(Location(i, j, 0));
        board.setTile(i, j, tiles[t]);
    }
}

// ==========================================================================
void HandleCommandLineArguments(int argc, char *argv[], std::string &filename,
                                int &rows, int &columns, bool &all_solutions, bool &allow_rotations)
{

    // must at least put the filename on the command line
    if (argc < 2)
    {
        usage(argc, argv);
    }
    filename = argv[1];

    // parse the optional arguments
    for (int i = 2; i < argc; i++)
    {
        if (argv[i] == std::string("--tile_size"))
        {
            i++;
            assert(i < argc);
            GLOBAL_TILE_SIZE = atoi(argv[i]);
            if (GLOBAL_TILE_SIZE < 11 || GLOBAL_TILE_SIZE % 2 == 0)
            {
                std::cerr << "ERROR: bad tile_size" << std::endl;
                usage(argc, argv);
            }
        }
        else if (argv[i] == std::string("--all_solutions"))
        {
            all_solutions = true;
        }
        else if (argv[i] == std::string("--board_dimensions"))
        {
            i++;
            assert(i < argc);
            rows = atoi(argv[i]);
            i++;
            assert(i < argc);
            columns = atoi(argv[i]);
            if (rows < 1 || columns < 1)
            {
                usage(argc, argv);
            }
        }
        else if (argv[i] == std::string("--allow_rotations"))
        {
            allow_rotations = true;
        }
        else
        {
            std::cerr << "ERROR: unknown argument '" << argv[i] << "'" << std::endl;
            usage(argc, argv);
        }
    }
}

// ==========================================================================
void ParseInputFile(int argc, char *argv[], const std::string &filename, std::vector<Tile *> &tiles)
{

    // open the file
    std::ifstream istr(filename.c_str());
    if (!istr)
    {
        std::cerr << "ERROR: cannot open file '" << filename << "'" << std::endl;
        usage(argc, argv);
    }
    assert(istr);

    // read each line of the file
    std::string token, north, east, south, west;
    while (istr >> token >> north >> east >> south >> west)
    {
        assert(token == "tile");
        Tile *t = new Tile(north, east, south, west);
        tiles.push_back(t);
    }
}

bool canPlaceUp(Board &board, Tile *tile, int i, int j, bool &unplaceable)
{
    std::cout << "canPlaceUp called\n";
    if (i == 0)
    {
        unplaceable = true;
        return false;
    }
    else if (board.getTile(i - 1, j) != NULL)
    {
        unplaceable = true;
        return false;
    }
    else if (board.getTile(i, j)->getNorth() == tile->getSouth() &&
             tile->getSouth() != "pasture")
        return true;
    return false;
}

bool canPlaceRight(Board &board, Tile *tile, int i, int j, bool &unplaceable)
{
    std::cout << "canPlaceRight called\n";
    if (j == board.numColumns() - 1)
    {
        unplaceable = true;
        return false;
    }
    else if (board.getTile(i, j + 1) != NULL)
    {
        unplaceable = true;
        return false;
    }
    else if (board.getTile(i, j)->getEast() == tile->getWest() &&
             tile->getWest() != "pasture")
        return true;
    return false;
}

bool canPlaceDown(Board &board, Tile *tile, int i, int j, bool &unplaceable)
{
    std::cout << "canPlaceDown called\n";
    if (i == board.numRows() - 1)
    {
        unplaceable = true;
        return false;
    }
    if (board.getTile(i + 1, j) != NULL)
    {
        unplaceable = true;
        return false;
    }
    if (board.getTile(i, j)->getSouth() == tile->getNorth() &&
        tile->getNorth() != "pasture")
        return true;
    return false;
}

bool canPlaceLeft(Board &board, Tile *tile, int i, int j, bool &unplaceable)
{
    std::cout << "canPlaceLeft called\n";
    if (j == 0)
    {
        unplaceable = true;
        return false;
    }
    else if (board.getTile(i, j - 1) != NULL)
    {
        unplaceable = true;
        return false;
    }
    else if (board.getTile(i, j)->getWest() == tile->getEast() &&
             tile->getEast() != "pasture")
        return true;
    return false;
}

bool validSolution(Board &board)
{
    std::cout << "validSolution() called \n";
    for (int i = 0; i < board.numRows(); i++)
    {
        std::cout << i;
        for (int j = 0; j < board.numColumns(); j++)
        {
            std::cout << "(i,j) = (" << i << "," << j << ")\n";
            Tile *current = board.getTile(i, j);

            // Current Tile is blank
            if (current == NULL)
                continue;

            // Check Up
            if (i != 0)
            {
                std::cout << "checking up \n";
                bool notNULL = true;
                Tile *above = board.getTile(i - 1, j);
                // No Tile above
                if (above == NULL)
                {
                    notNULL = false;
                    if (current->getNorth() != "pasture")
                        return false;
                }
                // Tile above
                if (notNULL && above->getSouth() != current->getNorth())
                    return false;
            }

            // Check down
            if (i != board.numRows() - 1)
            {
                std::cout << "checking down \n";
                bool notNULL = true;
                Tile *below = board.getTile(i + 1, j);

                // No Tile Below
                if (below == NULL)
                {
                    notNULL = false;
                    if (current->getSouth() != "pasture")
                        return false;
                }
                // Tile below
                if (notNULL && below->getNorth() != current->getSouth())
                    return false;
            }

            // Check Left
            if (j != 0)
            {
                std::cout << "checking left \n";
                bool notNULL = true;
                Tile *left = board.getTile(i, j - 1);

                // No Tile to the left
                if (left == NULL)
                {
                    notNULL = false;
                    if (current->getWest() != "pasture")
                        return false;
                }
                // Tile to the left
                if (notNULL && left->getEast() != current->getWest())
                    return false;
            }

            // Check Right
            if (j != board.numColumns() - 1)
            {
                std::cout << "checking right\n";
                bool notNULL = true;
                Tile *right = board.getTile(i, j + 1);

                // No Tile to the right
                if (right == NULL)
                {
                    if (current->getEast() != "pasture")
                        return false;
                    notNULL = false;
                }
                // Tile to the right
                if (notNULL && right->getWest() != current->getEast())
                    return false;
            }

            // Pasture check on outer perimiter
            if (i == 0 && current->getNorth() != "pasture")
                return false;
            if (i == board.numRows() - 1 && current->getSouth() != "pasture")
                return false;
            if (j == 0 && current->getWest() != "pasture")
                return false;
            if (j == board.numColumns() && current->getEast() != "pasture")
                return false;
        }
    }
    // All checks passed
    std::cout << "VALID SOLUTION!!!!!\n";
    return true;
}

int place_tile(Board &board, bool allow_rotations,
               int index, int rotation,
               std::vector<Tile *> &tiles,
               std::list<Location> &locations)
{

    board.Print();
    // Score Counter
    int c = 0;

    //If valid solution
    //Solution Case Return 1
    if (locations.size() == tiles.size() && validSolution(board))
        return 1;

    //End of tile list and not solution
    if (locations.size() == tiles.size())
    {
        std::list<Location>::iterator itr = locations.end();
        --itr;
        board.Nullify(itr->row, itr->column);
        locations.pop_back();
        return 0;
    }

    //Current Tile trying to place
    Tile *tile = tiles[index];
    std::cout << "Current Tile: " << index << '\n';
    std::cout << *tile;

    //Trying to place current tile
    for (int i = 0; i < board.numRows(); i++)
    {
        for (int j = 0; j < board.numColumns(); j++)
        {
            bool unplaceable = false;

            //Check 4 Directions
            Tile *current = board.getTile(i, j);
            if (index == 0)
                std::cout << "\n\n First Tile / New Attempt  \n\n";
            std::cout << "(i,j) = (" << i << ',' << j << ")\n";
            std::cout << "Tile got at index " << index << "|\n";

            // Empty and not first Tile to be placed
            if (current == NULL && index != 0)
                continue;

            // First Tile to be placed
            if (index == 0)
            {

                board.setTile(i, j, tile);
                locations.push_back(Location(i, j, rotation));
                //board.Print();
                c = place_tile(board, allow_rotations, index + 1, 0, tiles, locations);
                if (c == 1)
                    return 1;
            }

            if (index != 0)
            {

                // UP CODE IN THIS SCOPE
                // =========================================================================
                //Reset unplaceable
                unplaceable = false;
                //Try to Place Up
                if (canPlaceUp(board, tile, i, j, unplaceable))
                {
                    //Set Tile
                    std::cout << "can place up\n";
                    //Add tile to board
                    board.setTile(i - 1, j, tile);
                    locations.push_back(Location(i - 1, j, rotation));
                    //Recursive Step
                    c = place_tile(board, allow_rotations, index + 1, 0, tiles, locations);
                }

                // RIGHT CODE IN THIS SCOPE
                // =========================================================================
                //Reset unplaceable
                unplaceable = false;
                //Try to place Right
                if (canPlaceRight(board, tile, i, j, unplaceable))
                {
                    std::cout << "can place right\n";
                    //Add tile to board
                    board.setTile(i, j + 1, tile);
                    locations.push_back(Location(i, j + 1, rotation));
                    //Recursive Step
                    c = place_tile(board, allow_rotations, index + 1, 0, tiles, locations);
                }

                // DOWN CODE IN THIS SCOPE
                // =========================================================================
                //Reset unplaceable
                unplaceable = false;
                //Try to place Down
                if (canPlaceDown(board, tile, i, j, unplaceable))
                {
                    std::cout << "can place down\n";
                    //Add tile to board
                    board.setTile(i + 1, j, tile);
                    locations.push_back(Location(i + 1, j, rotation));
                    //Recursive Step
                    c = place_tile(board, allow_rotations, index + 1, 0, tiles, locations);
                }

                // LEFT CODE IN THIS SCOPE
                // =========================================================================
                //Reset Unplaceeable
                unplaceable = false;
                //Try to place left
                if (canPlaceLeft(board, tile, i, j, unplaceable))
                {
                    std::cout << "can place left\n";
                    //Add tile to board
                    board.setTile(i, j - 1, tile);
                    locations.push_back(Location(i, j - 1, rotation));
                    //Recursive Step
                    c = place_tile(board, allow_rotations, index + 1, 0, tiles, locations);
                }

                //Used so that we only get one solution
                if (c == 1)
                    return 1;
            }
        }
    }

    std::cout << "Before cannot place\n";
    std::cout << "Index : " << index << '\n';
    // Current piece cannot be placed on board

    std::cout << "index != 0\n";
    std::list<Location>::iterator itr = locations.end();
    --itr;
    board.Nullify(itr->row, itr->column);
    locations.pop_back();

    return 0;
}

// ==========================================================================
int main(int argc, char *argv[])
{

    std::string filename;
    int rows = -1;
    int columns = -1;
    bool all_solutions = false;
    bool allow_rotations = false;
    HandleCommandLineArguments(argc, argv, filename, rows, columns, all_solutions, allow_rotations);
    std::cout << "Command Lines Handled\n";

    // load in the tiles
    std::vector<Tile *> tiles;
    ParseInputFile(argc, argv, filename, tiles);
    std::cout << "Input File Parsed\n";

    // confirm the specified board is large enough
    if (rows < 1 || columns < 1 || rows * columns < (int)tiles.size())
    {
        std::cerr << "ERROR: specified board is not large enough" << rows << "X" << columns << "=" << rows * columns << " " << tiles.size() << std::endl;
        usage(argc, argv);
    }

    Board board(rows, columns);
    std::list<Location> locations;
    int placed = place_tile(board, allow_rotations, 0, 0, tiles, locations);
    std::cout << "\n\n Final Board \n\n\n";
    board.Print();

    if (placed == 0)
        std::cout << "No Solutions\n";
    else
    {
        std::cout << "Solutions: " << placed << '\n';
        std::list<Location>::iterator itr = locations.begin();
        while (itr != locations.end())
        {
            std::cout << *itr;
            itr++;
        }
        std::cout << '\n';

        board.Print();
    }

    // delete the tiles
    for (unsigned int t = 0; t < tiles.size(); t++)
    {
        delete tiles[t];
    }
}
// ==========================================================================
