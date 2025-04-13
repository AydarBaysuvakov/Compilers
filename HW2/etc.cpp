#include <iostream>
#include <cmath>
#include "etc.hpp"

using namespace etc;

//--------------------------- Tensor ------------------------------------------------------------------

Tensor::Tensor(int n, int c, int h, int w) : N(n), C(c), H(h), W(w), data(n * c * h * w) 
    { std::fill(data.begin(), data.end(), 0); }

Tensor::Tensor(int n, int c, int h, int w, const std::vector<float>& input_data) : N(n), C(c), H(h), W(w), data(input_data) {
    if (input_data.size() != n * c * h * w) {
        data.resize(n * c * h * w);
        std::cout << "Wrong input data size (extra elementss may be deleted)" << std::endl;
    }
}

Tensor::Tensor(const std::vector<int>& shape) {
    if (shape.size() != 4) {
        throw std::invalid_argument("Wrong input data shape.");
    } else {
        N = shape[0]; C = shape[1]; H = shape[2]; W = shape[3];
        data.resize(N * C * H * W);
        std::fill(data.begin(), data.end(), 0);
    }
}

Tensor::Tensor(const std::vector<int>& shape, const std::vector<float>& input_data) {
    if (shape.size() != 4) {
        throw std::invalid_argument("Wrong input data shape.");
    } else {
        N = shape[0]; C = shape[1]; H = shape[2]; W = shape[3];
        data = input_data;
        if (input_data.size() != N * C * H * W) {
            data.resize(N * C * H * W);
            std::cout << "Wrong input data size (extra elementss may be deleted)" << std::endl;
        }
    }
}

float& Tensor::operator()(int n, int c, int h, int w) {
    if (is_correct(n, c, h, w)) return data[get_index(n, c, h, w)];
    else throw std::out_of_range("Tensor index out of range.");;
}

const float& Tensor::operator()(int n, int c, int h, int w) const {
    if (is_correct(n, c, h, w)) return data[get_index(n, c, h, w)];
    else throw std::out_of_range("Tensor index out of range.");;
}

float& Tensor::operator()(int index) {
    if (index < data.size()) return data[index];
    else throw std::out_of_range("Tensor index out of range.");;
}

const float& Tensor::operator()(int index) const {
    if (index < data.size()) return data[index];
    else throw std::out_of_range("Tensor index out of range.");;
}

