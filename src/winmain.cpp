#include <windows.h>
#include <stdint.h>
#include "macros/patch.h"
#include "app.h"

CALL(0x005e1874, _callPixelError);
CALL(0x005e44d4, _callPixelError);
CALL(0x005e48da, _callPixelError);
CALL_NOP(0x005e1b08, _newSmackToBuffer);
CALL_NOP(0x005e2df5, _newSmackToBuffer);
CALL_NOP(0x005e30f5, _newSmackToBuffer);

HRESULT pixelFormat;
typedef struct SmackStruct Smack;

EXTERN_C __stdcall HRESULT callPixelError(HDC param_1) {
  pixelFormat = GetPixelFormat(param_1);
  return 0xC0000000;
}

using SmackToBufferDef = void (*)(SmackStruct *Smack, uint32_t Unknown1, uint32_t Unknown2, uint32_t Stride, uint32_t FrameHeightInPixels, BYTE *OutBuffer, uint32_t Flags);

EXTERN_C __stdcall void newSmackToBuffer(SmackStruct *Smack, uint32_t Unknown1, uint32_t Unknown2, uint32_t Stride,
                   uint32_t FrameHeightInPixels, BYTE *OutBuffer, uint32_t Flags){
  	SmackToBufferDef SmackToBuffer;
    SmackToBuffer = reinterpret_cast<SmackToBufferDef>(0x00a57ee8);
    SmackToBuffer(Smack, Unknown1, Unknown2, Stride, FrameHeightInPixels, OutBuffer, Flags);
    /*memset(OutBuffer, 0xFF, Stride * FrameHeightInPixels);
    auto *pixels = (uint32_t*)OutBuffer;
	pixels[0] = 0xFF0000FF;
	pixels[1] = 0x00FF00FF;
	pixels[2] = 0x0000FFFF;
	pixels[3] = 0xFF00FFFF;
	pixels[4] = 0xFFFF00FF;*/
}



int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    return OriginalCRTStartup();
}
