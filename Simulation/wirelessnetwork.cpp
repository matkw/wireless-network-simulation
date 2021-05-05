#include "wirelessnetwork.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <vector>
#include <fstream>
	

WirelessNetwork::WirelessNetwork()
{

}

WirelessNetwork::~WirelessNetwork()
{
	
}

int WirelessNetwork::get_k_number() const
{
	return k_number_;
}

int WirelessNetwork::get_ack_time() const
{
	return ack_time_;
}

int WirelessNetwork::get_max_retransmission_number() const
{
	return max_retransmission_number_;
}

std::vector<Transmitter*> WirelessNetwork::get_transmitter_vector() const
{
	return transmitter_vector_;
}

void WirelessNetwork::set_transmitter_vector(std::vector<Transmitter*> transmitter_vector)
{
	transmitter_vector_ = transmitter_vector;
}

std::vector<Receiver*> WirelessNetwork::get_receiver_vector() const
{
	return receiver_vector_;
}

void WirelessNetwork::set_receiver_vector(std::vector<Receiver*> receiver_vector)
{
	receiver_vector_ = receiver_vector;
}

Channel* WirelessNetwork::get_channel() const
{
	return channel;
}

std::vector<UniformGenerator*> WirelessNetwork::get_cgp_kernel_vector() const
{
	return CGP_kernel_vector_;
}

void WirelessNetwork::set_cgp_kernel_vector(std::vector<UniformGenerator*> cgp_kernel_vector)
{
	CGP_kernel_vector_ = cgp_kernel_vector;
}

std::vector<UniformGenerator*> WirelessNetwork::get_ctp_kernel_vector() const
{
	return CTP_kernel_vector_;
}

void WirelessNetwork::set_ctp_kernel_vector(std::vector<UniformGenerator*> ctp_kernel_vector)
{
	CTP_kernel_vector_ = ctp_kernel_vector;
}

std::vector<UniformGenerator*> WirelessNetwork::get_crp_kernel_vector() const
{
	return CRP_kernel_vector_;
}

void WirelessNetwork::set_crp_kernel_vector(std::vector<UniformGenerator*> crp_kernel_vector)
{
	CRP_kernel_vector_ = crp_kernel_vector;
}

UniformGenerator* WirelessNetwork::get_ter_kernel() const
{
	return TER_kernel_;
}

void WirelessNetwork::set_ter_kernel(UniformGenerator* ter_kernel)
{
	TER_kernel_ = ter_kernel;
}

void WirelessNetwork::Initialization(Logger* logger, UniformGenerator* root)
{
	logger->Info("->Initialization started");
	// vector of transmitters
	for(int i = 0; i < k_number_ ; i++)
	{
		Transmitter* transmitter = new Transmitter( i+1);
		//Building generators with transmitters
		UniformGenerator* temp_gen = new UniformGenerator(root->generate_kernel(100000));
		CGP_kernel_vector_.push_back(temp_gen);
		//std::cout << "CGP_kernel: " << CGP_kernel_vector_.at(i)->get_kernel() << "|";
		temp_gen = new UniformGenerator(root->generate_kernel(100000));
		CTP_kernel_vector_.push_back(temp_gen);
		//std::cout << "CTP_kernel: " << CTP_kernel_vector_.at(i)->get_kernel() << "|";
		temp_gen = new UniformGenerator(root->generate_kernel(100000));
		CRP_kernel_vector_.push_back(temp_gen);
		//std::cout << "CTP_kernel: " << CRP_kernel_vector_.at(i)->get_kernel() << "|";
		root->set_kernel(temp_gen->get_kernel());
		
		while (!transmitter->get_buffer().empty())
		{
			transmitter->get_buffer().pop();
		}
		std::vector<Transmitter*> local_transmitter_vector = get_transmitter_vector();
		local_transmitter_vector.push_back(transmitter);
		set_transmitter_vector(local_transmitter_vector);

	}
	UniformGenerator* temp_gen = new UniformGenerator(root->generate_kernel(100000));
	TER_kernel_ = temp_gen;
	root->set_kernel(temp_gen->get_kernel());
	
	// vector of receivers
	for (int i = 0; i < k_number_; i++)
	{
		Receiver* receiver = new Receiver(i + 1);
		std::vector<Receiver*> local_receiver_vector = get_receiver_vector();
		local_receiver_vector.push_back(receiver);
		set_receiver_vector(local_receiver_vector);

	}
	
}

