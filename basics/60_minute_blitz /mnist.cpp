//
// Created by outcastgeek on 4/26/20.
//

#include <iostream>
#include <torch/torch.h>

int main() {
    torch::Tensor tensorA = torch::tensor(5);
    std::cout << "tensorA => " << tensorA << std::endl;

    torch::Tensor tensorB = torch::tensor(7);
    std::cout << "tensorB => " << tensorB << std::endl;

    torch::Tensor tensorSum = tensorA + tensorB;
    std::cout << "tensorA + tensorSum = tensorSum => " << tensorSum << std::endl;
    return 0;
}
