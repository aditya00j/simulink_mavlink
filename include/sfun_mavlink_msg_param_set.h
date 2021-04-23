/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_header' on 19-Feb-2021 02:55:42
as part of Simulink MAVLink library.
*/

#include "C:\Users\Dell\Desktop\Matlab_Directory\PX4\EN\include\mavlink\v2.0\common\mavlink_msg_param_set.h"

#define BUS_NAME_PARAM_SET "mavlink_param_set_t"
#define NFIELDS_BUS_PARAM_SET 5
#define ENCODED_LEN_PARAM_SET (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_PARAM_SET_LEN)

/*
Encode the busInfo vector. This vector stores the starting index and total offset
for every element of the message bus. This is the standard way Simulink s-functions
handle bus interfaces.
*/
static inline void encode_businfo_param_set(SimStruct *S, int_T *busInfo, const int_T offset)
{
	slDataTypeAccess *dta = ssGetDataTypeAccess(S);
	const char *bpath = ssGetPath(S);
	DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_PARAM_SET);
	
	busInfo[offset+0] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 0);
	busInfo[offset+1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+2] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 1);
	busInfo[offset+3] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+4] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 2);
	busInfo[offset+5] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+6] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 3);
	busInfo[offset+7] = 16* dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+8] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 4);
	busInfo[offset+9] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	ssSetUserData(S, busInfo);
}


/*
Encode the incoming character vector into the MAVLink bitstream. This process
consists of two stages - encode this character vector into a bus (using the
busInfo vector), and pass this struct to the MAVLink library to encode it into
a bitstream.
*/
static inline uint16_t encode_vector_param_set(const char *uvec, const int_T *busInfo, uint8_T *yvec, const int_T offset)
{
	mavlink_param_set_t ubus;
	mavlink_message_t msg_encoded;
	
	
	(void) memcpy(&ubus.param_value, uvec + busInfo[offset+0], busInfo[offset+1]);
	(void) memcpy(&ubus.target_system, uvec + busInfo[offset+2], busInfo[offset+3]);
	(void) memcpy(&ubus.target_component, uvec + busInfo[offset+4], busInfo[offset+5]);
	(void) memcpy(ubus.param_id, uvec + busInfo[offset+6], busInfo[offset+7]);
	(void) memcpy(&ubus.param_type, uvec + busInfo[offset+8], busInfo[offset+9]);
	
	mavlink_msg_param_set_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);
	return mavlink_msg_to_send_buffer(yvec, &msg_encoded);
}


/*
Decode the incoming MAVLink message into an output character vector. This process
consists of two stages - use the MAVLink library to convert the MAVLink message
into its appropriate struct, and then decode this struct into the output character
vector according to busInfo.
*/
static inline void decode_msg_param_set(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec, const int_T offset)
{
	mavlink_param_set_t ybus;
	mavlink_msg_param_set_decode(msg_encoded, &ybus);
	
	
	(void) memcpy(yvec + busInfo[offset+0], &ybus.param_value, busInfo[offset+1]);
	(void) memcpy(yvec + busInfo[offset+2], &ybus.target_system, busInfo[offset+3]);
	(void) memcpy(yvec + busInfo[offset+4], &ybus.target_component, busInfo[offset+5]);
	(void) memcpy(yvec + busInfo[offset+6], ybus.param_id, busInfo[offset+7]);
	(void) memcpy(yvec + busInfo[offset+8], &ybus.param_type, busInfo[offset+9]);
}
