struct MAV_TYPE_DATA_TYP {
	int Value;
	const char Function[64];
	const char Description[237];
};

struct MAV_TYPE_DATA_TYP const MAV_TYPE_DATA[] = {
	{0,"MAV_TYPE_GENERIC","Generic micro air vehicle"},
	{1,"MAV_TYPE_FIXED_WING","Fixed wing aircraft."},
	{2,"MAV_TYPE_QUADROTOR","Quadrotor"},
	{3,"MAV_TYPE_COAXIAL","Coaxial helicopter"},
	{4,"MAV_TYPE_HELICOPTER","Normal helicopter with tail rotor."},
	{5,"MAV_TYPE_ANTENNA_TRACKER","Ground installation"},
	{6,"MAV_TYPE_GCS","Operator control unit / ground control station"},
	{7,"MAV_TYPE_AIRSHIP","Airship, controlled"},
	{8,"MAV_TYPE_FREE_BALLOON","Free balloon, uncontrolled"},
	{9,"MAV_TYPE_ROCKET","Rocket"},
	{10,"MAV_TYPE_GROUND_ROVER","Ground rover"},
	{11,"MAV_TYPE_SURFACE_BOAT","Surface vessel, boat, ship"},
	{12,"MAV_TYPE_SUBMARINE","Submarine"},
	{13,"MAV_TYPE_HEXAROTOR","Hexarotor"},
	{14,"MAV_TYPE_OCTOROTOR","Octorotor"},
	{15,"MAV_TYPE_TRICOPTER","Tricopter"},
	{16,"MAV_TYPE_FLAPPING_WING","Flapping wing"},
	{17,"MAV_TYPE_KITE","Kite"},
	{18,"MAV_TYPE_ONBOARD_CONTROLLER","Onboard companion controller"},
	{19,"MAV_TYPE_VTOL_TAILSITTER_DUOROTOR","Two-rotor Tailsitter VTOL that additionally uses control surfaces in vertical operation. Note, value previously named MAV_TYPE_VTOL_DUOROTOR."},
	{20,"MAV_TYPE_VTOL_TAILSITTER_QUADROTOR","Quad-rotor Tailsitter VTOL using a V-shaped quad config in vertical operation. Note: value previously named MAV_TYPE_VTOL_QUADROTOR."},
	{21,"MAV_TYPE_VTOL_TILTROTOR","Tiltrotor VTOL. Fuselage and wings stay (nominally) horizontal in all flight phases. It able to tilt (some) rotors to provide thrust in cruise flight."},
	{22,"MAV_TYPE_VTOL_FIXEDROTOR","VTOL with separate fixed rotors for hover and cruise flight. Fuselage and wings stay (nominally) horizontal in all flight phases."},
	{23,"MAV_TYPE_VTOL_TAILSITTER","Tailsitter VTOL. Fuselage and wings orientation changes depending on flight phase: vertical for hover, horizontal for cruise. Use more specific VTOL MAV_TYPE_VTOL_TAILSITTER_DUOROTOR or MAV_TYPE_VTOL_TAILSITTER_QUADROTOR if appropriate."},
	{24,"MAV_TYPE_VTOL_TILTWING","Tiltwing VTOL. Fuselage stays horizontal in all flight phases. The whole wing, along with any attached engine, can tilt between vertical and horizontal mode."},
	{25,"MAV_TYPE_VTOL_RESERVED5","VTOL reserved 5"},
	{26,"MAV_TYPE_GIMBAL","Gimbal"},
	{27,"MAV_TYPE_ADSB","ADSB system"},
	{28,"MAV_TYPE_PARAFOIL","Steerable, nonrigid airfoil"},
	{29,"MAV_TYPE_DODECAROTOR","Dodecarotor"},
	{30,"MAV_TYPE_CAMERA","Camera"},
	{31,"MAV_TYPE_CHARGING_STATION","Charging station"},
	{32,"MAV_TYPE_FLARM","FLARM collision avoidance system"},
	{33,"MAV_TYPE_SERVO","Servo"},
	{34,"MAV_TYPE_ODID","Open Drone ID. See https://mavlink.io/en/services/opendroneid.html."},
	{35,"MAV_TYPE_DECAROTOR","Decarotor"},
	{36,"MAV_TYPE_BATTERY","Battery"},
	{37,"MAV_TYPE_PARACHUTE","Parachute"},
	{38,"MAV_TYPE_LOG","Log"},
	{39,"MAV_TYPE_OSD","OSD"},
	{40,"MAV_TYPE_IMU","IMU"},
	{41,"MAV_TYPE_GPS","GPS"},
	{42,"MAV_TYPE_WINCH","Winch"},
	{43,"MAV_TYPE_GENERIC_MULTIROTOR","Generic multirotor that does not fit into a specific type or whose type is unknown"},
	{44,"MAV_TYPE_ILLUMINATOR","Illuminator. An illuminator is a light source that is used for lighting up dark areas external to the sytstem: e.g. a torch or searchlight (as opposed to a light source for illuminating the system itself, e.g. an indicator light)."}
};

