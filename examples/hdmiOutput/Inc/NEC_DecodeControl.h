/*
 * NEC_DecodeControl.h
 *
 *  Created on: 28 de nov de 2020
 *      Author: Deived
 */

#ifndef INC_NEC_DECODECONTROL_H_
#define INC_NEC_DECODECONTROL_H_

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_CHM		162
#define KEY_CH		98
#define KEY_PLUS	226
#define KEY_PREV	34
#define KEY_NEXT	2
#define KEY_PLAY	194
#define KEY_VOLM	224
#define KEY_VOLP	168
#define KEY_EQ		144
#define KEY_0		104
#define KEY_100P	152
#define KEY_200P 	176
#define KEY_1		48
#define KEY_2		24
#define KEY_3		122
#define KEY_4		16
#define KEY_5		56
#define KEY_6		90
#define KEY_7		66
#define KEY_8		74
#define KEY_9		82

void ControlIR_IncCounter(void);

//uint8_t ControlIR_GETKeyCode(void);
//Boolean ControlIR_KeyPressed(void);

#ifdef __cplusplus
}
#endif

#endif
