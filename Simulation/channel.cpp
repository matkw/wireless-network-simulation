#include "channel.h"

Channel::Channel(bool if_channel_free, bool if_collision)
	: if_channel_free_(if_channel_free),
	if_collision_(if_collision)
{
	
}
Channel::Channel()
{
	
}

std::vector<Packets*> Channel::get_in_channel_vector() const
{
	return in_channel_vector_;
}

void Channel::set_in_channel_vector(std::vector<Packets*> in_channel_vector)
{
	in_channel_vector_ = in_channel_vector;
}

bool Channel::is_if_channel_free() const
{
	return if_channel_free_;
}

void Channel::set_if_channel_free(bool if_channel_free)
{
	if_channel_free_ = if_channel_free;
}

bool Channel::is_if_collision() const
{
	return if_collision_;
}

void Channel::set_if_collision(bool if_collision)
{
	if_collision_ = if_collision;
}
int Channel::get_time_channel_busy() const
{
	return time_channel_busy;
}

void Channel::set_time_channel_busy(int time_channel_busy)
{
	this->time_channel_busy = time_channel_busy;
}