void Tensor::print() const {
    std::cout << "Tensor (N=" << N << ", C=" << C << ", H=" << H << ", W=" << W << ")" << std::endl;
    for (int n = 0; n < N; ++n) {
        std::cout << "Batch " << n << ":" << std::endl;
        for (int c = 0; c < C; ++c) {
            std::cout << "  Channel " << c << ":" << std::endl;
            for (int h = 0; h < H; ++h) {
                std::cout << "    ";
                for (int w = 0; w < W; ++w) {
                    std::cout << operator()(n, c, h, w) << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}

//--------------------------- Binary operations ------------------------------------------------------------------

void BinaryOperation::setArgs(const std::vector<INode*>& args) {
    if (args.size() != 2) {
        throw std::invalid_argument("Binary operation requires two argument.");
    }
    first  = std::shared_ptr<INode>(args[0]);
    second = std::shared_ptr<INode>(args[1]);
}

Tensor ScalarAddOperation::evaluate() const {
    Tensor tensor1 = first->evaluate();
    Tensor tensor2 = second->evaluate();

    if (tensor1.get_shape() != tensor2.get_shape()) {
        throw std::runtime_error("ScalarAddOperation: Input tensors must have the same shape.");
    }

    Tensor result(tensor1.get_shape());
    for (size_t i = 0; i < tensor1.get_data().size(); ++i) {
        result(i) = tensor1(i) + tensor2(i);
    }

    return result;
}

Tensor ScalarSubOperation::evaluate() const {
    Tensor tensor1 = first->evaluate();
    Tensor tensor2 = second->evaluate();

    if (tensor1.get_shape() != tensor2.get_shape()) {
        throw std::runtime_error("ScalarAddOperation: Input tensors must have the same shape.");
    }

    Tensor result(tensor1.get_shape());
    for (size_t i = 0; i < tensor1.get_data().size(); ++i) {
        result(i) = tensor1(i) - tensor2(i);
    }

    return result;
}

Tensor ScalarMulOperation::evaluate() const {
    Tensor tensor = first->evaluate();

    Tensor result(tensor.get_shape());
    for (size_t i = 0; i < tensor.get_data().size(); ++i) {
        result(i) = tensor(i) * coeff;
    }

    return result;
}

Tensor MatMulOperation::evaluate() const {
    Tensor tensor1 = first->evaluate();
    Tensor tensor2 = second->evaluate();

    if (tensor1.get_W() != tensor2.get_H()) {
        throw std::runtime_error("MatMulOperation: Incompatible matrix dimensions for multiplication.");
    }

    int N = tensor1.get_N();
    int C = tensor1.get_C();
    int H = tensor1.get_H();
    int X = tensor1.get_W();
    int W = tensor2.get_W();

    Tensor result(N, C, H, W);

    for (int n = 0; n < N; n++) {
        for (int c = 0; c < C; c++) {
            for (int i = 0; i < H; ++i) {
                for (int j = 0; j < W; ++j) {
                    int sum = 0;
                    for (int k = 0; k < X; ++k) {
                        sum += tensor1(n, c, i, k) * tensor2(n, c, k, j);
                    }
                    result(n, c, i, j) = sum;
                }
            }
        }
    }

    return result;
}

Tensor ConvolOperation::evaluate() const {
    Tensor input  = first->evaluate();
    Tensor kernel = second->evaluate();

    int N = input.get_N();
    int C = input.get_C();
    int H = input.get_H();
    int W = input.get_W();

    int KN = kernel.get_N();
    int KC = kernel.get_C();
    int KH = kernel.get_H();
    int KW = kernel.get_W();

    if (N != KN) {
        throw std::runtime_error("Input and kernel batches not match");
    }

    int output_C = C - KC + 1;
    int output_H = H - KH + 1;
    int output_W = W - KW + 1;

    Tensor result(N, output_C, output_H, output_W);

    for (int n = 0; n < N; ++n) {
        for (int oc = 0; oc < output_C; ++oc) {
            for (int oh = 0; oh < output_H; ++oh) {
                for (int ow = 0; ow < output_W; ++ow) {
                    float sum = 0.0f;
                    for (int kc = 0; kc < C; ++kc) {
                        for (int kh = 0; kh < KH; ++kh) {
                            for (int kw = 0; kw < KW; ++kw) {
                                sum += input(n, oc + kc, oh + kh, ow + kw) * kernel(n, kc, kh, kw);
                            }
                        }
                    }
                    result(n, oc, oh, ow) = sum;
                }
            }
        }
    }

    return result;
}

//--------------------------- Unary operations ------------------------------------------------------------------

void UnaryOperation::setArgs(const std::vector<INode*>& args) {
    if (args.size() != 1) {
        throw std::invalid_argument("Unary operation requires exactly one argument.");
    }
    arg = std::shared_ptr<INode>(args[0]);
}

Tensor ReLUOperation::evaluate() const {
    Tensor tensor = arg->evaluate();
    Tensor result(tensor.get_shape());
    for (size_t i = 0; i < tensor.get_data().size(); ++i) {
        result(i) = std::max(0.0f, tensor(i));
    }
    return result;
}

Tensor SoftmaxOperation::evaluate() const {
    Tensor tensor = arg->evaluate();
    Tensor result(tensor.get_shape());

    for (int n = 0; n < tensor.get_N(); ++n) {
        for (int h = 0; h < tensor.get_H(); ++h) {
            for (int w = 0; w < tensor.get_W(); ++w) {
                float sum_exp = 0;
                for (int i = 0; i < tensor.get_C(); ++i) {
                    sum_exp += tensor(n, i, h, w);
                }

                for (int i = 0; i < tensor.get_C(); ++i) {
                    result(n, i, h, w) = tensor(n, i, h, w) / sum_exp;
                }
            }
        }
    }

    return result;
}

//--------------------------- NewralNetwork ------------------------------------------------------------------


std::shared_ptr<IOperation> NeuralNetwork::addOp(std::shared_ptr<IOperation> op) {
    operations.push_back(op);
    return op;
}

Tensor NeuralNetwork::infer() {
    Tensor result;
    for (const auto& op : operations) {
        result = op->evaluate();
    }
    return result;
}
