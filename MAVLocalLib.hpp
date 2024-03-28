#pragma region Docs
// ====================================================================================
// 	File Name:	MAVLocalLib.hpp
//	Author:		Ulrich Sucker      
// -------------------------------------------------------------------------------------
// 	Version 00.01 - 2024-03-18
//   - Base
// -------------------------------------------------------------------------------------
#define MAVLocalLib_hpp_Version "00.01.004"
// =====================================================================================
#pragma endregion

#pragma once
// ---- include public libs ------------------------------------------------------------ */
#include <iostream>
#include <string>

// ---- include global libs ------------------------------------------------------------ */
#include "..\c_library_v2\common\mavlink.h"
#include "..\c_library_v2\common\common.h"

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

unsigned long last_heartbeat     = 0;
unsigned long heartbeat_interval = 2000;                  // Zeitraum, in dem ein Heard-Beat empfangen werden soll

struct mavMessage {
	bool printShort = false;
	bool printLong = false;
	bool used = false;
};

#define mavMsgCnt 285
mavMessage mavMessages[mavMsgCnt];

/* =========================================================================== */
//      Remote MAVLink Device (Drone)
/* =========================================================================== */
uint8_t target_system    = 1;
uint8_t target_component = 1;


/* =========================================================================== */
//      Funktion Prototyps
/* =========================================================================== */

/*
bool seralReceive()
serialSend()
udpReceive()
udpSend()
mavPrint()
*/
void mavPrint(std::string text);
void mavPrint(char* text);

void mavPrintLn(std::string text);
void mavPrintLn(char* text);

void printMAVlinkMessage(mavlink_message_t mav_msg, bool prntSrt, bool prntLng);



