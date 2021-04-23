/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_header' on 12-Apr-2021 17:04:07
as part of Simulink MAVLink library.
*/

#include "C:\Users\INFO STOCK\Desktop\MAVlink\include\mavlink\v2.0\common\mavlink_msg_request_data_stream.h"

#define BUS_NAME_REQUEST_DATA_STREAM "mavlink_request_data_stream_t"
#define NFIELDS_BUS_REQUEST_DATA_STREAM 5
#define ENCODED_LEN_REQUEST_DATA_STREAM (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_REQUEST_DATA_STREAM_LEN)

/*
Encode the busInfo vector. This vector stores the starting index and total offset
for every element of the message bus. This is the standard way Simulink s-functions
handle bus interfaces.
*/
static inline void encode_businfo_request_data_stream(SimStruct *S, int_T *busInfo, const int_T offset)
{
	slDataTypeAccess *dta = ssGetDataTypeAccess(S);
	const char *bpath = ssGetPath(S);
	DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_REQUEST_DATA_STREAM);
	
	busInfo[offset+0] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 0);
	busInfo[offset+1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint16"));
	busInfo[offset+2] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 1);
	busInfo[offset+3] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+4] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 2);
	busInfo[offset+5] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+6] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 3);
	busInfo[offset+7] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
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
static inline uint16_t encode_vector_request_data_stream(const char *uvec, const int_T *busInfo, uint8_T *yvec, const int_T offset)
{
	mavlink_request_data_stream_t ubus;
	mavlink_message_t msg_encoded;
	
	
	(void) memcpy(&ubus.req_message_rate, uvec + busInfo[offset+0], busInfo[offset+1]);
	(void) memcpy(&ubus.target_system, uvec + busInfo[offset+2], busInfo[offset+3]);
	(void) memcpy(&ubus.target_component, uvec + busInfo[offset+4], busInfo[offset+5]);
	(void) memcpy(&ubus.req_stream_id, uvec + busInfo[offset+6], busInfo[offset+7]);
	(void) memcpy(&ubus.start_stop, uvec + busInfo[offset+8], busInfo[offset+9]);
	
	mavlink_msg_request_data_stream_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);
	return mavlink_msg_to_send_buffer(yvec, &msg_encoded);
}


/*
Decode the incoming MAVLink message into an output character vector. This process
consists of two stages - use the MAVLink library to convert the MAVLink message
into its appropriate struct, and then decode this struct into the output character
vector according to busInfo.
*/
static inline void decode_msg_request_data_stream(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec, const int_T offset)
{
	mavlink_request_data_stream_t ybus;
	mavlink_msg_request_data_stream_decode(msg_encoded, &ybus);
	
	
	(void) memcpy(yvec + busInfo[offset+0], &ybus.req_message_rate, busInfo[offset+1]);
	(void) memcpy(yvec + busInfo[offset+2], &ybus.target_system, busInfo[offset+3]);
	(void) memcpy(yvec + busInfo[offset+4], &ybus.target_component, busInfo[offset+5]);
	(void) memcpy(yvec + busInfo[offset+6], &ybus.req_stream_id, busInfo[offset+7]);
	(void) memcpy(yvec + busInfo[offset+8], &ybus.start_stop, busInfo[offset+9]);
}
