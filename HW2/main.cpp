#include "etc.hpp"

using namespace etc;

int main() {
    NeuralNetwork nn;

    Tensor input({1, 1, 4, 4}, {1, 0, -2, 1, -1, 0, 1, 2, 0, 2, 1, 0, 1, 0, 0, 1});
    Tensor weight({1, 1, 2, 2}, {0, 1, -1, 2});

    const auto& input_data = std::make_shared<InputData>(input);

    //const auto& add = nn.addOp(std::make_shared<ScalarAddOperation>(input_data, weight));
    //const auto& mul = nn.addOp(std::make_shared<ScalarMulOperation>(add, 3));
    nn.addOp(std::make_shared<ConvolOperation>(input_data, weight));
    const auto& output = nn.infer();
    output.print();
}
