//
// Created by outcastgeek on 4/26/20.
//

#include <iostream>
#include <torch/torch.h>

int main() {
    auto x = torch::ones({4, 8}, torch::kLong);
    x = x.new_full({4, 8}, 1, torch::kDouble);
    x = torch::randn_like(x, torch::kFloat);;
    std::cout << "\nx => \n" << x << std::endl;

    auto y = torch::rand({4, 8});
    std::cout << "\ny => \n" << y << std::endl;

    auto sum = x + y;
    std::cout << "\nx + y = sum => \n" << sum << std::endl;

    auto sum2 = torch::add(x, y);
    std::cout << "\ntorch.add(x, y) => \n" << sum2 << std::endl;

    auto result = torch::empty({8, 8});
    torch::add_out(result, x, y);
    std::cout << "\ntorch.add(x, y, out=result) => \n" << result << std::endl;

    std::cout << "\nAny operation that mutates a tensor in-place is post-fixed with an _. For example: x.copy_(y), x.t_(), will change x." << std::endl;
    y = y.add_(x);
    std::cout << "y=y.add_(x) => \n" << y << std::endl;
    std::cout << "print(y[:, 1]) => \n" << y.slice(-1, 1) << std::endl;

    if (torch::hasCUDA()) {
        auto device = torch::device(c10::kCUDA);
        y = torch::ones_like(x, device);
        x = x.to(device);
        auto z = x + y;
        std::cout << "\nz value for CUDA => \n" << z << std::endl;
        std::cout << "\nz value for CPU => \n" << z.to(c10::kCPU) << std::endl;
    } else {
        std::cout << "\nNo CUDA Device Found." << std::endl;
    }

    return 0;
}
