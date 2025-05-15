#include <iostream>
#include <vector>
#include <span>
#include <assert.h>
#include <array>

template <int N>
class Adjacencymatrix {

public:
    struct Edge {
        int from{};
        int to{};
        int weight{};
    };
 
    Adjacencymatrix(std::array<Edge, N>& array)
    :   adjmtrx_( std::vector<std::vector<int>>(N, std::vector<int>(N)) )
    {
        for (int i{}; i < N; i++)
        {
            int x = array[i].from;
            int y = array[i].to;
            int w = array[i].weight;

            assert(w >= 0 && "Weight must be positive");

            adjmtrx_[x][y] = w;
            adjmtrx_[y][x] = -w;
        }
    }

    std::vector<int>& operator[](size_t i) noexcept { return adjmtrx_[i]; }

    friend std::ostream& operator<<(std::ostream& out, Adjacencymatrix& me) {
        for (const auto& ver : me.adjmtrx_)
        {
            for (const auto val : ver)
                out << val << ' ';

            out << '\n';
        }

        return out;
    }

private:
    std::vector<std::vector<int>> adjmtrx_;
};

int main(void) {

    std::array<Adjacencymatrix<5>::Edge, 5> array = { {
        { 1, 2, 3},
        { 3, 4, 3},
        { 3, 4, 3},
        { 2, 1, 3},
        { 2, 4, 3},
    } }; 

    Adjacencymatrix<5> matrix(array);

    std::cout << matrix;

    return 0;
}