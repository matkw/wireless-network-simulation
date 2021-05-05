
#include "generator.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

UniformGenerator::UniformGenerator(int kernel) : kernel_(kernel)
{
    // empty
}

UniformGenerator::~UniformGenerator()
{

}
double UniformGenerator::generate_kernel(int k)
{
    for (int i = 1; i <= k; i++)
    {
        rand();
    }
    //std::cout << "kernel: " << kernel_ << "\n";
    return kernel_;
}

double UniformGenerator::rand()
{
    int h = kernel_ / kQ;
    kernel_ = kA * (kernel_ - kQ * h) - kR * h;
    if (kernel_ < 0)
        kernel_ = kernel_ + static_cast<int>(kM);
    return kernel_ / kM;
}

int UniformGenerator::randMaxMin(int max, int min)
{
    int result = floor(rand() * (max)+min);
    results_randMaxMin_.push_back(result);
    return result;
}
//Algorytm dla generatora rozk³adu wyk³adniczego

double UniformGenerator::randExp(double lambda)
{
    double k = rand();
	double result = -(1.0 / lambda) * log(k);
    results_randExp_.push_back(result);
    return result;
}

//Algorytm dla generatora rozk³adu zero-jedynkowego

double UniformGenerator::randZeroONe(double p)
{
    double k = rand();
    if (k < p)
    {
        results_randZeroOne_.push_back(1);
        return 1;
    }
    results_randZeroOne_.push_back(0);
    return 0;
}

std::vector<double> UniformGenerator::get_results_rand_exp() const
{
	return results_randExp_;
}

void UniformGenerator::set_results_rand_exp(std::vector<double> results_rand_exp)
{
	results_randExp_ = results_rand_exp;
}

std::vector<int> UniformGenerator::get_results_rand_max_min() const
{
	return results_randMaxMin_;
}

void UniformGenerator::set_results_rand_max_min(std::vector<int> results_rand_max_min)
{
	results_randMaxMin_ = results_rand_max_min;
}

std::vector<double> UniformGenerator::get_results_rand_zero_one() const
{
	return results_randZeroOne_;
}

void UniformGenerator::set_results_rand_zero_one(std::vector<double> results_rand_zero_one)
{
	results_randZeroOne_ = results_rand_zero_one;
}

int UniformGenerator::get_kernel() const
{
	return kernel_;
}

void UniformGenerator::set_kernel(int kernel)
{
	kernel_ = kernel; 
}
