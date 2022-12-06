#include "app_touchgfx.h"


void touchgfx_init(void);
void touchgfx_components_init(void);
void touchgfx_taskEntry(void);


/**
 * PreOS Initialization function
 */
void MX_TouchGFX_PreOSInit(void)
{
}

/**
 * Initialize TouchGFX application
 */
void MX_TouchGFX_Init(void){
	// Calling forward to touchgfx_init in C++ domain
	touchgfx_init();
}

/**
 * TouchGFX application entry function
 */
void MX_TouchGFX_Process(void){
	// Calling forward to touchgfx_taskEntry in C++ domain
	touchgfx_taskEntry();
}

/**
 * TouchGFX application thread
 */
void TouchGFX_Task(void *argument){
	// Calling forward to touchgfx_taskEntry in C++ domain
	touchgfx_taskEntry();
}

