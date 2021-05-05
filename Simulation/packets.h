#ifndef PACKETS_H_
#define PACKETS_H_
class Packets
{
public:
	Packets(int packet_time_transmission, int transmitter_id, int time_packet_added_to_buffer);
	~Packets();

private:
	int packet_time_transmission_;
	int transmitter_id_;
	int retransmission_number_;
	int time_packet_added_to_buffer_;


public:
	int get_packet_time_transmission() const;
	void set_packet_time_transmission(int packet_time_transmission);
	int get_transmitter_id() const;
	void set_transmitter_id(int transmitter_id);
	int get_retransmission_number() const;
	void set_retransmission_number(int retransmission_number);
	int get_time_packet_added_to_buffer() const;
	void set_time_packet_added_to_buffer(int time_packet_added_to_buffer);
};

#endif 
