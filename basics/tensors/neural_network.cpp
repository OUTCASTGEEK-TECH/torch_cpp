//
// Created by outcastgeek on 4/26/20.
//

#include <iostream>
#include <torch/torch.h>

class Net: public torch::nn::Module {
public:
    Net()
    :
    // 1 input image channel, 6 output channels, 3x3 square convolution
    // kernel
    conv1(torch::nn::Conv2d(1, 6, 3)),
    conv2(torch::nn::Conv2d(6, 16, 3)),
    // an affine operation: y = Wx + b
    fc1(torch::nn::Linear(16 * 6 * 6, 120)),
    fc2(torch::nn::Linear(120, 84)),
    fc3(torch::nn::Linear(84, 10))
    {
        register_module("conv1", conv1);
        register_module("conv2", conv2);
        register_module("fc1", fc1);
        register_module("fc2", fc2);
        register_module("fc3", fc3);
    }

    torch::Tensor forward(torch::Tensor x) {
        namespace F = torch::nn::functional;
        // Max pooling over a (2, 2) window
        x = F::max_pool2d(F::relu(conv1(x)), F::MaxPool2dFuncOptions({2, 2}));
        // If the size is a square you can only specify a single number
        x = F::max_pool2d(F::relu(conv2(x)), F::MaxPool2dFuncOptions(2));
//        std::cout << "\ncurrent x => \n" << x << std::endl;
        x = x.view({-1, num_flat_features(x)});
        x = F::relu(fc1(x));
        x = F::relu(fc2(x));
        x = fc3(x);
        return x;
    }

    torch::nn::Conv2d conv1, conv2;
    torch::nn::Linear fc1, fc2, fc3;

private:
    long num_flat_features(torch::Tensor x) {
        // x.size()[1:]  # all dimensions except the batch dimension
        auto size = x.sizes(); // TODO: Revisit this
        auto num_features = 1;
        for (auto s : size) {
            num_features *= s;
        }
        return num_features;
    }
};

int main() {
    Net net;
    std::cout << "\nnet => \n" << net << std::endl;

    auto params = net.parameters();
    std::cout << "\nlen(params) => \n" << params.size() << std::endl;
    std::cout << "\nparams[0].size() => \n" << params.front().sizes() << std::endl; // conv1's .weight

    auto input = torch::randn({1, 1, 32, 32});
    // out = net(input)
    auto out = net.forward(input); // TODO: Revisit this
    std::cout << "\nout=net(input) => \n" << out << std::endl;

    net.zero_grad();
    auto random_gradients = torch::randn({1, 10});
    out.backward(random_gradients);

    auto output = net.forward(input);
    auto target = torch::randn(10); // a dummy target, for example
    target = target.view({1, -1}); // make it the same shape as output
    auto criterion = torch::nn::MSELoss();

    auto loss = criterion->forward(output, target);
    std::cout << "\nloss => \n" << loss << std::endl;

    std::cout << "\nloss.grad_fn => \n" << loss.grad_fn() << std::endl;
    // TODO: Revisit this
//    std::cout << "\nloss.grad_fn.next_functions[0][0] => \n" << loss.grad_fn()->next_edges().front() << std::endl;
    // TODO: Revisit this
//    std::cout << "\nloss.grad_fn.next_functions[0][0].next_functions[0][0] => \n" << loss.grad_fn()->next_edges().front() << std::endl;

    net.zero_grad(); // zeroes the gradient buffers of all parameters

    std::cout << "\nconv1.bias.grad before backward\n" << std::endl;
    std::cout << "\nnet.conv1.bias.grad\n" << net.conv1->bias.grad() << std::endl;

    loss.backward();

    std::cout << "\nconv1.bias.grad after backward\n" << std::endl;
    std::cout << "\nnet.conv1.bias.grad\n" << net.conv1->bias.grad() << std::endl;

    // weight = weight - learning_rate * gradient
    auto learning_rate = 0.01;
    for (auto f : net.parameters()) {
        f.data().sub_(f.grad().data() * learning_rate);
    }

    // create your optimizer
    auto optimizer = torch::optim::SGD(net.parameters(), torch::optim::SGDOptions(0.01));
    // in your training loop:
    optimizer.zero_grad(); // zero the gradient buffers
    output = net.forward(input);
    loss = criterion->forward(output, target);
    loss.backward();
    optimizer.step(); // Does the update

    std::cout << "\noutput => \n" << output << std::endl;
    std::cout << "\nloss => \n" << loss << std::endl;

    return 0;
}
