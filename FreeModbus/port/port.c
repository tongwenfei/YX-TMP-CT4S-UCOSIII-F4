 /*
  * FreeModbus Libary: LPC214X Port
  * Copyright (C) 2007 Tiago Prado Lone <tiago@maxwellbohr.com.br>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public
  * License along with this library; if not, write to the Free Software
  * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  *
  * File: $Id: port.c,v 1.1 2007/04/24 23:15:18 wolti Exp $
  */

/* ----------------------- System includes --------------------------------*/


/* ----------------------- Modbus includes ----------------------------------*/

#include "port.h"


#include "mb.h"
#include "mbport.h"
#include "global.h"

/* ----------------------- Variables ----------------------------------------*/


/* ----------------------- Start implementation -----------------------------*/
void
EnterCriticalSection(  )
{
	__ASM volatile("cpsid i");
}

void
ExitCriticalSection(  )
{
    __ASM volatile("cpsie i");
}





/******************************************************************************
                               定义Modbus相关参数
******************************************************************************/

USHORT usRegInputStart = REG_INPUT_START;
USHORT usRegInputBuf[REG_INPUT_NREGS];

USHORT usRegHoldingStart = REG_HOLDING_START;
USHORT usRegHoldingBuf[REG_HOLDING_NREGS];

USHORT usRegDutyStart = REG_DUTY_START;
USHORT usRegDutyBuf[REG_DUTY_NREGS];

USHORT usRegFlowStart = REG_FLOW_START;
USHORT usRegFlowBuf[REG_FLOW_NREGS];

USHORT usRegFlowSetStart = REG_FLOWSET_START;
USHORT usRegFlowSetBuf[REG_FLOWSET_NREGS];

USHORT usRegAd_VauleStart = REG_AD_VAULE_START;
USHORT usRegAd_VauleBuf[REG_AD_VAULE_NREGS];

USHORT usRegSample_State=REG_SAMPLE_STATE_START;

USHORT usReg_CalibrationStart = REG_CALIBRATION_START;
USHORT usReg_CalibrationBuf[REG_CALIBRATION_NREGS];
/**
  *****************************************************************************
  * @Name   : 操作输入寄存器
  *
  * @Brief  : 对应功能码0x04 -> eMBFuncReadInputRegister
  *
  * @Input  : *pucRegBuffer：数据缓冲区，响应主机用
  *           usAddress:     寄存器地址
  *           usNRegs:       操作寄存器个数
  *
  * @Output : none
  *
  * @Return : Modbus状态信息
  *****************************************************************************
**/
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int          iRegIndex = 0;
	
	//
	//判断地址合法性
	//
	if ((usAddress >= REG_INPUT_START) && (usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS))
	{
		iRegIndex = (int)(usAddress - usRegInputStart);
		while (usNRegs > 0)
		{
			*pucRegBuffer++ = (UCHAR)( usRegInputBuf[iRegIndex] >> 8);  //高8位字节
			*pucRegBuffer++ = (UCHAR)( usRegInputBuf[iRegIndex] & 0xFF); //低8位字节
			iRegIndex++;
			usNRegs--;
		}
	}
	else  //错误地址
	{
		eStatus = MB_ENOREG;
	}
	
	return eStatus;
}

