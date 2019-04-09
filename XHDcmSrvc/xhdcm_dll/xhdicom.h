#pragma once

#include "dcmtype.h"

typedef char * PCHAR;
typedef void * LPVOID;

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef XHDCM_EXPORTS
#define XHDICOM_API  __declspec(dllexport)
#else
#define XHDICOM_API __declspec(dllimport)
#endif

	XHDICOM_API void XHDCM_Test(void);

	XHDICOM_API void  XHDCM_StartLogger(const char * PropertiesFileName); //added in V3.0
    XHDICOM_API void  XHDCM_StopLogger(void); //added in V3.0

	XHDICOM_API void  XHDCM_GenerateStudyUID(PCHAR &uid);  //Generate Study Instance UID
	XHDICOM_API void  XHDCM_GenerateSeriesUID(PCHAR &uid); //Generate Series Instance UID
	XHDICOM_API void  XHDCM_GenerateSOPUID(PCHAR &uid);    //Generate SOP Instance UID
	XHDICOM_API void  XHDCM_GenerateOtherUID(PCHAR &uid);  //Generate Other UID //added in V2.1

	XHDICOM_API void  XHDCM_SaveRTImageIOD(TDcmRTImageIOD &RTImage, const char * DcmFileName);
	XHDICOM_API void  XHDCM_SaveRTPlanIOD(TDcmRTPlanIOD &RTPlan, const char * DcmFileName);
	XHDICOM_API void  XHDCM_SaveBrachyPlanIOD(TDcmBrachyPlanIOD &BrachyPlan, const char * DcmFileName); //added in V1.6
	XHDICOM_API void  XHDCM_SaveRTBeamsTreatRecordIOD(TDcmRTBeamsTreatRecordIOD &RTBeamsTreatRecord, const char * DcmFileName); //added in V1.3
	XHDICOM_API void  XHDCM_SaveCTImageIOD(TDcmCTImageIOD &CTImage, const char * DcmFileName); //added in V2.1
	XHDICOM_API void  XHDCM_SaveDXImageIOD(TDcmDXImageIOD &DXImage, const char * DcmFileName); //added in V3.0
	XHDICOM_API void  XHDCM_SaveWorklistIOD(TDcmModalityWorklist &Worklist, const char * DcmFileName); //added in V3.0

	//------------------------------------------------------------------------------
	//���º�������DICOM�����������������CDcmFileOperator

	//����DICOM����
	XHDICOM_API LPVOID  XHDCM_CreateDcmObject(const char * filename);
	XHDICOM_API LPVOID  XHDCM_CreateDcmRTImageObject(TDcmRTImageIOD &RTImage); //added in V1.8

	//��ȡDICOM��Ϣ
	XHDICOM_API TDcmInfoHeader *  XHDCM_GetDcmInfoHeader(LPVOID object);
	XHDICOM_API TDcmImageInfo  *  XHDCM_GetDcmImgInfo(LPVOID object);
	XHDICOM_API TDcmRTPlanInfo *  XHDCM_GetDcmRTPlanInfo(LPVOID object);
	XHDICOM_API TDcmRTImageInfo *  XHDCM_GetDcmRTImageInfo(LPVOID object); //added in V1.2
	XHDICOM_API TDcmRTDoseInfo *  XHDCM_GetDcmRTDoseInfo(LPVOID object); //added in V1.5
	XHDICOM_API TDcmBrachyPlanInfo *  XHDCM_GetDcmBrachyPlanInfo(LPVOID object); //added in V1.6 
	XHDICOM_API TDcmRTBeamsTreatRecordInfo *  XHDCM_GetDcmRTRecordInfo(LPVOID object); //added in V1.7
	XHDICOM_API TDcmDXImageInfo *  XHDCM_GetDcmDXImageInfo(LPVOID object); //added in V3.0
	XHDICOM_API TDcmModalityWorklistInfo *  XHDCM_GetDcmModalityWorklistInfo(LPVOID object); //added in V3.0

	XHDICOM_API HPALETTE  XHDCM_GetPalette(LPVOID object);

	XHDICOM_API unsigned char *  XHDCM_GetDibits(LPVOID object, unsigned long frame);
	XHDICOM_API unsigned char  *  XHDCM_GetDibitsEx(LPVOID object, unsigned long frame, unsigned short RectSize, unsigned char &AvgVal); //added in V1.8

	//����DICOM����
	XHDICOM_API bool  XHDCM_GetWindow(LPVOID object, double &center, double &width);
	XHDICOM_API bool  XHDCM_SetWindow(LPVOID object, double center, double width);
	XHDICOM_API bool  XHDCM_GetImgWindow(LPVOID object, double &center, double &width); //added in V1.8
	XHDICOM_API bool  XHDCM_SetHistogramWindow(LPVOID object); //added in V1.8
	XHDICOM_API bool  XHDCM_SetMinMaxWindow(LPVOID object); //added in V1.8
	XHDICOM_API bool  XHDCM_SetROIWindow(LPVOID object, unsigned long LeftPos, unsigned long TopPos, unsigned long width, unsigned long height, unsigned long frame); //added in V1.8

	//�޸�RT Image����
	XHDICOM_API bool  XHDCM_ModifyRIItem(LPVOID object, TModifiedRIItem item);
	XHDICOM_API bool  XHDCM_ModifyRTImage(LPVOID object, TUpdateRIItem &item); //added in V1.5.1
	XHDICOM_API bool  XHDCM_ModifyPixelData(LPVOID object, unsigned char * PixelData, unsigned long BytesOfPixelData); //added in V1.8

	//�޸�RT Plan��׼״̬
	XHDICOM_API bool  XHDCM_ModifyRTPlanApproval(LPVOID object, TDcmApproval &Approval); //added in V1.4

	//�޸�RT Plan��MLCҶƬλ��ֵ
	XHDICOM_API bool  XHDCM_ModifyRTPlanLeafPos(LPVOID object, TDcmRTPlanInfo * RTPlanInfo); //added in V1.5.1

	//�޸�RT Plan��FRACTION ����
	XHDICOM_API bool  XHDCM_ModifyRTPlanFraction(LPVOID object, TDcmRTFraction &RTFraction); //added in V1.7

	//�޸�RT Plan��General Plan����
	XHDICOM_API bool  XHDCM_ModifyRTGeneralPlan(LPVOID object, TDcmRTGeneralPlan &RTGeneralPlan); //added in V1.7

	//����ͼ��ָ����ʽ���ļ���
	//����:
	//format:  see dcmtype.h about its value ( only IMAGE_BMP and IMAGE_JPEG is supported now )
	//quality: used for JPEG image
	XHDICOM_API bool  XHDCM_SaveImgToFile(LPVOID object, const char * filename, unsigned long format, unsigned long quality);

	//����DICOM����DICOM�ļ���
	XHDICOM_API bool  XHDCM_SaveDcmObject(LPVOID object, const char * filename);

	//��ȡ�������ݴ�С���ֽ�����
	XHDICOM_API unsigned long  XHDCM_GetPixelDataSize(LPVOID object); //added in V1.6.1
	XHDICOM_API unsigned long  XHDCM_GetPixelDataSizeEx(LPVOID object, long bits); //added in V1.7.1
	//��ȡ��������
	XHDICOM_API bool  XHDCM_GetPixelData(LPVOID object, void* buffer, unsigned long size); //added in V1.6.1
	XHDICOM_API bool  XHDCM_GetPixelDataEx(LPVOID object, void* buffer, unsigned long size, long bits, unsigned long frame); //added in V1.7.1

	//ɾ��DICOM����
	XHDICOM_API bool  XHDCM_DeleteDcmObject(LPVOID object);

	//���Ϻ�������DICOM���������������CDcmFileOperator
	//------------------------------------------------------------------------------

#if defined(__cplusplus)
};
#endif
