#include "stdafx.h"
#include "DCMObj.h"
TDcmObjManager::TDcmObjManager(string ADcmFileName)
{
	FDcmFileName = ADcmFileName;
	FDcmObject = XHDCM_CreateDcmObject(ADcmFileName.c_str());
}
TDcmObjManager::~TDcmObjManager()
{
	XHDCM_DeleteDcmObject(FDcmObject);
}
bool TDcmObjManager::IsDcmOpenSuccess()
{
	if (FDcmObject == NULL)
	{
		return false;
	}
	return true;
}
TDcmInfoHeader* TDcmObjManager::GetDcmInfoHeader()
{
	return XHDCM_GetDcmInfoHeader(FDcmObject);
}
TDcmImageInfo* TDcmObjManager::GetDcmImageInfo()
{
	return XHDCM_GetDcmImgInfo(FDcmObject);
}
TDcmRTPlanInfo* TDcmObjManager::GetDcmRTPlanInfo()
{
	return XHDCM_GetDcmRTPlanInfo(FDcmObject);
}
TDcmRTImageInfo* TDcmObjManager::GetDcmRTImageInfo()
{
	return XHDCM_GetDcmRTImageInfo(FDcmObject);
}
TDcmRTDoseInfo* TDcmObjManager::GetDcmRTDoseInfo()
{
	return XHDCM_GetDcmRTDoseInfo(FDcmObject);
}
HPALETTE TDcmObjManager::GetPalette()
{
	return XHDCM_GetPalette(FDcmObject);
}
unsigned char* TDcmObjManager::GetDibits(unsigned int Frame)
{
	return XHDCM_GetDibits(FDcmObject, Frame);
}
bool TDcmObjManager::SetWindow(double Center, double Width)
{
	return XHDCM_SetWindow(FDcmObject, Center, Width);
}
bool TDcmObjManager::ModifyRIItem(TModifiedRIItem ARIItem)
{
	return XHDCM_ModifyRIItem(FDcmObject, ARIItem);
}
bool TDcmObjManager::ModifyRTPlanApproval(TDcmApproval &Approval)
{
	return XHDCM_ModifyRTPlanApproval(FDcmObject, Approval);
}
bool TDcmObjManager::ModifyRTPlanLeafPos(TDcmRTPlanInfo* RTPlanInfo)
{
	return XHDCM_ModifyRTPlanLeafPos(FDcmObject, RTPlanInfo);
}
bool TDcmObjManager::ModifyRTImage(TUpdateRIItem &ARIItem)
{
	return XHDCM_ModifyRTImage(FDcmObject, ARIItem);
}
bool TDcmObjManager::SaveImgToBmpFile(string ABmpFileName)
{
	return XHDCM_SaveImgToFile(FDcmObject, ABmpFileName.c_str(), IMAGE_BMP, 0);
}
bool TDcmObjManager::SaveDcmObject(string ADcmFileName)
{
	return XHDCM_SaveDcmObject(FDcmObject, ADcmFileName.c_str());
}


