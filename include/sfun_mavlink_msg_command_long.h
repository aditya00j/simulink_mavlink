/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_header' on 21-Apr-2021 14:28:00
as part of Simulink MAVLink library.
*/

#include "C:\Users\INFO STOCK\Desktop\MAVlink\include\mavlink\v2.0\common\mavlink_msg_command_long.h"

#define BUS_NAME_COMMAND_LONG "mavlink_command_long_t"
#define NFIELDS_BUS_COMMAND_LONG 11
#define ENCODED_LEN_COMMAND_LONG (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_COMMAND_LONG_LEN)

/*
Encode the busInfo vector. This vector stores the starting index and total offset
for every element of the message bus. This is the standard way Simulink s-functions
handle bus interfaces.
*/
static inline void encode_businfo_command_long(SimStruct *S, int_T *busInfo, const int_T offset)
{
	slDataTypeAccess *dta = ssGetDataTypeAccess(S);
	const char *bpath = ssGetPath(S);
	DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_COMMAND_LONG);
	
	busInfo[offset+0] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 0);
	busInfo[offset+1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+2] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 1);
	busInfo[offset+3] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+4] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 2);
	busInfo[offset+5] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+6] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 3);
	busInfo[offset+7] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+8] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 4);
	busInfo[offset+9] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+10] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 5);
	busInfo[offset+11] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+12] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 6);
	busInfo[offset+13] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+14] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 7);
	busInfo[offset+15] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint16"));
	busInfo[offset+16] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 8);
	busInfo[offset+17] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+18] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 9);
	busInfo[offset+19] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+20] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 10);
	busInfo[offset+21] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	ssSetUserData(S, busInfo);
}


/*
Encode the incoming character vector into the MAVLink bitstream. This process
consists of two stages - encode this character vector into a bus (using the
busInfo vector), and pass this struct to the MAVLink library to encode it into
a bitstream.
*/
static inline uint16_t encode_vector_command_long(const char *uvec, const int_T *busInfo, uint8_T *yvec, const int_T offset)
{
	mavlink_command_long_t ubus;
	mavlink_message_t msg_encoded;
	
	
	(void) memcpy(&ubus.param1, uvec + busInfo[offset+0], busInfo[offset+1]);
	(void) memcpy(&ubus.param2, uvec + busInfo[offset+2], busInfo[offset+3]);
	(void) memcpy(&ubus.param3, uvec + busInfo[offset+4], busInfo[offset+5]);
	(void) memcpy(&ubus.param4, uvec + busInfo[offset+6], busInfo[offset+7]);
	(void) memcpy(&ubus.param5, uvec + busInfo[offset+8], busInfo[offset+9]);
	(void) memcpy(&ubus.param6, uvec + busInfo[offset+10], busInfo[offset+11]);
	(void) memcpy(&ubus.param7, uvec + busInfo[offset+12], busInfo[offset+13]);
	(void) memcpy(&ubus.command, uvec + busInfo[offset+14], busInfo[offset+15]);
	(void) memcpy(&ubus.target_system, uvec + busInfo[offset+16], busInfo[offset+17]);
	(void) memcpy(&ubus.target_component, uvec + busInfo[offset+18], busInfo[offset+19]);
	(void) memcpy(&ubus.confirmation, uvec + busInfo[offset+20], busInfo[offset+21]);
	
	mavlink_msg_command_long_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);
	return mavlink_msg_to_send_buffer(yvec, &msg_encoded);
}


/*
Decode the incoming MAVLink message into an output character vector. This process
consists of two stages - use the MAVLink library to convert the MAVLink message
into its appropriate struct, and then decode this struct into the output character
vector according to busInfo.
*/
static inline void decode_msg_command_long(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec, const int_T offset)
{
	mavlink_command_long_t ybus;
	mavlink_msg_command_long_decode(msg_encoded, &ybus);
	
	
	(void) memcpy(yvec + busInfo[offset+0], &ybus.param1, busInfo[offset+1]);
	(void) memcpy(yvec + busInfo[offset+2], &ybus.param2, busInfo[offset+3]);
	(void) memcpy(yvec + busInfo[offset+4], &ybus.param3, busInfo[offset+5]);
	(void) memcpy(yvec + busInfo[offset+6], &ybus.param4, busInfo[offset+7]);
	(void) memcpy(yvec + busInfo[offset+8], &ybus.param5, busInfo[offset+9]);
	(void) memcpy(yvec + busInfo[offset+10], &ybus.param6, busInfo[offset+11]);
	(void) memcpy(yvec + busInfo[offset+12], &ybus.param7, busInfo[offset+13]);
	(void) memcpy(yvec + busInfo[offset+14], &ybus.command, busInfo[offset+15]);
	(void) memcpy(yvec + busInfo[offset+16], &ybus.target_system, busInfo[offset+17]);
	(void) memcpy(yvec + busInfo[offset+18], &ybus.target_component, busInfo[offset+19]);
	(void) memcpy(yvec + busInfo[offset+20], &ybus.confirmation, busInfo[offset+21]);
}
