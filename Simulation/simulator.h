#ifndef SIMULATOR_H_
#define SIMULATOR_H
#include "WirelessNetwork.h"
//#include "logger.h"

class Simulator
{
public:
    Simulator(UniformGenerator* root);
    void simulation(int time, Logger* logger, int sym_numb, double lambda);

private:
    //Logger* logger_ = nullptr;
    size_t generate_packet_max_time = 100;
    size_t transmission_max_time = 250;
    size_t clock_ = 0;
    WirelessNetwork* wireless_network = nullptr;
    bool step_or_not_step_ = false;
    UniformGenerator* root;

public:
    bool is_step_or_not_step() const;
    void set_step_or_not_step(bool step_or_not_step);
};

#endif