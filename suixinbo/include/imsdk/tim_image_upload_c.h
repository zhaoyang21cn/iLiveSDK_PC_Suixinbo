#ifndef _TIM_IMAGE_UPLOAD_C_H_
#define _TIM_IMAGE_UPLOAD_C_H_

#include "tim_comm_c.h"
#include "tim_msg_c.h"



extern "C"
{
	typedef void (*CBSubmitImageOnSuccess) (TIMMsgImageElemHandle handle, void* data);
	typedef void (*CBSubmitImageError) (int code, const char* desc, void* data);

	typedef struct _TIMSubmitImageCB
	{
		CBSubmitImageOnSuccess OnSuccess;
		CBSubmitImageError	OnError;
		void*		data;
	}TIMSubmitImageCB;

	TIM_DECL int TIMSubmitUploadTask(const char* path, uint32_t path_len, TIMSubmitImageCB* cb);
	TIM_DECL int TIMGetUploadProgress(int tast_id);
	TIM_DECL void TIMCancleTask(int tast_id);
	TIM_DECL int TIMCompressPic(const char* src, const char* dst, int level);
};



#endif