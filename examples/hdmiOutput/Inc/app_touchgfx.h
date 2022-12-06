#ifndef APP_TOUCHGFX_H
#define APP_TOUCHGFX_H
#ifdef __cplusplus
 extern "C" {
#endif


void MX_TouchGFX_PreOSInit(void);
void MX_TouchGFX_Init(void);
void MX_TouchGFX_Process(void);
void TouchGFX_Task(void *argument);



#ifdef __cplusplus
}
#endif
#endif
