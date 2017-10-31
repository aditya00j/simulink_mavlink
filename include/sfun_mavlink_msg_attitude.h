#include "D:/simulink_mavlink/include/mavlink/v1.0/common/mavlink_msg_attitude.h"

#define BUS_NAME_ATTITUDE "mavlink_attitude_t"
#define NFIELDS_BUS_ATTITUDE 7
#define ENCODED_LEN_ATTITUDE (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_ATTITUDE_LEN)

/*
Encode the busInfo vector. This vector stores the starting index and total offset
for every element of the message bus. This is the standard way Simulink s-functions
handle bus interfaces.
*/
static inline void encode_businfo_attitude(SimStruct *S, int_T *busInfo)
{
    slDataTypeAccess *dta = ssGetDataTypeAccess(S);
    const char *bpath = ssGetPath(S);
    DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_ATTITUDE);

    busInfo[0] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 0) ;
    busInfo[1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint32"));
    busInfo[2] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 1) ;
    busInfo[3] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
    busInfo[4] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 2) ;
    busInfo[5] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
    busInfo[6] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 3) ;
    busInfo[7] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
    busInfo[8] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 4) ;
    busInfo[9] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
    busInfo[10] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 5) ;
    busInfo[11] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
    busInfo[12] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, 6) ;
    busInfo[13] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
}

/*
Encode the incoming character vector into the MAVLink bitstream. This process
consists of two stages - encode this character vector into a bus (using the
busInfo vector), and pass this struct to the MAVLink library to encode it into
a bitstream.
*/
static inline uint16_t encode_vector_attitude(const char *uvec, const int_T *busInfo, uint8_T *yvec)
{
    mavlink_attitude_t ubus;
    mavlink_message_t msg_encoded;

    (void) memcpy(&ubus.time_boot_ms, uvec + busInfo[0], busInfo[1]);
    (void) memcpy(&ubus.roll, uvec + busInfo[2], busInfo[3]);
    (void) memcpy(&ubus.pitch, uvec + busInfo[4], busInfo[5]);
    (void) memcpy(&ubus.yaw, uvec + busInfo[6], busInfo[7]);
    (void) memcpy(&ubus.rollspeed, uvec + busInfo[8], busInfo[9]);
    (void) memcpy(&ubus.pitchspeed, uvec + busInfo[10], busInfo[11]);
    (void) memcpy(&ubus.yawspeed, uvec + busInfo[12], busInfo[13]);

    mavlink_msg_attitude_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);
    return mavlink_msg_to_send_buffer(yvec, &msg_encoded);
}


/*
Decode the incoming MAVLink message into an output character vector. This process
consists of two stages - use the MAVLink library to convert the MAVLink message
into its appropriate struct, and then decode this struct into the output character
vector according to busInfo.
*/
static inline void decode_msg_attitude(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec)
{
  mavlink_attitude_t ybus;
  mavlink_msg_attitude_decode(msg_encoded, &ybus);

  /*Copy output bus*/
  (void) memcpy(yvec + busInfo[0], &ybus.time_boot_ms, busInfo[1]);
  (void) memcpy(yvec + busInfo[2], &ybus.roll, busInfo[3]);
  (void) memcpy(yvec + busInfo[4], &ybus.pitch, busInfo[5]);
  (void) memcpy(yvec + busInfo[6], &ybus.yaw, busInfo[7]);
  (void) memcpy(yvec + busInfo[8], &ybus.rollspeed, busInfo[9]);
  (void) memcpy(yvec + busInfo[10], &ybus.pitchspeed, busInfo[11]);
  (void) memcpy(yvec + busInfo[12], &ybus.yawspeed, busInfo[13]);
}
