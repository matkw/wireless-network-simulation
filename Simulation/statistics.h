#ifndef STATISTICS_H_
#define STATISTICS_H_
#include <vector>

class Statistics
{
	
public:
	Statistics(int sym_time, int packet_number_to_start_collect_data);
	~Statistics();

	int get_packet_number_to_start_collect_data() const;
	int get_current_simulation_time() const;
	void set_current_simulation_time(int current_simulation_time);
	std::vector<double> get_packet_send_vector() const;
	void set_packet_send_vector(std::vector<double> packet_send_vector);
	std::vector<double> get_packet_lost_vector() const;
	void set_packet_lost_vector(std::vector<double> packet_lost_vector);
	std::vector<double> get_succes_packet_retransmission_vector() const;
	void set_succes_packet_retransmission_vector(std::vector<double> succes_packet_retransmission_vector);
	void ShowStats();
	void CalculateBER();
	double MaxBER();
	double AverageBER();
	double get_correct_send_packet_number() const;
	void set_correct_send_packet_number(double correct_send_packet_number);
	double get_correct_send_packet_number2() const;
	void set_correct_send_packet_number2(double correct_send_packet_number);
	int sym_time_;
	std::vector<double> get_packet_delay_vector() const;
	void set_packet_delay_vector(std::vector<double> packet_delay_vector);
	std::vector<double> get_packet_wait_time_vector() const;
	void set_packet_wait_time_vector(std::vector<double> packet_wait_time_vector);
	std::vector<double> get_average_retransmission_number_per_send_packets() const;
	void set_average_retransmission_number_per_send_packets(
		std::vector<double> average_retransmission_number_per_send_packets);
	std::vector<double> get_send_packets_as_vector_as_axis_x() const;
	void set_send_packets_as_vector_as_axis_x(std::vector<double> send_packets_as_vector_as_axis_x);
	void results_of_average_retransmission_number_per_moment();
	void stage_phase_data_to_file(int sym_numb);
private:
	int current_simulation_time_=0;
	int k_number_=10;
	int packet_number_to_start_collect_data_;
	std::vector<double> packet_send_vector_;
	std::vector<double> packet_lost_vector_;
	std::vector<double> succes_packet_retransmission_vector_; // number of retransmission which was need to succesable retransmission
	double correct_send_packet_number_ = 0.0;
	double correct_send_packet_number2_ = 0.0;
	std::vector<double> BER_vector_;
	double average_BER_ = 0;
	double max_BER_ = 0;
	double average_number_of_succesful_retransmission_ = 0; // successful*
	std::vector<double> packet_delay_vector_;
	std::vector<double> packet_wait_time_vector_;
	std::vector<double> average_retransmission_number_per_send_packets_;
	std::vector<double> send_packets_as_vector_as_axis_x_;


};

#endif 
