#include <fstream>
#include <iostream>
#include <string>


#include "Statistics.h"

Statistics::Statistics(int sym_time, int packet_number_to_start_collect_data)
	: sym_time_(sym_time),
	packet_number_to_start_collect_data_(packet_number_to_start_collect_data)
{
	for (int i = 0; i < k_number_; i++)
	{
		packet_send_vector_.push_back(0.0);
		packet_lost_vector_.push_back(0.0);
		BER_vector_.push_back(0.0);
	}
}
Statistics::~Statistics()
{
}

int Statistics::get_packet_number_to_start_collect_data() const
{
	return packet_number_to_start_collect_data_;
}

int Statistics::get_current_simulation_time() const
{
	return current_simulation_time_;
}

void Statistics::set_current_simulation_time(int current_simulation_time)
{
	current_simulation_time_ = current_simulation_time;
}

std::vector<double> Statistics::get_packet_send_vector() const
{
	return packet_send_vector_;
}

void Statistics::set_packet_send_vector(std::vector<double> packet_send_vector)
{
	packet_send_vector_ = packet_send_vector;
}

std::vector<double> Statistics::get_packet_lost_vector() const
{
	return packet_lost_vector_;
}

void Statistics::set_packet_lost_vector(std::vector<double> packet_lost_vector)
{
	packet_lost_vector_ = packet_lost_vector;
}

std::vector<double> Statistics::get_succes_packet_retransmission_vector() const
{
	return succes_packet_retransmission_vector_;
}

void Statistics::set_succes_packet_retransmission_vector(std::vector<double> succes_packet_retransmission_vector)
{
	succes_packet_retransmission_vector_ = succes_packet_retransmission_vector;
}

std::vector<double> Statistics::get_packet_wait_time_vector() const
{
	return packet_wait_time_vector_;
}

void Statistics::set_packet_wait_time_vector(std::vector<double> packet_wait_time_vector)
{
	packet_wait_time_vector_ = packet_wait_time_vector;
}

std::vector<double> Statistics::get_average_retransmission_number_per_send_packets() const
{
	return average_retransmission_number_per_send_packets_;
}

void Statistics::set_average_retransmission_number_per_send_packets(
	std::vector<double> average_retransmission_number_per_send_packets)
{
	average_retransmission_number_per_send_packets_ = average_retransmission_number_per_send_packets;
}

std::vector<double> Statistics::get_send_packets_as_vector_as_axis_x() const
{
	return send_packets_as_vector_as_axis_x_;
}

void Statistics::set_send_packets_as_vector_as_axis_x(std::vector<double> send_packets_as_vector_as_axis_x)
{
	send_packets_as_vector_as_axis_x_ = send_packets_as_vector_as_axis_x;
}

