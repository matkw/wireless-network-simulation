#include "receiver.h"

Receiver::Receiver(int receiver_id)
	: receiver_id_(receiver_id)
{
}
Receiver::~Receiver()
{
	
}

bool Receiver::is_send_ack() const
{
	return send_ack_;
}

void Receiver::set_send_ack(bool send_ack)
{
	send_ack_ = send_ack;
}

bool Receiver::is_ter_error() const
{
	return ter_error_;
}

void Receiver::set_ter_error(bool ter_error)
{
	ter_error_ = ter_error;
}

int Receiver::get_receiver_id() const
{
	return receiver_id_;
}

void Receiver::set_receiver_id(int receiver_id)
{
	receiver_id_ = receiver_id;
}

bool Receiver::generate_ter_error()
{
	int probability = rand() % 100 + 1;
	if (probability <= 80)
	{
		return true;
	}
	return false;
}

