#pragma region Docs
// ====================================================================================
// 	File Name:	MAVLocalLib.hpp
//	Author:		Ulrich Sucker      
// -------------------------------------------------------------------------------------
// 	Version 00.04 - 2024-04-17
//   - HardBeat-Anzeige mit ausfühlichen Informationen verbessert
//   - Header-Dateien mit MAVlink-Daten eingebunden
// -------------------------------------------------------------------------------------
// 	Version 00.03 - 2024-04-15
//   - Support of different devices
// -------------------------------------------------------------------------------------
// 	Version 00.02 - 2024-04-07
//   - Class UDPConnectSrvr
//		DPConnectSrvr::UDPConnectSrvr(int UDPport)
//		UDPConnectSrvr::~UDPConnectSrvr()
//		bool UDPConnectSrvr::RecMAVmsg()
// -------------------------------------------------------------------------------------
// 	Version 00.01 - 2024-03-18
//   - Base
// -------------------------------------------------------------------------------------
#define MAVLocalLib_hpp_Version "00.04.010"
// =====================================================================================
#pragma endregion

#pragma once
// ---- include public libs ------------------------------------------------------------ */
#include <iostream>
#include <string>
#include <winsock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib") // Winsock Library
#pragma warning(disable:4996) 

// ---- include global libs ------------------------------------------------------------ */
#include "..\c_library_v2\common\mavlink.h"
#include "..\c_library_v2\common\common.h"

/* ---- include local libs ------------------------------------------------------------- */
// #include "c:\Development\MavLinkProjects\udpMAVTest\lib\MAVLocalLib\MAVLocalLib.cpp" 
// #include "..\lib\MAVLocalLib\MAVLocalLib.cpp"
#include "mav_type.hpp"
#include "mav_autopilot.hpp"
#include "mav_state.hpp"


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

struct mavMessage {                 // Struktur für Infos für einen Nachrichtentyp
	bool printShort = false;
	bool printLong = false;
    unsigned long last = 0;         // Wann das letzte mal empfangen
	bool used = false;
};
#define mavMsgCnt 285               // Anzahl der unterschiedlichen Nachrichten
mavMessage mavMessages[mavMsgCnt];  // Array mit Infos für einzelne Nachrichten

/* =========================================================================== */
//      Remote MAVLink Devices (Drone)
/* =========================================================================== */
struct MAVentity { 
	int sysID;
	int compID;
	long LastRecHeartbeat = 0;
};

#define MAVENTITYCNT 32
MAVentity MAVentities[MAVENTITYCNT]; // Array zur Speicherung aller Heardbeat Sender
unsigned int mavEntityCnt = 0;

void recMAVEntityHeardBeat(int sysID_, int compID_);   // Funktion zur Speicherung eines empfangenen HBs
void listMAVEntties();

unsigned long last_heartbeat     = 0;
unsigned long heartbeat_interval = 2000;                  // Zeitraum, in dem ein Heard-Beat empfangen werden soll

/* =========================================================================== */
//      Local MAVLink Device (Ground Station)
/* =========================================================================== */
uint8_t target_system    = 1;
uint8_t target_component = 1;

/* =========================================================================== */
//      CLASSES Prototyps
/* =========================================================================== */
#define BUFLEN 512
#define DEFAULT_UDP_PORT 14552
int UDPport;

class UDPConnectSrvr {
private:
    WSADATA wsa;
    SOCKET server_socket;
    sockaddr_in server, client;
    bool exitRequested = false;
public:
	explicit UDPConnectSrvr(int UDPport);
	~UDPConnectSrvr();
	bool RecMAVmsg();
	bool SndMAVmsg();
};

/* =========================================================================== */
//      FUNCTIONS Prototyps
/* =========================================================================== */

/*
bool serialReceiveMAVmsg()
void serialSendMAVmsg()
bool RecMAVmsg()
void udpSendMAVmsg()
*/

void initMAVmessages();

void mavPrint(std::string text);
void mavPrint(char* text);
void mavPrint(int text);

void mavPrintLn(std::string text);
void mavPrintLn(char* text);
void mavPrintLn(int text);

void printMAVlinkMessage(mavlink_message_t mav_msg, bool prntSrt, bool prntLng);
//void mavPrintParameter(mavlink_param_value_t param_value); 
