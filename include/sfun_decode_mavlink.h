/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_decode' on 22-Apr-2021 16:50:56
as part of Simulink MAVLink library.
*/

#include "C:\Users\INFO STOCK\Desktop\MAVlink\include\sfun_mavlink_msg_attitude.h"

#define NFIELDS_OUTPUT_BUS (NFIELDS_BUS_ATTITUDE)

#define OFFSET_ATTITUDE 0

/*
Decode the incoming MAVLink message
*/
static inline void decode_mavlink_msg (SimStruct *S, const mavlink_message_t *msg)
{
	int_T *busInfo = (int_T *) ssGetUserData(S);

	char* yvec0 = (char *) ssGetOutputPortRealSignal(S, 0);
	switch (msg->msgid) {

		case MAVLINK_MSG_ID_ATTITUDE:
			decode_msg_attitude(msg, busInfo, yvec0, OFFSET_ATTITUDE);
			break;
	}
}
