/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_header' on 07-Aug-2020 10:58:54
as part of Simulink MAVLink library.
*/

#include "E:\rally\simulink_mavlink-master\include\mavlink\v2.0\common\mavlink_msg_vfr_hud.h"

#define BUS_NAME_VFR_HUD "mavlink_vfr_hud_t"
#define NFIELDS_BUS_VFR_HUD 6
#define ENCODED_LEN_VFR_HUD (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_VFR_HUD_LEN)

/*
Encode the busInfo vector. This vector stores the starting index and total offset
for every element of the message bus. This is the standard way Simulink s-functions
handle bus interfaces.
*/
static inline void encode_businfo_vfr_hud(SimStruct *S, int_T *busInfo, const int_T offset)
{
	slDataTypeAccess *dta = ssGetDataTypeAccess(S);
	const char *bpath = ssGetPath(S);
	DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_VFR_HUD);
	
	busInfo[offset+0] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 0);
	busInfo[offset+1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+2] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 1);
	busInfo[offset+3] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+4] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 2);
	busInfo[offset+5] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+6] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 3);
	busInfo[offset+7] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[offset+8] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 4);
	busInfo[offset+9] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "int16"));
	busInfo[offset+10] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 5);
	busInfo[offset+11] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint16"));
	ssSetUserData(S, busInfo);
}


/*
Encode the incoming character vector into the MAVLink bitstream. This process
consists of two stages - encode this character vector into a bus (using the
busInfo vector), and pass this struct to the MAVLink library to encode it into
a bitstream.
*/
static inline uint16_t encode_vector_vfr_hud(const char *uvec, const int_T *busInfo, uint8_T *yvec, const int_T offset)
{
	mavlink_vfr_hud_t ubus;
	mavlink_message_t msg_encoded;
	
	
	(void) memcpy(&ubus.airspeed, uvec + busInfo[offset+0], busInfo[offset+1]);
	(void) memcpy(&ubus.groundspeed, uvec + busInfo[offset+2], busInfo[offset+3]);
	(void) memcpy(&ubus.alt, uvec + busInfo[offset+4], busInfo[offset+5]);
	(void) memcpy(&ubus.climb, uvec + busInfo[offset+6], busInfo[offset+7]);
	(void) memcpy(&ubus.heading, uvec + busInfo[offset+8], busInfo[offset+9]);
	(void) memcpy(&ubus.throttle, uvec + busInfo[offset+10], busInfo[offset+11]);
	
	mavlink_msg_vfr_hud_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);
	return mavlink_msg_to_send_buffer(yvec, &msg_encoded);
}


/*
Decode the incoming MAVLink message into an output character vector. This process
consists of two stages - use the MAVLink library to convert the MAVLink message
into its appropriate struct, and then decode this struct into the output character
vector according to busInfo.
*/
static inline void decode_msg_vfr_hud(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec, const int_T offset)
{
	mavlink_vfr_hud_t ybus;
	mavlink_msg_vfr_hud_decode(msg_encoded, &ybus);
	
	
	(void) memcpy(yvec + busInfo[offset+0], &ybus.airspeed, busInfo[offset+1]);
	(void) memcpy(yvec + busInfo[offset+2], &ybus.groundspeed, busInfo[offset+3]);
	(void) memcpy(yvec + busInfo[offset+4], &ybus.alt, busInfo[offset+5]);
	(void) memcpy(yvec + busInfo[offset+6], &ybus.climb, busInfo[offset+7]);
	(void) memcpy(yvec + busInfo[offset+8], &ybus.heading, busInfo[offset+9]);
	(void) memcpy(yvec + busInfo[offset+10], &ybus.throttle, busInfo[offset+11]);
}
