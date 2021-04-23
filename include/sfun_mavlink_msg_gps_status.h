/*
DO NOT EDIT.
This file was automatically created by the Matlab function 'create_sfun_header' on 07-Aug-2020 09:59:47
as part of Simulink MAVLink library.
*/

#include "E:\rally\simulink_mavlink-master\include\mavlink\v2.0\common\mavlink_msg_gps_status.h"

#define BUS_NAME_GPS_STATUS "mavlink_gps_status_t"
#define NFIELDS_BUS_GPS_STATUS 6
#define ENCODED_LEN_GPS_STATUS (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_GPS_STATUS_LEN)

/*
Encode the busInfo vector. This vector stores the starting index and total offset
for every element of the message bus. This is the standard way Simulink s-functions
handle bus interfaces.
*/
static inline void encode_businfo_gps_status(SimStruct *S, int_T *busInfo, const int_T offset)
{
	slDataTypeAccess *dta = ssGetDataTypeAccess(S);
	const char *bpath = ssGetPath(S);
	DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_GPS_STATUS);
	
	busInfo[offset+0] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 0);
	busInfo[offset+1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+2] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 1);
	busInfo[offset+3] = 20* dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+4] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 2);
	busInfo[offset+5] = 20* dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+6] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 3);
	busInfo[offset+7] = 20* dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+8] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 4);
	busInfo[offset+9] = 20* dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[offset+10] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 5);
	busInfo[offset+11] = 20* dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	ssSetUserData(S, busInfo);
}


/*
Encode the incoming character vector into the MAVLink bitstream. This process
consists of two stages - encode this character vector into a bus (using the
busInfo vector), and pass this struct to the MAVLink library to encode it into
a bitstream.
*/
static inline uint16_t encode_vector_gps_status(const char *uvec, const int_T *busInfo, uint8_T *yvec, const int_T offset)
{
	mavlink_gps_status_t ubus;
	mavlink_message_t msg_encoded;
	
	
	(void) memcpy(&ubus.satellites_visible, uvec + busInfo[offset+0], busInfo[offset+1]);
	(void) memcpy(ubus.satellite_prn, uvec + busInfo[offset+2], busInfo[offset+3]);
	(void) memcpy(ubus.satellite_used, uvec + busInfo[offset+4], busInfo[offset+5]);
	(void) memcpy(ubus.satellite_elevation, uvec + busInfo[offset+6], busInfo[offset+7]);
	(void) memcpy(ubus.satellite_azimuth, uvec + busInfo[offset+8], busInfo[offset+9]);
	(void) memcpy(ubus.satellite_snr, uvec + busInfo[offset+10], busInfo[offset+11]);
	
	mavlink_msg_gps_status_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);
	return mavlink_msg_to_send_buffer(yvec, &msg_encoded);
}


/*
Decode the incoming MAVLink message into an output character vector. This process
consists of two stages - use the MAVLink library to convert the MAVLink message
into its appropriate struct, and then decode this struct into the output character
vector according to busInfo.
*/
static inline void decode_msg_gps_status(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec, const int_T offset)
{
	mavlink_gps_status_t ybus;
	mavlink_msg_gps_status_decode(msg_encoded, &ybus);
	
	
	(void) memcpy(yvec + busInfo[offset+0], &ybus.satellites_visible, busInfo[offset+1]);
	(void) memcpy(yvec + busInfo[offset+2], ybus.satellite_prn, busInfo[offset+3]);
	(void) memcpy(yvec + busInfo[offset+4], ybus.satellite_used, busInfo[offset+5]);
	(void) memcpy(yvec + busInfo[offset+6], ybus.satellite_elevation, busInfo[offset+7]);
	(void) memcpy(yvec + busInfo[offset+8], ybus.satellite_azimuth, busInfo[offset+9]);
	(void) memcpy(yvec + busInfo[offset+10], ybus.satellite_snr, busInfo[offset+11]);
}
