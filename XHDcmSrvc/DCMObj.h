//读取解析DICOM文件
#ifndef _DCMOBJ_H_
#define _DCMOBJ_H_
#include <string>
#include <time.h>
#include "windows.h"
#include "xhdcm_dll\dcmnet.h"
#include "xhdcm_dll\dcmtype.h"
#include "xhdcm_dll\xhdicom.h"
using namespace std;
#define IMAGE_BMP  0x00010001
#define IMAGE_GIF  0x00010002
#define IMAGE_JPEG 0x00010003
#define IMAGE_PCX  0x00010004
#define IMAGE_PGM  0x00010005
#define IMAGE_PICT 0x00010006
#define IMAGE_PNG  0x00010007
#define IMAGE_PSD  0x00010008
#define IMAGE_TGA  0x00010009
#define IMAGE_TIFF 0x0001000A
#define IMAGE_WMF  0x0001000B
class TDcmObjManager
{
private: 
	string FDcmFileName;
	LPVOID  FDcmObject;
public:
	TDcmObjManager(string ADcmFileName);
	~TDcmObjManager();

	TDcmInfoHeader* GetDcmInfoHeader();
	TDcmImageInfo* GetDcmImageInfo();
	TDcmRTPlanInfo* GetDcmRTPlanInfo();
	TDcmRTImageInfo* GetDcmRTImageInfo();
	TDcmRTDoseInfo* GetDcmRTDoseInfo();

	HPALETTE GetPalette();
	unsigned char* GetDibits(unsigned int Frame);

	bool SetWindow(double Center, double Width);
	bool ModifyRIItem(TModifiedRIItem ARIItem);
	bool ModifyRTPlanApproval(TDcmApproval &Approval);
	bool ModifyRTPlanLeafPos(TDcmRTPlanInfo* RTPlanInfo);
	bool ModifyRTImage(TUpdateRIItem &ARIItem);

	bool SaveImgToBmpFile(string ABmpFileName);
	bool SaveDcmObject(string ADcmFileName);
};





#endif // !_DCMOBJ_J_





