void WirelessNetwork::GetDataToFiles(int sym_numb)
{
	std::vector<double> numbers_exp;
	std::vector<double> numbers_max_min;
	std::vector<double> numbers_zero_one;
	for(int i=0 ; i < k_number_ ; i++)
	{
		// RAND EXP
		for(int j=0 ;j < CGP_kernel_vector_.at(i)->get_results_rand_exp().size(); j++)
		{
			numbers_exp.push_back(CGP_kernel_vector_.at(i)->get_results_rand_exp().at(j));
		}
		for (int j = 0; j < CTP_kernel_vector_.at(i)->get_results_rand_exp().size(); j++)
		{
			numbers_exp.push_back(CTP_kernel_vector_.at(i)->get_results_rand_exp().at(j));
		}
		for (int j = 0; j < CRP_kernel_vector_.at(i)->get_results_rand_exp().size(); j++)
		{
			numbers_exp.push_back(CRP_kernel_vector_.at(i)->get_results_rand_exp().at(j));
		}
		// RAND MAX MIN
		for (int j = 0; j < CGP_kernel_vector_.at(i)->get_results_rand_max_min().size(); j++)
		{
			numbers_max_min.push_back(CGP_kernel_vector_.at(i)->get_results_rand_max_min().at(j));
		}
		for (int j = 0; j < CTP_kernel_vector_.at(i)->get_results_rand_max_min().size(); j++)
		{
			numbers_max_min.push_back(CTP_kernel_vector_.at(i)->get_results_rand_max_min().at(j));
		}
		for (int j = 0; j < CRP_kernel_vector_.at(i)->get_results_rand_max_min().size(); j++)
		{
			numbers_max_min.push_back(CRP_kernel_vector_.at(i)->get_results_rand_max_min().at(j));
		}
		// RAND ZERO ONE
		for (int j = 0; j < CGP_kernel_vector_.at(i)->get_results_rand_zero_one().size(); j++)
		{
			numbers_zero_one.push_back(CGP_kernel_vector_.at(i)->get_results_rand_zero_one().at(j));
		}
		for (int j = 0; j < CTP_kernel_vector_.at(i)->get_results_rand_zero_one().size(); j++)
		{
			numbers_zero_one.push_back(CTP_kernel_vector_.at(i)->get_results_rand_zero_one().at(j));
		}
		for (int j = 0; j < CRP_kernel_vector_.at(i)->get_results_rand_zero_one().size(); j++)
		{
			numbers_zero_one.push_back(CRP_kernel_vector_.at(i)->get_results_rand_zero_one().at(j));
		}
	}
	//RAND EXP
	for (int j = 0; j < TER_kernel_->get_results_rand_exp().size(); j++)
	{
		numbers_exp.push_back(TER_kernel_->get_results_rand_exp().at(j));
	}
	//RAND MAX MIN
	for (int j = 0; j < TER_kernel_->get_results_rand_max_min().size(); j++)
	{
		numbers_max_min.push_back(TER_kernel_->get_results_rand_max_min().at(j));
	}
	//RAND ZERO ONE
	for (int j = 0; j < TER_kernel_->get_results_rand_zero_one().size(); j++)
	{
		numbers_zero_one.push_back(TER_kernel_->get_results_rand_zero_one().at(j));
	}
	std::string place_to_put_file = "./" + std::to_string(sym_numb) + "/randExp.txt";
	std::ofstream output_file1(place_to_put_file);
	std::ostream_iterator<double> output_iterator1(output_file1, "\n");
	std::copy(numbers_exp.begin(), numbers_exp.end(), output_iterator1);
	//
	place_to_put_file = "./" + std::to_string(sym_numb) + "/randMaxMin.txt";
	std::ofstream output_file2(place_to_put_file);
	std::ostream_iterator<double> output_iterator2(output_file2, "\n");
	std::copy(numbers_max_min.begin(), numbers_max_min.end(), output_iterator2);
	//
	place_to_put_file = "./" + std::to_string(sym_numb) + "/randZeroOne.txt";
	std::ofstream output_file3(place_to_put_file);
	std::ostream_iterator<double> output_iterator3(output_file3, "\n");
	std::copy(numbers_zero_one.begin(), numbers_zero_one.end(), output_iterator3);
}
void WirelessNetwork::KernelToFile(int sym_numb)
{
	std::vector<double> numbers;
	for(int i=0 ; i<CGP_kernel_vector_.size() ; i++)
	{
		numbers.push_back(CGP_kernel_vector_.at(i)->get_kernel());
	}
	for (int i = 0; i < CTP_kernel_vector_.size(); i++)
	{
		numbers.push_back(CTP_kernel_vector_.at(i)->get_kernel());
	}
	for (int i = 0; i < CRP_kernel_vector_.size(); i++)
	{
		numbers.push_back(CRP_kernel_vector_.at(i)->get_kernel());
	}
	numbers.push_back(TER_kernel_->get_kernel());
	// Save data to file
	std::string place_to_put_file = "./" + std::to_string(sym_numb) + "/kernel.txt";
	std::ofstream output_file(place_to_put_file);
	std::ostream_iterator<double> output_iterator(output_file, "\n");
	std::copy(numbers.begin(), numbers.end(), output_iterator);
	
}

