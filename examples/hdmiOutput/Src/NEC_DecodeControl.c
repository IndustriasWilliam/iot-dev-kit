/*
 * NEC_DecodeControl.c
 *
 *  Created on: 28 de nov de 2020
 *      Author: Deived W.S Azevedo
 */




#include "NEC_DecodeControl.h"
#include "stdio.h"


//static uint32_t counterTimer = 0;
//static uint8_t irdata[33];   				//Used to record the time between two falling edges
//static Boolean receiveComplete = False; 	//Receive Complete Flag Bits
//static uint8_t idx;          				//Number received for indexing
//static Boolean startflag = False;       	//Indicates start of reception
//
//
//void ControlIR_IncCounter(void)
//{
//	counterTimer++;
//}
//
//void NEC_EXTI_Handler(void)
//{
//	if(startflag)
//	{
//		if(counterTimer < 150 && counterTimer >= 50 ) // Receive Sync Header
//		{
//			idx = 0;  								// Array subscript zeroing
//		}
//
//		irdata[idx] = counterTimer;  						// Get Count Time
//		counterTimer = 0;            					// Zero count time for next count
//		idx++;                     						// Received a data, index plus 1
//
//		if(idx == 33)       							// If you receive 33 bits of data, including 32 bits and with a sync header
//		{
//			idx = 0;
//			counterTimer = 0;
//			receiveComplete = True;
//			startflag = False;
//			printf("Key Code = %i\r\n", ControlIR_GETKeyCode());
//		}
//	}
//	else   // Drop Edge First Trigger
//	{
//		idx = 0;
//		counterTimer = 0;
//		startflag = True;
//	}
//}
//
//
//uint8_t ControlIR_GETKeyCode(void)
//{
//	uint8_t i, j, idx = 1; //idx starts with 1 to indicate that the synchronization header time is not handled
//	uint8_t temp;
//	uint8_t remote_code[4];
//
//	for(i = 0; i < 4; i++)
//	{
//		for(j = 0; j < 8; j++)
//		{
//			if(irdata[idx] >=8 && irdata[idx] < 15)   //Represents 0
//			{
//				temp = 0;
//			}
//			else if(irdata[idx] >=18 && irdata[idx]<25) //Represents 1
//			{
//				temp = 1;
//			}
//			remote_code[i] <<= 1;
//			remote_code[i] |= temp;
//			idx++;
//		}
//	}
//
//	receiveComplete = False;
//
//	return remote_code[2];  // The array records control codes, each key is different
//}
//
//Boolean ControlIR_KeyPressed(void)
//{
//	return receiveComplete;
//}
