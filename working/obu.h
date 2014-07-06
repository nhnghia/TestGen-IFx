


/*
 *
 * IF-2.0 Intermediate Representation.
 * 
 * Copyright (C) Verimag Grenoble.
 *
 * Marius Bozga
 *
 */









#define if_SD_constant 300

#define if_N_TRAINS_constant 1

#define if_N_RBCS_constant 0

#define if_MAX_SPEED_constant 121

#define if_N_SECTIONS_constant 5


typedef if_integer_type if_ID_type;

#define if_ID_copy(x,y) if_integer_copy(x,y)
#define if_ID_compare(x,y) if_integer_compare(x,y)
#define if_ID_print(x,f) if_integer_print(x,f)
#define if_ID_print_xml(x,b) if_integer_print_xml(x,b)
#define if_ID_reset(x) (x)=0
#define if_ID_iterate(x) for(x=0;x<=100;x++)
#define if_ID_eq(x,y) if_ID_compare(x,y)==0
#define if_ID_ne(x,y) if_ID_compare(x,y)!=0

typedef if_integer_type if_Location_type;

#define if_Location_copy(x,y) if_integer_copy(x,y)
#define if_Location_compare(x,y) if_integer_compare(x,y)
#define if_Location_print(x,f) if_integer_print(x,f)
#define if_Location_print_xml(x,b) if_integer_print_xml(x,b)
#define if_Location_reset(x) (x)=100
#define if_Location_iterate(x) for(x=100;x<=100;x++)
#define if_Location_eq(x,y) if_Location_compare(x,y)==0
#define if_Location_ne(x,y) if_Location_compare(x,y)!=0

typedef if_integer_type if_Distance_type;

#define if_Distance_copy(x,y) if_integer_copy(x,y)
#define if_Distance_compare(x,y) if_integer_compare(x,y)
#define if_Distance_print(x,f) if_integer_print(x,f)
#define if_Distance_print_xml(x,b) if_integer_print_xml(x,b)
#define if_Distance_reset(x) (x)=100
#define if_Distance_iterate(x) for(x=100;x<=100;x++)
#define if_Distance_eq(x,y) if_Distance_compare(x,y)==0
#define if_Distance_ne(x,y) if_Distance_compare(x,y)!=0

typedef if_integer_type if_Timeout_type;

#define if_Timeout_copy(x,y) if_integer_copy(x,y)
#define if_Timeout_compare(x,y) if_integer_compare(x,y)
#define if_Timeout_print(x,f) if_integer_print(x,f)
#define if_Timeout_print_xml(x,b) if_integer_print_xml(x,b)
#define if_Timeout_reset(x) (x)=0
#define if_Timeout_iterate(x) for(x=0;x<=100;x++)
#define if_Timeout_eq(x,y) if_Timeout_compare(x,y)==0
#define if_Timeout_ne(x,y) if_Timeout_compare(x,y)!=0

typedef if_integer_type if_Size_type;

#define if_Size_copy(x,y) if_integer_copy(x,y)
#define if_Size_compare(x,y) if_integer_compare(x,y)
#define if_Size_print(x,f) if_integer_print(x,f)
#define if_Size_print_xml(x,b) if_integer_print_xml(x,b)
#define if_Size_reset(x) (x)=1
#define if_Size_iterate(x) for(x=1;x<=10;x++)
#define if_Size_eq(x,y) if_Size_compare(x,y)==0
#define if_Size_ne(x,y) if_Size_compare(x,y)!=0

typedef if_integer_type if_Bool_type;

#define if_Bool_copy(x,y) if_integer_copy(x,y)
#define if_Bool_compare(x,y) if_integer_compare(x,y)
#define if_Bool_print(x,f) if_integer_print(x,f)
#define if_Bool_print_xml(x,b) if_integer_print_xml(x,b)
#define if_Bool_reset(x) (x)=0
#define if_Bool_iterate(x) for(x=0;x<=1;x++)
#define if_Bool_eq(x,y) if_Bool_compare(x,y)==0
#define if_Bool_ne(x,y) if_Bool_compare(x,y)!=0

typedef if_integer_type if_Speed_type;

#define if_Speed_copy(x,y) if_integer_copy(x,y)
#define if_Speed_compare(x,y) if_integer_compare(x,y)
#define if_Speed_print(x,f) if_integer_print(x,f)
#define if_Speed_print_xml(x,b) if_integer_print_xml(x,b)
#define if_Speed_reset(x) (x)=120
#define if_Speed_iterate(x) for(x=120;x<=if_MAX_SPEED_constant;x++)
#define if_Speed_eq(x,y) if_Speed_compare(x,y)==0
#define if_Speed_ne(x,y) if_Speed_compare(x,y)!=0

typedef struct {
  if_Distance_type distance;
  if_Speed_type speed;
} if_DangerPointInfo_type;

inline void if_DangerPointInfo_copy
    (if_DangerPointInfo_type& x, const if_DangerPointInfo_type y);
inline int if_DangerPointInfo_compare
    (const if_DangerPointInfo_type x, const if_DangerPointInfo_type y);
inline void if_DangerPointInfo_print
    (const if_DangerPointInfo_type x, FILE* f);
inline void if_DangerPointInfo_reset
    (if_DangerPointInfo_type& x);
#define if_DangerPointInfo_iterate(x)\
  if_Distance_iterate(x.distance)\
  if_Speed_iterate(x.speed)
inline if_DangerPointInfo_type if_DangerPointInfo_make
    (if_Distance_type distance,if_Speed_type speed);
#define if_DangerPointInfo_eq(x,y) if_DangerPointInfo_compare(x,y)==0
#define if_DangerPointInfo_ne(x,y) if_DangerPointInfo_compare(x,y)!=0

typedef struct {
  if_Distance_type distance;
  if_Timeout_type timeout;
  if_Timeout_type distanceTimeout;
  if_Speed_type speed;
} if_OverlapInfo_type;

inline void if_OverlapInfo_copy
    (if_OverlapInfo_type& x, const if_OverlapInfo_type y);
inline int if_OverlapInfo_compare
    (const if_OverlapInfo_type x, const if_OverlapInfo_type y);
inline void if_OverlapInfo_print
    (const if_OverlapInfo_type x, FILE* f);
inline void if_OverlapInfo_reset
    (if_OverlapInfo_type& x);
#define if_OverlapInfo_iterate(x)\
  if_Distance_iterate(x.distance)\
  if_Timeout_iterate(x.timeout)\
  if_Timeout_iterate(x.distanceTimeout)\
  if_Speed_iterate(x.speed)
inline if_OverlapInfo_type if_OverlapInfo_make
    (if_Distance_type distance,if_Timeout_type timeout,if_Timeout_type distanceTimeout,if_Speed_type speed);
#define if_OverlapInfo_eq(x,y) if_OverlapInfo_compare(x,y)==0
#define if_OverlapInfo_ne(x,y) if_OverlapInfo_compare(x,y)!=0

typedef struct {
  if_Distance_type distance;
  if_Timeout_type timeout;
  if_Distance_type timeoutStop;
} if_Section_type;