/**
  *****************************************************************************
  * @Name   : 操作保持寄存器
  *
  * @Brief  : 对应功能码0x06 -> eMBFuncWriteHoldingRegister
  *                    0x16 -> eMBFuncWriteMultipleHoldingRegister
  *                    0x03 -> eMBFuncReadHoldingRegister
  *                    0x23 -> eMBFuncReadWriteMultipleHoldingRegister
  *
  * @Input  : *pucRegBuffer：数据缓冲区，响应主机用
  *           usAddress:     寄存器地址
  *           usNRegs:       操作寄存器个数
  *           eMode:         功能码
  *
  * @Output : none
  *
  * @Return : Modbus状态信息
  *****************************************************************************
**/
eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int          iRegIndex = 0;
	
	//
	//判断地址是否合法
	//
	if((usAddress >= REG_HOLDING_START) && ((usAddress + usNRegs) <= (REG_HOLDING_START + REG_HOLDING_NREGS)))
	{
		iRegIndex = (int)(usAddress - usRegHoldingStart);
		//
		//根据功能码进行操作
		//
		switch(eMode)
		{
			case MB_REG_READ:  //读保持寄存器
					while(usNRegs > 0)
					{
                                                usRegHoldingBuf[iRegIndex]=DEBUG_MODE[iRegIndex];
						*pucRegBuffer++ = (uint8_t)(usRegHoldingBuf[iRegIndex] >> 8);  //高8位字节
						*pucRegBuffer++ = (uint8_t)(usRegHoldingBuf[iRegIndex] & 0xFF); //低8位字节
						iRegIndex++;
						usNRegs--;
					}                            
					break;
					
			case MB_REG_WRITE:  //写保持寄存器
					while(usNRegs > 0)
					{
						usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;  //高8位字节
						usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;  //低8位字节
                                                DEBUG_MODE[iRegIndex]=(uint8_t)(usRegHoldingBuf[iRegIndex]&0xff);
						iRegIndex++;
						usNRegs--;
					}
					break;
		}
	}
        
        else if((usAddress >= REG_INPUT_START) && ((usAddress + usNRegs) <= (REG_INPUT_START + REG_INPUT_NREGS)))
        {
          iRegIndex = (int)(usAddress - usRegInputStart);
		//
		//根据功能码进行操作
		//
		switch(eMode)
		{
			case MB_REG_READ:  //读保持寄存器
					while(usNRegs > 0)
					{
						*pucRegBuffer++ = (uint8_t)(usRegInputBuf[iRegIndex] >> 8);  //高8位字节
						*pucRegBuffer++ = (uint8_t)(usRegInputBuf[iRegIndex] & 0xFF); //低8位字节
						iRegIndex++;
						usNRegs--;
					}                            
					break;
					
			case MB_REG_WRITE:  //写保持寄存器
					while(usNRegs > 0)
					{
						usRegInputBuf[iRegIndex] = *pucRegBuffer++ << 8;  //高8位字节
						usRegInputBuf[iRegIndex] |= *pucRegBuffer++;  //低8位字节
						iRegIndex++;
						usNRegs--;
					}
					break;
		}
        }
        else if((usAddress >= REG_DUTY_START) && ((usAddress + usNRegs) <= (REG_DUTY_START + REG_DUTY_NREGS)))
        {
          iRegIndex = (int)(usAddress - usRegDutyStart);
		//
		//根据功能码进行操作
		//
		switch(eMode)
		{
			case MB_REG_READ:  //读保持寄存器
					while(usNRegs > 0)
					{
                                          *pucRegBuffer++ = (uint8_t)(FlowPID_struct[iRegIndex].PWM_Vaule>>8);
                                          *pucRegBuffer++ = (uint8_t)(FlowPID_struct[iRegIndex].PWM_Vaule& 0xFF);
//						*pucRegBuffer++ = (uint8_t)(usRegDutyBuf[iRegIndex] >> 8);  //高8位字节
//						*pucRegBuffer++ = (uint8_t)(usRegDutyBuf[iRegIndex] & 0xFF); //低8位字节
						iRegIndex++;
						usNRegs--;
					}                            
					break;
					
			case MB_REG_WRITE:  //写保持寄存器
					while(usNRegs > 0)
					{
						if(DEBUG_MODE[iRegIndex]==2)
                                                {
                                                usRegDutyBuf[iRegIndex] = *pucRegBuffer++ << 8;  //高8位字节
						usRegDutyBuf[iRegIndex] |= *pucRegBuffer++;  //低8位字节
                                                if((usRegDutyBuf[iRegIndex]>0)&&(usRegDutyBuf[iRegIndex]<1000))
                                                {
                                                  FlowPID_struct[iRegIndex].PWM_Vaule=usRegDutyBuf[iRegIndex];
                                                }
                                                else if(usRegDutyBuf[iRegIndex]==0x8000)
                                                {
                                                  if(FlowPID_struct[iRegIndex].PWM_Vaule<999)FlowPID_struct[iRegIndex].PWM_Vaule++;
                                                }
                                                else if(usRegDutyBuf[iRegIndex]==0x4000)
                                                {
                                                  if(FlowPID_struct[iRegIndex].PWM_Vaule>0)FlowPID_struct[iRegIndex].PWM_Vaule--;
                                                }
                                                else if(usRegDutyBuf[iRegIndex]==0x8001)
                                                {
                                                  if(FlowPID_struct[iRegIndex].PWM_Vaule<989)FlowPID_struct[iRegIndex].PWM_Vaule+=10;
                                                }
                                                else if(usRegDutyBuf[iRegIndex]==0x4001)
                                                {
                                                  if(FlowPID_struct[iRegIndex].PWM_Vaule>9)FlowPID_struct[iRegIndex].PWM_Vaule-=10;
                                                }
                                                }
						iRegIndex++;
						usNRegs--;
					}
					break;
		}
        }
         else if((usAddress >= REG_FLOW_START) && ((usAddress + usNRegs) <= (REG_FLOW_START + REG_FLOW_NREGS)))
        {
          iRegIndex = (int)(usAddress - usRegFlowStart);
		//
		//根据功能码进行操作
		//
		switch(eMode)
		{
			case MB_REG_READ:  //读保持寄存器
					while(usNRegs > 0)
					{
                                          

                                          
						*pucRegBuffer++ = (uint8_t)(usRegFlowBuf[iRegIndex] >> 8);  //高8位字节
						*pucRegBuffer++ = (uint8_t)(usRegFlowBuf[iRegIndex] & 0xFF); //低8位字节
						iRegIndex++;
						usNRegs--;
					}                            
					break;
					
			case MB_REG_WRITE:  //写保持寄存器
					eStatus = MB_EINVAL;
					break;
		}
        }
        else if((usAddress >= REG_FLOWSET_START) && ((usAddress + usNRegs) <= (REG_FLOWSET_START + REG_FLOWSET_NREGS)))
        {
          iRegIndex = (int)(usAddress - usRegFlowSetStart);
          
		//
		//根据功能码进行操作
		//
		switch(eMode)
		{
			case MB_REG_READ:  //读保持寄存器
					while(usNRegs > 0)
					{
                                                                                
						*pucRegBuffer++ = (uint8_t)(usRegFlowSetBuf[iRegIndex] >> 8);  //高8位字节
						*pucRegBuffer++ = (uint8_t)(usRegFlowSetBuf[iRegIndex] & 0xFF); //低8位字节
						iRegIndex++;
						usNRegs--;
					}                            
					break;
					
			case MB_REG_WRITE:  //写保持寄存器
                                        
                                        {
                                          USHORT buff=0;
					while(usNRegs > 0)
					{
						buff=*pucRegBuffer++ << 8;
                                                buff|= *pucRegBuffer++;
                                                if(((buff%100)==0)&&(buff<=1000))
                                               {
                                                usRegFlowSetBuf[iRegIndex] = buff;  //高8位字节
						  //低8位字节
                                                FlowPID_struct[iRegIndex].SetPoint=(float)buff/1000.0;
						iRegIndex++;
						usNRegs--;
                                               }
                                               else 
                                               {
                                                 eStatus =MB_EIO;
                                                 return eStatus;
                                               }
					}
                                        }break;
					
		}
        }
         else if((usAddress >= REG_AD_VAULE_START) && ((usAddress + usNRegs) <= (REG_AD_VAULE_START + REG_AD_VAULE_NREGS)))
        {
          iRegIndex = (int)(usAddress - usRegAd_VauleStart);
		//
		//根据功能码进行操作
		//
		switch(eMode)
		{
			case MB_REG_READ:  //读保持寄存器
                                        FloatToUshort(FlowPID_struct[0].Value,&usRegAd_VauleBuf[0]);
                                        FloatToUshort(FlowPID_struct[1].Value,&usRegAd_VauleBuf[2]);
                                        FloatToUshort(FlowPID_struct[2].Value,&usRegAd_VauleBuf[4]);
                                        FloatToUshort(FlowPID_struct[3].Value,&usRegAd_VauleBuf[6]);
					while(usNRegs > 0)
					{                                       
						
                                                *pucRegBuffer++ = (uint8_t)(usRegAd_VauleBuf[iRegIndex] >> 8);  //高8位字节
						*pucRegBuffer++ = (uint8_t)(usRegAd_VauleBuf[iRegIndex] & 0xFF); //低8位字节
						iRegIndex++;
						usNRegs--;
					}                            
					break;
					
			case MB_REG_WRITE:  //写保持寄存器
					eStatus = MB_EINVAL;
					break;
		}
        }
          else if((usAddress >= REG_CALIBRATION_START) && ((usAddress + usNRegs) <= (REG_CALIBRATION_START + REG_CALIBRATION_NREGS)))
        {
          iRegIndex = (int)(usAddress - usReg_CalibrationStart);
		//
		//根据功能码进行操作
		//
		switch(eMode)
		{
			case MB_REG_READ:  //读保持寄存器
                                       
					while(usNRegs > 0)
					{                                       
						
                                                *pucRegBuffer++ = (uint8_t)(usReg_CalibrationBuf[iRegIndex] >> 8);  //高8位字节
						*pucRegBuffer++ = (uint8_t)(usReg_CalibrationBuf[iRegIndex] & 0xFF); //低8位字节
						iRegIndex++;
						usNRegs--;
					}                            
					break;
					
			case MB_REG_WRITE:  //写保持寄存器
					
                                        {
                                          while(usNRegs > 0)
                                          {
                                              usReg_CalibrationBuf[iRegIndex] = *pucRegBuffer++ << 8;  //高8位字节
                                              usReg_CalibrationBuf[iRegIndex] |= *pucRegBuffer++;  //低8位字节
						iRegIndex++;
						usNRegs--;
                                          }
                                          if((usReg_CalibrationBuf[28]==0x1111)||(usReg_CalibrationBuf[28]==0x2222)||(usReg_CalibrationBuf[28]==0x3333)||(usReg_CalibrationBuf[28]==0x4444))
                                          {
                                            Calibration_Ch=usReg_CalibrationBuf[28]&0x000f;
                                          }
                                         }
					break;
		}
        }
	else  //错误地址
	{
		eStatus = MB_ENOREG;
	}
	
	return eStatus;
}

