#pragma region Docs
// ====================================================================================
// 	File Name:	MAVLocalLib.cpp
//	Author:		Ulrich Sucker      
// -------------------------------------------------------------------------------------
// 	Version 00.00 - 2024-02-27
//   - Base
// -------------------------------------------------------------------------------------
#define MAVLocalLib_CPP_Version "00.01.005"
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
                //mavPrint(hb.custom_mode); 
                //mavPrintLn(" not known");
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
		}
		//std::cout << "#001:  SYS_STATUS" << std::endl;
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
		}		
		//std::cout << "#021:  MAVLINK_MSG_ID_PARAM_REQUEST_LIST" << std::endl;
		break;
		
	// =====  #22: PARAM_VALUE =========================================
	case MAVLINK_MSG_ID_PARAM_VALUE: 
		if (prntSrt) {
			mavPrintLn("#022:  Parameter Value");
		}
		if (prntLng) {
            mavPrintLn("\n#022:  Parameter Value");
		}
		//std::cout << "#022:  Parameter Value" << std::endl;
		mavlink_param_value_t param_value;
		mavlink_msg_param_value_decode(&mav_msg, &param_value);
		//mvPrintParameter(param_value);
		break;

	// =====  #23 MAVLINK_MSG_ID_PARAM_SET =============================
	case MAVLINK_MSG_ID_PARAM_SET:
		if (prntSrt) {
			mavPrintLn("#023:  MAVLINK_MSG_ID_PARAM_SET");
		}
		if (prntLng) {
            mavPrintLn("\n#023:  MAVLINK_MSG_ID_PARAM_SET");
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
		std::cout << "#024:  MAVLINK_MSG_ID_GPS_RAW_INT" << std::endl;
		break;
		
	// =====  #27: RAW_IMU =============================================
	case MAVLINK_MSG_ID_RAW_IMU:
		if (prntSrt) {
			mavPrintLn("#027:  RAW_IMU");
		}
		if (prntLng) {
            mavPrintLn("\n#027:  RAW_IMU");
		}		
		std::cout << "#027:  RAW_IMU" << std::endl;
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
