#include "transmitter.h"

Transmitter::Transmitter(int tansmitter_id)
	: tansmitter_id_(tansmitter_id)
{
}
Transmitter::~Transmitter()
{
	
}


int Transmitter::get_time_to_generate_new_packet() const
{
	return time_to_generate_new_packet_;
}

void Transmitter::set_time_to_generate_new_packet(int time_to_generate_new_packet)
{
	time_to_generate_new_packet_ = time_to_generate_new_packet;
}

int Transmitter::get_time_to_wait_for_ack() const
{
	return time_to_wait_for_ACK_;
}

void Transmitter::set_time_to_wait_for_ack(int time_to_wait_for_ack)
{
	time_to_wait_for_ACK_ = time_to_wait_for_ack;
}

int Transmitter::get_time_to_scan_channel() const
{
	return time_to_scan_channel_;
}

void Transmitter::set_time_to_scan_channel(int time_to_scan_channel)
{
	time_to_scan_channel_ = time_to_scan_channel;
}

int Transmitter::get_time_to_retransmission() const
{
	return time_to_retransmission_;
}

void Transmitter::set_time_to_retransmission(int time_to_retransmission)
{
	time_to_retransmission_ = time_to_retransmission;
}

int Transmitter::get_tansmitter_id() const
{
	return tansmitter_id_;
}

void Transmitter::set_tansmitter_id(int tansmitter_id)
{
	tansmitter_id_ = tansmitter_id;
}

std::queue<Packets*> Transmitter::get_buffer() const
{
	return buffer_;
}

void Transmitter::set_buffer(std::queue<Packets*> buffer)
{
	buffer_ = buffer;
}

bool Transmitter::is_start_transmission_flag() const
{
	return start_transmission_flag_;
}

void Transmitter::set_start_transmission_flag(bool start_transmission_flag)
{
	start_transmission_flag_ = start_transmission_flag;
}

int Transmitter::get_time_to_ask_ack() const
{
	return time_to_ask_ACK_;
}

void Transmitter::set_time_to_ask_ack(int time_to_ask_ack)
{
	time_to_ask_ACK_ = time_to_ask_ack;
}

