#include "PA6H.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

static PA6H_handler _handler;

#define UART_DELAY 10;

PA6H_result PA6H_init(	PA6H_handler handler,
						const char* UpdateRate,
						const char* FixPosUpRate,
						const char*	BaudRate)
{
	_handler=handler;
	if(PA6H_sendCommand(UpdateRate)==PA6H_Error)
		return PA6H_Error;
	if(PA6H_sendCommand(FixPosUpRate)==PA6H_Error)
		return PA6H_Error;
	if(PA6H_sendCommand(BaudRate)==PA6H_Error)
		return PA6H_Error;
	return PA6H_OK;
}

static PA6H_result PA6H_sendCommand(const char *Command)
{
	if(HAL_UART_Transmit_IT(&_handler.huart,(uint8_t*)Command,strlen(Command))==HAL_ERROR)
		return PA6H_Error;
	return PA6H_OK;
}

PA6H_result PA6H_getData(PA6H *DataStruct)
{
	if(HAL_UART_Receive_IT(&_handler.huart,(uint8_t*)DataStruct->NMEA_SENTENCE,strlen(DataStruct->NMEA_SENTENCE))==HAL_ERROR)
		return PA6H_Error;
	return PA6H_OK;
}

/*PA6H_result PA6H_setUpdateRate(PA6H_updateRate UR)
{
	return PA6H_sendCommand(UR);
}

PA6H_result PA6H_setPositionFixUpdateRate(const char* PUR)
{
	return PA6H_sendCommand(PUR);
}

PA6H_result PA6H_setBaud(const char* baud)
{
	return PA6H_sendCommand(baud);
}*/
