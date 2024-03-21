#pragma region Docs
// ====================================================================================
// 	File Name:	MAVLocalLib.hpp
//	Author:		Ulrich Sucker      
// -------------------------------------------------------------------------------------
// 	Version 00.01 - 2024-03-18
//   - Base
// -------------------------------------------------------------------------------------
#define SW_Version "00.01.002"
// =====================================================================================
#pragma endregion

#pragma once
// ---- include public libs ------------------------------------------------------------ */
#include <iostream>
#include <string>

// ---- include global libs ------------------------------------------------------------ */
#include "..\lib\ mavlink\c_library_v2\common\mavlink.h"
#include "..\lib\ mavlink\c_library_v2\common\common.h"

struct ApParameter
{
    std::string  param_id;
    float        param_value;
    char         param_type;
    unsigned int param_count;
    unsigned int param_index;
};


// void mavlinkConnectDialog();

/* =========================================================================== */
//      MAVLink Messages
/* =========================================================================== */
mavlink_message_t mav_msg;			// DIE globale Variable mit der MAVLink-Nachricht
mavlink_status_t mav_msg_status;	// DER MAVLINK-Status

/* =========================================================================== */
//      Remote MAVLink Device (Drone)
/* =========================================================================== */
uint8_t target_system    = 1;
uint8_t target_component = 1;




unsigned long last_heartbeat     = 0;
unsigned long heartbeat_interval = 2000;                  // Zeitraum, in dem ein Heard-Beat empfangen werden soll

