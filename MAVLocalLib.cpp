#pragma region Docs
// ====================================================================================
// 	File Name:	MAVLocalLib.cpp	MAVLINK_MSG_ID_COMMAND_ACK 
//	Author:		Ulrich Sucker      
// -------------------------------------------------------------------------------------
// 	Version 00.03 - 2024-04-011
//   - added: MAVLINK_MSG_ID_COMMAND_ACK
//
// -------------------------------------------------------------------------------------
// 	Version 00.02 - 2024-04-07
//   - Class UDPConnectSrvr
//		DPConnectSrvr::UDPConnectSrvr(int UDPport)
//		UDPConnectSrvr::~UDPConnectSrvr()
//		bool UDPConnectSrvr::RecMAVmsg()
//
// -------------------------------------------------------------------------------------
// 	Version 00.01 - 2024-03-18
//   - Base
// -------------------------------------------------------------------------------------
#define MAVLocalLib_CPP_Version "00.03.014"
// =====================================================================================
#pragma endregion

/* ---- include Header ----------------------------------------------------------------- */ 
#include "MAVLocalLib.hpp"


// ==== FUNCTION: initMAVmessages =============================================================
void initMAVmessages()
{
	for (int i = 0; i < mavMsgCnt; i++){
		mavMessages[i].printLong = false;
		mavMessages[i].printShort = false;
	}
};

// ==== FUNCTION: mavPrint =============================================================
void mavPrint(std::string text){
	std::cout << text;
};
void mavPrint(char* text){
	std::cout << text;
};
void mavPrint(int text){
	std::cout << text;
};

// ==== FUNCTION: mavPrintLn =============================================================
void mavPrintLn(std::string text){
	std::cout << text <<std::endl;
};
void mavPrintLn(char* text){
	std::cout << (char *)text <<std::endl;
};
void mavPrintLn(int  text){
	std::cout << text <<std::endl;
};

/* ==== CLASS: UDPConnectSrvr ============================================================== *
	This function creates a server socket
 * ========================================================================================= */
UDPConnectSrvr::UDPConnectSrvr(int UDPport) {
	// initialise winsock
	printf("Initialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Failed. Error Code: %d", WSAGetLastError());
		exit(0);
	}
	printf("Initialised.\n");

	// create a socket
	if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket: %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Socket created.\n");

	// prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(UDPport);

	// bind
	if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done.");
}

UDPConnectSrvr::~UDPConnectSrvr() {
	closesocket(server_socket);
	WSACleanup();
}

bool UDPConnectSrvr::RecMAVmsg() {
	while (!exitRequested) {
		// Define receive buffer 
		char message[BUFLEN] = {};

		// try to receive some data, this is a blocking call
		int message_len;
		int slen = sizeof(sockaddr_in);

		// Create a nonblocking request
		fd_set recv_set;
		timeval tv = {0, 10}; // 10usec
		FD_ZERO(&recv_set);
		FD_SET(server_socket, &recv_set);

		while (select(0, &recv_set, NULL, NULL, &tv) > 0) {
			/* recv... */
			FD_SET(server_socket, &recv_set); /* actually redundant, since it is already set */
			
			if ((message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen)) == SOCKET_ERROR) {
				printf("recvfrom() failed with error code: %d", WSAGetLastError());
				exit(0);
			};

			/* print details of the client/peer and the data received
			printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
			printf("Length: %i\t Data: %s", message_len, message);
			printf("\n");
			*/
			// try to decode the message char by char
			for (int p = 0; p <= message_len;p++) {
				uint8_t receive_char = message[p];
				if (mavlink_parse_char(MAVLINK_COMM_0,
									receive_char,
									&mav_msg,
									&mav_msg_status)) {
					return true; 	// Return "true" if success. 
									// The result can be found in the globel variables "mav_msg" and "mav_msg_status"
				}
			}
		}
	}
	return false;
}

bool UDPConnectSrvr::SndMAVmsg()
{

}

