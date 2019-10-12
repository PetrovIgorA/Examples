#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <functional>

class Function
{
public:
    Function() : func_([](double x) { return x; }) {}
    Function(std::function<double(double)> func) : func_(func) {}
    Function(const Function& other) = default;
    Function(Function&& other) noexcept = default;

    Function& operator=(const Function& other) = default;
    Function& operator=(Function&& other) noexcept = default;

    double operator()(double x) const noexcept { return func_(x); }

    friend Function operator+(const Function& lhs, const Function& rhs) noexcept;
    friend Function operator-(const Function& lhs, const Function& rhs) noexcept;
    friend Function operator*(const Function& lhs, const Function& rhs) noexcept;
    friend Function operator/(const Function& lhs, const Function& rhs) noexcept;

    ~Function() = default;

private:
    std::function<double(double)> func_;
};

Function operator+(const Function& lhs, const Function& rhs) noexcept
{
    return Function([lf = lhs.func_, rf = rhs.func_](double x) { return lf(x) + rf(x); });
}

Function operator-(const Function& lhs, const Function& rhs) noexcept
{
    return Function([lf = lhs.func_, rf = rhs.func_](double x) { return lf(x) - rf(x); });
}

Function operator*(const Function& lhs, const Function& rhs) noexcept
{
    return Function([lf = lhs.func_, rf = rhs.func_](double x) { return lf(x) * rf(x); });
}

Function operator/(const Function& lhs, const Function& rhs) noexcept
{
    return Function([lf = lhs.func_, rf = rhs.func_](double x) { return lf(x) / rf(x); });
}

#endif // FUNCTION_HPP