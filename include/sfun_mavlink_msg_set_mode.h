/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_header' on 08-Mar-2021 14:40:53
as part of Simulink MAVLink library.
*/

#include "C:\Users\INFO STOCK\Desktop\Communication MAVlink\include\mavlink\v2.0\common\mavlink_msg_set_mode.h"

#define BUS_NAME_SET_MODE "mavlink_set_mode_t"
#define NFIELDS_BUS_SET_MODE 3
#define ENCODED_LEN_SET_MODE (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_SET_MODE_LEN)

/*
Encode the busInfo vector. This vector stores the starting index and total offset
for every element of the message bus. This is the standard way Simulink s-functions
handle bus interfaces.
*/
static inline void encode_businfo_set_mode(SimStruct *S, int_T *busInfo, const int_T offset)
{
	slDataTypeAccess *dta = ssGetDataTypeAccess(S);
	const char *bpath = ssGetPath(S);
	DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_SET_MODE);
	
	busInfo[offset+0] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 0);
	busInfo[offset+1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint32"));
	busInfo[offset+2] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 1);
	busInfo[offset+3] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+4] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 2);
	busInfo[offset+5] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	ssSetUserData(S, busInfo);
}


/*
Encode the incoming character vector into the MAVLink bitstream. This process
consists of two stages - encode this character vector into a bus (using the
busInfo vector), and pass this struct to the MAVLink library to encode it into
a bitstream.
*/
static inline uint16_t encode_vector_set_mode(const char *uvec, const int_T *busInfo, uint8_T *yvec, const int_T offset)
{
	mavlink_set_mode_t ubus;
	mavlink_message_t msg_encoded;
	
	
	(void) memcpy(&ubus.custom_mode, uvec + busInfo[offset+0], busInfo[offset+1]);
	(void) memcpy(&ubus.target_system, uvec + busInfo[offset+2], busInfo[offset+3]);
	(void) memcpy(&ubus.base_mode, uvec + busInfo[offset+4], busInfo[offset+5]);
	
	mavlink_msg_set_mode_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);
	return mavlink_msg_to_send_buffer(yvec, &msg_encoded);
}


/*
Decode the incoming MAVLink message into an output character vector. This process
consists of two stages - use the MAVLink library to convert the MAVLink message
into its appropriate struct, and then decode this struct into the output character
vector according to busInfo.
*/
static inline void decode_msg_set_mode(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec, const int_T offset)
{
	mavlink_set_mode_t ybus;
	mavlink_msg_set_mode_decode(msg_encoded, &ybus);
	
	
	(void) memcpy(yvec + busInfo[offset+0], &ybus.custom_mode, busInfo[offset+1]);
	(void) memcpy(yvec + busInfo[offset+2], &ybus.target_system, busInfo[offset+3]);
	(void) memcpy(yvec + busInfo[offset+4], &ybus.base_mode, busInfo[offset+5]);
}
