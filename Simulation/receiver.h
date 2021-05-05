#ifndef RECEIVER_H_
#define RECEIVER_H_
#include <queue>
#include "packets.h"


class Receiver
{
public:
	Receiver(int receiver_id);
	~Receiver();

private:

	bool send_ack_ = false; // variable set as true when ACK communication can be send
	bool ter_error_; //variable set as true when TER error happened
	int receiver_id_;


public:
	bool is_send_ack() const;
	void set_send_ack(bool send_ack);
	bool is_ter_error() const;
	void set_ter_error(bool ter_error);
	int get_receiver_id() const;
	void set_receiver_id(int receiver_id);
	bool generate_ter_error();
};
#endif #pragma once