inline void if_Section_copy
    (if_Section_type& x, const if_Section_type y);
inline int if_Section_compare
    (const if_Section_type x, const if_Section_type y);
inline void if_Section_print
    (const if_Section_type x, FILE* f);
inline void if_Section_reset
    (if_Section_type& x);
#define if_Section_iterate(x)\
  if_Distance_iterate(x.distance)\
  if_Timeout_iterate(x.timeout)\
  if_Distance_iterate(x.timeoutStop)
inline if_Section_type if_Section_make
    (if_Distance_type distance,if_Timeout_type timeout,if_Distance_type timeoutStop);
#define if_Section_eq(x,y) if_Section_compare(x,y)==0
#define if_Section_ne(x,y) if_Section_compare(x,y)!=0

typedef struct {
  if_Distance_type distance;
  if_Timeout_type timeout;
  if_Distance_type timeoutStop;
  if_Timeout_type endTimeout;
  if_Distance_type endDistance;
  if_DangerPointInfo_type dangerInfo;
  if_OverlapInfo_type overlapInfo;
} if_EndSection_type;

inline void if_EndSection_copy
    (if_EndSection_type& x, const if_EndSection_type y);
inline int if_EndSection_compare
    (const if_EndSection_type x, const if_EndSection_type y);
inline void if_EndSection_print
    (const if_EndSection_type x, FILE* f);
inline void if_EndSection_reset
    (if_EndSection_type& x);
#define if_EndSection_iterate(x)\
  if_Distance_iterate(x.distance)\
  if_Timeout_iterate(x.timeout)\
  if_Distance_iterate(x.timeoutStop)\
  if_Timeout_iterate(x.endTimeout)\
  if_Distance_iterate(x.endDistance)\
  if_DangerPointInfo_iterate(x.dangerInfo)\
  if_OverlapInfo_iterate(x.overlapInfo)
inline if_EndSection_type if_EndSection_make
    (if_Distance_type distance,if_Timeout_type timeout,if_Distance_type timeoutStop,if_Timeout_type endTimeout,if_Distance_type endDistance,if_DangerPointInfo_type dangerInfo,if_OverlapInfo_type overlapInfo);
#define if_EndSection_eq(x,y) if_EndSection_compare(x,y)==0
#define if_EndSection_ne(x,y) if_EndSection_compare(x,y)!=0

typedef if_Section_type if_Sections_type[if_N_SECTIONS_constant];

inline void if_Sections_copy
    (if_Sections_type& x, const if_Sections_type y);
inline int if_Sections_compare
    (const if_Sections_type x, const if_Sections_type y);
inline void if_Sections_print
    (const if_Sections_type x, FILE* f);
inline void if_Sections_reset
    (if_Sections_type& x);
#define if_Sections_iterate(x)\
  if_Section_iterate(x[4])\
  if_Section_iterate(x[3])\
  if_Section_iterate(x[2])\
  if_Section_iterate(x[1])\
  if_Section_iterate(x[0])
#define if_Sections_eq(x,y) if_Sections_compare(x,y)==0
#define if_Sections_ne(x,y) if_Sections_compare(x,y)!=0

typedef struct {
  if_Distance_type distance;
  if_Speed_type speed;
} if_MovementAuthority_type;

inline void if_MovementAuthority_copy
    (if_MovementAuthority_type& x, const if_MovementAuthority_type y);
inline int if_MovementAuthority_compare
    (const if_MovementAuthority_type x, const if_MovementAuthority_type y);
inline void if_MovementAuthority_print
    (const if_MovementAuthority_type x, FILE* f);
inline void if_MovementAuthority_reset
    (if_MovementAuthority_type& x);
#define if_MovementAuthority_iterate(x)\
  if_Distance_iterate(x.distance)\
  if_Speed_iterate(x.speed)
inline if_MovementAuthority_type if_MovementAuthority_make
    (if_Distance_type distance,if_Speed_type speed);
#define if_MovementAuthority_eq(x,y) if_MovementAuthority_compare(x,y)==0
#define if_MovementAuthority_ne(x,y) if_MovementAuthority_compare(x,y)!=0

typedef enum {
  if_DRIVER_constant,
  if_TIME_BEFORE_EOA_LOA_constant,
  if_TIMER_EXPIRED_constant,
  if_TRACK_DES_constant,
  if_TRACK_FREEUP_constant
} if_Reason_type;

extern const char* if_Reason_name[];

#define if_Reason_copy(x,y) (x)=(y)
#define if_Reason_compare(x,y) (x)-(y)
#define if_Reason_print(x,f) fprintf(f,"%s",if_Reason_name[x])
#define if_Reason_print_xml(x,b) b << "<Reason value=\"" << if_Reason_name[x] << "\" />"
#define if_Reason_reset(x) (x)=(if_Reason_type)0
#define if_Reason_iterate(x) for(x=(if_Reason_type)0;x<=if_TRACK_FREEUP_constant;x=(if_Reason_type)(x + 1))
#define if_Reason_eq(x,y) if_Reason_compare(x,y)==0
#define if_Reason_ne(x,y) if_Reason_compare(x,y)!=0

typedef enum {
  if_NORMAL_constant,
  if_INDICATION_constant,
  if_OVERSPEED_constant,
  if_WARNING_constant,
  if_INTERVENTION_constant
} if_STATUS_type;

extern const char* if_STATUS_name[];

#define if_STATUS_copy(x,y) (x)=(y)
#define if_STATUS_compare(x,y) (x)-(y)
#define if_STATUS_print(x,f) fprintf(f,"%s",if_STATUS_name[x])
#define if_STATUS_print_xml(x,b) b << "<STATUS value=\"" << if_STATUS_name[x] << "\" />"
#define if_STATUS_reset(x) (x)=(if_STATUS_type)0
#define if_STATUS_iterate(x) for(x=(if_STATUS_type)0;x<=if_INTERVENTION_constant;x=(if_STATUS_type)(x + 1))
#define if_STATUS_eq(x,y) if_STATUS_compare(x,y)==0
#define if_STATUS_ne(x,y) if_STATUS_compare(x,y)!=0

typedef struct {
  if_MovementAuthority_type p1;
} if_t_MA_type;

inline void if_t_MA_copy
    (if_t_MA_type& x, const if_t_MA_type y);
inline int if_t_MA_compare
    (const if_t_MA_type x, const if_t_MA_type y);
inline void if_t_MA_print
    (const if_t_MA_type x, FILE* f);
inline void if_t_MA_reset
    (if_t_MA_type& x);
#define if_t_MA_iterate(x)\
  if_MovementAuthority_iterate(x.p1)
inline if_t_MA_type if_t_MA_make
    (if_MovementAuthority_type p1);
#define if_t_MA_eq(x,y) if_t_MA_compare(x,y)==0
#define if_t_MA_ne(x,y) if_t_MA_compare(x,y)!=0


typedef if_void_type if_t_RequestToStopEarlier_type;

