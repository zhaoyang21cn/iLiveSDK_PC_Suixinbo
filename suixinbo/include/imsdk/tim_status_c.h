#ifndef _TIM_SRATUS_C_H_
#define _TIM_SRATUS_C_H_

#include "tim_comm_c.h"

extern "C"
{
	typedef void* TIMUserStatusHandle;

	typedef void (*CBGetUserStatusCallbackOnSuccess) (TIMUserStatusHandle * handles, uint32_t num, void * data);
	typedef void (*CBGetUserStatusCallbackOnError) (int code, const char * desc, void * data);
	typedef struct _T_TIMGetUserStatusCallback
	{
		CBGetUserStatusCallbackOnSuccess OnSuccess;
		CBGetUserStatusCallbackOnError OnError;
		void * data;
	}TIMGetUserStatusCallback;

	typedef void(*CBStatusChange)(TIMUserStatusHandle * handle, void * data);
	typedef struct _TIMStatusChangeCallBack_c
	{
		CBStatusChange OnStatusChange;
		void* data;
	}TIMStatusChangeCB;

	TIM_DECL TIMUserStatusHandle CreateUserStatusHandle();
	TIM_DECL TIMUserStatusHandle CloneUserStatusHandle(TIMUserStatusHandle handle);
	TIM_DECL void DestroyUserStatusHandle(TIMUserStatusHandle handle);
	TIM_DECL int GetUserID4UserStatusHandle(TIMUserStatusHandle handle, char * id, uint32_t * len);
	TIM_DECL int GetUserDefined4UserStatusHandle(TIMUserStatusHandle handle, char * defined, uint32_t * len);


	TIM_DECL void TIMGetUserStatus(char** ids, uint32_t num, TIMGetUserStatusCallback * cb);
	TIM_DECL void TIMSetUserDefinedStatus(const char* data, uint32_t data_len, TIMCommCB* cb);
}


#endif