#pragma once

#define ANALYSIS_HRESULT(InValue) \
{\
	HRESULT handle=InValue;\
	if (FAILED(handle))\
	{\
		Engine_Log_Error("Error = %i",(int)handle);\
		assert(0);\
	}\
	else if (SUCCEEDED(handle))\
	{\
		Engine_Log_Success("Success !");\
	}\
}