#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_
#include <queue>
#include "packets.h"

class Transmitter
{
public:
	Transmitter(int tansmitter_id);
	~Transmitter();

private:
	//Transmitter(-1, ack_time_, 5, -1, i + 1);
	int time_to_generate_new_packet_ = -1;
	int time_to_wait_for_ACK_ = -1; 
	int time_to_scan_channel_ = -1;// 5*0.1ms = 0.5ms
	int time_to_retransmission_ = -1;
	int tansmitter_id_; // to check which transmitter got acces and where to send ACK from receiver
	std::queue<Packets*>buffer_; // buffer is a place where packets are waiting for transmission if channel is busy
	bool start_transmission_flag_ = false;// flag to inform loop that it can not scan channel cuz was scanned and that it's possible to start transmission
	int time_to_ask_ACK_ = -1; // It/s time to wait for moment to ask if ACK was send


public:
	int get_time_to_generate_new_packet() const;
	void set_time_to_generate_new_packet(int time_to_generate_new_packet);
	int get_time_to_wait_for_ack() const;
	void set_time_to_wait_for_ack(int time_to_wait_for_ack);
	int get_time_to_scan_channel() const;
	void set_time_to_scan_channel(int time_to_scan_channel);
	int get_time_to_retransmission() const;
	void set_time_to_retransmission(int time_to_retransmission);
	int get_tansmitter_id() const;
	void set_tansmitter_id(int tansmitter_id);
	std::queue<Packets*> get_buffer() const;
	void set_buffer(std::queue<Packets*> buffer);
	bool is_start_transmission_flag() const;
	void set_start_transmission_flag(bool start_transmission_flag);
	int get_time_to_ask_ack() const;
	void set_time_to_ask_ack(int time_to_ask_ack);
};
#endif 