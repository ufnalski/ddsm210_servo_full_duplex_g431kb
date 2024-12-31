/*
 * ddsm210_servo.c
 *
 *  Created on: Dec 29, 2024
 *      Author: user
 */

#include "ddsm210_servo.h"

void DDSM_SetVelocity(uint8_t drive_id, float ddsm_velocity /* rpm */,
		uint8_t ddsm_acceleration_time /* in 0.1 ms per 1 rpm */,
		DDSM_BrakeTypeDef ddsm_brake)
{
	if (ddsm_velocity > 210)
	{
		ddsm_velocity = 210;
	}
	else if (ddsm_velocity < -210)
	{
		ddsm_velocity = -210;
	}
	else
	{
		__NOP();
	}

	Int16toUint8DecoderTypeDef int16_to_bytes;
	int16_to_bytes.int16 = (int16_t) (ddsm_velocity * 10);
	uint8_t tx_data[DDSM_MSG_LENGTH];
	tx_data[0] = drive_id;
	tx_data[1] = 0x64;
	tx_data[2] = int16_to_bytes.uint8[1];
	tx_data[3] = int16_to_bytes.uint8[0];
	tx_data[4] = 0;
	tx_data[5] = 0;
	tx_data[6] = ddsm_acceleration_time;
	tx_data[7] = ddsm_brake;
	tx_data[8] = 0;
	tx_data[9] = (uint8_t) HAL_CRC_Calculate(&hcrc, (uint32_t*) tx_data, 9);
	HAL_UART_Transmit_DMA(&huart1, tx_data, DDSM_MSG_LENGTH);
}

void DDSM_AskForMileage(uint8_t drive_id)
{
	uint8_t tx_data[DDSM_MSG_LENGTH];
	tx_data[0] = drive_id;
	tx_data[1] = 0x74;
	tx_data[2] = 0;
	tx_data[3] = 0;
	tx_data[4] = 0;
	tx_data[5] = 0;
	tx_data[6] = 0;
	tx_data[7] = 0;
	tx_data[8] = 0;
	tx_data[9] = (uint8_t) HAL_CRC_Calculate(&hcrc, (uint32_t*) tx_data, 9);
	HAL_UART_Transmit_DMA(&huart1, tx_data, DDSM_MSG_LENGTH);
}

DDSM_CrcStatusTypeDef DDSM_CheckCRC(uint8_t *ddsm_msg)
{
	if (HAL_CRC_Calculate(&hcrc, (uint32_t*) ddsm_msg, 9) == ddsm_msg[9])
	{
		return DDSM_CRC_OK;
	}
	else
	{
		return DDSM_CRC_ERROR;
	}
}

DDSM_MsgStatusTypeDef DDSM_MessageDecode(uint8_t drive_id, uint8_t *ddsm_msg,
		DDSM_ResponseTypeDef *ddsm_response)
{
	if (DDSM_CheckCRC(ddsm_msg) == DDSM_CRC_OK)
	{
		if (ddsm_msg[0] == drive_id)
		{
			if (ddsm_msg[1] == 0x64)
			{
				ddsm_response->temperature = ddsm_msg[7];
				ddsm_response->error_code = ddsm_msg[8];
				Int16toUint8DecoderTypeDef bytes_to_int16;
				bytes_to_int16.uint8[0] = ddsm_msg[3];
				bytes_to_int16.uint8[1] = ddsm_msg[2];
				ddsm_response->velocity = ((float) bytes_to_int16.int16) / 10;
				return DDSM_MSG_OK;
			}
			else if (ddsm_msg[1] == 0x74)
			{
				Int32toUint8DecoderTypeDef bytes_to_int32;
				bytes_to_int32.uint8[0] = ddsm_msg[5];
				bytes_to_int32.uint8[1] = ddsm_msg[4];
				bytes_to_int32.uint8[2] = ddsm_msg[3];
				bytes_to_int32.uint8[3] = ddsm_msg[2];
				ddsm_response->mileage = bytes_to_int32.int32;
				Uint16toUint8DecoderTypeDef bytes_to_uint16;
				bytes_to_uint16.uint8[0] = ddsm_msg[7];
				bytes_to_uint16.uint8[1] = ddsm_msg[6];
				ddsm_response->position = ((float) bytes_to_uint16.uint16)
						* (360.0f / 32767.0f);
				return DDSM_MSG_OK;
			}
			else
			{
				return DDSM_MSG_UNSUPPORTED;
			}
		}
		else
		{
			return DDSM_MSG_ID_ERROR;
		}
	}
	else
	{
		return DDSM_MSG_CRC_ERROR;
	}
}
