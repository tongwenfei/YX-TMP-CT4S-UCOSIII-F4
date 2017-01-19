/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
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
 * File: $Id: port.h,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

#ifndef _PORT_H
#define _PORT_H

#include <assert.h>
#include <inttypes.h>
#include "usart.h"
#include "sys.h"

//#define	INLINE                      inline
#define PR_BEGIN_EXTERN_C           extern "C" {
#define	PR_END_EXTERN_C             }

#define ENTER_CRITICAL_SECTION( )   INTX_DISABLE()//__set_PRIMASK(1)  //关总中断
#define EXIT_CRITICAL_SECTION( )    INTX_ENABLE()//__set_PRIMASK(0)  //开总中断

typedef uint8_t BOOL;

typedef unsigned char UCHAR;
typedef char CHAR;

typedef uint16_t USHORT;
typedef int16_t SHORT;

typedef uint32_t ULONG;
typedef int32_t LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif


/******************************************************************************
                               定义Modbus相关参数
******************************************************************************/

#define REG_INPUT_START                          (USHORT)0x0001  //起始寄存器
#define REG_INPUT_NREGS                          (USHORT)4  //寄存器个数
#define REG_HOLDING_START                        (USHORT)0x0005  //保持寄存器
#define REG_HOLDING_NREGS                        (USHORT)4  //保持寄存器个数
#define REG_DUTY_START                           (USHORT)0x0009  //占空比寄存器
#define REG_DUTY_NREGS                           (USHORT)4  //占空比寄存器个数
#define REG_FLOW_START                           (USHORT)0x000D  //实时流量寄存器 （只读）
#define REG_FLOW_NREGS                           (USHORT)4  //实时流量寄存器个数
#define REG_FLOWSET_START                        (USHORT)0x0011  //设置流量保持寄存器
#define REG_FLOWSET_NREGS                        (USHORT)4  //设置流量寄存器个数
#define REG_AD_VAULE_START                       (USHORT)0x0015  //实时电压寄存器（只读）
#define REG_AD_VAULE_NREGS                       (USHORT)8  //实时电压寄存器个数

#define REG_SAMPLE_STATE_START                   (USHORT)0X1D
#define REG_SAMPLE_STATE_NREGS                   (USHORT)4
#define REG_CALIBRATION_START                    (USHORT)0X21
#define REG_CALIBRATION_NREGS                    (USHORT)29
/******************************************************************************
                               外部调用功能函数
******************************************************************************/

extern USHORT usRegInputBuf[REG_INPUT_NREGS];
extern USHORT usRegHoldingBuf[REG_HOLDING_NREGS];
extern USHORT usRegDutyBuf[REG_DUTY_NREGS];

extern USHORT usRegFlowBuf[REG_FLOW_NREGS];
extern USHORT usRegFlowSetBuf[REG_FLOWSET_NREGS];
extern USHORT usRegAd_VauleBuf[REG_AD_VAULE_NREGS];
extern USHORT usReg_CalibrationBuf[REG_CALIBRATION_NREGS];

#endif
