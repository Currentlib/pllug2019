#include <iostream>
#include <vector>
#include <memory>
#include <random>

class MazeGenerator
{
public:
    static std::shared_ptr<std::vector<std::vector<char>>> generate(unsigned width, unsigned height)
    {
        if ((width < 1) || (height < 1))
            return nullptr;

        const auto top_limit = std::numeric_limits<unsigned>::max();

        if (((top_limit - 1) / 2 <= width) || ((top_limit - 1) / 2 <= height))
            return nullptr;

        const unsigned output_height = height * 2 + 1;
        const unsigned output_width = width * 2 + 1;

        auto maze = std::make_shared<std::vector<std::vector<char>>>();

        maze.get()->reserve(output_height);


        for (unsigned i = 0; i < output_height; ++i)
        {
            std::vector<char> row;
            row.reserve(output_width);
            for (unsigned j = 0; j < output_width; ++j)

                if ((i % 2 == 1) && (j % 2 == 1))
                    row.push_back(' ');
                else

                    if (((i % 2 == 1) && (j % 2 == 0) && (j != 0) && (j != output_width - 1)) ||
                        ((j % 2 == 1) && (i % 2 == 0) && (i != 0) && (i != output_height - 1)))
                        row.push_back(' ');
                    else
                        row.push_back('#');
            maze.get()->push_back(std::move(row));
        }


        std::vector<unsigned> row_set;
        row_set.reserve(width);

        for (unsigned i = 0; i < width; ++i)
            row_set.push_back(0);
        unsigned set = 1;
        std::random_device rd;
        std::mt19937 mt(rd());

        std::uniform_int_distribution<int> dist(0, 2);

        for (unsigned i = 0; i < height; ++i)
        {
            for (unsigned j = 0; j < width; ++j)
                if (row_set[j] == 0)
                    row_set[j] = set++;


            for (unsigned j = 0; j < width - 1; ++j)
            {

                const auto right_wall = dist(mt);

                if ((right_wall == 1) || (row_set[j] == row_set[j + 1]))
                    maze.get()->at(i * 2 + 1).at(j * 2 + 2) = '#';
                else
                {

                    const auto changing_set = row_set[j + 1];
                    for (unsigned l = 0; l < width; ++l)
                        if (row_set[l] == changing_set)
                            row_set[l] = row_set[j];
                }
            }

            for (unsigned j = 0; j < width; ++j)
            {
                const auto bottom_wall = dist(mt);
                unsigned int count_current_set = 0;
                for (unsigned l = 0; l < width; ++l)
                    if (row_set[j] == row_set[l])
                        count_current_set++;
                if ((bottom_wall == 1) && (count_current_set != 1))
                    maze.get()->at(i * 2 + 2).at(j * 2 + 1) = '#';
            }

            if (i != height - 1)
            {

                for (unsigned j = 0; j < width; ++j) {
                    unsigned count_hole = 0;
                    for (unsigned l = 0; l < width; ++l)
                        if ((row_set[l] == row_set[j]) && (maze.get()->at(i * 2 + 2).at(l * 2 + 1) == ' '))
                            count_hole++;
                    if (count_hole == 0)
                        maze.get()->at(i * 2 + 2).at(j * 2 + 1) = ' ';
                }

                for (unsigned j = 0; j < width; ++j)
                    if (maze.get()->at(i * 2 + 2).at(j * 2 + 1) == '#')
                        row_set[j] = 0;
            }
        }
        for (unsigned int j = 0; j < width - 1; ++j)
        {
            if (row_set[j] != row_set[j + 1])
                maze.get()->at(output_height - 2).at(j * 2 + 2) = ' ';
        }
        return maze;
    }

    static void print(const std::shared_ptr<std::vector<std::vector<char>>>& maze)
    {
        if (maze == nullptr)
            return;

        for (unsigned i = 0; i < maze.get()->size(); ++i)
        {
            for (unsigned j = 0; j < maze.get()->at(0).size(); ++j)
                std::cout << maze.get()->at(i).at(j);
            std::cout << std::endl;
        }
    }


private:
    MazeGenerator() = default;
};
int main()
{
    std::shared_ptr<std::vector<std::vector<char>>> mg = MazeGenerator::generate(12,8);
    MazeGenerator::print(mg);
}