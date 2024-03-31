#pragma region Docs
// ====================================================================================
// 	File Name:	MAVLocalLib.cpp
//	Author:		Ulrich Sucker      
// -------------------------------------------------------------------------------------
// 	Version 00.00 - 2024-02-27
//   - Base
// -------------------------------------------------------------------------------------
#define MAVLocalLib_CPP_Version "00.01.006"
// =====================================================================================
#pragma endregion

/* ---- include Header ----------------------------------------------------------------- */ 
#include "MAVLocalLib.hpp"


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
	std::cout << text <<std::endl;
};

void mavPrintLn(int  text){
	std::cout << text <<std::endl;
};

// ==== FUNCTION: printMAVlinkMessage ==================================================
void printMAVlinkMessage(mavlink_message_t mav_msg, bool prntSrt, bool prntLng)
{
	// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
	/*
	if (prntSrt == true){
		// std::cout << "Short "; 
		mavPrint("Short ");
	}
	if (prntLng == true){
		//std::cout << "Long ";
		mavPrint("Long ");
		
	}
	//std::cout << ":" <<std::endl; 
	mavPrintLn(":");
	*/
	// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-


	switch (mav_msg.msgid) {
	// ====  #0: Heartbeat =============================================================	
	case MAVLINK_MSG_ID_HEARTBEAT:
		if (prntSrt) {
			mavPrintLn("#000:  Hard beat");
		}
		if (prntLng) {
			mavPrintLn("\n#000   Hard Beat");
			mavlink_heartbeat_t hb;
			mavlink_msg_heartbeat_decode(&mav_msg, &hb);
		    mavPrint("State        : "); mavPrintLn(hb.base_mode == 209 ? "Armed" : "Disarmed");
			mavPrint("Mode         : ");
			switch(hb.custom_mode) {
			case 0:
				mavPrintLn("Manual");
				break;
			case 1:
				mavPrintLn("Circle");
				break;
			case 2:
				mavPrintLn("Stabilize");
				break;
			case 3:
				mavPrintLn("Training");
			  break;
			  case 5:
				mavPrintLn("FBWA");
	          break;
              case 6:
                mavPrintLn("FBWB");
              break;
              case 7:
                mavPrintLn("Cruise");
              break;
              case 8:
                mavPrintLn("AUTOTUNE");
              break;
              case 10:
                mavPrintLn("Auto");
              break;
              case 11:
                mavPrintLn("RTL");
              break;
              case 12:
                mavPrintLn("Loiter");
              break;
              case 13:
                mavPrintLn("Take Off");
              break;
              case 14:
                mavPrintLn("Avoid ADSB");
              break;
              case 15:
                mavPrintLn("Guided");
              break;
              case 17:
                mavPrintLn("QStabilize");
              break;
              case 18:
                mavPrintLn("QHover");
              break;
              case 19:
                mavPrintLn("QLoiter");
              break;
              case 20:
                mavPrintLn("QLand");
              break;
              case 21:
                mavPrintLn("QRTL");
              break;
              case 22:
                mavPrintLn("QAutoTune");
              break;
              case 23:
                mavPrintLn("QAcro");
              break;
              case 24:
                mavPrintLn("Thermal");
              break;
              case 25:
                mavPrintLn("Loiter to QLand");
              break;
              default:
                mavPrint("Mode "); 
                mavPrint(hb.custom_mode); 
                mavPrintLn(" not known");
              break;
            }
            mavPrint("type         : "); mavPrintLn(hb.type);
            mavPrint("autopilot    : "); mavPrintLn(hb.autopilot);
            mavPrint("system_status: "); mavPrintLn(hb.system_status);
            //mavPrintLn("");
          	
		}
		break;
		
	// =====  #1: SYS_STATUS ===========================================
	case MAVLINK_MSG_ID_SYSTEM_TIME:  // #2 MAVLINK_MSG_ID_SYSTEM_TIME
		if (prntSrt) {
			mavPrintLn("#001:  SYS_STATUS");
		}
		if (prntLng) {
            mavPrintLn("\n#001:  SYS_STATUS");

			mavlink_sys_status_t sys_status;
            mavlink_msg_sys_status_decode(&mav_msg, &sys_status);
           
            mavPrint("onboard_control_sensors_present : "); 
            mavPrintLn(sys_status.onboard_control_sensors_present);
           
            mavPrint("onboard_control_sensors_enabled : "); 
            mavPrintLn(sys_status.onboard_control_sensors_enabled);
            
            mavPrint("onboard_control_sensors_health  : "); 
            mavPrintLn(sys_status.onboard_control_sensors_health);
            
            mavPrint("load             : "); 
            mavPrintLn(sys_status.load);
            
            mavPrint("voltage_battery  : "); 
            mavPrintLn(sys_status.voltage_battery);
            
            mavPrint("current_battery  : "); 
            mavPrintLn(sys_status.current_battery);

            mavPrint("drop_rate_comm   : "); 
            mavPrintLn(sys_status.drop_rate_comm);
/*         
            mavPrint("errors_comm      : "); 
            mavPrintLn(sys_status.errors_comm);
               
            mavPrint("errors_count1    : "); 
            mavPrintLn(sys_status.errors_count1);
            
            mavPrint("errors_count2    : "); 
            mavPrintLn(sys_status.errors_count2);
            
            mavPrint("errors_count3    : "); 
            mavPrintLn(sys_status.errors_count3);
            
            mavPrint("errors_count4    : "); 
            mavPrintLn(sys_status.errors_count4);
*/            
            mavPrint("battery_remaining: "); 
            mavPrintLn(sys_status.battery_remaining);			

		}
		break;
		
	// =====  #2 MAVLINK_MSG_ID_SYSTEM_TIME   ==========================
	case MAVLINK_MSG_ID_SYS_STATUS:  
		if (prntSrt) {
			mavPrintLn("#002:  MAVLINK_MSG_ID_SYSTEM_TIME");
		}
		if (prntLng) {
            mavPrintLn("\n#002:  MAVLINK_MSG_ID_SYSTEM_TIME");
		}		
		//std::cout << "#002:  MAVLINK_MSG_ID_SYSTEM_TIME  " << std::endl;
		break;
		
	// =====  #21 MAVLINK_MSG_ID_PARAM_REQUEST_LIST ====================
	case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
		if (prntSrt) {
			mavPrintLn("#021:  MAVLINK_MSG_ID_PARAM_REQUEST_LIST");
		}
		if (prntLng) {
            mavPrintLn("\n#021:  MAVLINK_MSG_ID_PARAM_REQUEST_LIST");
            mavlink_command_long_t packet;
            mavlink_msg_command_long_decode(&mav_msg, &packet);
            mavPrint("command:");mavPrintLn(packet.command);
            mavPrint("target_system:    ");mavPrintLn(packet.target_system);
            mavPrint("target_component: ");mavPrintLn(packet.target_component);
            mavPrint("          param1: ");mavPrintLn(packet.param1);
            mavPrint("          param2: ");mavPrintLn(packet.param2);
            mavPrint("          param3: ");mavPrintLn(packet.param3);
            mavPrint("          param4: ");mavPrintLn(packet.param4);
            mavPrint("          param5: ");mavPrintLn(packet.param5);
            mavPrint("          param6: ");mavPrintLn(packet.param6);
            mavPrint("          param7: ");mavPrintLn(packet.param7);			
		}
		break;
		
	// =====  #22: PARAM_VALUE =========================================
	case MAVLINK_MSG_ID_PARAM_VALUE: 
		if (prntSrt) {
			mavPrintLn("#022:  Parameter Value");
		}
		if (prntLng) {
            mavPrintLn("\n#022:  Parameter Value");
            mavlink_param_value_t param_value;
            mavlink_msg_param_value_decode(&mav_msg, &param_value);
            mavPrint("ID:    ");mavPrintLn(param_value.param_id);
            mavPrint("Value: ");mavPrintLn(param_value.param_value);
            mavPrint("Count: ");mavPrintLn(param_value.param_count);
            mavPrint("Index: ");mavPrintLn(param_value.param_index);
            mavPrint("Type:  ");mavPrintLn(param_value.param_type);			
		}
		break;

	// =====  #23 MAVLINK_MSG_ID_PARAM_SET =============================
	case MAVLINK_MSG_ID_PARAM_SET:
		if (prntSrt) {
			mavPrintLn("#023:  MAVLINK_MSG_ID_PARAM_SET");
		}
		if (prntLng) {
            mavPrintLn("\n#023:  MAVLINK_MSG_ID_PARAM_SET");
            mavlink_param_set_t param_set;
            mavlink_msg_param_set_decode(&mav_msg, &param_set);
            
            mavPrint("param_value:    ");
            mavPrintLn(param_set.param_value);
            
            mavPrint("target_system:    ");
            mavPrintLn(param_set.target_system);
            
            mavPrint("target_component:    ");
            mavPrintLn(param_set.target_component);
            
            mavPrint("param_type:    ");
            mavPrintLn(param_set.param_type);			
		}		
		//std::cout << "#023:  MAVLINK_MSG_ID_PARAM_SET" << std::endl;
		break;
		
	// =====  #24 MAVLINK_MSG_ID_GPS_RAW_INT ===========================
	case MAVLINK_MSG_ID_GPS_RAW_INT:
		if (prntSrt) {
			mavPrintLn("#024:  MAVLINK_MSG_ID_GPS_RAW_INT");
		}
		if (prntLng) {
            mavPrintLn("\n#024:  MAVLINK_MSG_ID_GPS_RAW_INT");
		}		
		//std::cout << "#024:  MAVLINK_MSG_ID_GPS_RAW_INT" << std::endl;
		break;
		
	// =====  #27: RAW_IMU =============================================
	case MAVLINK_MSG_ID_RAW_IMU:
		if (prntSrt) {
			mavPrintLn("#027:  RAW_IMU");
		}
		if (prntLng) {
            mavPrintLn("\n#027: Raw IMU Data ___________");
            mavlink_raw_imu_t raw_imu;
            mavlink_msg_raw_imu_decode(&mav_msg, &raw_imu);
            mavPrintLn("\n#027: Raw IMU Data ___________");			
            mavPrint("       xacc:  "); mavPrintLn(raw_imu.xacc);
            mavPrint("       yacc:  "); mavPrintLn(raw_imu.yacc);
            mavPrint("       zacc:  "); mavPrintLn(raw_imu.zacc);
            mavPrint("       xgyro: "); mavPrintLn(raw_imu.xgyro);
            mavPrint("       ygyro: "); mavPrintLn(raw_imu.ygyro);
            mavPrint("       zgyro: "); mavPrintLn(raw_imu.zgyro);
            mavPrint("       xmag:  "); mavPrintLn(raw_imu.xmag);
            mavPrint("       ymag:  "); mavPrintLn(raw_imu.ymag);
            mavPrint("       zmag:  "); mavPrintLn(raw_imu.zmag);			
		}		
		//std::cout << "#027:  RAW_IMU" << std::endl;
		break;
		
	// =====  #29: MAVLINK_MSG_ID_SCALED_PRESSURE ======================
	case MAVLINK_MSG_ID_SCALED_PRESSURE:  // 
		if (prntSrt) {
			mavPrintLn("#029:  MAVLINK_MSG_ID_SCALED_PRESSURE");
		}
		if (prntLng) {
            mavPrintLn("\n#029:  MAVLINK_MSG_ID_SCALED_PRESSURE");
		}		
		std::cout << "#029:  MAVLINK_MSG_ID_SCALED_PRESSURE" << std::endl;
		break;
		
	// =====   #30: MAVLINK_MSG_ID_ATTITUDE ============================
	case MAVLINK_MSG_ID_ATTITUDE:
		if (prntSrt) {
			mavPrintLn("#030:  MAVLINK_MSG_ID_ATTITUDE");
		}
		if (prntLng) {
            mavPrintLn("\n#030:  MAVLINK_MSG_ID_ATTITUDE");
		}		
		std::cout << "#030:  MAVLINK_MSG_ID_ATTITUDE" << std::endl;
		break;
		
	// =====  #32: MAVLINK_MSG_ID_LOCAL_POSITION_NED ===================
	case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
		if (prntSrt) {
			mavPrintLn("#032:  MAVLINK_MSG_ID_LOCAL_POSITION_NED");
		}
		if (prntLng) {
            mavPrintLn("\n#032:  MAVLINK_MSG_ID_LOCAL_POSITION_NED");
		}		
		std::cout << "#032:  MAVLINK_MSG_ID_LOCAL_POSITION_NED" << std::endl;
		break;

	// =====  #33: MAVLINK_MSG_ID_GLOBAL_POSITION_INT ==================
	case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
		if (prntSrt) {
			mavPrintLn("#033:  MAVLINK_MSG_ID_GLOBAL_POSITION_INT");
		}
		if (prntLng) {
            mavPrintLn("\n#033:  MAVLINK_MSG_ID_GLOBAL_POSITION_INT");
		}		
		//std::cout << "#033:  MAVLINK_MSG_ID_GLOBAL_POSITION_INT" << std::endl;
		break;

	// =====  #36: MAVLINK_MSG_ID_SERVO_OUTPUT_RAW ======================
	case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
		if (prntSrt) {
			mavPrintLn("#036:  MAVLINK_MSG_ID_SERVO_OUTPUT_RAW");
		}
		if (prntLng) {
            mavPrintLn("\n#036:  MAVLINK_MSG_ID_SERVO_OUTPUT_RAW");
		}
		//std::cout << "#036:  MAVLINK_MSG_ID_SERVO_OUTPUT_RAW" << std::endl;
		break;
		
	// =====  #42: MAVLINK_MSG_ID_MISSION_CURRENT ======================
	case MAVLINK_MSG_ID_MISSION_CURRENT:
		if (prntSrt) {
			mavPrintLn("#042:  MAVLINK_MSG_ID_MISSION_CURRENT");
		}
		if (prntLng) {
            mavPrintLn("\n#042:  MAVLINK_MSG_ID_MISSION_CURRENT");
		}
		//std::cout << "#042:  MAVLINK_MSG_ID_MISSION_CURRENT" << std::endl;
		break;
		
	// =====  #49: MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN ====================
	case MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN:
		if (prntSrt) {
			mavPrintLn("#049:  MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN");
		}
		if (prntLng) {
            mavPrintLn("\n#049:  MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN");
		}
		//std::cout << "#049:  MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN" << std::endl;
		break;
		
	// =====  #62: MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT ================
	case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:
		if (prntSrt) {
			mavPrintLn("#062:  MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT");
		}
		if (prntLng) {
            mavPrintLn("\n#062:  MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT");
		}
		//std::cout << "#062:  MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT" << std::endl;
		break;
		
	// =====  #65: MAVLINK_MSG_ID_RC_CHANNELS ==========================
	case MAVLINK_MSG_ID_RC_CHANNELS:
		if (prntSrt) {
			mavPrintLn("#065:  MAVLINK_MSG_ID_RC_CHANNELS");
		}
		if (prntLng) {
            mavPrintLn("\n#065:  MAVLINK_MSG_ID_RC_CHANNELS");
	        mavlink_rc_channels_t rc_channels;
            mavlink_msg_rc_channels_decode(&mav_msg, &rc_channels);
            mavPrint("# Channels:       "); mavPrintLn(rc_channels.chancount);
            mavPrint("RSSI:             "); mavPrintLn(rc_channels.rssi);
            mavPrint("RC Channel  1:    "); mavPrintLn(rc_channels.chan1_raw);
            mavPrint("RC Channel  2:    "); mavPrintLn(rc_channels.chan2_raw);
            mavPrint("RC Channel  3:    "); mavPrintLn(rc_channels.chan3_raw);
            mavPrint("RC Channel  4:    "); mavPrintLn(rc_channels.chan4_raw);
            mavPrint("RC Channel  5:    "); mavPrintLn(rc_channels.chan5_raw);
            mavPrint("RC Channel  6:    "); mavPrintLn(rc_channels.chan6_raw);
            mavPrint("RC Channel  7:    "); mavPrintLn(rc_channels.chan7_raw);
            mavPrint("RC Channel  8:    "); mavPrintLn(rc_channels.chan8_raw);
            mavPrint("RC Channel  9:    "); mavPrintLn(rc_channels.chan9_raw);
            mavPrint("RC Channel 10:    "); mavPrintLn(rc_channels.chan10_raw);
            mavPrint("RC Channel 11:    "); mavPrintLn(rc_channels.chan11_raw);
            mavPrint("RC Channel 12:    "); mavPrintLn(rc_channels.chan12_raw);
            mavPrint("RC Channel 13:    "); mavPrintLn(rc_channels.chan13_raw);
            mavPrint("RC Channel 14:    "); mavPrintLn(rc_channels.chan14_raw);
            mavPrint("RC Channel 15:    "); mavPrintLn(rc_channels.chan15_raw);
            mavPrint("RC Channel 16:    "); mavPrintLn(rc_channels.chan16_raw);
            mavPrint("RC Channel 17:    "); mavPrintLn(rc_channels.chan17_raw);
            mavPrint("RC Channel 18:    "); mavPrintLn(rc_channels.chan18_raw);
		}
		//std::cout << "#065:  MAVLINK_MSG_ID_RC_CHANNELS" << std::endl;
		break;
		
	// =====  #66: MAVLINK_MSG_ID_REQUEST_DATA_STREAM ==================
	case MAVLINK_MSG_ID_REQUEST_DATA_STREAM :
		if (prntSrt) {
			mavPrintLn("#066:  MAVLINK_MSG_ID_REQUEST_DATA_STREAM");
		}
		if (prntLng) {
            mavPrintLn("\n#066:  MAVLINK_MSG_ID_REQUEST_DATA_STREAM");
		}
		//std::cout << "#066:  MAVLINK_MSG_ID_REQUEST_DATA_STREAM" << std::endl;
		break;
		
	// =====  #74: MAVLINK_MSG_ID_VFR_HUD ==============================
	case MAVLINK_MSG_ID_VFR_HUD:
		if (prntSrt) {
			mavPrintLn("#074:  MAVLINK_MSG_ID_VFR_HUD");
		}
		if (prntLng) {
            mavPrintLn("\n#074:  MAVLINK_MSG_ID_VFR_HUD");
		}
		std::cout << "#074:  MAVLINK_MSG_ID_VFR_HUD" << std::endl;
		break;
		
	// =====  #76: MAVLINK_MSG_ID_COMMAND_LONG =========================
	case MAVLINK_MSG_ID_COMMAND_LONG:
		if (prntSrt) {
			mavPrintLn("#076:  MAVLINK_MSG_ID_COMMAND_LONG");
		}
		if (prntLng) {
            mavPrintLn("\n#076:  MAVLINK_MSG_ID_COMMAND_LONG");
            mavlink_command_long_t command_long;
            mavlink_msg_command_long_decode(&mav_msg, &command_long);

            mavPrint("target_system:    ");
            mavPrintLn(command_long.target_system);
            mavPrint("target_component: ");
            mavPrintLn(command_long.target_component);
            mavPrint("command: ");
            mavPrintLn(command_long.command);
            mavPrint("confirmation: ");
            mavPrintLn(command_long.confirmation);
            mavPrint("param1: ");
            mavPrintLn(command_long.param1);
            mavPrint("param2: ");
            mavPrintLn(command_long.param2);
            mavPrint("param3: ");
            mavPrintLn(command_long.param3);
            mavPrint("param4: ");
            mavPrintLn(command_long.param4);
            mavPrint("param5: ");
            mavPrintLn(command_long.param5);
            mavPrint("param6: ");
            mavPrintLn(command_long.param6);
            mavPrint("param7: ");
            mavPrintLn(command_long.param7);			
		}
		//std::cout << "#076:  MAVLINK_MSG_ID_COMMAND_LONG" << std::endl;
		break;
		
	// =====  #87: MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT ===========
	case MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT:
		if (prntSrt) {
			mavPrintLn("#087:  MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT");
		}
		if (prntLng) {
            mavPrintLn("\n#087:  MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT");
		}
		//std::cout << "#087:  MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT" << std::endl;
		break;
		
	// =====  #111: MAVLINK_MSG_ID_TIMESYNC ============================
	case MAVLINK_MSG_ID_TIMESYNC:
		if (prntSrt) {
			mavPrintLn("#111:  MAVLINK_MSG_ID_TIMESYNC");
		}
		if (prntLng) {
            mavPrintLn("\n#111:  MAVLINK_MSG_ID_TIMESYNC");
		}
		//std::cout << "#111:  MAVLINK_MSG_ID_TIMESYNC" << std::endl;
		break;
		
	// =====  #116: MAVLINK_MSG_ID_SCALED_IMU2 =========================
	case MAVLINK_MSG_ID_SCALED_IMU2:
		if (prntSrt) {
			mavPrintLn("#116:  MAVLINK_MSG_ID_SCALED_IMU2");
		}
		if (prntLng) {
            mavPrintLn("\n#116:  MAVLINK_MSG_ID_SCALED_IMU2");
		}
		//std::cout << "#116:  MAVLINK_MSG_ID_SCALED_IMU2" << std::endl;
		break;
		
	// =====  #125: MAVLINK_MSG_ID_POWER_STATUS ========================
	case MAVLINK_MSG_ID_POWER_STATUS:
		if (prntSrt) {
			mavPrintLn("#125:  MAVLINK_MSG_ID_POWER_STATUS");
		}
		if (prntLng) {
            mavPrintLn("\n#125:  MAVLINK_MSG_ID_POWER_STATUS");
		}
		//std::cout << "#125:  MAVLINK_MSG_ID_POWER_STATUS" << std::endl;
		break;
		
	// =====  #129: AVLINK_MSG_ID_SCALED_IMU3 ==========================
	case MAVLINK_MSG_ID_SCALED_IMU3:
		if (prntSrt) {
			mavPrintLn("#129:  AVLINK_MSG_ID_SCALED_IMU3");
		}
		if (prntLng) {
            mavPrintLn("\n#129:  AVLINK_MSG_ID_SCALED_IMU3");
		}
		//std::cout << "#129:  AVLINK_MSG_ID_SCALED_IMU3" << std::endl;
		break;
		
	// =====  #136: MAVLINK_MSG_ID_TERRAIN_REPORT ======================
	case MAVLINK_MSG_ID_TERRAIN_REPORT:
		if (prntSrt) {
			mavPrintLn("#136:  MAVLINK_MSG_ID_TERRAIN_REPORT");
		}
		if (prntLng) {
            mavPrintLn("\n#136:  MAVLINK_MSG_ID_TERRAIN_REPORT");
		}
		//std::cout << "#136:  MAVLINK_MSG_ID_TERRAIN_REPORT" << std::endl;
		break;
		
	// =====  #137: MAVLINK_MSG_ID_SCALED_PRESSURE2 ====================
	case MAVLINK_MSG_ID_SCALED_PRESSURE2:
		if (prntSrt) {
			mavPrintLn("#137:  MAVLINK_MSG_ID_SCALED_PRESSURE2");
		}
		if (prntLng) {
            mavPrintLn("\n#137:  MAVLINK_MSG_ID_SCALED_PRESSURE2");
		}
		//std::cout << "#137:  MAVLINK_MSG_ID_SCALED_PRESSURE2" << std::endl;
		break;
		
	// =====  #147: MAVLINK_MSG_ID_BATTERY_STATUS ======================
	case MAVLINK_MSG_ID_BATTERY_STATUS:
		if (prntSrt) {
			mavPrintLn("#147:  MAVLINK_MSG_ID_BATTERY_STATUS");
		}
		if (prntLng) {
            mavPrintLn("\n#147:  MAVLINK_MSG_ID_BATTERY_STATUS");
		}
		//std::cout << "#147:  MAVLINK_MSG_ID_BATTERY_STATUS" << std::endl;
		break;
		
	// =====  #241: MAVLINK_MSG_ID_VIBRATION ===========================
	case MAVLINK_MSG_ID_VIBRATION:
		if (prntSrt) {
			mavPrintLn("#241:  MAVLINK_MSG_ID_VIBRATION");
		}
		if (prntLng) {
            mavPrintLn("\n#241:  MAVLINK_MSG_ID_VIBRATION");
		}
		//std::cout << "#241:  MAVLINK_MSG_ID_VIBRATION" << std::endl;
		break;
		
	// =====  #242: MAVLINK_MSG_ID_HOME_POSITION =======================
	case MAVLINK_MSG_ID_HOME_POSITION:
		if (prntSrt) {
			mavPrintLn("#242:  MAVLINK_MSG_ID_HOME_POSITION");
		}
		if (prntLng) {
            mavPrintLn("\n#242:  MAVLINK_MSG_ID_HOME_POSITION");
		}
		//std::cout << "#242:  MAVLINK_MSG_ID_HOME_POSITION" << std::endl;
		break;
		
	// =====  #251: MAVLINK_MSG_ID_NAMED_VALUE_FLOAT ===================
	case MAVLINK_MSG_ID_NAMED_VALUE_FLOAT:
		if (prntSrt) {
			mavPrintLn("#251:  MAVLINK_MSG_ID_NAMED_VALUE_FLOAT");
		}
		if (prntLng) {
            mavPrintLn("\n#251:  MAVLINK_MSG_ID_NAMED_VALUE_FLOAT");
		}
		//std::cout << "#251:  MAVLINK_MSG_ID_NAMED_VALUE_FLOAT" << std::endl;
		break;
		
	// =====  #253: MAVLINK_MSG_ID_STATUSTEXT ==========================
	case MAVLINK_MSG_ID_STATUSTEXT:
		if (prntSrt) {
			mavPrintLn("#253   STATUSTEXT");
		}
		if (prntLng) {
            mavPrintLn("\n#253   STATUSTEXT");

			char mstxt[50];
			mavlink_msg_statustext_get_text(&mav_msg, mstxt);
			mavPrintLn(mstxt);
		}
		//std::cout << "#253   STATUSTEXT" << std::endl;
		break;
		
	// =====  #285: AVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS ========
	case MAVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS:
		if (prntSrt) {
			mavPrintLn("#285:  AVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS");
		}
		if (prntLng) {
            mavPrintLn("\n#285:  AVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS");
		}
		//std::cout << "#285:  AVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS" << std::endl;
		break;
	// =====  DEFAULT ==================================================
	default:
		std::cout << mav_msg.msgid << std::endl;
		break;
	}
}