#define if_t_RequestToStopEarlier_copy(x,y) if_void_copy(x,y)
#define if_t_RequestToStopEarlier_compare(x,y) if_void_compare(x,y)
#define if_t_RequestToStopEarlier_print(x,f) if_void_print(x,f)
#define if_t_RequestToStopEarlier_print_xml(x,b) if_void_print_xml(x,b)
#define if_t_RequestToStopEarlier_reset(x) if_void_reset(x)
#define if_t_RequestToStopEarlier_iterate(x) if_void_iterate(x)
#define if_t_RequestToStopEarlier_eq(x,y) if_t_RequestToStopEarlier_compare(x,y)==0
#define if_t_RequestToStopEarlier_ne(x,y) if_t_RequestToStopEarlier_compare(x,y)!=0


typedef if_void_type if_t_EmergencyMessages_type;

#define if_t_EmergencyMessages_copy(x,y) if_void_copy(x,y)
#define if_t_EmergencyMessages_compare(x,y) if_void_compare(x,y)
#define if_t_EmergencyMessages_print(x,f) if_void_print(x,f)
#define if_t_EmergencyMessages_print_xml(x,b) if_void_print_xml(x,b)
#define if_t_EmergencyMessages_reset(x) if_void_reset(x)
#define if_t_EmergencyMessages_iterate(x) if_void_iterate(x)
#define if_t_EmergencyMessages_eq(x,y) if_t_EmergencyMessages_compare(x,y)==0
#define if_t_EmergencyMessages_ne(x,y) if_t_EmergencyMessages_compare(x,y)!=0


typedef if_void_type if_t_TemporarySpeedRestrictions_type;

#define if_t_TemporarySpeedRestrictions_copy(x,y) if_void_copy(x,y)
#define if_t_TemporarySpeedRestrictions_compare(x,y) if_void_compare(x,y)
#define if_t_TemporarySpeedRestrictions_print(x,f) if_void_print(x,f)
#define if_t_TemporarySpeedRestrictions_print_xml(x,b) if_void_print_xml(x,b)
#define if_t_TemporarySpeedRestrictions_reset(x) if_void_reset(x)
#define if_t_TemporarySpeedRestrictions_iterate(x) if_void_iterate(x)
#define if_t_TemporarySpeedRestrictions_eq(x,y) if_t_TemporarySpeedRestrictions_compare(x,y)==0
#define if_t_TemporarySpeedRestrictions_ne(x,y) if_t_TemporarySpeedRestrictions_compare(x,y)!=0

typedef struct {
  if_Location_type p1;
} if_t_MARequest_type;

inline void if_t_MARequest_copy
    (if_t_MARequest_type& x, const if_t_MARequest_type y);
inline int if_t_MARequest_compare
    (const if_t_MARequest_type x, const if_t_MARequest_type y);
inline void if_t_MARequest_print
    (const if_t_MARequest_type x, FILE* f);
inline void if_t_MARequest_reset
    (if_t_MARequest_type& x);
#define if_t_MARequest_iterate(x)\
  if_Location_iterate(x.p1)
inline if_t_MARequest_type if_t_MARequest_make
    (if_Location_type p1);
#define if_t_MARequest_eq(x,y) if_t_MARequest_compare(x,y)==0
#define if_t_MARequest_ne(x,y) if_t_MARequest_compare(x,y)!=0


typedef if_void_type if_t_NeedSendMARequest_type;

#define if_t_NeedSendMARequest_copy(x,y) if_void_copy(x,y)
#define if_t_NeedSendMARequest_compare(x,y) if_void_compare(x,y)
#define if_t_NeedSendMARequest_print(x,f) if_void_print(x,f)
#define if_t_NeedSendMARequest_print_xml(x,b) if_void_print_xml(x,b)
#define if_t_NeedSendMARequest_reset(x) if_void_reset(x)
#define if_t_NeedSendMARequest_iterate(x) if_void_iterate(x)
#define if_t_NeedSendMARequest_eq(x,y) if_t_NeedSendMARequest_compare(x,y)==0
#define if_t_NeedSendMARequest_ne(x,y) if_t_NeedSendMARequest_compare(x,y)!=0

typedef struct {
  if_STATUS_type p1;
} if_t_CurrentStatus_type;

inline void if_t_CurrentStatus_copy
    (if_t_CurrentStatus_type& x, const if_t_CurrentStatus_type y);
inline int if_t_CurrentStatus_compare
    (const if_t_CurrentStatus_type x, const if_t_CurrentStatus_type y);
inline void if_t_CurrentStatus_print
    (const if_t_CurrentStatus_type x, FILE* f);
inline void if_t_CurrentStatus_reset
    (if_t_CurrentStatus_type& x);
#define if_t_CurrentStatus_iterate(x)\
  if_STATUS_iterate(x.p1)
inline if_t_CurrentStatus_type if_t_CurrentStatus_make
    (if_STATUS_type p1);
#define if_t_CurrentStatus_eq(x,y) if_t_CurrentStatus_compare(x,y)==0
#define if_t_CurrentStatus_ne(x,y) if_t_CurrentStatus_compare(x,y)!=0

typedef struct {
  if_Speed_type p1;
} if_t_ESpeed_type;

inline void if_t_ESpeed_copy
    (if_t_ESpeed_type& x, const if_t_ESpeed_type y);
inline int if_t_ESpeed_compare
    (const if_t_ESpeed_type x, const if_t_ESpeed_type y);
inline void if_t_ESpeed_print
    (const if_t_ESpeed_type x, FILE* f);
inline void if_t_ESpeed_reset
    (if_t_ESpeed_type& x);
#define if_t_ESpeed_iterate(x)\
  if_Speed_iterate(x.p1)
inline if_t_ESpeed_type if_t_ESpeed_make
    (if_Speed_type p1);
#define if_t_ESpeed_eq(x,y) if_t_ESpeed_compare(x,y)==0
#define if_t_ESpeed_ne(x,y) if_t_ESpeed_compare(x,y)!=0

typedef struct {
  if_Location_type p1;
} if_t_ELocation_type;

inline void if_t_ELocation_copy
    (if_t_ELocation_type& x, const if_t_ELocation_type y);
inline int if_t_ELocation_compare
    (const if_t_ELocation_type x, const if_t_ELocation_type y);
inline void if_t_ELocation_print
    (const if_t_ELocation_type x, FILE* f);
inline void if_t_ELocation_reset
    (if_t_ELocation_type& x);
#define if_t_ELocation_iterate(x)\
  if_Location_iterate(x.p1)
inline if_t_ELocation_type if_t_ELocation_make
    (if_Location_type p1);
#define if_t_ELocation_eq(x,y) if_t_ELocation_compare(x,y)==0
#define if_t_ELocation_ne(x,y) if_t_ELocation_compare(x,y)!=0

typedef struct {
  if_Bool_type p1;
} if_t_ServiceBrakingCmd_type;

inline void if_t_ServiceBrakingCmd_copy
    (if_t_ServiceBrakingCmd_type& x, const if_t_ServiceBrakingCmd_type y);
