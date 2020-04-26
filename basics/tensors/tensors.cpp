//
// Created by outcastgeek on 4/26/20.
//

#include <iostream>
#include <torch/torch.h>

int main() {
    torch::Tensor tensor = torch::eye(16);
    std::cout << "\ntensor = torch.eye(16) => \n" << tensor << std::endl;

    torch::Tensor x = torch::empty({4, 8});
    std::cout << "\nx = torch.empty(4, 8) => \n" << x << std::endl;

    x = torch::rand({4, 8});
    std::cout << "\nx = torch.rand(4, 8) => \n" << x << std::endl;

    x = torch::zeros({4, 8}, torch::kLong);
    std::cout << "\nx = torch.zeros(4, 8, dtype=torch.long) => \n" << x << std::endl;

    x = torch::ones({4, 8}, torch::kLong);
    std::cout << "\nx = torch.ones(4, 8, dtype=torch.long) => \n" << x << std::endl;

    x = x.new_full({4, 8}, 1, torch::kDouble);
    std::cout << "\nx = x.new_ones(4, 8, dtype=torch.double) => \n" << x << std::endl;

    x = torch::randn_like(x, torch::kFloat);
    std::cout << "\nx = torch.randn_like(x, dtype=torch.float) => \n" << x << std::endl;
    std::cout << "\nx.size(0) => \n" << x.size(0) << std::endl;
    std::cout << "\nx.size(1) => \n" << x.size(1) << std::endl;
    std::cout << "\nx.size() => \n" << x.sizes() << std::endl;
    std::cout << "\nx.ndimension() => \n" << x.ndimension() << std::endl;

    auto t = torch::tensor({5.5, 3., 8.9, 4.4}, torch::kFloat);
    std::cout << "\nt=torch.tensor([5.5, 3, 8.9, 4.4], dtype=torch.float) => \n" << t << std::endl;

    std::cout << "\nx.view(4, 8) => \n" << x.view({4, 8}) << std::endl;
    auto y = x.view(32);
    std::cout << "\nx.view(32) => \n" << y << std::endl;
    auto z = x.view({-1, 16});
    std::cout << "\nx.view(-1, 16)   # the size -1 is inferred from other dimensions => \n" << z << std::endl;

    auto a = torch::ones(4);
    std::cout << "\na => \n" << a << std::endl;

    auto b = a.numpy_T();
    std::cout << "\nb => \n" << b << std::endl;

    a.add_(1);
    std::cout << "\nSee how the numpy array changed in value." << std::endl;
    std::cout << "a => " << a << std::endl;
    std::cout << "b => \n" << b << std::endl;

    return 0;
}
