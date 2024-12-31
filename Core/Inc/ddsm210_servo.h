/*
 * ddsm210_servo.h
 *
 *  Created on: Dec 29, 2024
 *      Author: user
 */

#ifndef INC_DDSM210_SERVO_H_
#define INC_DDSM210_SERVO_H_

#include "main.h"
#include "crc.h"
#include "usart.h"

#define DDSM_MSG_LENGTH 10

typedef enum
{
	DDSM_MSG_OK = 0x00U,
	DDSM_MSG_CRC_ERROR = 0x01U,
	DDSM_MSG_ID_ERROR = 0x02U,
	DDSM_MSG_UNSUPPORTED = 0x03U
} DDSM_MsgStatusTypeDef;

typedef enum
{
	DDSM_CRC_OK = 0x00U, DDSM_CRC_ERROR = 0x01U
} DDSM_CrcStatusTypeDef;

typedef enum
{
	DDSM_BRAKE_OFF = 0x00U, DDSM_BRAKE_ON = 0xFFU
} DDSM_BrakeTypeDef;

typedef union
{
	int16_t int16;
	uint8_t uint8[2];
} Int16toUint8DecoderTypeDef;

typedef union
{
	int32_t int32;
	uint8_t uint8[4];
} Int32toUint8DecoderTypeDef;

typedef union
{
	uint16_t uint16;
	uint8_t uint8[2];
} Uint16toUint8DecoderTypeDef;

typedef struct
{
	float velocity; // rpm
	float position;  // deg
	uint8_t temperature;
	uint8_t error_code;
	int32_t mileage; // laps
} DDSM_ResponseTypeDef;

void DDSM_SetVelocity(uint8_t drive_id, float ddsm_velocity /* rpm */,
		uint8_t ddsm_acceleration_time /* in 0.1 ms per 1 rpm */,
		DDSM_BrakeTypeDef ddsm_brake);
void DDSM_AskForMileage(uint8_t drive_id);
DDSM_CrcStatusTypeDef DDSM_CheckCRC(uint8_t *ddsm_msg);
DDSM_MsgStatusTypeDef DDSM_MessageDecode(uint8_t drive_id, uint8_t *ddsm_msg,
		DDSM_ResponseTypeDef *ddsm_response);

#endif /* INC_DDSM210_SERVO_H_ */
