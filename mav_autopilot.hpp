struct MAV_AUTOPILOT_DATA_TYP {
	int Value;
	const char Function[150];
	const char Description[150];
};

struct MAV_AUTOPILOT_DATA_TYP const MAV_AUTOPILOT_DATA[] = {
	{0,"MAV_AUTOPILOT_GENERIC","Generic autopilot, full support for everything"},
	{1,"MAV_AUTOPILOT_RESERVED","Reserved for future use."},
	{2,"MAV_AUTOPILOT_SLUGS","SLUGS autopilot, http://slugsuav.soe.ucsc.edu"},
	{3,"MAV_AUTOPILOT_ARDUPILOTMEGA","ArduPilot - Plane/Copter/Rover/Sub/Tracker, https://ardupilot.org"},
	{4,"MAV_AUTOPILOT_OPENPILOT","OpenPilot, http://openpilot.org"},
	{5,"MAV_AUTOPILOT_GENERIC_WAYPOINTS_ONLY","Generic autopilot only supporting simple waypoints"},
	{6,"MAV_AUTOPILOT_GENERIC_WAYPOINTS_AND_SIMPLE_NAVIGATION_ONLY","Generic autopilot supporting waypoints and other simple navigation commands"},
	{7,"MAV_AUTOPILOT_GENERIC_MISSION_FULL","Generic autopilot supporting the full mission command set"},
	{8,"MAV_AUTOPILOT_INVALID","No valid autopilot, e.g. a GCS or other MAVLink component"},
	{9,"MAV_AUTOPILOT_PPZ","PPZ UAV - http://nongnu.org/paparazzi"},
	{10,"MAV_AUTOPILOT_UDB","UAV Dev Board"},
	{11,"MAV_AUTOPILOT_FP","FlexiPilot"},
	{12,"MAV_AUTOPILOT_PX4","PX4 Autopilot - http://px4.io/"},
	{13,"MAV_AUTOPILOT_SMACCMPILOT","SMACCMPilot - http://smaccmpilot.org"},
	{14,"MAV_AUTOPILOT_AUTOQUAD","AutoQuad -- http://autoquad.org"},
	{15,"MAV_AUTOPILOT_ARMAZILA","Armazila -- http://armazila.com"},
	{16,"MAV_AUTOPILOT_AEROB","Aerob -- http://aerob.ru"},
	{17,"MAV_AUTOPILOT_ASLUAV","ASLUAV autopilot -- http://www.asl.ethz.ch"},
	{18,"MAV_AUTOPILOT_SMARTAP","SmartAP Autopilot - http://sky-drones.com"},
	{19,"MAV_AUTOPILOT_AIRRAILS","AirRails - http://uaventure.com"},
	{20,"MAV_AUTOPILOT_REFLEX","Fusion Reflex - https://fusion.engineering"}
};

