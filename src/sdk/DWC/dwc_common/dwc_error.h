#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

typedef enum DWCError {

} DWCError;

typedef enum DWCErrorType {

} DWCErrorType;

u32 DWC_GetLastErrorEx(int* r3, int* r4);
void DWC_ClearError(void);
void DWCi_SetError(int r3, int r4);

#ifdef __cplusplus
}
#endif