inline int if_t_ServiceBrakingCmd_compare
    (const if_t_ServiceBrakingCmd_type x, const if_t_ServiceBrakingCmd_type y);
inline void if_t_ServiceBrakingCmd_print
    (const if_t_ServiceBrakingCmd_type x, FILE* f);
inline void if_t_ServiceBrakingCmd_reset
    (if_t_ServiceBrakingCmd_type& x);
#define if_t_ServiceBrakingCmd_iterate(x)\
  if_Bool_iterate(x.p1)
inline if_t_ServiceBrakingCmd_type if_t_ServiceBrakingCmd_make
    (if_Bool_type p1);
#define if_t_ServiceBrakingCmd_eq(x,y) if_t_ServiceBrakingCmd_compare(x,y)==0
#define if_t_ServiceBrakingCmd_ne(x,y) if_t_ServiceBrakingCmd_compare(x,y)!=0

typedef struct {
  if_Bool_type p1;
} if_t_EBcmd_type;

inline void if_t_EBcmd_copy
    (if_t_EBcmd_type& x, const if_t_EBcmd_type y);
inline int if_t_EBcmd_compare
    (const if_t_EBcmd_type x, const if_t_EBcmd_type y);
inline void if_t_EBcmd_print
    (const if_t_EBcmd_type x, FILE* f);
inline void if_t_EBcmd_reset
    (if_t_EBcmd_type& x);
#define if_t_EBcmd_iterate(x)\
  if_Bool_iterate(x.p1)
inline if_t_EBcmd_type if_t_EBcmd_make
    (if_Bool_type p1);
#define if_t_EBcmd_eq(x,y) if_t_EBcmd_compare(x,y)==0
#define if_t_EBcmd_ne(x,y) if_t_EBcmd_compare(x,y)!=0

typedef struct {
  if_Speed_type p1;
} if_t_DMIcmd_type;

inline void if_t_DMIcmd_copy
    (if_t_DMIcmd_type& x, const if_t_DMIcmd_type y);
inline int if_t_DMIcmd_compare
    (const if_t_DMIcmd_type x, const if_t_DMIcmd_type y);
inline void if_t_DMIcmd_print
    (const if_t_DMIcmd_type x, FILE* f);
inline void if_t_DMIcmd_reset
    (if_t_DMIcmd_type& x);
#define if_t_DMIcmd_iterate(x)\
  if_Speed_iterate(x.p1)
inline if_t_DMIcmd_type if_t_DMIcmd_make
    (if_Speed_type p1);
#define if_t_DMIcmd_eq(x,y) if_t_DMIcmd_compare(x,y)==0
#define if_t_DMIcmd_ne(x,y) if_t_DMIcmd_compare(x,y)!=0


typedef if_void_type if_t_EmergencyBrake_type;

#define if_t_EmergencyBrake_copy(x,y) if_void_copy(x,y)
#define if_t_EmergencyBrake_compare(x,y) if_void_compare(x,y)
#define if_t_EmergencyBrake_print(x,f) if_void_print(x,f)
#define if_t_EmergencyBrake_print_xml(x,b) if_void_print_xml(x,b)
#define if_t_EmergencyBrake_reset(x) if_void_reset(x)
#define if_t_EmergencyBrake_iterate(x) if_void_iterate(x)
#define if_t_EmergencyBrake_eq(x,y) if_t_EmergencyBrake_compare(x,y)==0
#define if_t_EmergencyBrake_ne(x,y) if_t_EmergencyBrake_compare(x,y)!=0

typedef struct {
  if_Location_type p1;
} if_t_DLocation_type;

inline void if_t_DLocation_copy
    (if_t_DLocation_type& x, const if_t_DLocation_type y);
inline int if_t_DLocation_compare
    (const if_t_DLocation_type x, const if_t_DLocation_type y);
inline void if_t_DLocation_print
    (const if_t_DLocation_type x, FILE* f);
inline void if_t_DLocation_reset
    (if_t_DLocation_type& x);
#define if_t_DLocation_iterate(x)\
  if_Location_iterate(x.p1)
inline if_t_DLocation_type if_t_DLocation_make
    (if_Location_type p1);
#define if_t_DLocation_eq(x,y) if_t_DLocation_compare(x,y)==0
#define if_t_DLocation_ne(x,y) if_t_DLocation_compare(x,y)!=0

typedef IfMessage* if_t_if_signal_type;

#define if_t_if_signal_eq(x,y) if_t_if_signal_compare(x,y)==0
#define if_t_if_signal_ne(x,y) if_t_if_signal_compare(x,y)!=0


/* 
 * MA message interface 
 *
 */

#define if_MA_signal 0


typedef struct {
  if_MovementAuthority_type p1;
} if_MA_par_type;

inline void if_MA_par_copy
    (if_MA_par_type& x, const if_MA_par_type y);
inline int if_MA_par_compare
    (const if_MA_par_type x, const if_MA_par_type y);
inline void if_MA_par_print
    (const if_MA_par_type x, FILE* f);
inline void if_MA_par_reset
    (if_MA_par_type& x);
#define if_MA_par_iterate(x)\
  if_MovementAuthority_iterate(x.p1)
inline if_MA_par_type if_MA_par_make
    (if_MovementAuthority_type p1);
#define if_MA_par_eq(x,y) if_MA_par_compare(x,y)==0
#define if_MA_par_ne(x,y) if_MA_par_compare(x,y)!=0