// ==== FUNCTION: printMAVlinkMessage ==================================================
void printMAVlinkMessage(mavlink_message_t mav_msg, bool prntSrt, bool prntLng)
{
	// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
	/*
	if (prntSrt == true){
		// std::cout << "Short "; 
		mavPrint((char *)"Short ");
	}
	if (prntLng == true){
		//std::cout << "Long ";
		mavPrint((char *)"Long ");
		
	}
	//std::cout << ":" <<std::endl; 
	mavPrintLn((char *)":");
	*/
	// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-


	switch (mav_msg.msgid) {
	// ====  #0: Heartbeat =============================================================	
	case MAVLINK_MSG_ID_HEARTBEAT:
		if (prntSrt) {
			mavPrintLn((char *)"#000:  Hard beat");
		}
		if (prntLng) {
			mavPrintLn((char *)"\n#000   Hard Beat");
			mavlink_heartbeat_t hb;
			mavlink_msg_heartbeat_decode(&mav_msg, &hb);
		    mavPrint((char *)"State        : "); mavPrintLn(hb.base_mode == 209 ? "Armed" : "Disarmed");
			mavPrint((char *)"Mode         : ");
			switch(hb.custom_mode) {
			case 0:
				mavPrintLn((char *)"Manual");
				break;
			case 1:
				mavPrintLn((char *)"Circle");
				break;
			case 2:
				mavPrintLn((char *)"Stabilize");
				break;
			case 3:
				mavPrintLn((char *)"Training");
			  break;
			  case 5:
				mavPrintLn((char *)"FBWA");
	          break;
              case 6:
                mavPrintLn((char *)"FBWB");
              break;
              case 7:
                mavPrintLn((char *)"Cruise");
              break;
              case 8:
                mavPrintLn((char *)"AUTOTUNE");
              break;
              case 10:
                mavPrintLn((char *)"Auto");
              break;
              case 11:
                mavPrintLn((char *)"RTL");
              break;
              case 12:
                mavPrintLn((char *)"Loiter");
              break;
              case 13:
                mavPrintLn((char *)"Take Off");
              break;
              case 14:
                mavPrintLn((char *)"Avoid ADSB");
              break;
              case 15:
                mavPrintLn((char *)"Guided");
              break;
              case 17:
                mavPrintLn((char *)"QStabilize");
              break;
              case 18:
                mavPrintLn((char *)"QHover");
              break;
              case 19:
                mavPrintLn((char *)"QLoiter");
              break;
              case 20:
                mavPrintLn((char *)"QLand");
              break;
              case 21:
                mavPrintLn((char *)"QRTL");
              break;
              case 22:
                mavPrintLn((char *)"QAutoTune");
              break;
              case 23:
                mavPrintLn((char *)"QAcro");
              break;
              case 24:
                mavPrintLn((char *)"Thermal");
              break;
              case 25:
                mavPrintLn((char *)"Loiter to QLand");
              break;
              default:
                mavPrint((char *)"Mode "); 
                mavPrint(hb.custom_mode); 
                mavPrintLn((char *)" not known");
              break;
            }
            mavPrint((char *)"type         : "); mavPrintLn(hb.type);
            mavPrint((char *)"autopilot    : "); mavPrintLn(hb.autopilot);
            mavPrint((char *)"system_status: "); mavPrintLn(hb.system_status);     	
		}
		break;
		
	// =====  #1: SYS_STATUS ===========================================
	case MAVLINK_MSG_ID_SYSTEM_TIME:  // #2 MAVLINK_MSG_ID_SYSTEM_TIME
		if (prntSrt) {
			mavPrintLn((char *)"#001:  SYS_STATUS");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#001:  SYS_STATUS");

			mavlink_sys_status_t sys_status;
            mavlink_msg_sys_status_decode(&mav_msg, &sys_status);
           
            mavPrint((char *)"onboard_control_sensors_present : "); 
            mavPrintLn(sys_status.onboard_control_sensors_present);
           
            mavPrint((char *)"onboard_control_sensors_enabled : "); 
            mavPrintLn(sys_status.onboard_control_sensors_enabled);
            
            mavPrint((char *)"onboard_control_sensors_health  : "); 
            mavPrintLn(sys_status.onboard_control_sensors_health);
            
            mavPrint((char *)"load             : "); 
            mavPrintLn(sys_status.load);
            
            mavPrint((char *)"voltage_battery  : "); 
            mavPrintLn(sys_status.voltage_battery);
            
            mavPrint((char *)"current_battery  : "); 
            mavPrintLn(sys_status.current_battery);

            mavPrint((char *)"drop_rate_comm   : "); 
            mavPrintLn(sys_status.drop_rate_comm);
/*         
            mavPrint((char *)"errors_comm      : "); 
            mavPrintLn(sys_status.errors_comm);
               
            mavPrint((char *)"errors_count1    : "); 
            mavPrintLn(sys_status.errors_count1);
            
            mavPrint((char *)"errors_count2    : "); 
            mavPrintLn(sys_status.errors_count2);
            
            mavPrint((char *)"errors_count3    : "); 
            mavPrintLn(sys_status.errors_count3);
            
            mavPrint((char *)"errors_count4    : "); 
            mavPrintLn(sys_status.errors_count4);
*/            
            mavPrint((char *)"battery_remaining: "); 
            mavPrintLn(sys_status.battery_remaining);			
		}
		break;
		
	// =====  #2 MAVLINK_MSG_ID_SYSTEM_TIME   ==========================
	case MAVLINK_MSG_ID_SYS_STATUS:  
		if (prntSrt) {
			mavPrintLn((char *)"#002:  MAVLINK_MSG_ID_SYSTEM_TIME");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#002:  MAVLINK_MSG_ID_SYSTEM_TIME");
		}		
		break;
		
	// =====  #21 MAVLINK_MSG_ID_PARAM_REQUEST_LIST ====================
	case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
		if (prntSrt) {
			mavPrintLn((char *)"#021:  MAVLINK_MSG_ID_PARAM_REQUEST_LIST");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#021:  MAVLINK_MSG_ID_PARAM_REQUEST_LIST");
            mavlink_command_long_t packet;
            mavlink_msg_command_long_decode(&mav_msg, &packet);
            mavPrint((char *)"command:");mavPrintLn(packet.command);
            mavPrint((char *)"target_system:    ");mavPrintLn(packet.target_system);
            mavPrint((char *)"target_component: ");mavPrintLn(packet.target_component);
            mavPrint((char *)"          param1: ");mavPrintLn(packet.param1);
            mavPrint((char *)"          param2: ");mavPrintLn(packet.param2);
            mavPrint((char *)"          param3: ");mavPrintLn(packet.param3);
            mavPrint((char *)"          param4: ");mavPrintLn(packet.param4);
            mavPrint((char *)"          param5: ");mavPrintLn(packet.param5);
            mavPrint((char *)"          param6: ");mavPrintLn(packet.param6);
            mavPrint((char *)"          param7: ");mavPrintLn(packet.param7);			
		}
		break;
		
	// =====  #22: PARAM_VALUE =========================================
	case MAVLINK_MSG_ID_PARAM_VALUE: 
		if (prntSrt) {
			mavPrintLn((char *)"#022:  Parameter Value");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#022:  Parameter Value");
            mavlink_param_value_t param_value;
            mavlink_msg_param_value_decode(&mav_msg, &param_value);
            mavPrint((char *)"ID:    ");mavPrintLn(param_value.param_id);
            mavPrint((char *)"Value: ");mavPrintLn(param_value.param_value);
            mavPrint((char *)"Count: ");mavPrintLn(param_value.param_count);
            mavPrint((char *)"Index: ");mavPrintLn(param_value.param_index);
            mavPrint((char *)"Type:  ");mavPrintLn(param_value.param_type);			
		}
		break;

	// =====  #23 MAVLINK_MSG_ID_PARAM_SET =============================
	case MAVLINK_MSG_ID_PARAM_SET:
		if (prntSrt) {
			mavPrintLn((char *)"#023:  MAVLINK_MSG_ID_PARAM_SET");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#023:  MAVLINK_MSG_ID_PARAM_SET");
            mavlink_param_set_t param_set;
            mavlink_msg_param_set_decode(&mav_msg, &param_set);
            
            mavPrint((char *)"param_value:    ");
            mavPrintLn(param_set.param_value);
            
            mavPrint((char *)"target_system:    ");
            mavPrintLn(param_set.target_system);
            
            mavPrint((char *)"target_component:    ");
            mavPrintLn(param_set.target_component);
            
            mavPrint((char *)"param_type:    ");
            mavPrintLn(param_set.param_type);			
		}		
		break;
		
	// =====  #24 MAVLINK_MSG_ID_GPS_RAW_INT ===========================
	case MAVLINK_MSG_ID_GPS_RAW_INT:
		if (prntSrt) {
			mavPrintLn((char *)"#024:  MAVLINK_MSG_ID_GPS_RAW_INT");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#024:  MAVLINK_MSG_ID_GPS_RAW_INT");
		}		
		break;
		
	// =====  #27: RAW_IMU =============================================
	case MAVLINK_MSG_ID_RAW_IMU:
		if (prntSrt) {
			mavPrintLn((char *)"#027:  RAW_IMU");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#027: Raw IMU Data ___________");

            mavlink_raw_imu_t raw_imu;
            mavlink_msg_raw_imu_decode(&mav_msg, &raw_imu);

            mavPrint((char *)"       xacc:  "); mavPrintLn(raw_imu.xacc);
            mavPrint((char *)"       yacc:  "); mavPrintLn(raw_imu.yacc);
            mavPrint((char *)"       zacc:  "); mavPrintLn(raw_imu.zacc);
            mavPrint((char *)"       xgyro: "); mavPrintLn(raw_imu.xgyro);
            mavPrint((char *)"       ygyro: "); mavPrintLn(raw_imu.ygyro);
            mavPrint((char *)"       zgyro: "); mavPrintLn(raw_imu.zgyro);
            mavPrint((char *)"       xmag:  "); mavPrintLn(raw_imu.xmag);
            mavPrint((char *)"       ymag:  "); mavPrintLn(raw_imu.ymag);
            mavPrint((char *)"       zmag:  "); mavPrintLn(raw_imu.zmag);			
		}		
		break;
		
	// =====  #29: MAVLINK_MSG_ID_SCALED_PRESSURE ======================
	case MAVLINK_MSG_ID_SCALED_PRESSURE:  // 
		if (prntSrt) {
			mavPrintLn((char *)"#029:  MAVLINK_MSG_ID_SCALED_PRESSURE");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#029:  MAVLINK_MSG_ID_SCALED_PRESSURE");
		}		
		break;
		
	// =====   #30: MAVLINK_MSG_ID_ATTITUDE ============================
	case MAVLINK_MSG_ID_ATTITUDE:
		if (prntSrt) {
			mavPrintLn((char *)"#030:  MAVLINK_MSG_ID_ATTITUDE");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#030:  MAVLINK_MSG_ID_ATTITUDE");
		}		
		break;
		
	// =====  #32: MAVLINK_MSG_ID_LOCAL_POSITION_NED ===================
	case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
		if (prntSrt) {
			mavPrintLn((char *)"#032:  MAVLINK_MSG_ID_LOCAL_POSITION_NED");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#032:  MAVLINK_MSG_ID_LOCAL_POSITION_NED");
		}		
		break;

	// =====  #33: MAVLINK_MSG_ID_GLOBAL_POSITION_INT ==================
	case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
		if (prntSrt) {
			mavPrintLn((char *)"#033:  MAVLINK_MSG_ID_GLOBAL_POSITION_INT");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#033:  MAVLINK_MSG_ID_GLOBAL_POSITION_INT");
		}		
		break;

	// =====  #36: MAVLINK_MSG_ID_SERVO_OUTPUT_RAW ======================
	case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
		if (prntSrt) {
			mavPrintLn((char *)"#036:  MAVLINK_MSG_ID_SERVO_OUTPUT_RAW");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#036:  MAVLINK_MSG_ID_SERVO_OUTPUT_RAW");
		}
		break;
		
	// =====  #42: MAVLINK_MSG_ID_MISSION_CURRENT ======================
	case MAVLINK_MSG_ID_MISSION_CURRENT:
		if (prntSrt) {
			mavPrintLn((char *)"#042:  MAVLINK_MSG_ID_MISSION_CURRENT");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#042:  MAVLINK_MSG_ID_MISSION_CURRENT");
		}
		break;
		
	// =====  #49: MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN ====================
	case MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN:
		if (prntSrt) {
			mavPrintLn((char *)"#049:  MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#049:  MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN");
		}
		break;
		
	// =====  #62: MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT ================
	case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:
		if (prntSrt) {
			mavPrintLn((char *)"#062:  MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#062:  MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT");
		}
		break;
		
	// =====  #65: MAVLINK_MSG_ID_RC_CHANNELS ==========================
	case MAVLINK_MSG_ID_RC_CHANNELS:
		if (prntSrt) {
			mavPrintLn((char *)"#065:  MAVLINK_MSG_ID_RC_CHANNELS");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#065:  MAVLINK_MSG_ID_RC_CHANNELS");
	        mavlink_rc_channels_t rc_channels;
            mavlink_msg_rc_channels_decode(&mav_msg, &rc_channels);
            mavPrint((char *)"# Channels:       "); mavPrintLn(rc_channels.chancount);
            mavPrint((char *)"RSSI:             "); mavPrintLn(rc_channels.rssi);
            mavPrint((char *)"RC Channel  1:    "); mavPrintLn(rc_channels.chan1_raw);
            mavPrint((char *)"RC Channel  2:    "); mavPrintLn(rc_channels.chan2_raw);
            mavPrint((char *)"RC Channel  3:    "); mavPrintLn(rc_channels.chan3_raw);
            mavPrint((char *)"RC Channel  4:    "); mavPrintLn(rc_channels.chan4_raw);
            mavPrint((char *)"RC Channel  5:    "); mavPrintLn(rc_channels.chan5_raw);
            mavPrint((char *)"RC Channel  6:    "); mavPrintLn(rc_channels.chan6_raw);
            mavPrint((char *)"RC Channel  7:    "); mavPrintLn(rc_channels.chan7_raw);
            mavPrint((char *)"RC Channel  8:    "); mavPrintLn(rc_channels.chan8_raw);
            mavPrint((char *)"RC Channel  9:    "); mavPrintLn(rc_channels.chan9_raw);
            mavPrint((char *)"RC Channel 10:    "); mavPrintLn(rc_channels.chan10_raw);
            mavPrint((char *)"RC Channel 11:    "); mavPrintLn(rc_channels.chan11_raw);
            mavPrint((char *)"RC Channel 12:    "); mavPrintLn(rc_channels.chan12_raw);
            mavPrint((char *)"RC Channel 13:    "); mavPrintLn(rc_channels.chan13_raw);
            mavPrint((char *)"RC Channel 14:    "); mavPrintLn(rc_channels.chan14_raw);
            mavPrint((char *)"RC Channel 15:    "); mavPrintLn(rc_channels.chan15_raw);
            mavPrint((char *)"RC Channel 16:    "); mavPrintLn(rc_channels.chan16_raw);
            mavPrint((char *)"RC Channel 17:    "); mavPrintLn(rc_channels.chan17_raw);
            mavPrint((char *)"RC Channel 18:    "); mavPrintLn(rc_channels.chan18_raw);
		}
		break;
		
	// =====  #66: MAVLINK_MSG_ID_REQUEST_DATA_STREAM ==================
	case MAVLINK_MSG_ID_REQUEST_DATA_STREAM :
		if (prntSrt) {
			mavPrintLn((char *)"#066:  MAVLINK_MSG_ID_REQUEST_DATA_STREAM");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#066:  MAVLINK_MSG_ID_REQUEST_DATA_STREAM");
		}
		break;
		
	// =====  #74: MAVLINK_MSG_ID_VFR_HUD ==============================
	case MAVLINK_MSG_ID_VFR_HUD:
		if (prntSrt) {
			mavPrintLn((char *)"#074:  MAVLINK_MSG_ID_VFR_HUD");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#074:  MAVLINK_MSG_ID_VFR_HUD");
		}
		break;
		
	// =====  #76: MAVLINK_MSG_ID_COMMAND_LONG =========================
	case MAVLINK_MSG_ID_COMMAND_LONG:
		if (prntSrt) {
			mavPrintLn((char *)"#076:  MAVLINK_MSG_ID_COMMAND_LONG");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#076:  MAVLINK_MSG_ID_COMMAND_LONG");
            mavlink_command_long_t command_long;
            mavlink_msg_command_long_decode(&mav_msg, &command_long);		

            mavPrint((char *)"target_system    : "); mavPrintLn(command_long.target_system);
            mavPrint((char *)"target_component : "); mavPrintLn(command_long.target_component);
            mavPrint((char *)"command          : "); mavPrintLn(command_long.command);
            mavPrint((char *)"confirmation     : "); mavPrintLn(command_long.confirmation);
            mavPrint((char *)"param1           : "); mavPrintLn(command_long.param1);
            mavPrint((char *)"param2           : "); mavPrintLn(command_long.param2);
            mavPrint((char *)"param3           : "); mavPrintLn(command_long.param3);
            mavPrint((char *)"param4           : "); mavPrintLn(command_long.param4);
            mavPrint((char *)"param5           : "); mavPrintLn(command_long.param5);
            mavPrint((char *)"param6           : "); mavPrintLn(command_long.param6);
            mavPrint((char *)"param7           : "); mavPrintLn(command_long.param7);			
		}
		break;

	// =====  #77: MAVLINK_MSG_ID_COMMAND_ACK  ==============================
	/*
	* @brief Decode a command_ack message into a struct
	*
	* @param msg The message to decode
	* @param command_ack C-struct to decode the message contents into
	*
	static inline void mavlink_msg_command_ack_decode(const mavlink_message_t* msg, mavlink_command_ack_t* command_ack)
	{
	#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
		command_ack->command = mavlink_msg_command_ack_get_command(msg);
		command_ack->result = mavlink_msg_command_ack_get_result(msg);
		command_ack->progress = mavlink_msg_command_ack_get_progress(msg);
		command_ack->result_param2 = mavlink_msg_command_ack_get_result_param2(msg);
		command_ack->target_system = mavlink_msg_command_ack_get_target_system(msg);
		command_ack->target_component = mavlink_msg_command_ack_get_target_component(msg);
	#else
			uint8_t len = msg->len < MAVLINK_MSG_ID_COMMAND_ACK_LEN? msg->len : MAVLINK_MSG_ID_COMMAND_ACK_LEN;
			memset(command_ack, 0, MAVLINK_MSG_ID_COMMAND_ACK_LEN);
		memcpy(command_ack, _MAV_PAYLOAD(msg), len);
	#endif
	}
	*/
	case MAVLINK_MSG_ID_COMMAND_ACK:
		if (prntSrt) {
			mavPrintLn((char *)"#077:  MAVLINK_MSG_ID_COMMAND_ACK ");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#077:  MAVLINK_MSG_ID_COMMAND_ACK ");
			mavlink_command_ack_t* command_ack;
            //mavlink_msg_command_ack_decode(&mav_msg, command_ack);
			
			mavPrint((char *)" Command          : "); mavPrintLn(mavlink_msg_command_ack_get_command(&mav_msg));
			mavPrint((char *)" Result           : "); mavPrintLn(mavlink_msg_command_ack_get_result(&mav_msg));
			mavPrint((char *)" Progress         : "); mavPrintLn(mavlink_msg_command_ack_get_progress(&mav_msg));
			mavPrint((char *)" Result Param2    : "); mavPrintLn(mavlink_msg_command_ack_get_result_param2(&mav_msg));
			mavPrint((char *)" Target System    : "); mavPrintLn(mavlink_msg_command_ack_get_target_system(&mav_msg));
			mavPrint((char *)" Target Component : "); mavPrintLn(mavlink_msg_command_ack_get_target_component(&mav_msg));
		}
		break;	

	// =====  #87: MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT ===========
	/*
	 * @brief Decode a position_target_global_int message into a struct
	 *
	 * @param msg The message to decode
	 * @param position_target_global_int C-struct to decode the message contents into
	 

	static inline void mavlink_msg_position_target_global_int_decode(const mavlink_message_t* msg, mavlink_position_target_global_int_t* position_target_global_int)
	{
	#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
		position_target_global_int->time_boot_ms = mavlink_msg_position_target_global_int_get_time_boot_ms(msg);
		position_target_global_int->lat_int = mavlink_msg_position_target_global_int_get_lat_int(msg);
		position_target_global_int->lon_int = mavlink_msg_position_target_global_int_get_lon_int(msg);
		position_target_global_int->alt = mavlink_msg_position_target_global_int_get_alt(msg);
		position_target_global_int->vx = mavlink_msg_position_target_global_int_get_vx(msg);
		position_target_global_int->vy = mavlink_msg_position_target_global_int_get_vy(msg);
		position_target_global_int->vz = mavlink_msg_position_target_global_int_get_vz(msg);
		position_target_global_int->afx = mavlink_msg_position_target_global_int_get_afx(msg);
		position_target_global_int->afy = mavlink_msg_position_target_global_int_get_afy(msg);
		position_target_global_int->afz = mavlink_msg_position_target_global_int_get_afz(msg);
		position_target_global_int->yaw = mavlink_msg_position_target_global_int_get_yaw(msg);
		position_target_global_int->yaw_rate = mavlink_msg_position_target_global_int_get_yaw_rate(msg);
		position_target_global_int->type_mask = mavlink_msg_position_target_global_int_get_type_mask(msg);
		position_target_global_int->coordinate_frame = mavlink_msg_position_target_global_int_get_coordinate_frame(msg);
	#else
		uint8_t len = msg->len < MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT_LEN? msg->len : MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT_LEN;
		memset(position_target_global_int, 0, MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT_LEN);
		memcpy(position_target_global_int, _MAV_PAYLOAD(msg), len);
	#endif
	}
	*/
	case MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT:
		if (prntSrt) {
			mavPrintLn((char *)"#087:  MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#087:  MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT");
			
			mavlink_position_target_global_int_t* position_target_global_int;
			mavlink_msg_position_target_global_int_decode(&mav_msg,  position_target_global_int);
			
			//               "------------------------------- : "			
			mavPrint((char *)"time_boot_ms                    : "); 
            mavPrintLn(position_target_global_int->time_boot_ms);
			//               "------------------------------- : "			
			mavPrint((char *)"lat_int                         : "); 
            mavPrintLn(position_target_global_int->lat_int);
			//               "------------------------------- : "			
			mavPrint((char *)"lon_int                         : "); 
            mavPrintLn(position_target_global_int->lon_int);
			//               "------------------------------- : "			
			mavPrint((char *)"alt                             : "); 
            mavPrintLn(position_target_global_int->alt);
			//               "------------------------------- : "			
			mavPrint((char *)"vx                              : "); 
            mavPrintLn(position_target_global_int->vx);
			//               "------------------------------- : "			
			mavPrint((char *)"vy                              : "); 
            mavPrintLn(position_target_global_int->vy);
			//               "------------------------------- : "			
			mavPrint((char *)"vx                              : "); 
            mavPrintLn(position_target_global_int->vx);
			//               "------------------------------- : "			
			mavPrint((char *)"vz                              : "); 
            mavPrintLn(position_target_global_int->vz);
			//               "------------------------------- : "			
			mavPrint((char *)"afx                             : "); 
            mavPrintLn(position_target_global_int->afx);
			//               "------------------------------- : "			
			mavPrint((char *)"afy                             : "); 
            mavPrintLn(position_target_global_int->afy);
			//               "------------------------------- : "			
			mavPrint((char *)"afy                             : "); 
            mavPrintLn(position_target_global_int->afy);
			//               "------------------------------- : "			
			mavPrint((char *)"afz                             : "); 
            mavPrintLn(position_target_global_int->afz);
			//               "------------------------------- : "			
			mavPrint((char *)"yaw_rate                        : "); 
            mavPrintLn(position_target_global_int->yaw_rate);
			//               "------------------------------- : "			
			mavPrint((char *)"type_mask                       : "); 
            mavPrintLn(position_target_global_int->type_mask);
			//               "------------------------------- : "			
			mavPrint((char *)"coordinate_frame                : "); 
            mavPrintLn(position_target_global_int->coordinate_frame);
		}
		//std::cout << "#087:  MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT" << std::endl;
		break;
		
	// =====  #111: MAVLINK_MSG_ID_TIMESYNC ============================
	case MAVLINK_MSG_ID_TIMESYNC:
		if (prntSrt) {
			mavPrintLn((char *)"#111:  MAVLINK_MSG_ID_TIMESYNC");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#111:  MAVLINK_MSG_ID_TIMESYNC");
		}
		break;
		
	// =====  #116: MAVLINK_MSG_ID_SCALED_IMU2 =========================
	case MAVLINK_MSG_ID_SCALED_IMU2:
		if (prntSrt) {
			mavPrintLn((char *)"#116:  MAVLINK_MSG_ID_SCALED_IMU2");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#116:  MAVLINK_MSG_ID_SCALED_IMU2");
		}
		break;
		
	// =====  #125: MAVLINK_MSG_ID_POWER_STATUS ========================
	case MAVLINK_MSG_ID_POWER_STATUS:
		if (prntSrt) {
			mavPrintLn((char *)"#125:  MAVLINK_MSG_ID_POWER_STATUS");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#125:  MAVLINK_MSG_ID_POWER_STATUS");
		}
		break;
		
	// =====  #129: AVLINK_MSG_ID_SCALED_IMU3 ==========================
	case MAVLINK_MSG_ID_SCALED_IMU3:
		if (prntSrt) {
			mavPrintLn((char *)"#129:  AVLINK_MSG_ID_SCALED_IMU3");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#129:  AVLINK_MSG_ID_SCALED_IMU3");
		}
		break;
		
	// =====  #136: MAVLINK_MSG_ID_TERRAIN_REPORT ======================
	case MAVLINK_MSG_ID_TERRAIN_REPORT:
		if (prntSrt) {
			mavPrintLn((char *)"#136:  MAVLINK_MSG_ID_TERRAIN_REPORT");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#136:  MAVLINK_MSG_ID_TERRAIN_REPORT");
		}
		break;
		
	// =====  #137: MAVLINK_MSG_ID_SCALED_PRESSURE2 ====================
	case MAVLINK_MSG_ID_SCALED_PRESSURE2:
		if (prntSrt) {
			mavPrintLn((char *)"#137:  MAVLINK_MSG_ID_SCALED_PRESSURE2");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#137:  MAVLINK_MSG_ID_SCALED_PRESSURE2");
		}
		break;
		
	// =====  #147: MAVLINK_MSG_ID_BATTERY_STATUS ======================
	/*
	static inline void mavlink_msg_battery_status_decode(const mavlink_message_t* msg, mavlink_battery_status_t* battery_status)
	{
	#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
		battery_status->current_consumed = mavlink_msg_battery_status_get_current_consumed(msg);
		battery_status->energy_consumed = mavlink_msg_battery_status_get_energy_consumed(msg);
		battery_status->temperature = mavlink_msg_battery_status_get_temperature(msg);
		mavlink_msg_battery_status_get_voltages(msg, battery_status->voltages);
		battery_status->current_battery = mavlink_msg_battery_status_get_current_battery(msg);
		battery_status->id = mavlink_msg_battery_status_get_id(msg);
		battery_status->battery_function = mavlink_msg_battery_status_get_battery_function(msg);
		battery_status->type = mavlink_msg_battery_status_get_type(msg);
		battery_status->battery_remaining = mavlink_msg_battery_status_get_battery_remaining(msg);
		battery_status->time_remaining = mavlink_msg_battery_status_get_time_remaining(msg);
		battery_status->charge_state = mavlink_msg_battery_status_get_charge_state(msg);
		mavlink_msg_battery_status_get_voltages_ext(msg, battery_status->voltages_ext);
		battery_status->mode = mavlink_msg_battery_status_get_mode(msg);
		battery_status->fault_bitmask = mavlink_msg_battery_status_get_fault_bitmask(msg);
	#else
		uint8_t len = msg->len < MAVLINK_MSG_ID_BATTERY_STATUS_LEN? msg->len : MAVLINK_MSG_ID_BATTERY_STATUS_LEN;
		memset(battery_status, 0, MAVLINK_MSG_ID_BATTERY_STATUS_LEN);
		memcpy(battery_status, _MAV_PAYLOAD(msg), len);
	#endif
	*/	
	case MAVLINK_MSG_ID_BATTERY_STATUS:
		if (prntSrt) {
			mavPrintLn((char *)"#147:  MAVLINK_MSG_ID_BATTERY_STATUS");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#147:  LONG: MAVLINK_MSG_ID_BATTERY_STATUS");

	        mavPrint((char *)"  current_consumed  : "); mavPrint(mavlink_msg_battery_status_get_current_consumed(&mav_msg));mavPrintLn((char *)"mAh");
	        mavPrint((char *)"  energy_consumed   : "); mavPrint(mavlink_msg_battery_status_get_energy_consumed(&mav_msg));	mavPrintLn((char *)"hJ");
	        mavPrint((char *)"  temperature       : "); mavPrint(mavlink_msg_battery_status_get_temperature(&mav_msg));     mavPrintLn((char *)"cdegC");
/*	
	        mavPrint((char *)"voltages          : ");
			mavlink_battery_status_t* battery_status;			
			mavlink_msg_battery_status_get_voltages(&mav_msg, battery_status->voltages);
			std::cout << battery_status->voltages << std::endl;
*/
	        mavPrint((char *)"  current_battery   : "); mavPrintLn(mavlink_msg_battery_status_get_current_battery(&mav_msg));
	        mavPrint((char *)"  id                : "); mavPrintLn(mavlink_msg_battery_status_get_id(&mav_msg));
	        mavPrint((char *)"  battery_function  : "); mavPrintLn(mavlink_msg_battery_status_get_battery_function(&mav_msg));	
	        mavPrint((char *)"  type              : "); mavPrintLn(mavlink_msg_battery_status_get_type(&mav_msg));
	        mavPrint((char *)"  battery_remaining : "); mavPrintLn(mavlink_msg_battery_status_get_battery_remaining(&mav_msg));
	        mavPrint((char *)"  time_remaining    : "); mavPrintLn(mavlink_msg_battery_status_get_time_remaining(&mav_msg));
	        mavPrint((char *)"  charge_state      : "); mavPrintLn(mavlink_msg_battery_status_get_charge_state(&mav_msg));
//			mavPrint((char *)"mavlink_msg_battery_status_get_voltages_ext                  : "); 
//          mavPrintLn(battery_status->mavlink_msg_battery_status_get_voltages_ext);
	        mavPrint((char *)"  mode              : "); mavPrintLn( mavlink_msg_battery_status_get_mode(&mav_msg));
	        mavPrint((char *)"  fault_bitmask     : "); mavPrintLn(mavlink_msg_battery_status_get_fault_bitmask(&mav_msg));
		}
		break;
		
	// =====  #241: MAVLINK_MSG_ID_VIBRATION ===========================
	case MAVLINK_MSG_ID_VIBRATION:
		if (prntSrt) {
			mavPrintLn((char *)"#241:  MAVLINK_MSG_ID_VIBRATION");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#241:  MAVLINK_MSG_ID_VIBRATION");
		}
		break;
		
	// =====  #242: MAVLINK_MSG_ID_HOME_POSITION =======================
	case MAVLINK_MSG_ID_HOME_POSITION:
		if (prntSrt) {
			mavPrintLn((char *)"#242:  MAVLINK_MSG_ID_HOME_POSITION");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#242:  MAVLINK_MSG_ID_HOME_POSITION");
		}
		break;
		
	// =====  #246: MAVLINK_MSG_ID_ADSB_VEHICLE ========================
	/*
	static inline void mavlink_msg_adsb_vehicle_decode(const mavlink_message_t* msg, mavlink_adsb_vehicle_t* adsb_vehicle)
	{
	#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
		adsb_vehicle->ICAO_address = mavlink_msg_adsb_vehicle_get_ICAO_address(msg);
		adsb_vehicle->lat = mavlink_msg_adsb_vehicle_get_lat(msg);
		adsb_vehicle->lon = mavlink_msg_adsb_vehicle_get_lon(msg);
		adsb_vehicle->altitude = mavlink_msg_adsb_vehicle_get_altitude(msg);
		adsb_vehicle->heading = mavlink_msg_adsb_vehicle_get_heading(msg);
		adsb_vehicle->hor_velocity = mavlink_msg_adsb_vehicle_get_hor_velocity(msg);
		adsb_vehicle->ver_velocity = mavlink_msg_adsb_vehicle_get_ver_velocity(msg);
		adsb_vehicle->flags = mavlink_msg_adsb_vehicle_get_flags(msg);
		adsb_vehicle->squawk = mavlink_msg_adsb_vehicle_get_squawk(msg);
		adsb_vehicle->altitude_type = mavlink_msg_adsb_vehicle_get_altitude_type(msg);
		mavlink_msg_adsb_vehicle_get_callsign(msg, adsb_vehicle->callsign);
		adsb_vehicle->emitter_type = mavlink_msg_adsb_vehicle_get_emitter_type(msg);
		adsb_vehicle->tslc = mavlink_msg_adsb_vehicle_get_tslc(msg);
	#else
			uint8_t len = msg->len < MAVLINK_MSG_ID_ADSB_VEHICLE_LEN? msg->len : MAVLINK_MSG_ID_ADSB_VEHICLE_LEN;
			memset(adsb_vehicle, 0, MAVLINK_MSG_ID_ADSB_VEHICLE_LEN);
		memcpy(adsb_vehicle, _MAV_PAYLOAD(msg), len);
	#endif
	*/	
	case MAVLINK_MSG_ID_ADSB_VEHICLE:
		if (prntSrt) {
			mavPrintLn((char *)"#246:  MAVLINK_MSG_ID_ADSB_VEHICLE");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#246:  MAVLINK_MSG_ID_ADSB_VEHICLE");
			
			mavlink_adsb_vehicle_t* adsb_vehicle;
			mavlink_msg_adsb_vehicle_decode(&mav_msg, adsb_vehicle);
			//               "------------------------------- : "			
			mavPrint((char *)"ICAO_address                    : "); 
            mavPrintLn(adsb_vehicle->ICAO_address);
			//               "------------------------------- : "			
			mavPrint((char *)"lat                             : "); 
            mavPrintLn(adsb_vehicle->lat);
			//               "------------------------------- : "			
			mavPrint((char *)"lon                             : "); 
            mavPrintLn(adsb_vehicle->lon);
			//               "------------------------------- : "			
			mavPrint((char *)"altitude                        : "); 
            mavPrintLn(adsb_vehicle->altitude);
			//               "------------------------------- : "			
			mavPrint((char *)"heading                         : "); 
            mavPrintLn(adsb_vehicle->heading);
			//               "------------------------------- : "			
			mavPrint((char *)"hor_velocity                    : "); 
            mavPrintLn(adsb_vehicle->hor_velocity);
			//               "------------------------------- : "			
			mavPrint((char *)"ver_velocity                    : "); 
            mavPrintLn(adsb_vehicle->ver_velocity);
			//               "------------------------------- : "			
			mavPrint((char *)"flags                           : "); 
            mavPrintLn(adsb_vehicle->flags);
			//               "------------------------------- : "			
			mavPrint((char *)"squawk                          : "); 
            mavPrintLn(adsb_vehicle->squawk);
			//               "------------------------------- : "			
			mavPrint((char *)"altitude_type                   : "); 
            mavPrintLn(adsb_vehicle->altitude_type);
			//               "------------------------------- : "			
			mavPrint((char *)"callsign                        : "); 
            mavPrintLn(adsb_vehicle->callsign);
			//               "------------------------------- : "			
			mavPrint((char *)"emitter_type                    : "); 
            mavPrintLn(adsb_vehicle->emitter_type);
			//               "------------------------------- : "			
			mavPrint((char *)"tslc                            : "); 
            mavPrintLn(adsb_vehicle->tslc);
			
		}
		break;
		
	// =====  #251: MAVLINK_MSG_ID_NAMED_VALUE_FLOAT ===================
	case MAVLINK_MSG_ID_NAMED_VALUE_FLOAT:
		if (prntSrt) {
			mavPrintLn((char *)"#251:  MAVLINK_MSG_ID_NAMED_VALUE_FLOAT");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#251:  MAVLINK_MSG_ID_NAMED_VALUE_FLOAT");
		}
		break;
		
	// =====  #253: MAVLINK_MSG_ID_STATUSTEXT ==========================
	case MAVLINK_MSG_ID_STATUSTEXT:
		if (prntSrt) {
			mavPrintLn((char *)"#253   STATUSTEXT");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#253   STATUSTEXT");

			char mstxt[50];
			mavlink_msg_statustext_get_text(&mav_msg, mstxt);
			mavPrintLn(mstxt);
		}
		break;
		
	// =====  #285: AVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS ========
	case MAVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS:
		if (prntSrt) {
			mavPrintLn((char *)"#285:  AVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS");
		}
		if (prntLng) {
            mavPrintLn((char *)"\n#285:  AVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS");
		}
		break;
	// =====  DEFAULT ==================================================
	default:
		std::cout << ">>> New Message ID: " << mav_msg.msgid << " <<<" << std::endl;
		break;
	}
}
