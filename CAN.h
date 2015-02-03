#pragma once


#include <pshpack8.h>

// CAN message structure
typedef struct _CAN_MSg
{
	SHORT length;
	ULONG 	id;
	SHORT 	flags;
	union
	{
		BYTE 		data[8];
		WORD		wData[4];
		DWORD		dwData[2];
		LONGLONG	lData;
	};
}CAN_MSG;

// Definitions to use for CAN_MSG flags 
#define MSG_RTR (1<<0)		// Remote Transmission Request flag
#define MSG_EXT (1<<1)		// Extended identifier format flag


/* Acceptance filter message structure */
typedef struct __CAN_MSG_FILTER
{
  BOOL mode  ;		// set to 0 for dual filter mode, or 1 for single
  BYTE code0 ;
  BYTE code1 ;
  BYTE code2 ;
  BYTE code3 ;
  BYTE mask0 ;
  BYTE mask1 ;
  BYTE mask2 ;
  BYTE mask3 ;
} CAN_MSG_FILTER, *PCAN_MSG_FILTER;

#define ENGINE_RID	0x00

#define IOCTL_CAN_SET_ACCEPTANCE_FILTER   	0x01
#define IOCTL_CAN_GET_ACCEPTANCE_FILTER  	0x02
#define IOCTL_CAN_SET_BAUDRATE            	0x03
#define IOCTL_CAN_GET_BAUDRATE            	0x04
#define IOCTL_RESET_CHIP                  	0x05
#define IOCTL_SEND_COMMAND                	0x06
#define IOCTL_CAN_GET_STATUS_REG          	0x07
#define IOCTL_CAN_CLEAR_QUEUE				0x08
#define IOCTL_CAN_GET_NUM_MSGS				0x09
#define IOCTL_GET_DRIVER_VERSION			0xA0 

// Masks to retrieve parts of the id
#define MASK_SOURCE_ADDRESS(v)  (BYTE)( (0x000000FF & v))
#define MASK_PGN(v)				(DWORD)((0x03FFFF00 & v) >> 8)
#define MASK_PRIORITY(v)		(BYTE)( (0x1C000000 & v ) >> 24)

#define MASK_ALL_ID(pgn, src, p) ((0x03FFFF00 & (pgn << 8)) | (0x1C000000 & (p << 26)) | (0x000000FF & src))

// Masks to parse PGN to its parts
#define MASK_DATA_PAGE(v)		(BYTE)((0x00010000 & v) >> 16)
#define MASK_PDU_FORMAT(v)		(BYTE)((0x0000FF00 & v) >> 8)
#define MASK_PDU_SPECIFIC(v)	(BYTE)((0x000000FF & v))

#define SET_SOURCE_ADDRESS(v)	(BYTE)( (0x000000FF & v))
#define SET_PGN(v)				(DWORD)((0x03FFFF00 & (v << 8))
#define SET_PRIORITY(v)			(BYTE)((0x1C000000 & v ) >> 24)

// Masks to parse PGN to its parts
#define SET_DATA_PAGE(v)		(BYTE)((0x00010000 & v) >> 16)
#define SET_PDU_FORMAT(v)		(BYTE)((0x0000FF00 & v) >> 8)
#define SET_PDU_SPECIFIC(v)	(BYTE)((0x000000FF & v))

// DTC Masks
#define SPN(v)	(DWORD)	((0xFFFFE000 & v) >> 12)
#define FMI(v)	(WORD)  ((0x00001F00 & v) >> 8)
#define CM(v)	(BYTE)  ((0x00000080 & v) >> 7)
#define OC(v)	(BYTE)   (0x0000007F & v)

#define	ADDRESS_UNASSIGNED			0xFE
#define ADDRESS_GLOBAL				0xFF
#define PRIORITY_DEFAULT			0x06

enum PGN
{
	CRUISE_CONTROL_VEH_SPD			= 65265,  //CCVS PF=254
	ENGINE_ELECRONIC_CONTROLLER1	= 61444,  //EEC1 PF=240 	
	ENGINE_ELECRONIC_CONTROLLER2	= 61443,  //EEC2 PF=240
	ENGINE_FLUID_LEVEL_PRESSURE1	= 65263,  //EFL/P1 PF=254
	INLET_EXHAUST_CONDITIONS1		= 65270,  //IC1 PF=254
	ENGINE_TEMPERATURE1				= 65262,  //ET1 PF=254
	FUEL_CONSUMPTION				= 65257,  //LFC PF=254
	FUEL_ECONOMY					= 65266,  //LFE PF=254
	TRIP_SHUTDOWN_INFO				= 65206,  // TVI PF=254
	TRIP_FUEL_INFORMATION			= 65208,  // GTFI
	IDLE_OPERATION					= 65244,  // IO
	FUEL_INFORMATION				= 65203,  // LFI PF=254
	VEHICLE_STABILITY_CONTROL2		= 61449,  // VDC2 PF=240
	VEHICLE_HOURS					= 65255,  // VH	(PTO hours)
	VEHICLE_DIRECTION				= 65256,  // VDS (Pitch)	
	ATC_ASR_INFORMATION				= 61441,
	VEHICLE_DISTANCE				= 65248,  // VD 
	ENGINE_HOURS					= 65253,  // HOURS	
	VEHICLE_ELECTRICAL_POWER1		= 65271,  // VEP1
	DASH_DISPLAY					= 65276,  // DD

	HIGH_RES_VEHICLE_DISTANCE		= 65217,  // FEC1       -- hino
	HIGH_RES_FUEL_CONSUMPTION		= 65393,  // FF71       -- hino


	// DTC's
	ACTIVE_DIAGNOSTIC_CODE			= 65226,  // DTC DM1
	PREVIOUS_DIAGNOSTIC_CODE		= 65227,  // DTC DM2
	CLEAR__PREVIOUS_DIAGNOSTIC_CODE	= 65228,  // DTC DM3
	PENDING_DIAGNOSTIC_CODE			= 65231,  // DTC DM6
	OXYGEN_SENSOR_DIAGNOSTIC_CODE	= 65233,  // DTC DM9
	CLEAR_ACTIVE_DIAGNOSTIC_CODE	= 65235,  // DTC DM11
	
	REQUEST_PGN						= 59904,	
	ACKNOWLEDGEMENT					= 59647,  // ACK/NACK
	ADDRESS_CLAIMED					= 60928,  
	ADDRESS_CLAIMED_GLOBAL			= 61183,
	REQUEST_ADDRESS_GLOBAL			= 60159,

	// These are not used as of now
	TRANSMISSION_FLUIDS				= 65272	  // TF
} ;

#include <poppack.h>

