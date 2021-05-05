#ifndef WIRELESSNETWORK_H_
#define WIRELESSNETWORK_H_
#include "transmitter.h"
#include "receiver.h"
#include "channel.h"
#include <vector>
#include "logger.h"
#include "generator.h"
#include "statistics.h"
class WirelessNetwork
{
public:
	WirelessNetwork();
	~WirelessNetwork();
	void StartTransmission(Logger* logger, Channel* channel, Transmitter* transmitter);

private:
	const int k_number_ = 10;// number of pairs transmitters and receivers existing in the system.
	const int ack_time_ = 10; // 10*0.1 ms = 1ms
	const int max_retransmission_number_ = 15;
	std::vector<Transmitter*>transmitter_vector_;
	std::vector<Receiver*>receiver_vector_;
	Logger* logger_ = nullptr;
	Channel* channel = new Channel(true, false);
	std::vector<UniformGenerator*>CGP_kernel_vector_;
	std::vector<UniformGenerator*>CTP_kernel_vector_;
	std::vector<UniformGenerator*>CRP_kernel_vector_;
	UniformGenerator* TER_kernel_ = nullptr;
	//jeszcze generator bledu TER

public:
	int get_k_number() const;
	int get_ack_time() const;
	int get_max_retransmission_number() const;
	std::vector<Transmitter*> get_transmitter_vector() const;
	void set_transmitter_vector(std::vector<Transmitter*> transmitter_vector);
	std::vector<Receiver*> get_receiver_vector() const;
	Channel* get_channel() const;
	void set_receiver_vector(std::vector<Receiver*> receiver_vector);
	std::vector<UniformGenerator*> get_cgp_kernel_vector() const;
	void set_cgp_kernel_vector(std::vector<UniformGenerator*> cgp_kernel_vector);
	std::vector<UniformGenerator*> get_ctp_kernel_vector() const;
	void set_ctp_kernel_vector(std::vector<UniformGenerator*> ctp_kernel_vector);
	std::vector<UniformGenerator*> get_crp_kernel_vector() const;
	void set_crp_kernel_vector(std::vector<UniformGenerator*> crp_kernel_vector);
	UniformGenerator* get_ter_kernel() const;
	void set_ter_kernel(UniformGenerator* ter_kernel);
	void GeneratePacket(Logger* logger, Transmitter* transmitter, int time);
	void CheckIfChannelFree(Logger* logger, Transmitter* transmitter, Channel* channel, Receiver* receiver);
	void print_queue(std::queue<Packets*> q);
	void StartTransmission(Logger* logger, Channel* channel, Transmitter* transmitter, Receiver* receiver, Statistics* stats);
	void SendACK(Logger* logger, Channel* channel, Receiver* receiver, Transmitter* transmitter);
	void StopWaitForACK(Logger* logger, Receiver* receiver, Transmitter* transmitter, Channel* channel);
	void EndTransmission(Logger* logger, Transmitter* transmitter, Channel* channel, Statistics* stats);
	void Retransmission(Logger* logger, Transmitter* transmitter, Channel* channel, Statistics* stats);
	void Initialization(Logger* logger, UniformGenerator* root);
	int generate_time_to_retransmission(Transmitter* transmitter);
	void KernelToFile(int sym_numb);
	void GetDataToFiles(int sym_numb);
};

#endif