void WirelessNetwork::GeneratePacket(Logger* logger, Transmitter* transmitter, int time)
{
	//int packet_time_transmission = 10;
	int packet_time_transmission = get_ctp_kernel_vector().at(transmitter->get_tansmitter_id()-1)->randMaxMin(100, 10);
	Packets *packet = new Packets(packet_time_transmission, transmitter -> get_tansmitter_id(),time);	//czas dodania pakietu do bufora
	std::queue<Packets*> local_buffer = transmitter->get_buffer();
	if(local_buffer.empty())
	{
		transmitter->set_time_to_scan_channel(0); // odrazu po wygenerowaniu pakietu rozpocznij skanowanie, ale tylko jesli jest to pierwszy pakiet
	}
	else
	{
		transmitter->set_time_to_scan_channel(transmitter->get_time_to_scan_channel());
	}
	local_buffer.push(packet);
	if(local_buffer.empty())
	{
		std::cout << "error bufer pusty";
	}
	transmitter->set_buffer(local_buffer);

}
	
void WirelessNetwork::CheckIfChannelFree(Logger* logger, Transmitter* transmitter, Channel* channel, Receiver* receiver) 
{
	std::string message = "->Transmitter nr: " + std::to_string(transmitter->get_tansmitter_id()) + " is scanning channel";
	logger->Info(message);
	if(channel->is_if_channel_free())
	{
		logger->Info("Channel is free.");
		transmitter->set_time_to_scan_channel(-1);
		if(!transmitter->get_buffer().empty())
		{
			transmitter->set_start_transmission_flag(true);
		}
		transmitter->set_start_transmission_flag(true);
	}
	else
	{
		logger->Info("Channel is busy.");
		transmitter->set_time_to_scan_channel(5); // 0.5 ms if busy

	}
}

