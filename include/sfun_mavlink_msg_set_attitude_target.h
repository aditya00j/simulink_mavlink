/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_header' on 12-Apr-2021 17:04:06
as part of Simulink MAVLink library.
*/

#include "C:\Users\INFO STOCK\Desktop\MAVlink\include\mavlink\v2.0\common\mavlink_msg_set_attitude_target.h"

#define BUS_NAME_SET_ATTITUDE_TARGET "mavlink_set_attitude_target_t"
#define NFIELDS_BUS_SET_ATTITUDE_TARGET 9
#define ENCODED_LEN_SET_ATTITUDE_TARGET (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_SET_ATTITUDE_TARGET_LEN)

/*
Encode the busInfo vector. This vector stores the starting index and total offset
for every element of the message bus. This is the standard way Simulink s-functions
handle bus interfaces.
*/
static inline void encode_businfo_set_attitude_target(SimStruct *S, int_T *busInfo, const int_T offset)
{
	slDataTypeAccess *dta = ssGetDataTypeAccess(S);
	const char *bpath = ssGetPath(S);
	DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_SET_ATTITUDE_TARGET);
	
	busInfo[offset+0] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 0);
	busInfo[offset+1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint32"));
	busInfo[offset+2] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 1);
	busInfo[offset+3] = 4* dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+4] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 2);
	busInfo[offset+5] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+6] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 3);
	busInfo[offset+7] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+8] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 4);
	busInfo[offset+9] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+10] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 5);
	busInfo[offset+11] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+12] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 6);
	busInfo[offset+13] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+14] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 7);
	busInfo[offset+15] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+16] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 8);
	busInfo[offset+17] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	ssSetUserData(S, busInfo);
}


/*
Encode the incoming character vector into the MAVLink bitstream. This process
consists of two stages - encode this character vector into a bus (using the
busInfo vector), and pass this struct to the MAVLink library to encode it into
a bitstream.
*/
static inline uint16_t encode_vector_set_attitude_target(const char *uvec, const int_T *busInfo, uint8_T *yvec, const int_T offset)
{
	mavlink_set_attitude_target_t ubus;
	mavlink_message_t msg_encoded;
	
	
	(void) memcpy(&ubus.time_boot_ms, uvec + busInfo[offset+0], busInfo[offset+1]);
	(void) memcpy(ubus.q, uvec + busInfo[offset+2], busInfo[offset+3]);
	(void) memcpy(&ubus.body_roll_rate, uvec + busInfo[offset+4], busInfo[offset+5]);
	(void) memcpy(&ubus.body_pitch_rate, uvec + busInfo[offset+6], busInfo[offset+7]);
	(void) memcpy(&ubus.body_yaw_rate, uvec + busInfo[offset+8], busInfo[offset+9]);
	(void) memcpy(&ubus.thrust, uvec + busInfo[offset+10], busInfo[offset+11]);
	(void) memcpy(&ubus.target_system, uvec + busInfo[offset+12], busInfo[offset+13]);
	(void) memcpy(&ubus.target_component, uvec + busInfo[offset+14], busInfo[offset+15]);
	(void) memcpy(&ubus.type_mask, uvec + busInfo[offset+16], busInfo[offset+17]);
	
	mavlink_msg_set_attitude_target_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);
	return mavlink_msg_to_send_buffer(yvec, &msg_encoded);
}


/*
Decode the incoming MAVLink message into an output character vector. This process
consists of two stages - use the MAVLink library to convert the MAVLink message
into its appropriate struct, and then decode this struct into the output character
vector according to busInfo.
*/
static inline void decode_msg_set_attitude_target(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec, const int_T offset)
{
	mavlink_set_attitude_target_t ybus;
	mavlink_msg_set_attitude_target_decode(msg_encoded, &ybus);
	
	
	(void) memcpy(yvec + busInfo[offset+0], &ybus.time_boot_ms, busInfo[offset+1]);
	(void) memcpy(yvec + busInfo[offset+2], ybus.q, busInfo[offset+3]);
	(void) memcpy(yvec + busInfo[offset+4], &ybus.body_roll_rate, busInfo[offset+5]);
	(void) memcpy(yvec + busInfo[offset+6], &ybus.body_pitch_rate, busInfo[offset+7]);
	(void) memcpy(yvec + busInfo[offset+8], &ybus.body_yaw_rate, busInfo[offset+9]);
	(void) memcpy(yvec + busInfo[offset+10], &ybus.thrust, busInfo[offset+11]);
	(void) memcpy(yvec + busInfo[offset+12], &ybus.target_system, busInfo[offset+13]);
	(void) memcpy(yvec + busInfo[offset+14], &ybus.target_component, busInfo[offset+15]);
	(void) memcpy(yvec + busInfo[offset+16], &ybus.type_mask, busInfo[offset+17]);
}
