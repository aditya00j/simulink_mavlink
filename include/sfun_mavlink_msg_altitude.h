/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_header' on 07-Aug-2020 10:58:54
as part of Simulink MAVLink library.
*/

#include "E:\rally\simulink_mavlink-master\include\mavlink\v2.0\common\mavlink_msg_altitude.h"

#define BUS_NAME_ALTITUDE "mavlink_altitude_t"
#define NFIELDS_BUS_ALTITUDE 7
#define ENCODED_LEN_ALTITUDE (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_ALTITUDE_LEN)

/*
Encode the busInfo vector. This vector stores the starting index and total offset
for every element of the message bus. This is the standard way Simulink s-functions
handle bus interfaces.
*/
static inline void encode_businfo_altitude(SimStruct *S, int_T *busInfo, const int_T offset)
{
	slDataTypeAccess *dta = ssGetDataTypeAccess(S);
	const char *bpath = ssGetPath(S);
	DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_ALTITUDE);
	
	busInfo[offset+0] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 0);
	busInfo[offset+1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "double"));
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
	ssSetUserData(S, busInfo);
}


/*
Encode the incoming character vector into the MAVLink bitstream. This process
consists of two stages - encode this character vector into a bus (using the
busInfo vector), and pass this struct to the MAVLink library to encode it into
a bitstream.
*/
static inline uint16_t encode_vector_altitude(const char *uvec, const int_T *busInfo, uint8_T *yvec, const int_T offset)
{
	mavlink_altitude_t ubus;
	mavlink_message_t msg_encoded;
	
	double time_usec;
	
	(void) memcpy(&time_usec, uvec + busInfo[offset+0], busInfo[offset+1]);
	ubus.time_usec = (uint64_t) time_usec;
	(void) memcpy(&ubus.altitude_monotonic, uvec + busInfo[offset+2], busInfo[offset+3]);
	(void) memcpy(&ubus.altitude_amsl, uvec + busInfo[offset+4], busInfo[offset+5]);
	(void) memcpy(&ubus.altitude_local, uvec + busInfo[offset+6], busInfo[offset+7]);
	(void) memcpy(&ubus.altitude_relative, uvec + busInfo[offset+8], busInfo[offset+9]);
	(void) memcpy(&ubus.altitude_terrain, uvec + busInfo[offset+10], busInfo[offset+11]);
	(void) memcpy(&ubus.bottom_clearance, uvec + busInfo[offset+12], busInfo[offset+13]);
	
	mavlink_msg_altitude_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);
	return mavlink_msg_to_send_buffer(yvec, &msg_encoded);
}


/*
Decode the incoming MAVLink message into an output character vector. This process
consists of two stages - use the MAVLink library to convert the MAVLink message
into its appropriate struct, and then decode this struct into the output character
vector according to busInfo.
*/
static inline void decode_msg_altitude(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec, const int_T offset)
{
	mavlink_altitude_t ybus;
	mavlink_msg_altitude_decode(msg_encoded, &ybus);
	
	double time_usec = (double) ybus.time_usec;
	
	(void) memcpy(yvec + busInfo[offset+0], &time_usec, busInfo[offset+1]);
	(void) memcpy(yvec + busInfo[offset+2], &ybus.altitude_monotonic, busInfo[offset+3]);
	(void) memcpy(yvec + busInfo[offset+4], &ybus.altitude_amsl, busInfo[offset+5]);
	(void) memcpy(yvec + busInfo[offset+6], &ybus.altitude_local, busInfo[offset+7]);
	(void) memcpy(yvec + busInfo[offset+8], &ybus.altitude_relative, busInfo[offset+9]);
	(void) memcpy(yvec + busInfo[offset+10], &ybus.altitude_terrain, busInfo[offset+11]);
	(void) memcpy(yvec + busInfo[offset+12], &ybus.bottom_clearance, busInfo[offset+13]);
}
