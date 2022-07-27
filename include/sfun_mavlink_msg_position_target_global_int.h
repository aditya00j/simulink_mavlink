/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_header' on 12-Mar-2021 15:44:24
as part of Simulink MAVLink library.
*/

#include "C:\Users\INFO STOCK\Desktop\Communication MAVlink\include\mavlink\v2.0\common\mavlink_msg_position_target_global_int.h"

#define BUS_NAME_POSITION_TARGET_GLOBAL_INT "mavlink_position_target_global_int_t"
#define NFIELDS_BUS_POSITION_TARGET_GLOBAL_INT 14
#define ENCODED_LEN_POSITION_TARGET_GLOBAL_INT (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT_LEN)

/*
Encode the busInfo vector. This vector stores the starting index and total offset
for every element of the message bus. This is the standard way Simulink s-functions
handle bus interfaces.
*/
static inline void encode_businfo_position_target_global_int(SimStruct *S, int_T *busInfo, const int_T offset)
{
	slDataTypeAccess *dta = ssGetDataTypeAccess(S);
	const char *bpath = ssGetPath(S);
	DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_POSITION_TARGET_GLOBAL_INT);
	
	busInfo[offset+0] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 0);
	busInfo[offset+1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint32"));
	busInfo[offset+2] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 1);
	busInfo[offset+3] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "int32"));
	busInfo[offset+4] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 2);
	busInfo[offset+5] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "int32"));
	busInfo[offset+6] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 3);
	busInfo[offset+7] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+8] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 4);
	busInfo[offset+9] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+10] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 5);
	busInfo[offset+11] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+12] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 6);
	busInfo[offset+13] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+14] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 7);
	busInfo[offset+15] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+16] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 8);
	busInfo[offset+17] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+18] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 9);
	busInfo[offset+19] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+20] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 10);
	busInfo[offset+21] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+22] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 11);
	busInfo[offset+23] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+24] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 12);
	busInfo[offset+25] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint16"));
	busInfo[offset+26] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 13);
	busInfo[offset+27] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	ssSetUserData(S, busInfo);
}


/*
Encode the incoming character vector into the MAVLink bitstream. This process
consists of two stages - encode this character vector into a bus (using the
busInfo vector), and pass this struct to the MAVLink library to encode it into
a bitstream.
*/
static inline uint16_t encode_vector_position_target_global_int(const char *uvec, const int_T *busInfo, uint8_T *yvec, const int_T offset)
{
	mavlink_position_target_global_int_t ubus;
	mavlink_message_t msg_encoded;
	
	
	(void) memcpy(&ubus.time_boot_ms, uvec + busInfo[offset+0], busInfo[offset+1]);
	(void) memcpy(&ubus.lat_int, uvec + busInfo[offset+2], busInfo[offset+3]);
	(void) memcpy(&ubus.lon_int, uvec + busInfo[offset+4], busInfo[offset+5]);
	(void) memcpy(&ubus.alt, uvec + busInfo[offset+6], busInfo[offset+7]);
	(void) memcpy(&ubus.vx, uvec + busInfo[offset+8], busInfo[offset+9]);
	(void) memcpy(&ubus.vy, uvec + busInfo[offset+10], busInfo[offset+11]);
	(void) memcpy(&ubus.vz, uvec + busInfo[offset+12], busInfo[offset+13]);
	(void) memcpy(&ubus.afx, uvec + busInfo[offset+14], busInfo[offset+15]);
	(void) memcpy(&ubus.afy, uvec + busInfo[offset+16], busInfo[offset+17]);
	(void) memcpy(&ubus.afz, uvec + busInfo[offset+18], busInfo[offset+19]);
	(void) memcpy(&ubus.yaw, uvec + busInfo[offset+20], busInfo[offset+21]);
	(void) memcpy(&ubus.yaw_rate, uvec + busInfo[offset+22], busInfo[offset+23]);
	(void) memcpy(&ubus.type_mask, uvec + busInfo[offset+24], busInfo[offset+25]);
	(void) memcpy(&ubus.coordinate_frame, uvec + busInfo[offset+26], busInfo[offset+27]);
	
	mavlink_msg_position_target_global_int_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);
	return mavlink_msg_to_send_buffer(yvec, &msg_encoded);
}


/*
Decode the incoming MAVLink message into an output character vector. This process
consists of two stages - use the MAVLink library to convert the MAVLink message
into its appropriate struct, and then decode this struct into the output character
vector according to busInfo.
*/
static inline void decode_msg_position_target_global_int(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec, const int_T offset)
{
	mavlink_position_target_global_int_t ybus;
	mavlink_msg_position_target_global_int_decode(msg_encoded, &ybus);
	
	
	(void) memcpy(yvec + busInfo[offset+0], &ybus.time_boot_ms, busInfo[offset+1]);
	(void) memcpy(yvec + busInfo[offset+2], &ybus.lat_int, busInfo[offset+3]);
	(void) memcpy(yvec + busInfo[offset+4], &ybus.lon_int, busInfo[offset+5]);
	(void) memcpy(yvec + busInfo[offset+6], &ybus.alt, busInfo[offset+7]);
	(void) memcpy(yvec + busInfo[offset+8], &ybus.vx, busInfo[offset+9]);
	(void) memcpy(yvec + busInfo[offset+10], &ybus.vy, busInfo[offset+11]);
	(void) memcpy(yvec + busInfo[offset+12], &ybus.vz, busInfo[offset+13]);
	(void) memcpy(yvec + busInfo[offset+14], &ybus.afx, busInfo[offset+15]);
	(void) memcpy(yvec + busInfo[offset+16], &ybus.afy, busInfo[offset+17]);
	(void) memcpy(yvec + busInfo[offset+18], &ybus.afz, busInfo[offset+19]);
	(void) memcpy(yvec + busInfo[offset+20], &ybus.yaw, busInfo[offset+21]);
	(void) memcpy(yvec + busInfo[offset+22], &ybus.yaw_rate, busInfo[offset+23]);
	(void) memcpy(yvec + busInfo[offset+24], &ybus.type_mask, busInfo[offset+25]);
	(void) memcpy(yvec + busInfo[offset+26], &ybus.coordinate_frame, busInfo[offset+27]);
}
