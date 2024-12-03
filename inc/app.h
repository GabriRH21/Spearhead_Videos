#ifndef APP_H 
#define APP_H


#ifdef __cplusplus
extern "C" {
#endif

// This header works with sym.cpp which defines the Vanilla symbols
// This header will be split up as it becomes larger
#include <stdint.h>
#include <windows.h>
// ### Types ###


// ### Variables ###
typedef struct SmackStruct Smack;

// ### Functions ###

int OriginalCRTStartup(void);
//__stdcall DWORD OriginalSmackToBuffer(struct SmackStruct *Smack, uint32_t Unknown1, uint32_t Unknown2, uint32_t Stride,
                       uint32_t FrameHeightInPixels, BYTE *OutBuffer, uint32_t Flags);


#ifdef __cplusplus
};
#endif

#endif