void Statistics::ShowStats()
{
	std::vector<double> temporary_vector;
	for (int i = 0; i < k_number_; i++)
	{
		/*std::cout << "Transmitter nr: " << i + 1 << "\n";
		std::cout << "Lost packets: " << packet_lost_vector_.at(i) << "\n";
		std::cout << "Success send packets: " << packet_send_vector_.at(i) << "\n"*/;
		if (packet_lost_vector_.at(i) == 0.0 && packet_send_vector_.at(i) == 0.0)
		{
			temporary_vector.push_back(0);
		}
		else
		{
			temporary_vector.push_back(packet_lost_vector_.at(i) / packet_send_vector_.at(i));
		}

		/*std::cout << "BER: " << temporary_vector.at(i) << "\n";*/
	}
	double max = 0.0;
	for(int i=0;i<k_number_;i++)
	{
		if(max<temporary_vector.at(i))
		{
			max = temporary_vector.at(i);
		}
	}
	std::cout << "Max BER: " << max<< "\n";
	double average = 0.0;
	for (int i = 0; i < k_number_; i++)
	{
		average += temporary_vector.at(i);
	}
	std::cout << "Average BER: "<<average/k_number_ <<"\n";
	double average_retransmission = 0.0;
	if(!get_succes_packet_retransmission_vector().empty())
	{
		for (int i = 0; i < get_succes_packet_retransmission_vector().size(); i++)
		{
			average_retransmission += get_succes_packet_retransmission_vector().at(i);
		}
		std::cout << "Average retransmission number to success: "<<average_retransmission/ get_succes_packet_retransmission_vector().size() <<"\n";
	}
	else
	{
		std::cout << "There was not succesful retransmission"<<"\n";
	}
	std::cout << "Correct send packets amounts/s: " <<correct_send_packet_number_/(sym_time_/10000)<< "\n";
	//Srednie opoznienie pakietu tzn. jaki czas uplywa miedzy pojawieniem sie pakietu w buforze a jego poprawnym odebraniem w ms
	average_retransmission = 0; //AVERAGE DELAY
	if(!get_packet_delay_vector().empty())
	{
		for (int i = 0 ; i < get_packet_delay_vector().size(); i++)
		{
			average_retransmission += get_packet_delay_vector().at(i);
		}
		std::cout << "Average packets delay in ms: "<<(average_retransmission/ get_packet_delay_vector().size())/10 <<"\n";
	}
	//œredni czas oczekiwania, tzn. czas miêdzy pojawieniem siê pakietu w buforze, a jego opuszczeniem(w ms)
	average_retransmission = 0; //AVERAGE PACKET WAIT TIME
	if (!get_packet_wait_time_vector().empty())
	{
		for (int i = 0; i < get_packet_wait_time_vector().size(); i++)
		{
			average_retransmission += get_packet_wait_time_vector().at(i);
		}
		std::cout << "Average packets wait time in ms: " << (average_retransmission / get_packet_wait_time_vector().size()) / 10 << "\n";
	}
	std::cout << "=================" << "\n";
}
void Statistics::results_of_average_retransmission_number_per_moment()
{
	double average_retransmission = 0.0;
	if (!succes_packet_retransmission_vector_.empty())
	{
		for (int i = 0; i < succes_packet_retransmission_vector_.size(); i++)
		{
			average_retransmission += succes_packet_retransmission_vector_.at(i);
		}
	}
	average_retransmission_number_per_send_packets_.push_back(average_retransmission / average_retransmission_number_per_send_packets_.size());
	send_packets_as_vector_as_axis_x_.push_back(correct_send_packet_number_);
}

void Statistics::stage_phase_data_to_file(int sym_numb)
{
	
	std::string place_to_put_file = "./" + std::to_string(sym_numb) + "/average_packet_retransmission_at_moment.txt";
	std::ofstream output_file1(place_to_put_file);
	std::ostream_iterator<double> output_iterator1(output_file1, "\n");
	std::copy(average_retransmission_number_per_send_packets_.begin(), average_retransmission_number_per_send_packets_.end(), output_iterator1);

	place_to_put_file = "./" + std::to_string(sym_numb) + "/send_packet_numbers_axis_x.txt";
	std::ofstream output_file2(place_to_put_file);
	std::ostream_iterator<double> output_iterator2(output_file2, "\n");
	std::copy(send_packets_as_vector_as_axis_x_.begin(), send_packets_as_vector_as_axis_x_.end(), output_iterator2);
}

void Statistics::CalculateBER()
{
	
	for(int i=0;i<k_number_;i++)
	{
		BER_vector_.at(i) = packet_lost_vector_.at(i) / packet_send_vector_.at(i);
	}

}
double Statistics::MaxBER()
{
	max_BER_ = BER_vector_.at(0);
	for(int i=1;i<k_number_;i++)
	{
		if(max_BER_<BER_vector_.at(i))
		{
			max_BER_ = BER_vector_.at(i);
		}
	}
	return max_BER_;
}

double Statistics::AverageBER()
{
	double sum = 0;
	for(int i=0 ;i<k_number_;i++)
	{
		sum += BER_vector_.at(i);
	}
	return sum / k_number_;
}

double Statistics::get_correct_send_packet_number() const
{
	return correct_send_packet_number_;
}

void Statistics::set_correct_send_packet_number(double correct_send_packet_number)
{
	correct_send_packet_number_ = correct_send_packet_number;
}

double Statistics::get_correct_send_packet_number2() const
{
	return correct_send_packet_number2_;
}

void Statistics::set_correct_send_packet_number2(double correct_send_packet_number2)
{
	correct_send_packet_number2_ = correct_send_packet_number2;
}

std::vector<double> Statistics::get_packet_delay_vector() const
{
	return packet_delay_vector_;
}

void Statistics::set_packet_delay_vector(std::vector<double> packet_delay_vector)
{
	packet_delay_vector_ = packet_delay_vector;
}

