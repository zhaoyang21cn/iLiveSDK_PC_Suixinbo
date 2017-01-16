#ifndef _TIM_RELAY_C_H_
#define _TIM_RELAY_C_H_
#include "tim_comm_c.h"

extern "C"
{
		TIM_DECL void	TIMSendDataWithEncryption(const char* data, uint32_t data_len, TIMRequestCB *callback);
		TIM_DECL void	TIMSendDataWithOutEncryption(const char* data, uint32_t data_len, TIMRequestCB *callback);
}

#endif