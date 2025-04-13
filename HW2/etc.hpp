#include <vector>
#include <memory>

namespace etc {

class Tensor {
    int N, C, H, W;
    std::vector<float> data;

public:
    Tensor() = default;
    Tensor(int n, int c, int h, int w);
    Tensor(int n, int c, int h, int w, const std::vector<float>& input_data);
    Tensor(const std::vector<int>& shape);
    Tensor(const std::vector<int>& shape, const std::vector<float>& input_data);

    int get_N() const { return N; }
    int get_C() const { return C; }
    int get_H() const { return H; }
    int get_W() const { return W; }
    std::vector<int> get_shape() const { return {N, C, H, W}; }

    float& operator()(int n, int c, int h, int w);
    const float& operator()(int n, int c, int h, int w) const;
    float& operator()(int index);
    const float& operator()(int index) const;

    const std::vector<float>& get_data() const { return data; }
    std::vector<float>& get_data() { return data; }
    void print() const;

private:
    int get_index(int n, int c, int h, int w) const 
        { return n * C * H * W + c * H * W + h * W + w; }

    bool is_correct(int n, int c, int h, int w) const 
        { return (n >= 0 || n < N || c >= 0 || c < C || h >= 0 || h < H || w >= 0 || w < W); }
};

class INode {
public:
    virtual ~INode() = default;
    virtual Tensor evaluate() const = 0;
};

class InputData : public INode {
    Tensor tensor;

public:
    InputData(const Tensor& tensor_) : tensor(tensor_) {};

    Tensor evaluate() const override { return tensor; }
};

class IOperation : public INode {
public:
    virtual ~IOperation() = default;
    virtual void setArgs(const std::vector<INode*>& args) = 0;
    virtual const std::vector<INode*>& getArgs() const = 0;
};


class BinaryOperation : public IOperation {
protected:
    std::shared_ptr<INode> first;
    std::shared_ptr<INode> second;
    std::vector<INode*> args;

public:
    BinaryOperation(const std::shared_ptr<INode> first_, const Tensor& second_) : first(first_) 
        { second = std::make_shared<InputData>(second_); }
    BinaryOperation(const std::shared_ptr<INode> first_, const std::shared_ptr<INode> second_)  : first(first_), second(second_) {}
    BinaryOperation(const std::shared_ptr<INode> first_)  : first(first_) { second = nullptr; }

    void setArgs(const std::vector<INode*>& args) override;
    const std::vector<INode*>& getArgs() const override { return args; }
};

class ScalarAddOperation : public BinaryOperation {
public:
    ScalarAddOperation(const std::shared_ptr<INode> first, const Tensor& second) : BinaryOperation(first, second) {}
    ScalarAddOperation(const std::shared_ptr<INode> first, const std::shared_ptr<INode> second) : BinaryOperation(first, second) {}

    Tensor evaluate() const override ;
};

class ScalarSubOperation : public BinaryOperation {
public:
    ScalarSubOperation(const std::shared_ptr<INode> first, const Tensor& second) : BinaryOperation(first, second) {}
    ScalarSubOperation(const std::shared_ptr<INode> first, const std::shared_ptr<INode> second) : BinaryOperation(first, second) {}

    Tensor evaluate() const override ;
};

class ScalarMulOperation : public BinaryOperation {
    float coeff;
public:
    ScalarMulOperation(const std::shared_ptr<INode> tensor, const float coeff) : BinaryOperation(tensor), coeff(coeff) {}

    Tensor evaluate() const override ;
};

class MatMulOperation    : public BinaryOperation {
public:
    MatMulOperation(const std::shared_ptr<INode> left, const std::shared_ptr<INode> right) : BinaryOperation(left, right) {}

    Tensor evaluate() const override;
};

class ConvolOperation    : public BinaryOperation {
public:
    ConvolOperation(const std::shared_ptr<INode> first, const Tensor& second) : BinaryOperation(first, second) {}
    ConvolOperation(const std::shared_ptr<INode> input, const std::shared_ptr<INode> kernel) : BinaryOperation(input, kernel) {}

    Tensor evaluate() const override;
};

class UnaryOperation : public IOperation {
protected:
    std::shared_ptr<INode> arg;
    std::vector<INode*> args;

public:
    UnaryOperation(const std::shared_ptr<INode> arg_) : arg(arg_) {}

    void setArgs(const std::vector<INode*>& args) override ;
    const std::vector<INode*>& getArgs() const override { return args; }
};

class ReLUOperation      : public UnaryOperation {
public:
    ReLUOperation(const std::shared_ptr<INode> arg) : UnaryOperation(arg) {}

    Tensor evaluate() const override ;
};

class SoftmaxOperation   : public UnaryOperation {
public:
    SoftmaxOperation(const std::shared_ptr<INode> arg) : UnaryOperation(arg) {}

    Tensor evaluate() const override ;
};

class NeuralNetwork {
    std::vector<std::shared_ptr<IOperation>> operations;

public:
    std::shared_ptr<IOperation> addOp(std::shared_ptr<IOperation> op);
    Tensor infer();
};

}