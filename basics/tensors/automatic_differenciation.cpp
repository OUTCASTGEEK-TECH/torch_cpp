//
// Created by outcastgeek on 4/26/20.
//

#include <iostream>
#include <torch/torch.h>

int main() {
    auto x = torch::ones({4, 4}).set_requires_grad(true);
    std::cout << "\nx => \n" << x << std::endl;

    auto y = x + 2;
    std::cout << "\ny => \n" << y << std::endl;
    std::cout << "\ny.grad_fn => \n" << y.grad_fn() << std::endl;

    auto z  = y * y * 3;
    auto out = z.mean();
    std::cout << "\nz => \n" << z << std::endl;
    std::cout << "\nout => \n" << out << std::endl;

    std::cout << "\n.requires_grad_( ... ) changes an existing Tensor’s requires_grad flag in-place. The input flag defaults to False if not given." << std::endl;
    auto a = torch::randn({4, 4});
    a = ((a * 3) / (a - 1));
    std::cout << "\na.requires_grad => \n" << a.requires_grad() << std::endl;

    a.requires_grad_(true);
    std::cout << "\na.requires_grad => \n" << a.requires_grad() << std::endl;

    auto b = (a * a).sum();
    std::cout << "\nb.grad_fn => \n" << b.grad_fn() << std::endl;

    std::cout << "\nLet’s backprop now. Because out contains a single scalar, out.backward() is equivalent to out.backward(torch.tensor(1.))." << std::endl;
    out.backward();
    std::cout << "x.grad => \n" << x.grad() << std::endl;

    std::cout << "\nvector-Jacobian product" << std::endl;
    x = torch::randn(3).requires_grad_(true);
    y = x * 2;
    while (y.data().norm().item().toFloat() < 1000) {
        y = y * 2;
    }
    std::cout << "\ny => \n" << y << std::endl;

    auto v = torch::tensor({0.1, 1.0, 0.0001}, torch::kFloat);
    y.backward(v);
    std::cout << "x.grad => \n" << x.grad() << std::endl;

    std::cout << "\nx.requires_grad => \n" << x.requires_grad() << std::endl;
    std::cout << "\n(x ** 2).requires_grad => \n" << x.pow(2).requires_grad() << std::endl;
    {
        torch::NoGradGuard no_grad;
        std::cout << "\n(x ** 2).requires_grad => \n" << x.pow(2).requires_grad() << std::endl;
    }

    std::cout << "\nx.requires_grad => \n" << x.requires_grad() << std::endl;
    y = x.detach();
    std::cout << "\ny.requires_grad => \n" << y.requires_grad() << std::endl;
    std::cout << "\nx.eq(y).all() => \n" << x.eq(y).all() << std::endl;

    return 0;
}
