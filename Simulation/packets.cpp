#include "packets.h"
Packets::Packets(int packet_time_transmission, int transmitter_id, int time_packet_added_to_buffer)
	: packet_time_transmission_(packet_time_transmission),
	transmitter_id_(transmitter_id),
	time_packet_added_to_buffer_(time_packet_added_to_buffer), retransmission_number_(0)
{
	
}
Packets::~Packets()
{
	
}

int Packets::get_packet_time_transmission() const
{
	return packet_time_transmission_;
}

void Packets::set_packet_time_transmission(int packet_time_transmission)
{
	packet_time_transmission_ = packet_time_transmission;
}

int Packets::get_transmitter_id() const
{
	return transmitter_id_;
}

void Packets::set_transmitter_id(int transmitter_id)
{
	transmitter_id_ = transmitter_id;
}

int Packets::get_retransmission_number() const
{
	return retransmission_number_;
}

void Packets::set_retransmission_number(int retransmission_number)
{
	retransmission_number_ = retransmission_number;
}

int Packets::get_time_packet_added_to_buffer() const
{
	return time_packet_added_to_buffer_;
}

void Packets::set_time_packet_added_to_buffer(int time_packet_added_to_buffer)
{
	time_packet_added_to_buffer_ = time_packet_added_to_buffer;
}


