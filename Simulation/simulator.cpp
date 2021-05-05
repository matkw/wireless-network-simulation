#include "simulator.h"
#include "WirelessNetwork.h"
#include "generator.h"
#include "statistics.h"
#include <iostream>

Simulator::Simulator(UniformGenerator* root)
	: root(root)
{
}

	bool Simulator::is_step_or_not_step() const
	{
		return step_or_not_step_;
	}

	void Simulator::set_step_or_not_step(bool step_or_not_step)
	{
		step_or_not_step_ = step_or_not_step;
	}

void Simulator::simulation(int time, Logger* logger, int sym_numb, double lambda)
{
	WirelessNetwork* wireless_network = new WirelessNetwork();
	clock_ = 0;
	Statistics* stats = new Statistics(time, 320); // 320 is number of packet sends after this moment statistics start collecting data
	wireless_network->Initialization(logger, root);
	wireless_network->KernelToFile(sym_numb);
	if (step_or_not_step_==true)
	{
		system("pause");
	}
	for(int i = 0; i < wireless_network->get_k_number() ; i++)
	{
		int rand_number = int(round(wireless_network->get_cgp_kernel_vector().at(i)->randExp(lambda)));
		wireless_network->get_transmitter_vector().at(i)->set_time_to_generate_new_packet(rand_number);
		std::string message = "["+std::to_string(clock_)+"]  " +"Time to generate packet for transmitter nr: "+ std::to_string(i+1)+" is: " + std::to_string(rand_number);
		logger->Info(message);
		
	}
	if (step_or_not_step_ == true)
	{
		system("pause");
	}
	
	while(time >= 0)
	{
		std::string message = "[" + std::to_string(clock_) + "]  " + "Simulation time";
		logger->Info(message);
		bool event_trigger = true;
		while (event_trigger == true)
		{
			event_trigger = false;
			//Generate packet event
			for(int i = 0; i < wireless_network->get_k_number();i++)
			{
				if(wireless_network->get_transmitter_vector().at(i)->get_time_to_generate_new_packet() == 0)
				{
					std::string message = "[" + std::to_string(clock_) + "]  " + "->Generate Packet for transmitter nr: " + std::to_string(wireless_network->get_transmitter_vector().at(i)->get_tansmitter_id());
					logger->Info(message);
					wireless_network->GeneratePacket(logger, wireless_network->get_transmitter_vector().at(i), clock_);

					int rand_number = int(round(wireless_network->get_cgp_kernel_vector().at(i)->randExp(lambda)));
					wireless_network->get_transmitter_vector().at(i)->set_time_to_generate_new_packet(rand_number);
				
					event_trigger = true;
				}
			}
			
			
			//Send ACK
			for (int i = 0; i < wireless_network->get_k_number(); i++)
			{
				if(wireless_network->get_transmitter_vector().at(i)->get_time_to_ask_ack()==0)
				{

					wireless_network->SendACK(logger, wireless_network->get_channel(), wireless_network->get_receiver_vector().at(i), wireless_network->get_transmitter_vector().at(i));
					event_trigger = true;
				}
			}
			
			//End transmission
			for (int i = 0; i < wireless_network->get_k_number(); i++)
			{
				if(wireless_network->get_receiver_vector().at(i)->is_send_ack() == true && wireless_network->get_transmitter_vector().at(i)->get_time_to_wait_for_ack()==0)
				{
				
					wireless_network->EndTransmission(logger, wireless_network->get_transmitter_vector().at(i), wireless_network->get_channel(),stats);
					event_trigger = true;
					if (stats->get_correct_send_packet_number2() > stats->get_packet_number_to_start_collect_data()) 
					{
						stats->results_of_average_retransmission_number_per_moment();
					}
				}
			}

			//Retransmission
			for (int i = 0; i < wireless_network->get_k_number(); i++)
			{
				if (wireless_network->get_receiver_vector().at(i)->is_send_ack() == false && wireless_network->get_transmitter_vector().at(i)->get_time_to_wait_for_ack() == 0)
				{
					
					wireless_network->Retransmission(logger, wireless_network->get_transmitter_vector().at(i), wireless_network->get_channel(),stats);
					event_trigger = true;
				}
			}

			//Scan channel
			for(int i = 0 ; i < wireless_network-> get_k_number(); i++)
			{
				if(wireless_network->get_transmitter_vector().at(i)->get_time_to_scan_channel() == 0)
				{
				
					wireless_network->CheckIfChannelFree(logger, wireless_network->get_transmitter_vector().at(i), wireless_network->get_channel(), wireless_network->get_receiver_vector().at(i));
					event_trigger = true;
				}
			}

			//Start transmission
			for (int i = 0; i < wireless_network->get_k_number(); i++)
			{
				if(wireless_network->get_transmitter_vector().at(i)->is_start_transmission_flag())
				{
				
					wireless_network->StartTransmission(logger, wireless_network->get_channel(), wireless_network->get_transmitter_vector().at(i), wireless_network->get_receiver_vector().at(i),stats);
					event_trigger = true;
				}
			}

		}
		if (step_or_not_step_ == true)
		{
			system("pause");
		}
		//update time
		time -= 1;
		clock_ += 1;
		stats->set_current_simulation_time(clock_);
		for (int i = 0; i < wireless_network->get_k_number(); i++)
		{
			wireless_network->get_transmitter_vector().at(i)->set_time_to_generate_new_packet(wireless_network->get_transmitter_vector().at(i)-> get_time_to_generate_new_packet()-1);
			wireless_network->get_transmitter_vector().at(i)->set_time_to_wait_for_ack(wireless_network->get_transmitter_vector().at(i)->get_time_to_wait_for_ack() - 1);
			wireless_network->get_transmitter_vector().at(i)->set_time_to_scan_channel(wireless_network->get_transmitter_vector().at(i)->get_time_to_scan_channel() - 1);
			wireless_network->get_transmitter_vector().at(i)->set_time_to_ask_ack(wireless_network->get_transmitter_vector().at(i)->get_time_to_ask_ack() - 1);
		}
		wireless_network->get_channel()->set_time_channel_busy(wireless_network->get_channel()->get_time_channel_busy() - 1);
	}
	wireless_network->GetDataToFiles(sym_numb); // zmienic na zmienna
	stats->stage_phase_data_to_file(sym_numb);
	stats->ShowStats();
}
