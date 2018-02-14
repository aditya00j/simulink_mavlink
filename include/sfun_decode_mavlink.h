/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_decode' on 03-Feb-2018 14:21:39
as part of Simulink MAVLink library.
*/

#include "D:\simulink_mavlink\include\sfun_mavlink_msg_ga_payload_feedback.h"
#include "D:\simulink_mavlink\include\sfun_mavlink_msg_ga_payload_commands.h"
#include "D:\simulink_mavlink\include\sfun_mavlink_msg_data96.h"
#include "D:\simulink_mavlink\include\sfun_mavlink_msg_heartbeat.h"

#define NFIELDS_OUTPUT_BUS (NFIELDS_BUS_GA_PAYLOAD_FEEDBACK + NFIELDS_BUS_GA_PAYLOAD_COMMANDS + NFIELDS_BUS_DATA96 + NFIELDS_BUS_HEARTBEAT)

#define OFFSET_GA_PAYLOAD_FEEDBACK 0
#define OFFSET_GA_PAYLOAD_COMMANDS 2*(NFIELDS_BUS_GA_PAYLOAD_FEEDBACK)
#define OFFSET_DATA96 2*(NFIELDS_BUS_GA_PAYLOAD_COMMANDS+NFIELDS_BUS_GA_PAYLOAD_FEEDBACK)
#define OFFSET_HEARTBEAT 2*(NFIELDS_BUS_DATA96+NFIELDS_BUS_GA_PAYLOAD_COMMANDS+NFIELDS_BUS_GA_PAYLOAD_FEEDBACK)

/*
Decode the incoming MAVLink message
*/
static inline void decode_mavlink_msg (SimStruct *S, const mavlink_message_t *msg)
{
	int_T *busInfo = (int_T *) ssGetUserData(S);

	char* yvec0 = (char *) ssGetOutputPortRealSignal(S, 0);
	char* yvec1 = (char *) ssGetOutputPortRealSignal(S, 1);
	char* yvec2 = (char *) ssGetOutputPortRealSignal(S, 2);
	char* yvec3 = (char *) ssGetOutputPortRealSignal(S, 3);
	switch (msg->msgid) {

		case MAVLINK_MSG_ID_GA_PAYLOAD_FEEDBACK:
			decode_msg_ga_payload_feedback(msg, busInfo, yvec0, OFFSET_GA_PAYLOAD_FEEDBACK);
			break;

		case MAVLINK_MSG_ID_GA_PAYLOAD_COMMANDS:
			decode_msg_ga_payload_commands(msg, busInfo, yvec1, OFFSET_GA_PAYLOAD_COMMANDS);
			break;

		case MAVLINK_MSG_ID_DATA96:
			decode_msg_data96(msg, busInfo, yvec2, OFFSET_DATA96);
			break;

		case MAVLINK_MSG_ID_HEARTBEAT:
			decode_msg_heartbeat(msg, busInfo, yvec3, OFFSET_HEARTBEAT);
			break;
	}
}