void WirelessNetwork::StartTransmission(Logger* logger, Channel* channel, Transmitter* transmitter, Receiver* receiver, Statistics* stats)
{
	std::string message = "->Start transmission in transmitter nr: " + std::to_string(transmitter->get_tansmitter_id());
	logger->Info(message);
	std::queue<Packets*> local_transmitter_buffer = transmitter->get_buffer();
	if (local_transmitter_buffer.empty())
	{
		std::cout << "Error StartTransmission";
	}
	if (stats->get_correct_send_packet_number2() > stats->get_packet_number_to_start_collect_data()) 
	{
		// PACKET WAIT TIME DATA
			int result =stats->get_current_simulation_time() - local_transmitter_buffer.front()->get_time_packet_added_to_buffer();
		std::vector<double> temporary_vector = stats->get_packet_send_vector();
		temporary_vector.push_back(result);
		stats->set_packet_wait_time_vector(temporary_vector);
		
	}
	transmitter->set_start_transmission_flag(false);
	channel->set_if_channel_free(false);
	std::vector<Packets*> local_channel_vector = channel->get_in_channel_vector();
	
	local_channel_vector.push_back(local_transmitter_buffer.front()); // adding the oldest packet to channel vector
	// Set the longest packet time transmission as channel busy time
	transmitter->set_time_to_ask_ack(local_transmitter_buffer.front()->get_packet_time_transmission()); //ACK send  time
	if(channel->get_time_channel_busy()< local_transmitter_buffer.front()->get_packet_time_transmission())
	{
		channel->set_time_channel_busy(local_transmitter_buffer.front()->get_packet_time_transmission());
	}


	//checking if is it collision in channel
	
	if (local_channel_vector.size() == 1)
	{
		channel->set_if_collision(false);

	}
	else
	{
		channel->set_if_collision(true);

	}

	// checking if TER error exist
	if(TER_kernel_->randZeroONe(0.2) == 1)
	{
		receiver->set_ter_error(true);

	}
	else
	{
		receiver->set_ter_error(false);
;
	}	
	channel->set_in_channel_vector(local_channel_vector);

	int wait_for_ack = ack_time_ + channel -> get_in_channel_vector().back()->get_packet_time_transmission(); //CTPk + CTIZ	
	transmitter->set_time_to_wait_for_ack(wait_for_ack); //here will be set time to wait for ack

}
void WirelessNetwork::SendACK(Logger* logger, Channel* channel, Receiver* receiver, Transmitter* transmitter)
{
	if(channel->is_if_collision()==false && receiver->is_ter_error()==false)
	{
		//channel stay busy for time to transmit ACK
		channel->set_time_channel_busy(ack_time_);
		
		//clear vector of packets in channel
		std::vector<Packets*> local_channel_vector = channel->get_in_channel_vector();
		local_channel_vector.clear();
		channel->set_in_channel_vector(local_channel_vector);
		receiver->set_send_ack(true);
		transmitter->set_time_to_ask_ack(-1);
		
	}
	else
	{
		// wait for the longest packet time transmission end
		if(channel->get_time_channel_busy() == 0)
		{
			//clear vecotr of packets in channel
			std::vector<Packets*> local_channel_vector = channel->get_in_channel_vector();
			local_channel_vector.clear();
			channel->set_in_channel_vector(local_channel_vector);
			channel->set_if_channel_free(true);

			channel->set_time_channel_busy(-1);
		}
		

		receiver->set_send_ack(false);
		transmitter->set_time_to_ask_ack(-1);
	}
}
void WirelessNetwork::StopWaitForACK(Logger* logger, Receiver* receiver, Transmitter* transmitter, Channel* channel)
{

	//
	if(receiver->is_send_ack() == true)
	{
	
	}
	else
	{

	}
}

