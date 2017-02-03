// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2015.2
// Copyright (C) 2015 Xilinx Inc. All rights reserved.
// 
// ==============================================================

#ifndef XFOO_H
#define XFOO_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xfoo_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Bus_a_BaseAddress;
} XFoo_Config;
#endif

typedef struct {
    u32 Bus_a_BaseAddress;
    u32 IsReady;
} XFoo;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XFoo_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XFoo_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XFoo_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XFoo_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XFoo_Initialize(XFoo *InstancePtr, u16 DeviceId);
XFoo_Config* XFoo_LookupConfig(u16 DeviceId);
int XFoo_CfgInitialize(XFoo *InstancePtr, XFoo_Config *ConfigPtr);
#else
int XFoo_Initialize(XFoo *InstancePtr, const char* InstanceName);
int XFoo_Release(XFoo *InstancePtr);
#endif

void XFoo_Start(XFoo *InstancePtr);
u32 XFoo_IsDone(XFoo *InstancePtr);
u32 XFoo_IsIdle(XFoo *InstancePtr);
u32 XFoo_IsReady(XFoo *InstancePtr);
void XFoo_EnableAutoRestart(XFoo *InstancePtr);
void XFoo_DisableAutoRestart(XFoo *InstancePtr);

void XFoo_Set_byte_block_in_offset(XFoo *InstancePtr, u32 Data);
u32 XFoo_Get_byte_block_in_offset(XFoo *InstancePtr);
void XFoo_Set_byte_x_in_in_offset(XFoo *InstancePtr, u32 Data);
u32 XFoo_Get_byte_x_in_in_offset(XFoo *InstancePtr);
void XFoo_Set_byte_y_out_out_offset(XFoo *InstancePtr, u32 Data);
u32 XFoo_Get_byte_y_out_out_offset(XFoo *InstancePtr);

void XFoo_InterruptGlobalEnable(XFoo *InstancePtr);
void XFoo_InterruptGlobalDisable(XFoo *InstancePtr);
void XFoo_InterruptEnable(XFoo *InstancePtr, u32 Mask);
void XFoo_InterruptDisable(XFoo *InstancePtr, u32 Mask);
void XFoo_InterruptClear(XFoo *InstancePtr, u32 Mask);
u32 XFoo_InterruptGetEnabled(XFoo *InstancePtr);
u32 XFoo_InterruptGetStatus(XFoo *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif