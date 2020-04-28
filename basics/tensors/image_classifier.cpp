//
// Created by outcastgeek on 4/28/20.
//

#include <iostream>
#include <torch/torch.h>

// Define a Convolutional Neural Network
class Net: public torch::nn::Module {
public:
    Net()
    :
    conv1(torch::nn::Conv2d(3, 6, 5)),
    pool(torch::nn::MaxPool2d(torch::nn::MaxPool2dOptions({2, 2}))),
    conv2(torch::nn::Conv2d(6, 16, 5)),
    fc1(torch::nn::Linear(16 * 5 * 5, 120)),
    fc2(torch::nn::Linear(120, 84)),
    fc3(torch::nn::Linear(84, 10))
    {
        register_module("conv1", conv1);
        register_module("pool", pool);
        register_module("conv2", conv2);
        register_module("fc1", fc1);
        register_module("fc2", fc2);
        register_module("fc3", fc3);
    }

    torch::Tensor forward(torch::Tensor x) {
        namespace F = torch::nn::functional;
        x = pool(F::relu(conv1(x)));
        x = pool(F::relu(conv2(x)));
        x = x.view({-1, 16 * 5 * 5});
        x = F::relu(fc1(x));
        x = F::relu(fc2(x));
        x = fc3(x);
        return x;
    }

private:
    torch::nn::Conv2d conv1;
    torch::nn::MaxPool2d pool;
    torch::nn::Conv2d conv2;
    torch::nn::Linear fc1, fc2, fc3;
};

/// The CIFAR10 dataset.
class TORCH_API CIFAR10 : public torch::data::Dataset<CIFAR10> {
public:
    /// The mode in which the dataset is loaded.
    enum class Mode { kTrain, kTest };

    /// Loads the CIFAR10 dataset from the `root` path.
    ///
    /// The supplied `root` path should contain the *content* of the unzipped
    /// CIFAR10 dataset, available from https://www.cs.toronto.edu/~kriz/cifar.html.
    explicit CIFAR10(const std::string& root, Mode mode = Mode::kTrain);

    /// Returns the `Example` at the given `index`.
    torch::data::Example<> get(size_t index) override;

    /// Returns the size of the dataset.
    c10::optional<size_t> size() const override;

    /// Returns true if this is the training subset of CIFAR10.
    bool is_train() const noexcept;

    /// Returns all images stacked into a single tensor.
    const torch::Tensor& images() const;

    /// Returns all targets stacked into a single tensor.
    const torch::Tensor& targets() const;

private:
    torch::Tensor images_, targets_;
};

int main() {
    Net net;
    std::cout << "\nnet => \n" << net << std::endl;

    // Define a Loss function and optimizer
    torch::nn::CrossEntropyLoss criterion;
    auto optimizer = torch::optim::SGD(
            net.parameters(),
            torch::optim::SGDOptions(0.001).momentum(0.9)
    );

    // Loading Data
//    auto dataset = CIFAR10("./")
//            .map(torch::data::transforms::Normalize<>(0.5, 0.5))
//            .map(torch::data::transforms::Stack<>());
//    auto data_loader = torch::data::make_data_loader(
//            std::move(dataset),
//            torch::data::DataLoaderOptions().workers(4)
//    );
//
//    for (int epoch = 0; epoch <= 2; epoch++) {  // loop over the dataset multiple times
//        // get the inputs; data is a list of [inputs, labels]
//
//    }
}