void WirelessNetwork::EndTransmission(Logger* logger, Transmitter* transmitter, Channel* channel, Statistics* stats)
{
	std::queue<Packets*> local_buffer = transmitter->get_buffer();
	if(stats->get_correct_send_packet_number2() > stats->get_packet_number_to_start_collect_data())
	{
		//packet send counter
		std::vector<double> temporary_vector = stats->get_packet_send_vector();
		double counter = temporary_vector.at(transmitter->get_tansmitter_id() - 1) + 1.0;
		temporary_vector.at(transmitter->get_tansmitter_id() - 1) = counter;
		stats->set_packet_send_vector(temporary_vector);
		
		//packet success retransmission counter
		temporary_vector = stats->get_succes_packet_retransmission_vector();
		//liczba retransmisji potrzebna do sukcesu
		int packet_retransmission_number =transmitter->get_buffer().front()->get_retransmission_number();
		temporary_vector.push_back(double(packet_retransmission_number));
		stats->set_succes_packet_retransmission_vector(temporary_vector);
		//correct succes transmission counter
		
		int correct_send_packet_counter = stats->get_correct_send_packet_number();
		correct_send_packet_counter += 1.0;
		stats->set_correct_send_packet_number(correct_send_packet_counter);
		
		//time when packet left buffer counter
		double result = stats->get_current_simulation_time() - 10 - local_buffer.front()->get_time_packet_added_to_buffer();
		temporary_vector = stats->get_packet_delay_vector();
		temporary_vector.push_back(result);
		stats->set_packet_delay_vector(temporary_vector);
	}
	else
	{
		int correct_send_packet_counter2 = stats->get_correct_send_packet_number2();
		correct_send_packet_counter2 += 1.0;
		stats->set_correct_send_packet_number2(correct_send_packet_counter2);
	}
	local_buffer.pop();
	transmitter->set_buffer(local_buffer);
	if(local_buffer.empty())
	{
		transmitter->set_time_to_scan_channel(-1);
	}
	else
	{
		transmitter->set_time_to_scan_channel(0);
	}
	channel->set_if_channel_free(true);
	channel->set_time_channel_busy(-1); // <-----------------

	transmitter->set_time_to_wait_for_ack(-1);
	
}

void WirelessNetwork::Retransmission(Logger* logger, Transmitter* transmitter, Channel* channel, Statistics* stats)
{
	std::queue<Packets*> local_buffer = transmitter->get_buffer();
	int retransmission_number = local_buffer.front()->get_retransmission_number();

	if(retransmission_number < max_retransmission_number_)
	{

		retransmission_number++;
		transmitter->get_buffer().front()->set_retransmission_number(retransmission_number);
		
		


		transmitter->set_time_to_retransmission(generate_time_to_retransmission(transmitter));
		transmitter->set_time_to_scan_channel(transmitter->get_time_to_retransmission()); // try to start transmssion after CRP time

		transmitter->set_time_to_wait_for_ack(-1);
		
	}
	else
	{
		if(stats->get_correct_send_packet_number2()>stats->get_packet_number_to_start_collect_data())
		{
			//lost packet counter
			std::vector<double> temporary_vector = stats->get_packet_lost_vector();
			double count = temporary_vector.at(transmitter->get_tansmitter_id() - 1) + 1.0;
			temporary_vector.at(transmitter->get_tansmitter_id()-1)= count;
			stats->set_packet_lost_vector(temporary_vector);
		}

		std::queue<Packets*> local_buffer = transmitter->get_buffer();
		local_buffer.pop();
		transmitter->set_buffer(local_buffer);
		if (local_buffer.empty())
		{
			transmitter->set_time_to_scan_channel(-1);
		}
		else
		{
			transmitter->set_time_to_scan_channel(0);
		}

		transmitter->set_time_to_wait_for_ack(-1);
	}
}

int WirelessNetwork::generate_time_to_retransmission(Transmitter* transmitter)
{
	int CTP = transmitter->get_buffer().front()->get_packet_time_transmission(); //packet time transmission
	int r = transmitter->get_buffer().front()->get_retransmission_number(); //  retransmission number
	int pow = 2;
	if(r==1)
	{
		return CTP;
	}
	else
	{
		for(int i=0; i<r-1 ; i++)
		{
			pow = pow * 2;
		}
		int big_r = get_ctp_kernel_vector().at(transmitter->get_tansmitter_id()-1)->randMaxMin(pow-1, 0);//R <0,(2^r -1)>
		//int big_r = rand() % (pow + 1);;//R <0,(2^r -1)>
		return big_r;
	}
}

void print_queue(std::queue<Packets*> q)
{
	while (!q.empty())
	{
		std::cout << q.front() << " ";
		q.pop();
	}
	std::cout << std::endl;
}