class if_MA_message : public IfMessage {

public:
  if_MA_message();
  if_MA_message(if_MovementAuthority_type p1);
  if_MA_message(const if_MA_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_MA_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * RequestToStopEarlier message interface 
 *
 */

#define if_RequestToStopEarlier_signal 1



typedef if_void_type if_RequestToStopEarlier_par_type;

#define if_RequestToStopEarlier_par_copy(x,y) if_void_copy(x,y)
#define if_RequestToStopEarlier_par_compare(x,y) if_void_compare(x,y)
#define if_RequestToStopEarlier_par_print(x,f) if_void_print(x,f)
#define if_RequestToStopEarlier_par_print_xml(x,b) if_void_print_xml(x,b)
#define if_RequestToStopEarlier_par_reset(x) if_void_reset(x)
#define if_RequestToStopEarlier_par_iterate(x) if_void_iterate(x)
#define if_RequestToStopEarlier_par_eq(x,y) if_RequestToStopEarlier_par_compare(x,y)==0
#define if_RequestToStopEarlier_par_ne(x,y) if_RequestToStopEarlier_par_compare(x,y)!=0

class if_RequestToStopEarlier_message : public IfMessage {

public:
  
  if_RequestToStopEarlier_message();
  if_RequestToStopEarlier_message(const if_RequestToStopEarlier_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_RequestToStopEarlier_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * EmergencyMessages message interface 
 *
 */

#define if_EmergencyMessages_signal 2



typedef if_void_type if_EmergencyMessages_par_type;

#define if_EmergencyMessages_par_copy(x,y) if_void_copy(x,y)
#define if_EmergencyMessages_par_compare(x,y) if_void_compare(x,y)
#define if_EmergencyMessages_par_print(x,f) if_void_print(x,f)
#define if_EmergencyMessages_par_print_xml(x,b) if_void_print_xml(x,b)
#define if_EmergencyMessages_par_reset(x) if_void_reset(x)
#define if_EmergencyMessages_par_iterate(x) if_void_iterate(x)
#define if_EmergencyMessages_par_eq(x,y) if_EmergencyMessages_par_compare(x,y)==0
#define if_EmergencyMessages_par_ne(x,y) if_EmergencyMessages_par_compare(x,y)!=0

class if_EmergencyMessages_message : public IfMessage {

public:
  
  if_EmergencyMessages_message();
  if_EmergencyMessages_message(const if_EmergencyMessages_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_EmergencyMessages_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * TemporarySpeedRestrictions message interface 
 *
 */

#define if_TemporarySpeedRestrictions_signal 3



typedef if_void_type if_TemporarySpeedRestrictions_par_type;

#define if_TemporarySpeedRestrictions_par_copy(x,y) if_void_copy(x,y)
#define if_TemporarySpeedRestrictions_par_compare(x,y) if_void_compare(x,y)
#define if_TemporarySpeedRestrictions_par_print(x,f) if_void_print(x,f)
#define if_TemporarySpeedRestrictions_par_print_xml(x,b) if_void_print_xml(x,b)
#define if_TemporarySpeedRestrictions_par_reset(x) if_void_reset(x)
#define if_TemporarySpeedRestrictions_par_iterate(x) if_void_iterate(x)
#define if_TemporarySpeedRestrictions_par_eq(x,y) if_TemporarySpeedRestrictions_par_compare(x,y)==0
#define if_TemporarySpeedRestrictions_par_ne(x,y) if_TemporarySpeedRestrictions_par_compare(x,y)!=0

class if_TemporarySpeedRestrictions_message : public IfMessage {

public:
  
  if_TemporarySpeedRestrictions_message();
  if_TemporarySpeedRestrictions_message(const if_TemporarySpeedRestrictions_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_TemporarySpeedRestrictions_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * MARequest message interface 
 *
 */

#define if_MARequest_signal 4


typedef struct {
  if_Location_type p1;
} if_MARequest_par_type;

inline void if_MARequest_par_copy
    (if_MARequest_par_type& x, const if_MARequest_par_type y);
inline int if_MARequest_par_compare
    (const if_MARequest_par_type x, const if_MARequest_par_type y);
inline void if_MARequest_par_print
    (const if_MARequest_par_type x, FILE* f);
inline void if_MARequest_par_reset
    (if_MARequest_par_type& x);
#define if_MARequest_par_iterate(x)\
  if_Location_iterate(x.p1)
inline if_MARequest_par_type if_MARequest_par_make
    (if_Location_type p1);
#define if_MARequest_par_eq(x,y) if_MARequest_par_compare(x,y)==0
#define if_MARequest_par_ne(x,y) if_MARequest_par_compare(x,y)!=0

class if_MARequest_message : public IfMessage {

public:
  if_MARequest_message();
  if_MARequest_message(if_Location_type p1);
  if_MARequest_message(const if_MARequest_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_MARequest_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * NeedSendMARequest message interface 
 *
 */

#define if_NeedSendMARequest_signal 5



typedef if_void_type if_NeedSendMARequest_par_type;

#define if_NeedSendMARequest_par_copy(x,y) if_void_copy(x,y)
#define if_NeedSendMARequest_par_compare(x,y) if_void_compare(x,y)
#define if_NeedSendMARequest_par_print(x,f) if_void_print(x,f)
#define if_NeedSendMARequest_par_print_xml(x,b) if_void_print_xml(x,b)
#define if_NeedSendMARequest_par_reset(x) if_void_reset(x)
#define if_NeedSendMARequest_par_iterate(x) if_void_iterate(x)
#define if_NeedSendMARequest_par_eq(x,y) if_NeedSendMARequest_par_compare(x,y)==0
#define if_NeedSendMARequest_par_ne(x,y) if_NeedSendMARequest_par_compare(x,y)!=0

class if_NeedSendMARequest_message : public IfMessage {

public:
  
  if_NeedSendMARequest_message();
  if_NeedSendMARequest_message(const if_NeedSendMARequest_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_NeedSendMARequest_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * CurrentStatus message interface 
 *
 */

#define if_CurrentStatus_signal 6


typedef struct {
  if_STATUS_type p1;
} if_CurrentStatus_par_type;

inline void if_CurrentStatus_par_copy
    (if_CurrentStatus_par_type& x, const if_CurrentStatus_par_type y);
inline int if_CurrentStatus_par_compare
    (const if_CurrentStatus_par_type x, const if_CurrentStatus_par_type y);
inline void if_CurrentStatus_par_print
    (const if_CurrentStatus_par_type x, FILE* f);
inline void if_CurrentStatus_par_reset
    (if_CurrentStatus_par_type& x);
#define if_CurrentStatus_par_iterate(x)\
  if_STATUS_iterate(x.p1)
inline if_CurrentStatus_par_type if_CurrentStatus_par_make
    (if_STATUS_type p1);
#define if_CurrentStatus_par_eq(x,y) if_CurrentStatus_par_compare(x,y)==0
#define if_CurrentStatus_par_ne(x,y) if_CurrentStatus_par_compare(x,y)!=0

class if_CurrentStatus_message : public IfMessage {

public:
  if_CurrentStatus_message();
  if_CurrentStatus_message(if_STATUS_type p1);
  if_CurrentStatus_message(const if_CurrentStatus_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_CurrentStatus_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * ESpeed message interface 
 *
 */

#define if_ESpeed_signal 7


typedef struct {
  if_Speed_type p1;
} if_ESpeed_par_type;

inline void if_ESpeed_par_copy
    (if_ESpeed_par_type& x, const if_ESpeed_par_type y);
inline int if_ESpeed_par_compare
    (const if_ESpeed_par_type x, const if_ESpeed_par_type y);
inline void if_ESpeed_par_print
    (const if_ESpeed_par_type x, FILE* f);
inline void if_ESpeed_par_reset
    (if_ESpeed_par_type& x);
#define if_ESpeed_par_iterate(x)\
  if_Speed_iterate(x.p1)
inline if_ESpeed_par_type if_ESpeed_par_make
    (if_Speed_type p1);
#define if_ESpeed_par_eq(x,y) if_ESpeed_par_compare(x,y)==0
#define if_ESpeed_par_ne(x,y) if_ESpeed_par_compare(x,y)!=0

class if_ESpeed_message : public IfMessage {

public:
  if_ESpeed_message();
  if_ESpeed_message(if_Speed_type p1);
  if_ESpeed_message(const if_ESpeed_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_ESpeed_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * ELocation message interface 
 *
 */

#define if_ELocation_signal 8


typedef struct {
  if_Location_type p1;
} if_ELocation_par_type;

inline void if_ELocation_par_copy
    (if_ELocation_par_type& x, const if_ELocation_par_type y);
inline int if_ELocation_par_compare
    (const if_ELocation_par_type x, const if_ELocation_par_type y);
inline void if_ELocation_par_print
    (const if_ELocation_par_type x, FILE* f);
inline void if_ELocation_par_reset
    (if_ELocation_par_type& x);
#define if_ELocation_par_iterate(x)\
  if_Location_iterate(x.p1)
inline if_ELocation_par_type if_ELocation_par_make
    (if_Location_type p1);
#define if_ELocation_par_eq(x,y) if_ELocation_par_compare(x,y)==0
#define if_ELocation_par_ne(x,y) if_ELocation_par_compare(x,y)!=0

class if_ELocation_message : public IfMessage {

public:
  if_ELocation_message();
  if_ELocation_message(if_Location_type p1);
  if_ELocation_message(const if_ELocation_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_ELocation_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * ServiceBrakingCmd message interface 
 *
 */

#define if_ServiceBrakingCmd_signal 9


typedef struct {
  if_Bool_type p1;
} if_ServiceBrakingCmd_par_type;

inline void if_ServiceBrakingCmd_par_copy
    (if_ServiceBrakingCmd_par_type& x, const if_ServiceBrakingCmd_par_type y);
inline int if_ServiceBrakingCmd_par_compare
    (const if_ServiceBrakingCmd_par_type x, const if_ServiceBrakingCmd_par_type y);
inline void if_ServiceBrakingCmd_par_print
    (const if_ServiceBrakingCmd_par_type x, FILE* f);
inline void if_ServiceBrakingCmd_par_reset
    (if_ServiceBrakingCmd_par_type& x);
#define if_ServiceBrakingCmd_par_iterate(x)\
  if_Bool_iterate(x.p1)
inline if_ServiceBrakingCmd_par_type if_ServiceBrakingCmd_par_make
    (if_Bool_type p1);
#define if_ServiceBrakingCmd_par_eq(x,y) if_ServiceBrakingCmd_par_compare(x,y)==0
#define if_ServiceBrakingCmd_par_ne(x,y) if_ServiceBrakingCmd_par_compare(x,y)!=0

class if_ServiceBrakingCmd_message : public IfMessage {

public:
  if_ServiceBrakingCmd_message();
  if_ServiceBrakingCmd_message(if_Bool_type p1);
  if_ServiceBrakingCmd_message(const if_ServiceBrakingCmd_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_ServiceBrakingCmd_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * EBcmd message interface 
 *
 */

#define if_EBcmd_signal 10


typedef struct {
  if_Bool_type p1;
} if_EBcmd_par_type;

inline void if_EBcmd_par_copy
    (if_EBcmd_par_type& x, const if_EBcmd_par_type y);
inline int if_EBcmd_par_compare
    (const if_EBcmd_par_type x, const if_EBcmd_par_type y);
inline void if_EBcmd_par_print
    (const if_EBcmd_par_type x, FILE* f);
inline void if_EBcmd_par_reset
    (if_EBcmd_par_type& x);
#define if_EBcmd_par_iterate(x)\
  if_Bool_iterate(x.p1)
inline if_EBcmd_par_type if_EBcmd_par_make
    (if_Bool_type p1);
#define if_EBcmd_par_eq(x,y) if_EBcmd_par_compare(x,y)==0
#define if_EBcmd_par_ne(x,y) if_EBcmd_par_compare(x,y)!=0

class if_EBcmd_message : public IfMessage {

public:
  if_EBcmd_message();
  if_EBcmd_message(if_Bool_type p1);
  if_EBcmd_message(const if_EBcmd_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_EBcmd_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * DMIcmd message interface 
 *
 */

#define if_DMIcmd_signal 11


typedef struct {
  if_Speed_type p1;
} if_DMIcmd_par_type;

inline void if_DMIcmd_par_copy
    (if_DMIcmd_par_type& x, const if_DMIcmd_par_type y);
inline int if_DMIcmd_par_compare
    (const if_DMIcmd_par_type x, const if_DMIcmd_par_type y);
inline void if_DMIcmd_par_print
    (const if_DMIcmd_par_type x, FILE* f);
inline void if_DMIcmd_par_reset
    (if_DMIcmd_par_type& x);
#define if_DMIcmd_par_iterate(x)\
  if_Speed_iterate(x.p1)
inline if_DMIcmd_par_type if_DMIcmd_par_make
    (if_Speed_type p1);
#define if_DMIcmd_par_eq(x,y) if_DMIcmd_par_compare(x,y)==0
#define if_DMIcmd_par_ne(x,y) if_DMIcmd_par_compare(x,y)!=0

class if_DMIcmd_message : public IfMessage {

public:
  if_DMIcmd_message();
  if_DMIcmd_message(if_Speed_type p1);
  if_DMIcmd_message(const if_DMIcmd_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_DMIcmd_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * EmergencyBrake message interface 
 *
 */

#define if_EmergencyBrake_signal 12



typedef if_void_type if_EmergencyBrake_par_type;

#define if_EmergencyBrake_par_copy(x,y) if_void_copy(x,y)
#define if_EmergencyBrake_par_compare(x,y) if_void_compare(x,y)
#define if_EmergencyBrake_par_print(x,f) if_void_print(x,f)
#define if_EmergencyBrake_par_print_xml(x,b) if_void_print_xml(x,b)
#define if_EmergencyBrake_par_reset(x) if_void_reset(x)
#define if_EmergencyBrake_par_iterate(x) if_void_iterate(x)
#define if_EmergencyBrake_par_eq(x,y) if_EmergencyBrake_par_compare(x,y)==0
#define if_EmergencyBrake_par_ne(x,y) if_EmergencyBrake_par_compare(x,y)!=0

class if_EmergencyBrake_message : public IfMessage {

public:
  
  if_EmergencyBrake_message();
  if_EmergencyBrake_message(const if_EmergencyBrake_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_EmergencyBrake_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * DLocation message interface 
 *
 */

#define if_DLocation_signal 13


typedef struct {
  if_Location_type p1;
} if_DLocation_par_type;

inline void if_DLocation_par_copy
    (if_DLocation_par_type& x, const if_DLocation_par_type y);
inline int if_DLocation_par_compare
    (const if_DLocation_par_type x, const if_DLocation_par_type y);
inline void if_DLocation_par_print
    (const if_DLocation_par_type x, FILE* f);
inline void if_DLocation_par_reset
    (if_DLocation_par_type& x);
#define if_DLocation_par_iterate(x)\
  if_Location_iterate(x.p1)
inline if_DLocation_par_type if_DLocation_par_make
    (if_Location_type p1);
#define if_DLocation_par_eq(x,y) if_DLocation_par_compare(x,y)==0
#define if_DLocation_par_ne(x,y) if_DLocation_par_compare(x,y)!=0

class if_DLocation_message : public IfMessage {

public:
  if_DLocation_message();
  if_DLocation_message(if_Location_type p1);
  if_DLocation_message(const if_DLocation_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_DLocation_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};



/*
 * RBC_to_OBU buffer interface
 *
 */

#define if_RBC_to_OBU_route 1

class if_RBC_to_OBU_buffer : public IfFifoBuffer {

public:
  if_RBC_to_OBU_buffer();
  if_RBC_to_OBU_buffer(const if_RBC_to_OBU_buffer&);

public:
  virtual IfInstance* copy() const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

};

/*
 * OBU_to_RBC buffer interface
 *
 */

#define if_OBU_to_RBC_route 2

class if_OBU_to_RBC_buffer : public IfFifoBuffer {

public:
  if_OBU_to_RBC_buffer();
  if_OBU_to_RBC_buffer(const if_OBU_to_RBC_buffer&);

public:
  virtual IfInstance* copy() const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

};






/* 
 * ETCS [system] instance interface 
 *
 */

class if_ETCS_instance : public IfInstance { 

  public:
    if_ETCS_instance(if_pid_type = 0, IfQueue* = IfQueue::NIL);
    if_ETCS_instance(const if_ETCS_instance&);

  protected:

};


/* 
 * OBU instance interface 
 *
 */
 
#define if_OBU_process 7



typedef if_void_type if_OBU_par_type;

#define if_OBU_par_copy(x,y) if_void_copy(x,y)
#define if_OBU_par_compare(x,y) if_void_compare(x,y)
#define if_OBU_par_print(x,f) if_void_print(x,f)
#define if_OBU_par_print_xml(x,b) if_void_print_xml(x,b)
#define if_OBU_par_reset(x) if_void_reset(x)
#define if_OBU_par_iterate(x) if_void_iterate(x)
#define if_OBU_par_eq(x,y) if_OBU_par_compare(x,y)==0
#define if_OBU_par_ne(x,y) if_OBU_par_compare(x,y)!=0


typedef struct {
  if_MovementAuthority_type m;
  if_Speed_type v;
  if_clock_type c0;
  if_clock_type c;
  if_Location_type l;
  if_pid_type rbc;
} if_OBU_var_type;

inline void if_OBU_var_copy
    (if_OBU_var_type& x, const if_OBU_var_type y);
inline int if_OBU_var_compare
    (const if_OBU_var_type x, const if_OBU_var_type y);
inline void if_OBU_var_print
    (const if_OBU_var_type x, FILE* f);
inline void if_OBU_var_reset
    (if_OBU_var_type& x);
#define if_OBU_var_iterate(x)\
  if_MovementAuthority_iterate(x.m)\
  if_Speed_iterate(x.v)\
  if_clock_iterate(x.c0)\
  if_clock_iterate(x.c)\
  if_Location_iterate(x.l)\
  if_pid_iterate(x.rbc)
inline if_OBU_var_type if_OBU_var_make
    (if_MovementAuthority_type m,if_Speed_type v,if_clock_type c0,if_clock_type c,if_Location_type l,if_pid_type rbc);
#define if_OBU_var_eq(x,y) if_OBU_var_compare(x,y)==0
#define if_OBU_var_ne(x,y) if_OBU_var_compare(x,y)!=0


typedef struct {
  if_integer_type top;
} if_OBU_ctl_type;

inline void if_OBU_ctl_copy
    (if_OBU_ctl_type& x, const if_OBU_ctl_type y);
inline int if_OBU_ctl_compare
    (const if_OBU_ctl_type x, const if_OBU_ctl_type y);
inline void if_OBU_ctl_print
    (const if_OBU_ctl_type x, FILE* f);
inline void if_OBU_ctl_reset
    (if_OBU_ctl_type& x);
#define if_OBU_ctl_iterate(x)\
  if_integer_iterate(x.top)
inline if_OBU_ctl_type if_OBU_ctl_make
    (if_integer_type top);
#define if_OBU_ctl_eq(x,y) if_OBU_ctl_compare(x,y)==0
#define if_OBU_ctl_ne(x,y) if_OBU_ctl_compare(x,y)!=0

class if_OBU_instance : public if_ETCS_instance {

public:
  
  if_OBU_instance();
  if_OBU_instance(const if_OBU_instance&);

  inline int GetSP() const { return m_ctl.top; }	// still used by observer operator "instate" -> only working without concurrent SMs

public:
  virtual const char* getState() const;
  virtual int is(const unsigned) const;

public:
  virtual int compare(const IfInstance*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfInstance* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public: 
  virtual void reset();
  virtual void iterate(IfIterator*);
  virtual void copy(const IfInstance*);

public:
  static const char* NAME;

public:
  
  inline if_MovementAuthority_type& m()
    { return m_var.m; }
  inline if_Speed_type& v()
    { return m_var.v; }
  inline if_clock_type& c0()
    { return m_var.c0; }
  inline if_clock_type& c()
    { return m_var.c; }
  inline if_Location_type& l()
    { return m_var.l; }
  inline if_pid_type& rbc()
    { return m_var.rbc; }
  

private: 
  if_OBU_par_type m_par;  /* parameters */ 
  if_OBU_var_type m_var;  /* variables */
  if_OBU_ctl_type m_ctl;  /* control */

private:  
  inline int input(unsigned signal) const {
    int ok = 0;
    if (m_ctl.top != -1)
      ok |= (STATE[m_ctl.top].sigtab[signal] & 1);
    return ok;
  }
  inline int save(unsigned signal) const {
    int ok = 0;
    if (m_ctl.top != -1) 
      ok |= (STATE[m_ctl.top].sigtab[signal] & 2);
    return ok;
  }

private:
         void fire();
//         void tpc();
         void dispatch(IfMessage*, int);
  inline void nextstate();

         void _top_dispatch(IfMessage*);

         void _init_dispatch(IfMessage*);

         void _init_1_fire(IfMessage*);
  inline void _init_1a_fire(IfMessage*);
  inline void _init_1b_fire();
  inline void _init_1c_fire();
  inline void _init_1d_fire();


         void _TEMP_dispatch(IfMessage*);

         void _TEMP_1_fire(IfMessage*);
  inline void _TEMP_1a_fire(IfMessage*);
  inline void _TEMP_1b_fire();
  inline void _TEMP_1c_fire();


         void _NORMAL_dispatch(IfMessage*);

         void _NORMAL_1_fire(IfMessage*);
  inline void _NORMAL_1a_fire();
  inline void _NORMAL_1b_fire();
  inline void _NORMAL_1c_fire();

         void _NORMAL_2_fire(IfMessage*);
  inline void _NORMAL_2a_fire();
  inline void _NORMAL_2b_fire();


         void _INDICATION_dispatch(IfMessage*);

         void _INDICATION_1_fire(IfMessage*);
  inline void _INDICATION_1a_fire(IfMessage*);
  inline void _INDICATION_1b_fire();
  inline void _INDICATION_1c_fire();

         void _INDICATION_2_fire(IfMessage*);
  inline void _INDICATION_2a_fire(IfMessage*);
  inline void _INDICATION_2b_fire();
  inline void _INDICATION_2c_fire();

         void _INDICATION_3_fire(IfMessage*);
  inline void _INDICATION_3a_fire(IfMessage*);
  inline void _INDICATION_3b_fire();
  inline void _INDICATION_3c_fire();
  inline void _INDICATION_3d_fire();


         void _INTERVENTION_dispatch(IfMessage*);

         void _INTERVENTION_1_fire(IfMessage*);
  inline void _INTERVENTION_1a_fire();
  inline void _INTERVENTION_1b_fire();
  inline void _INTERVENTION_1c_fire();

         void _INTERVENTION_2_fire(IfMessage*);
  inline void _INTERVENTION_2a_fire(IfMessage*);
  inline void _INTERVENTION_2b_fire();
  inline void _INTERVENTION_2c_fire();


private:
  typedef void (if_OBU_instance::*dispatcher)(IfMessage*);
//  typedef void (if_OBU_instance::*tpcchecker)();
  static if_state<15,dispatcher/*,tpcchecker*/> STATE[];


};



/* 
 * RBC instance interface 
 *
 */
 
#define if_RBC_process 8


typedef struct {
  if_pid_type obu;
} if_RBC_par_type;

inline void if_RBC_par_copy
    (if_RBC_par_type& x, const if_RBC_par_type y);
inline int if_RBC_par_compare
    (const if_RBC_par_type x, const if_RBC_par_type y);
inline void if_RBC_par_print
    (const if_RBC_par_type x, FILE* f);
inline void if_RBC_par_reset
    (if_RBC_par_type& x);
#define if_RBC_par_iterate(x)\
  if_pid_iterate(x.obu)
inline if_RBC_par_type if_RBC_par_make
    (if_pid_type obu);
#define if_RBC_par_eq(x,y) if_RBC_par_compare(x,y)==0
#define if_RBC_par_ne(x,y) if_RBC_par_compare(x,y)!=0


typedef struct {
  if_MovementAuthority_type m;
  if_Location_type x;
  if_Speed_type v;
  if_Location_type y;
  if_Distance_type d;
  if_clock_type c;
  if_clock_type c1;
} if_RBC_var_type;

inline void if_RBC_var_copy
    (if_RBC_var_type& x, const if_RBC_var_type y);
inline int if_RBC_var_compare
    (const if_RBC_var_type x, const if_RBC_var_type y);
inline void if_RBC_var_print
    (const if_RBC_var_type x, FILE* f);
inline void if_RBC_var_reset
    (if_RBC_var_type& x);
#define if_RBC_var_iterate(x)\
  if_MovementAuthority_iterate(x.m)\
  if_Location_iterate(x.x)\
  if_Speed_iterate(x.v)\
  if_Location_iterate(x.y)\
  if_Distance_iterate(x.d)\
  if_clock_iterate(x.c)\
  if_clock_iterate(x.c1)
inline if_RBC_var_type if_RBC_var_make
    (if_MovementAuthority_type m,if_Location_type x,if_Speed_type v,if_Location_type y,if_Distance_type d,if_clock_type c,if_clock_type c1);
#define if_RBC_var_eq(x,y) if_RBC_var_compare(x,y)==0
#define if_RBC_var_ne(x,y) if_RBC_var_compare(x,y)!=0


typedef struct {
  if_integer_type top;
} if_RBC_ctl_type;

inline void if_RBC_ctl_copy
    (if_RBC_ctl_type& x, const if_RBC_ctl_type y);
inline int if_RBC_ctl_compare
    (const if_RBC_ctl_type x, const if_RBC_ctl_type y);
inline void if_RBC_ctl_print
    (const if_RBC_ctl_type x, FILE* f);
inline void if_RBC_ctl_reset
    (if_RBC_ctl_type& x);
#define if_RBC_ctl_iterate(x)\
  if_integer_iterate(x.top)
inline if_RBC_ctl_type if_RBC_ctl_make
    (if_integer_type top);
#define if_RBC_ctl_eq(x,y) if_RBC_ctl_compare(x,y)==0
#define if_RBC_ctl_ne(x,y) if_RBC_ctl_compare(x,y)!=0

class if_RBC_instance : public if_ETCS_instance {

public:
  if_RBC_instance();
  if_RBC_instance(if_pid_type obu);
  if_RBC_instance(const if_RBC_instance&);

  inline int GetSP() const { return m_ctl.top; }	// still used by observer operator "instate" -> only working without concurrent SMs

public:
  virtual const char* getState() const;
  virtual int is(const unsigned) const;

public:
  virtual int compare(const IfInstance*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfInstance* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public: 
  virtual void reset();
  virtual void iterate(IfIterator*);
  virtual void copy(const IfInstance*);

public:
  static const char* NAME;

public:
  inline if_pid_type& obu()
    { return m_par.obu; }
  
  inline if_MovementAuthority_type& m()
    { return m_var.m; }
  inline if_Location_type& x()
    { return m_var.x; }
  inline if_Speed_type& v()
    { return m_var.v; }
  inline if_Location_type& y()
    { return m_var.y; }
  inline if_Distance_type& d()
    { return m_var.d; }
  inline if_clock_type& c()
    { return m_var.c; }
  inline if_clock_type& c1()
    { return m_var.c1; }
  

private: 
  if_RBC_par_type m_par;  /* parameters */ 
  if_RBC_var_type m_var;  /* variables */
  if_RBC_ctl_type m_ctl;  /* control */

private:  
  inline int input(unsigned signal) const {
    int ok = 0;
    if (m_ctl.top != -1)
      ok |= (STATE[m_ctl.top].sigtab[signal] & 1);
    return ok;
  }
  inline int save(unsigned signal) const {
    int ok = 0;
    if (m_ctl.top != -1) 
      ok |= (STATE[m_ctl.top].sigtab[signal] & 2);
    return ok;
  }

private:
         void fire();
//         void tpc();
         void dispatch(IfMessage*, int);
  inline void nextstate();


    if_Speed_type getReleaseSpeed(if_Distance_type d);

         void _top_dispatch(IfMessage*);

         void _init_dispatch(IfMessage*);

         void _init_1_fire(IfMessage*);
  inline void _init_1a_fire(IfMessage*);
  inline void _init_1b_fire();
  inline void _init_1c_fire();
  inline void _init_1d_fire();


         void _IDLE_dispatch(IfMessage*);

         void _IDLE_1_fire(IfMessage*);
  inline void _IDLE_1a_fire(IfMessage*);

  inline void _IDLE_1b_fire();

         void _IDLE_2_fire(IfMessage*);
  inline void _IDLE_2a_fire(IfMessage*);
  inline void _IDLE_2b_fire();
  inline void _IDLE_2c_fire();

         void _IDLE_3_fire(IfMessage*);

  inline void _IDLE_3a_fire();


         void _MA_dispatch(IfMessage*);

         void _MA_1_fire(IfMessage*);
  inline void _MA_1a_fire();
  inline void _MA_1b_fire();
  inline void _MA_1c_fire();
  inline void _MA_1d_fire();
  inline void _MA_1e_fire();


private:
  typedef void (if_RBC_instance::*dispatcher)(IfMessage*);
//  typedef void (if_RBC_instance::*tpcchecker)();
  static if_state<15,dispatcher/*,tpcchecker*/> STATE[];


};




