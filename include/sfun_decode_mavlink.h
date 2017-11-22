/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_decode' on 22-Nov-2017 11:13:27
as part of Simulink MAVLink library.
*/

#include "C:\Simulation\simulink_mavlink\include\sfun_mavlink_msg_heartbeat.h"
#include "C:\Simulation\simulink_mavlink\include\sfun_mavlink_msg_attitude.h"
#include "C:\Simulation\simulink_mavlink\include\sfun_mavlink_msg_raw_imu.h"

#define NFIELDS_OUTPUT_BUS (NFIELDS_BUS_HEARTBEAT + NFIELDS_BUS_ATTITUDE + NFIELDS_BUS_RAW_IMU)

#define OFFSET_HEARTBEAT 0
#define OFFSET_ATTITUDE 2*(NFIELDS_BUS_HEARTBEAT)
#define OFFSET_RAW_IMU 2*(NFIELDS_BUS_ATTITUDE+NFIELDS_BUS_HEARTBEAT)

/*
Decode the incoming MAVLink message
*/
static inline void decode_mavlink_msg (SimStruct *S, const mavlink_message_t *msg)
{
	int_T *busInfo = (int_T *) ssGetUserData(S);

	char* yvec0 = (char *) ssGetOutputPortRealSignal(S, 0);
	char* yvec1 = (char *) ssGetOutputPortRealSignal(S, 1);
	char* yvec2 = (char *) ssGetOutputPortRealSignal(S, 2);
	switch (msg->msgid) {

		case MAVLINK_MSG_ID_HEARTBEAT:
			decode_msg_heartbeat(msg, busInfo, yvec0, OFFSET_HEARTBEAT);

		case MAVLINK_MSG_ID_ATTITUDE:
			decode_msg_attitude(msg, busInfo, yvec1, OFFSET_ATTITUDE);

		case MAVLINK_MSG_ID_RAW_IMU:
			decode_msg_raw_imu(msg, busInfo, yvec2, OFFSET_RAW_IMU);
	}
}
