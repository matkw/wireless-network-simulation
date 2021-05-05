#ifndef RANDOM_GENERATOR_H_
#define RANDOM_GENERATOR_H_

#include <string>
#include <vector>

class UniformGenerator
{
public:
    UniformGenerator(int kernel);
    virtual ~UniformGenerator();

    // Draws number between <0,1>
    double rand();
    int get_kernel() const;
    void set_kernel(int kernel);
    double generate_kernel(int k);
    int randMaxMin(int max, int min);
    double randExp(double lambda);
    double randZeroONe(double probability);
    std::vector<double> results_randExp_; // CGP
    std::vector<int> results_randMaxMin_; // CTP i CRP
    std::vector<double> results_randZeroOne_;// TER_error
    std::vector<double> get_results_rand_exp() const;
    void set_results_rand_exp(std::vector<double> results_rand_exp);
    std::vector<int> get_results_rand_max_min() const;
    void set_results_rand_max_min(std::vector<int> results_rand_max_min);
    std::vector<double> get_results_rand_zero_one() const;
    void set_results_rand_zero_one(std::vector<double> results_rand_zero_one);
private:
    int kernel_;
    const double kM = 2147483647.0;
    static const int kA = 16807;
    static const int kQ = 127773;
    static const int kR = 2836;
};


#endif /* RANDOM_GENERATOR_H_ */