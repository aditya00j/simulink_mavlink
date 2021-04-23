/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_header' on 21-Apr-2021 14:28:00
as part of Simulink MAVLink library.
*/

#include "C:\Users\INFO STOCK\Desktop\MAVlink\include\mavlink\v2.0\common\mavlink_msg_command_ack.h"

#define BUS_NAME_COMMAND_ACK "mavlink_command_ack_t"
#define NFIELDS_BUS_COMMAND_ACK 2
#define ENCODED_LEN_COMMAND_ACK (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_COMMAND_ACK_LEN)

/*
Encode the busInfo vector. This vector stores the starting index and total offset
for every element of the message bus. This is the standard way Simulink s-functions
handle bus interfaces.
*/
static inline void encode_businfo_command_ack(SimStruct *S, int_T *busInfo, const int_T offset)
{
	slDataTypeAccess *dta = ssGetDataTypeAccess(S);
	const char *bpath = ssGetPath(S);
	DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_COMMAND_ACK);
	
	busInfo[offset+0] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 0);
	busInfo[offset+1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint16"));
	busInfo[offset+2] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 1);
	busInfo[offset+3] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	ssSetUserData(S, busInfo);
}


/*
Encode the incoming character vector into the MAVLink bitstream. This process
consists of two stages - encode this character vector into a bus (using the
busInfo vector), and pass this struct to the MAVLink library to encode it into
a bitstream.
*/
static inline uint16_t encode_vector_command_ack(const char *uvec, const int_T *busInfo, uint8_T *yvec, const int_T offset)
{
	mavlink_command_ack_t ubus;
	mavlink_message_t msg_encoded;
	
	
	(void) memcpy(&ubus.command, uvec + busInfo[offset+0], busInfo[offset+1]);
	(void) memcpy(&ubus.result, uvec + busInfo[offset+2], busInfo[offset+3]);
	
	mavlink_msg_command_ack_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);
	return mavlink_msg_to_send_buffer(yvec, &msg_encoded);
}


/*
Decode the incoming MAVLink message into an output character vector. This process
consists of two stages - use the MAVLink library to convert the MAVLink message
into its appropriate struct, and then decode this struct into the output character
vector according to busInfo.
*/
static inline void decode_msg_command_ack(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec, const int_T offset)
{
	mavlink_command_ack_t ybus;
	mavlink_msg_command_ack_decode(msg_encoded, &ybus);
	
	
	(void) memcpy(yvec + busInfo[offset+0], &ybus.command, busInfo[offset+1]);
	(void) memcpy(yvec + busInfo[offset+2], &ybus.result, busInfo[offset+3]);
}
