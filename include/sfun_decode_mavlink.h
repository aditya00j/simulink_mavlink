/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_decode' on 04-Dec-2017 15:46:49
as part of Simulink MAVLink library.
*/

#include "include/sfun_mavlink_msg_attitude.h"
#include "include/sfun_mavlink_msg_raw_imu.h"

#define NFIELDS_OUTPUT_BUS (NFIELDS_BUS_ATTITUDE + NFIELDS_BUS_RAW_IMU)

#define OFFSET_ATTITUDE 0
#define OFFSET_RAW_IMU 2*(NFIELDS_BUS_ATTITUDE)

/*
Decode the incoming MAVLink message
*/
static inline void decode_mavlink_msg (SimStruct *S, const mavlink_message_t *msg)
{
	int_T *busInfo = (int_T *) ssGetUserData(S);

	char* yvec0 = (char *) ssGetOutputPortRealSignal(S, 0);
	char* yvec1 = (char *) ssGetOutputPortRealSignal(S, 1);
	switch (msg->msgid) {

		case MAVLINK_MSG_ID_ATTITUDE:
			decode_msg_attitude(msg, busInfo, yvec0, OFFSET_ATTITUDE);
			break;

		case MAVLINK_MSG_ID_RAW_IMU:
			decode_msg_raw_imu(msg, busInfo, yvec1, OFFSET_RAW_IMU);
			break;
	}
}