/**
  *****************************************************************************
  * @Name   : 操作线圈
  *
  * @Brief  : 对应功能码0x01 -> eMBFuncReadCoils
  *                    0x05 -> eMBFuncWriteCoil
  *                    0x15 -> 写多个线圈 eMBFuncWriteMultipleCoils
  *
  * @Input  : *pucRegBuffer：数据缓冲区，响应主机用
  *           usAddress:     寄存器地址
  *           usNRegs:       操作寄存器个数
  *           eMode:         功能码
  *
  * @Output : none
  *
  * @Return : Modbus状态信息
  *****************************************************************************
**/
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int          iRegIndex = 0;
	
	//
	//判断地址合法性
	//
	if ((usAddress >= REG_HOLDING_START) && ((usAddress + usNCoils) <= (REG_HOLDING_START + REG_HOLDING_NREGS)))
	{
		iRegIndex = (int)(usAddress - usRegHoldingStart);
		//
		//根据功能码操作
		//
		switch (eMode)
		{
			case MB_REG_READ:  //读取操作
				while (usNCoils > 0)
				{
					*pucRegBuffer++ = (uint8_t)(usRegHoldingBuf[iRegIndex] >> 8);  //高8位字节
					*pucRegBuffer++ = (uint8_t)(usRegHoldingBuf[iRegIndex] & 0xFF);  //低8位字节
					iRegIndex++;
					usNCoils--;
				}
				break;
				
			case MB_REG_WRITE:  //写操作
				while (usNCoils > 0)
				{
					usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;  //高8位字节
					usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;  //低8位字节
					iRegIndex++;
					usNCoils--;
				}
				break;
		}
	}
	else  //错误地址
	{
		eStatus = MB_ENOREG;
	}
	
	return eStatus;
}

/**
  *****************************************************************************
  * @Name   : 操作离散寄存器
  *
  * @Brief  : 对应功能码0x02 -> eMBFuncReadDiscreteInputs
  *
  * @Input  : *pucRegBuffer：数据缓冲区，响应主机用
  *           usAddress:     寄存器地址
  *           usNRegs:       操作寄存器个数
  *
  * @Output : none
  *
  * @Return : Modbus状态信息
  *****************************************************************************
**/
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	pucRegBuffer = pucRegBuffer;
	
	return MB_ENOREG;
}
