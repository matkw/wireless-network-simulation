#ifndef CHANNEL_H_
#define CHANNEL_H_
#include <vector>
#include "packets.h"

class Channel
{
public:
	Channel(bool if_channel_free, bool if_collision);
	Channel();
	~Channel();


private:
	std::vector<Packets*>in_channel_vector_{}; //vector of packets in channel
	bool if_channel_free_; // flag which if true it means channel is free and we can start transmission
	bool if_collision_; //flag which inform us if there was send to in_channel_vector_ more then 1 packet
	int time_channel_busy = -1;

public:
	std::vector<Packets*> get_in_channel_vector() const;
	void set_in_channel_vector(std::vector<Packets*> in_channel_vector);
	bool is_if_channel_free() const;
	void set_if_channel_free(bool if_channel_free);
	bool is_if_collision() const;
	void set_if_collision(bool if_collision);
	int get_time_channel_busy() const;
	void set_time_channel_busy(int time_channel_busy);
};

#endif 
