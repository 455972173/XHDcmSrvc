#pragma once

//see PS3.5 6.2 about VR

//VR Length Const
#define VRAELen 16   //AE: Application Entity
#define VRASLen 4    //AS: Age String
#define VRCSLen 16   //CS: Code String
#define VRDALen 8    //DA: Date (format YYYYMMDD, example: 20100712)
#define VRDSLen 16   //DS: Decimal String
#define VRISLen 12   //IS: Integer String
#define VRLOLen 64   //LO: Long String
#define VRPNLen 64   //PN: Person Name
#define VRSHLen 16   //SH: Short String
#define VRUILen 64   //UI: Unique Identifier(UID)
//modified in V3.0 begin
//#define VRTMLen 16   //TM: Time (format hhmmss, example: 080100)
#define VRTMLen    14   //TM: Time (format HHMMSS.FFFFFF, example: 080100.000000)
#define VRQryDALen 18   //DA: Date in query (format YYYYMMDD-YYYYMMDD, example: 20100712-20100713)
#define VRQryTMLen 28   //TM: Time in query (format HHMMSS.FFFFFF, example: 080100.000000-160100.000000)
#define VRSTLen    1024 //ST: Short Text 
//modified in V3.0 end

//VR Types begin
typedef char TVRApplicationEntity[VRAELen + 1]; //AE
typedef char TVRAgeString[VRASLen + 1];         //AS
typedef char TVRCodeString[VRCSLen + 1];        //CS
typedef char TVRDate[VRDALen + 1];              //DA
typedef char TVRDecimalString[VRDSLen + 1];     //DS
typedef char TVRIntegerString[VRISLen + 1];     //IS
typedef char TVRLongString[VRLOLen + 1];        //LO
typedef char TVRPersonName[5][VRPNLen + 1];     //PN
typedef char TVRShortString[VRSHLen + 1];       //SH
typedef char TVRTime[VRTMLen + 1];              //TM
typedef char TVRUniqueIdentifier[VRUILen + 1];  //UI
//added in V3.0 begin
typedef char TVRQryDate[VRQryDALen + 1];        //DA: Date in query
typedef char TVRQryTime[VRQryTMLen + 1];        //TM: Time in query
typedef char TVRShortText[VRSTLen + 1];         //ST 
//added in V3.0 end
typedef long  TVRSignedLong;             //SL
typedef short TVRSignedShort;            //SS
typedef unsigned long  TVRUnsignedLong;  //UL
typedef unsigned short TVRUnsignedShort; //US
typedef float  TVRFloatingPointSingle;   //FL      
typedef double TVRFloatingPointDouble;   //FD      
//VR Types end

typedef char TFileName[253]; //added in V3.0
typedef char TErrorString[1024]; //added in V3.0

//moved here in V3.0 begin
//image file format code ( only IMAGE_BMP and IMAGE_JPEG is supported now)
#ifndef _IMAGEPRO_H  
#define IMAGE_BMP		0x00010001
#define IMAGE_GIF		0x00010002
#define IMAGE_JPEG	0x00010003
#define IMAGE_PCX		0x00010004
#define IMAGE_PGM		0x00010005
#define IMAGE_PICT	0x00010006
#define IMAGE_PNG		0x00010007
#define IMAGE_PSD		0x00010008
#define IMAGE_TGA		0x00010009
#define IMAGE_TIFF	0x0001000A
#define IMAGE_WMF		0x0001000B
#endif
//moved here in V3.0 end

#pragma pack(push, 1)   

//------------------------------------------------------------------------------
typedef TVRDecimalString T3DCoordinates[3]; //added in V1.6

//------------------------------------------------------------------------------
typedef struct {
  TVRUniqueIdentifier SOPClassUID;    //VR:UI Tag:(0008,0016) Type:1
  TVRUniqueIdentifier SOPInstanceUID; //VR:UI Tag:(0008,0018) Type:1
} TDcmSOPCommon; //PS3.3 C.12.1

typedef struct {
  TVRPersonName PatientsName;      //VR:PN Tag:(0010,0010) Type:2
  TVRLongString PatientID;         //VR:LO Tag:(0010,0020) Type:2
  TVRDate       PatientsBirthDate; //VR:DA Tag:(0010,0030) Type:2
  TVRCodeString PatientsSex;       //VR:CS Tag:(0010,0040) Type:2 //M|F|O
} TDcmPatient; //PS3.3 C.7.1.1

typedef struct {
  TVRUniqueIdentifier StudyInstanceUID;        //VR:UI Tag:(0020,000D) Type:1
  TVRDate             StudyDate;               //VR:DA Tag:(0008,0020) Type:2
  TVRTime             StudyTime;               //VR:TM Tag:(0008,0030) Type:2
  TVRPersonName       ReferringPhysiciansName; //VR:PN Tag:(0008,0090) Type:2
  TVRShortString      StudyID;                 //VR:SH Tag:(0020,0010) Type:2
  TVRShortString      AccessionNumber;         //VR:SH Tag:(0008,0050) Type:2
  TVRLongString       StudyDescription;        //VR:LO Tag:(0008,1030) Type:3
} TDcmGeneralStudy; //PS3.3 C.7.2.1

typedef struct {
  TVRCodeString       Modality;          //VR:CS Tag:(0008,0060) Type:1
  TVRUniqueIdentifier SeriesInstanceUID; //VR:UI Tag:(0020,000E) Type:1
  TVRIntegerString    SeriesNumber;      //VR:IS Tag:(0020,0011) Type:2
  TVRCodeString 	    Laterality;        //VR:CS Tag:(0020,0060) Type:2C
  TVRCodeString       PatientPosition;   //VR:CS Tag:(0018,5100) Type:2C
} TDcmGeneralSeries; //PS3.3 C.7.3.1  //added in V2.1

typedef struct {
  TVRUniqueIdentifier	FrameOfReferenceUID;        //VR:UI Tag:(0020,0052) Type:1
  TVRLongString	      PositionReferenceIndicator; //VR:LO Tag:(0020,1040) Type:2
} TDcmFrameOfReference; //PS3.3 C.7.4.1  added in V2.1

typedef struct {
  TVRCodeString       Modality;          //VR:CS Tag:(0008,0060) Type:1
  TVRUniqueIdentifier SeriesInstanceUID; //VR:UI Tag:(0020,000E) Type:1
  TVRIntegerString    SeriesNumber;      //VR:IS Tag:(0020,0011) Type:2
  TVRPersonName       OperatorsName;     //VR:PN Tag:(0008,1070) Type:2   //added in V2.0
} TDcmRTSeries; //PS3.3 C.8.8.1

typedef struct {
  TVRCodeString PresentationIntentType;  //VR:CS Tag:(0008,0068) Type:1
} TDcmDXSeries; //PS3.3 C.8.11.1  //added in V3.0

typedef struct {
  TVRCodeString ImageLaterality;         //VR:CS Tag:(0020,0062) Type:1
} TDcmDXAnatomyImaged; //PS3.3 C.8.11.2  //added in V3.0

typedef struct {
  TVRCodeString    PixelIntensityRelationship;     //VR:CS Tag:(0028,1040) Type:1
  TVRSignedShort   PixelIntensityRelationshipSign; //VR:SS Tag:(0028,1041) Type:1
  TVRDecimalString RescaleIntercept;               //VR:DS Tag:(0028,1052) Type:1
  TVRDecimalString RescaleSlope;                   //VR:DS Tag:(0028,1053) Type:1
  TVRLongString    RescaleType;                    //VR:LO Tag:(0028,1054) Type:1
  TVRCodeString    LossyImageCompression;          //VR:CS Tag:(0028,2110) Type:1
  TVRCodeString    BurnedInAnnotation;             //VR:CS Tag:(0028,0301) Type:1
  TVRCodeString    PresentationLUTShape;           //VR:CS Tag:(2050,0020) Type:1
} TDcmDXImage; //PS3.3 C.8.11.3  //added in V3.0

typedef struct {
  TVRDecimalString ImagerPixelSpacing[2]; //VR:DS Tag:(0018,1164) Type:1
  TVRCodeString    DetectorType;          //VR:CS Tag:(0018,7004) Type:2
} TDcmDXDetector; //PS3.3 C.8.11.4  //added in V3.0

typedef struct {
  TVRLongString Manufacturer;           //VR:LO Tag:(0008,0070) Type:2
  TVRLongString InstitutionName;        //VR:LO Tag:(0008,0080) Type:3
  TVRLongString ManufacturersModelName; //VR:LO Tag:(0008,1090) Type:3
  TVRLongString DeviceSerialNumber;     //VR:LO Tag:(0018,1000) Type:3
} TDcmGeneralEquipment; //PS3.3 C.7.5.1

typedef struct {
  TVRIntegerString InstanceNumber;     //VR:IS Tag:(0020,0013) Type:2
  TVRCodeString    PatientOrientation; //VR:CS Tag:(0020,0020) Type:2C
  TVRDate          ContentDate;        //VR:DA Tag:(0008,0023) Type:2C
  TVRTime          ContentTime;        //VR:TM Tag:(0008,0033) Type:2C
  TVRCodeString    ImageType[3];       //VR:CS Tag:(0008,0008) Type:3
} TDcmGeneralImage; //PS3.3 C.7.6.1

typedef struct {
  TVRDecimalString PixelSpacing[2];            //VR:DS Tag:(0028,0030) Type:1
  TVRDecimalString ImageOrientationPatient[6]; //VR:DS Tag:(0020,0037) Type:1
  TVRDecimalString ImagePositionPatient[3];    //VR:DS Tag:(0020,0032) Type:1
  TVRDecimalString SliceThickness;             //VR:DS Tag:(0018,0050) Type:2
} TDcmImagePlane; //PS3.3 C.7.6.2 added in V2.1

typedef struct {
  TVRUnsignedShort SamplesPerPixel;           //VR:US Tag:(0028,0002) Type:1
  TVRCodeString    PhotometricInterpretation; //VR:CS Tag:(0028,0004) Type:1
  TVRUnsignedShort Rows;                      //VR:US Tag:(0028,0010) Type:1
  TVRUnsignedShort Columns;                   //VR:US Tag:(0028,0011) Type:1
  TVRUnsignedShort BitsAllocated;             //VR:US Tag:(0028,0100) Type:1
  TVRUnsignedShort BitsStored;                //VR:US Tag:(0028,0101) Type:1
  TVRUnsignedShort HighBit;                   //VR:US Tag:(0028,0102) Type:1
  TVRUnsignedShort PixelRepresentation;       //VR:US Tag:(0028,0103) Type:1
  TVRIntegerString PixelAspectRatio[2];       //VR:IS Tag:(0028,0034) Type:1C
  unsigned long    BytesOfPixelData;
  unsigned char *  PixelData;
} TDcmImagePixel; //PS3.3 C.7.6.3

typedef struct {
  //以下成员已存在于前面其它record中
  //TVRUnsignedShort SamplesPerPixel;
  //TVRCodeString        PhotometricInterpretation;
  //TVRUnsignedShort     BitsAllocated;
  //TVRUnsignedShort     BitsStored;
  //TVRUnsignedShort     HighBit;
  //TVRCodeString        ImageType[3];
  //以上成员已存在于前面其它record中
  TVRDecimalString       RescaleIntercept;       //VR:DS Tag:(0028,1052) Type:1
  TVRDecimalString       RescaleSlope;           //VR:DS Tag:(0028,1053) Type:1
  TVRDecimalString       KVP;                    //VR:DS Tag:(0018,0060) Type:2
  TVRIntegerString       AcquisitionNumber;      //VR:IS Tag:(0020,0012) Type:2
  TVRCodeString          ScanOptions;            //VR:CS Tag:(0018,0022) Type:3
  TVRDecimalString       DataCollectionDiameter; //VR:DS Tag:(0018,0090) Type:3
  TVRDecimalString       TableHeight;            //VR:DS Tag:(0018,1130) Type:3
  TVRCodeString          RotationDirection;      //VR:CS Tag:(0018,1140) Type:3
  TVRIntegerString       ExposureTime;           //VR:IS Tag:(0018,1150) Type:3
  TVRIntegerString       XRayTubeCurrent;        //VR:IS Tag:(0018,1151) Type:3
  TVRShortString         FilterType;             //VR:SH Tag:(0018,1160) Type:3
  TVRIntegerString       GeneratorPower;         //VR:IS Tag:(0018,1170) Type:3
  TVRDecimalString       FocalSpots;             //VR:DS Tag:(0018,1190) Type:3
  TVRShortString         ConvolutionKernel;      //VR:SH Tag:(0018,1210) Type:3
  TVRFloatingPointDouble TotalCollimationWidth;  //VR:FD Tag:(0018,9307) Type:3
  TVRFloatingPointDouble SpiralPitchFactor;      //VR:FD Tag:(0018,9311) Type:3
}TDcmCTImage; //PS3.3 C.8.2.1  //added in V2.1

typedef struct {
  TVRDecimalString WindowCenter; //VR:DS Tag:(0028,1050) Type:3
  TVRDecimalString WindowWidth;  //VR:DS Tag:(0028,1051) Type:1C
} TDcmVOILUT; //PS3.3 C.11.2

typedef struct {
  TVRCodeString    RTBeamLimitingDeviceType;   //VR:CS Tag:(300A,00B8) Type:1
  TVRIntegerString NumberOfLeafJawPairs;       //VR:IS Tag:(300A,00BC) Type:1
  TVRDecimalString SourceToThisDeviceDistance; //VR:DS Tag:(300A,00BA) Type:3
  TVRDecimalString *LeafJawPositions;          //VR:DS Tag:(300A,011C) Type:1C
  TVRDecimalString *LeafPositionBoundaries;    //VR:DS Tag:(300A,00BE) Type:2C
} TBeamLimitDevice; //PS3.3 C.8.8.2, C.8.8.14, C.8.8.21

typedef struct {
  const char * RTBeamLimitingDeviceType;
  const char * NumberOfLeafJawPairs;
  const char * SourceToThisDeviceDistance;
  const char * LeafJawPositions;
  const char * LeafPositionBoundaries;
} TBeamLimitDeviceR;

//-------------------------------------------------------------------
typedef struct {
  TVRDecimalString KVP;                   //VR:DS Tag:(0018,0060) Type:2C
  TVRIntegerString ExposureTime;          //VR:IS Tag:(0018,1150) Type:2C
  TVRIntegerString XRayTubeCurrent;       //VR:IS Tag:(0018,1151) Type:2C
  TVRDecimalString DiaphragmPosition[4];  //VR:DS Tag:(3002,0034) Type:3
  TVRIntegerString NumberOfBlocks;        //VR:IS Tag:(300A,00F0) Type:1C //set to 0
  unsigned char    NumOfBeamLimitDevices;
  TBeamLimitDevice BeamLimitDevices[2];
} TExposureItem; //PS3.3 C.8.8.2

typedef struct {
  //以下成员已存在于前面其它record中
  //TVRUnsignedShort SamplesPerPixel;
  //TVRCodeString    PhotometricInterpretation;
  //TVRUnsignedShort BitsAllocated;
  //TVRUnsignedShort BitsStored;
  //TVRUnsignedShort HighBit;
  //TVRUnsignedShort PixelRepresentation;
  //TVRCodeString    ImageType[3];
  //以上成员已存在于前面其它record中
  TVRShortString   RTImageLabel;                  //VR:SH Tag:(3002,0002) Type:1
  TVRCodeString    ConversionType;                //VR:CS Tag:(0008,0064) Type:2
  TVRCodeString    ReportedValuesOrigin;          //VR:CS Tag:(3002,000A) Type:2C
  TVRCodeString    RTImagePlane;                  //VR:CS Tag:(3002,000C) Type:1
  TVRDecimalString XRayImageReceptorAngle;        //VR:DS Tag:(3002,000E) Type:2
  TVRDecimalString ImagePlanePixelSpacing[2];     //VR:DS Tag:(3002,0011) Type:2
  TVRDecimalString RTImagePosition[2];            //VR:DS Tag:(3002,0012) Type:2
  TVRShortString   RadiationMachineName;          //VR:SH Tag:(3002,0020) Type:2
  TVRCodeString    PrimaryDosimeterUnit;          //VR:CS Tag:(300A,00B3) Type:2
  TVRDecimalString RadiationMachineSAD;           //VR:DS Tag:(3002,0022) Type:2
  TVRDecimalString RadiationMachineSSD;           //VR:DS Tag:(3002,0024) Type:3 //added in V1.2
  TVRDecimalString RTImageSID;                    //VR:DS Tag:(3002,0026) Type:2
  TVRDecimalString SourceToReferObjectDistance;   //VR:DS Tag:(3002,0028) Type:3 //added in V1.2
  TVRDecimalString GantryAngle;                   //VR:DS Tag:(300A,011E) Type:3
  TVRDecimalString BeamLimitingDeviceAngle;       //VR:DS Tag:(300A,0120) Type:3
  TVRDecimalString PatientSupportAngle;           //VR:DS Tag:(300A,0122) Type:3
  TVRDecimalString TableTopEccentricAxisDistance; //VR:DS Tag:(300A,0124) Type:3
  TVRDecimalString TableTopEccentricAngle;        //VR:DS Tag:(300A,0125) Type:3
  TVRDecimalString TableTopVerticalPosition;      //VR:DS Tag:(300A,0128) Type:3
  TVRDecimalString TableTopLongitudinalPosition;  //VR:DS Tag:(300A,0129) Type:3
  TVRDecimalString TableTopLateralPosition;       //VR:DS Tag:(300A,012A) Type:3
  TExposureItem    ExposureItem;
} TDcmRTImage; //PS3.3 C.8.8.2

typedef struct {
  TVRShortString RTPlanLabel;    //VR:SH Tag:(300A,0002) Type:1
  TVRDate        RTPlanDate;     //VR:DA Tag:(300A,0006) Type:2
  TVRTime        RTPlanTime;     //VR:TM Tag:(300A,0007) Type:2
  TVRCodeString  RTPlanGeometry; //VR:CS Tag:(300A,000C) Type:1 //set to TREATMENT_DEVICE
  TDcmSOPCommon  ReferStructSet;
} TDcmRTGeneralPlan; //PS3.3 C.8.8.9

//-------------------------------------------------------------------
typedef struct {
  TVRIntegerString WedgeNumber;               //VR:IS Tag:(300A,00D2) Type:1C
  TVRCodeString    WedgeType;                 //VR:CS Tag:(300A,00D3) Type:2C
  TVRShortString   WedgeID;                   //VR:SH Tag:(300A,00D4) Type:3 //added in V1.3
  TVRIntegerString WedgeAngle;                //VR:IS Tag:(300A,00D5) Type:2C
  TVRDecimalString WedgeFactor;               //VR:DS Tag:(300A,00D6) Type:2C //added in V1.3 
  TVRDecimalString WedgeOrientation;          //VR:DS Tag:(300A,00D8) Type:2C
  TVRDecimalString SourceToWedgeTrayDistance; //VR:DS Tag:(300A,00DA) Type:3 //added in V1.3 
} TWedge; //PS3.3 C.8.8.14

typedef struct {
  const char * WedgeNumber;
  const char * WedgeType;
  const char * WedgeID; //added in V1.3
  const char * WedgeAngle;
  const char * WedgeFactor; //added in V1.3 
  const char * WedgeOrientation;
  const char * SourceToWedgeTrayDistance; //added in V1.3 
} TWedgeR;

typedef struct {
  TVRCodeString    BlockType;                 //VR:CS Tag:(300A,00F8) Type:1C
  TVRIntegerString BlockNumber;               //VR:IS Tag:(300A,00FC) Type:1C
  TVRLongString    BlockName;                 //VR:LO Tag:(300A,00FE) Type:3  //added in V1.3
  //added in V1.5 begin
  TVRShortString   BlockTrayID;               //VR:SH Tag:(300A,00F5) Type:3
  TVRDecimalString SourceToBlockTrayDistance; //VR:DS Tag:(300A,00F6) Type:2C 
  TVRCodeString    BlockDivergence;           //VR:CS Tag:(300A,00FA) Type:2C
  TVRShortString   MaterialID;                //VR:SH Tag:(300A,00E1) Type:2C
  TVRDecimalString BlockThickness;            //VR:DS Tag:(300A,0100) Type:2C
  TVRDecimalString BlockTransmission;         //VR:DS Tag:(300A,0102) Type:2C
  TVRIntegerString BlockNumberOfPoints;       //VR:IS Tag:(300A,0104) Type:2C
  TVRDecimalString *BlockData;                //VR:DS Tag:(300A,0106) Type:2C
  //added in V1.5 end
} TBlock; //PS3.3 C.8.8.14

typedef struct {
  const char * BlockType;
  const char * BlockNumber;
  const char * BlockName; //added in V1.3
  //added in V1.5 begin
  const char * BlockTrayID;
  const char * SourceToBlockTrayDistance;
  const char * BlockDivergence;
  const char * MaterialID;
  const char * BlockThickness;
  const char * BlockTransmission;
  const char * BlockNumberOfPoints;
  const char * BlockData;
  //added in V1.5 end
} TBlockR;

typedef struct {
  TVRShortString ApplicatorID;          //VR:SH Tag:(300A,0108) Type:1C
  TVRCodeString  ApplicatorType;        //VR:CS Tag:(300A,0109) Type:1C
  TVRLongString  ApplicatorDescription; //VR:LO Tag:(300A,010A) Type:3
} TApplicator; //PS3.3 C.8.8.14 //added in V1.8        

typedef struct {
  const char * ApplicatorID;
  const char * ApplicatorType;
  const char * ApplicatorDescription;
} TApplicatorR; //added in V1.8       

//-------------------------------------------------------------------
typedef struct {
  TVRIntegerString  ControlPointIndex;                  //VR:IS Tag:(300A,0112) Type:1C
  TVRDecimalString  NominalBeamEnergy;                  //VR:DS Tag:(300A,0114) Type:3  //added in V1.2
  TVRDecimalString  DoseRateSet;                        //VR:DS Tag:(300A,0115) Type:3  //added in V1.5
  TVRDecimalString  CumulativeMetersetWeight;           //VR:DS Tag:(300A,0134) Type:2C
  TVRDecimalString  GantryAngle;                        //VR:DS Tag:(300A,011E) Type:1C
  TVRCodeString     GantryRotationDirection;            //VR:CS Tag:(300A,011F) Type:1C
  TVRDecimalString  BeamLimitDeviceAngle;               //VR:DS Tag:(300A,0120) Type:1C
  TVRCodeString     BeamLimitDeviceRotationDirection;   //VR:CS Tag:(300A,0121) Type:1C
  TVRDecimalString  PatientSupportAngle;                //VR:DS Tag:(300A,0122) Type:1C
  TVRCodeString     PatientSupportRotationDirection;    //VR:CS Tag:(300A,0123) Type:1C
  TVRDecimalString  TabletopEccentricAngle;             //VR:DS Tag:(300A,0125) Type:1C
  TVRCodeString     TabletopEccentricRotationDirection; //VR:CS Tag:(300A,0126) Type:1C
  TVRDecimalString  TabletopVertPosition;               //VR:DS Tag:(300A,0128) Type:2C
  TVRDecimalString  TabletopLongPosition;               //VR:DS Tag:(300A,0129) Type:2C
  TVRDecimalString  TabletopLatPosition;                //VR:DS Tag:(300A,012A) Type:2C
  T3DCoordinates    IsocenterPosition;                  //VR:DS Tag:(300A,012C) Type:2C //added in V1.6
  TVRDecimalString  SourceToSurfaceDistance;            //VR:DS Tag:(300A,0130) Type:3  //added in V1.2
  //added in V2.0 begin
  TVRFloatingPointSingle TableTopPitchAngle;             //VR:FL Tag:(300A,0140) Type:1C
  TVRCodeString          TableTopPitchRotationDirection; //VR:CS Tag:(300A,0142) Type:1C
  TVRFloatingPointSingle TableTopRollAngle;              //VR:FL Tag:(300A,0144) Type:1C
  TVRCodeString          TableTopRollRotationDirection;  //VR:CS Tag:(300A,0146) Type:1C
  //added in V2.0 end 
  unsigned char     NumOfBeamLimitDevices;
  TBeamLimitDevice* BeamLimitDevicePositions;
} TControlPoint; //PS3.3 C.8.8.14

typedef struct {
  const char *       ControlPointIndex;
  const char *       NominalBeamEnergy; //added in V1.2
  const char *       DoseRateSet; //added in V1.5
  const char *       CumulativeMetersetWeight;
  const char *       GantryAngle;
  const char *       GantryRotationDirection;
  const char *       BeamLimitDeviceAngle;
  const char *       BeamLimitDeviceRotationDirection;
  const char *       PatientSupportAngle;
  const char *       PatientSupportRotationDirection;
  const char *       TabletopEccentricAngle;
  const char *       TabletopEccentricRotationDirection;
  const char *       TabletopVertPosition;
  const char *       TabletopLongPosition;
  const char *       TabletopLatPosition;
  const char *       IsocenterPosition; //added in V1.6
  const char *       SourceToSurfaceDistance; //added in V1.2
  //added in V2.0 begin
  const char *       TableTopPitchAngle;
  const char *       TableTopPitchRotationDirection;
  const char *       TableTopRollAngle;
  const char *       TableTopRollRotationDirection;
  //added in V2.0 end 
  unsigned char      NumOfBeamLimitDevices;
  TBeamLimitDeviceR* BeamLimitDevicePositions;
} TControlPointR;

//-------------------------------------------------------------------
typedef struct {
  TVRCodeString  FixationDeviceType;     //VR:CS Tag:(300A,0192) Type:1C
  TVRShortString FixationDeviceLabel;    //VR:SH Tag:(300A,0194) Type:2C
  TVRShortString FixationDevicePosition; //VR:SH Tag:(300A,0198) Type:3
} TFixationDevice; //PS3.3 C.8.8.12 //added in V1.4 

typedef struct {
  const char * FixationDeviceType;
  const char * FixationDeviceLabel;
  const char * FixationDevicePosition;
} TFixationDeviceR; //added in V1.4

typedef struct {
  TVRCodeString  ShieldingDeviceType;     //VR:CS Tag:(300A,01A2) Type:1C
  TVRShortString ShieldingDeviceLabel;    //VR:SH Tag:(300A,01A4) Type:2C
  TVRShortString ShieldingDevicePosition; //VR:SH Tag:(300A,01A8) Type:3
} TShieldingDevice; //PS3.3 C.8.8.12 //added in V1.4

typedef struct {
  const char * ShieldingDeviceType;
  const char * ShieldingDeviceLabel;
  const char * ShieldingDevicePosition;
} TShieldingDeviceR; //added in V1.4

typedef struct {
  TVRCodeString    SetupDeviceType;      //VR:CS Tag:(300A,01B6) Type:1C
  TVRShortString   SetupDeviceLabel;     //VR:SH Tag:(300A,01B8) Type:2C
  TVRDecimalString SetupDeviceParameter; //VR:DS Tag:(300A,01BC) Type:2C
} TSetupDevice; //PS3.3 C.8.8.12 //added in V1.4

typedef struct {
  const char * SetupDeviceType;
  const char * SetupDeviceLabel;
  const char * SetupDeviceParameter;
} TSetupDeviceR; //added in V1.4

typedef struct {
  TVRIntegerString  PatientSetupNumber; //VR:IS Tag:(300A,0182) Type:1
  TVRCodeString     PatientPosition;    //VR:CS Tag:(0018,5100) Type:1C
  TVRCodeString     SetupTechnique;     //VR:CS Tag:(300A,01B0) Type:3
  unsigned char     NumOfFixationDevices;
  unsigned char     NumOfShieldingDevices;
  unsigned char     NumOfSetupDevices;
  TFixationDevice*  FixationDevices;
  TShieldingDevice* ShieldingDevices;
  TSetupDevice*     SetupDevices;
} TDcmRTPatientSetup; //PS3.3 C.8.8.12 //added in V1.4

typedef struct {
  const char *       PatientSetupNumber;
  const char *       PatientPosition;
  const char *       SetupTechnique;
  unsigned char      NumOfFixationDevices;
  unsigned char      NumOfShieldingDevices;
  unsigned char      NumOfSetupDevices;
  TFixationDeviceR*  FixationDevices;
  TShieldingDeviceR* ShieldingDevices;
  TSetupDeviceR*     SetupDevices;
} TDcmRTPatientSetupR; //added in V1.4

//-------------------------------------------------------------------
typedef struct {
  TVRIntegerString  BeamNumber;                   //VR:IS Tag:(300A,00C0) Type:1
  TVRCodeString     BeamType;                     //VR:CS Tag:(300A,00C4) Type:1
  TVRCodeString     RadiationType;                //VR:CS Tag:(300A,00C6) Type:2
  TVRShortString    TreatmentMachineName;         //VR:SH Tag:(300A,00B2) Type:2
  TVRCodeString     PrimaryDosimeterUnit;         //VR:CS Tag:(300A,00B3) Type:3
  TVRDecimalString  SourceAxisDistance;           //VR:DS Tag:(300A,00B4) Type:3
  TVRDecimalString  FinalCumulMetersetWeight;     //VR:DS Tag:(300A,010E) Type:1C
  TVRIntegerString  NumberOfWedges;               //VR:IS Tag:(300A,00D0) Type:1
  TVRIntegerString  NumberOfCompensators;         //VR:IS Tag:(300A,00E0) Type:1  //set to 0
  TVRIntegerString  NumberOfBoli;                 //VR:IS Tag:(300A,00ED) Type:1  //set to 0
  TVRIntegerString  NumberOfBlocks;               //VR:IS Tag:(300A,00F0) Type:1
  TVRIntegerString  NumberOfControlPoints;        //VR:IS Tag:(300A,0110) Type:1
  unsigned char     NumOfBeamLimitDevices;
  TWedge*           Wedges;
  TBlock*           Blocks;
  TControlPoint*    ControlPoints;
  TBeamLimitDevice* BeamLimitDevices;
  TVRLongString     Manufacturer;                 //VR:LO Tag:(0008,0070) Type:3  //added in V1.2
  TVRIntegerString  ReferencedPatientSetupNumber; //VR:IS Tag:(300C,006A) Type:3  //added in V1.4
  TVRDecimalString  TotalBlockTrayFactor;         //VR:DS Tag:(300A,00F2) Type:3  //added in V1.5
  TVRCodeString     TreatmentDeliveryType;        //VR:CS Tag:(300A,00CE) Type:3  //added in V2.0
  unsigned char     NumOfApplicators; //added in V1.8
  TApplicator*      Applicators;      //added in V1.8
} TDcmRTBeam; //PS3.3 C.8.8.14

typedef struct {
  const char *       BeamNumber;
  const char *       BeamType;
  const char *       RadiationType;
  const char *       TreatmentMachineName;
  const char *       PrimaryDosimeterUnit;
  const char *       SourceAxisDistance;
  const char *       FinalCumulMetersetWeight;
  const char *       NumberOfWedges;
  const char *       NumberOfBlocks;
  const char *       NumberOfControlPoints;
  unsigned char      NumOfBeamLimitDevices;
  TWedgeR*           Wedges;
  TBlockR*           Blocks;
  TControlPointR*    ControlPoints;
  TBeamLimitDeviceR* BeamLimitDevices;
  const char *       ReferencedPatientSetupNumber; //added in V1.4
  const char *       TotalBlockTrayFactor; //added in V1.5
  const char *       TreatmentDeliveryType; //added in V2.0
  unsigned char      NumOfApplicators; //added in V1.8
  TApplicatorR*      Applicators;      //added in V1.8
} TDcmRTBeamR;

//-------------------------------------------------------------------
typedef struct {
  TVRShortString TreatmentMachineName;   //VR:SH Tag:(300A,00B2) Type:2
  TVRLongString  Manufacturer;           //VR:LO Tag:(0008,0070) Type:3
  TVRLongString  InstitutionName;        //VR:LO Tag:(0008,0080) Type:3
  TVRLongString  ManufacturersModelName; //VR:LO Tag:(0008,1090) Type:3
  TVRLongString  DeviceSerialNumber;     //VR:LO Tag:(0018,1000) Type:3
} TDcmBrachyTreatMachine; //PS3.3 C.8.8.15 //added in V1.6

typedef struct {
  const char * TreatmentMachineName;
  const char * Manufacturer;
  const char * InstitutionName;
  const char * ManufacturersModelName;
  const char * DeviceSerialNumber;
} TDcmBrachyTreatMachineR; //added in V1.6

typedef struct {
  TVRIntegerString SourceNumber;              //VR:IS Tag:(300A,0212) Type:1
  TVRCodeString    SourceType;                //VR:CS Tag:(300A,0214) Type:1
  TVRLongString    SourceIsotopeName;         //VR:LO Tag:(300A,0226) Type:1
  TVRDecimalString SourceIsotopeHalfLife;     //VR:DS Tag:(300A,0228) Type:1
  TVRDecimalString ReferenceAirKermaRate;     //VR:DS Tag:(300A,022A) Type:1
  TVRDate          AirKermaRateReferenceDate; //VR:DA Tag:(300A,022C) Type:1
  TVRTime          AirKermaRateReferenceTime; //VR:TM Tag:(300A,022E) Type:1
} TDcmBrachySource; //PS3.3 C.8.8.15 //added in V1.6

typedef struct {
  const char * SourceNumber;
  const char * SourceType;
  const char * SourceIsotopeName;
  const char * SourceIsotopeHalfLife;
  const char * ReferenceAirKermaRate;
  const char * AirKermaRateReferenceDate;
  const char * AirKermaRateReferenceTime;
} TDcmBrachySourceR; //added in V1.6

typedef struct {
  TVRIntegerString ControlPointIndex;            //VR:IS Tag:(300A,0112) Type:1
  TVRDecimalString CumulativeTimeWeight;         //VR:DS Tag:(300A,02D6) Type:2
  TVRDecimalString ControlPointRelativePosition; //VR:DS Tag:(300A,02D2) Type:1
} TDcmBrachyControlPoint; //PS3.3 C.8.8.15 //added in V1.6

typedef struct {
  const char * ControlPointIndex;
  const char * CumulativeTimeWeight;
  const char * ControlPointRelativePosition;
} TDcmBrachyControlPointR; //added in V1.6

typedef struct {
  TVRIntegerString        ChannelNumber;             //VR:IS Tag:(300A,0282) Type:1
  TVRDecimalString        ChannelLength;             //VR:DS Tag:(300A,0284) Type:2
  TVRDecimalString        ChannelTotalTime;          //VR:DS Tag:(300A,0286) Type:1
  TVRCodeString           SourceMovementType;        //VR:CS Tag:(300A,0288) Type:1
  TVRDecimalString        SourceApplicatorStepSize;  //VR:DS Tag:(300A,02A0) Type:1C
  TVRIntegerString        TransferTubeNumber;        //VR:IS Tag:(300A,02A2) Type:2
  TVRDecimalString        TransferTubeLength;        //VR:DS Tag:(300A,02A4) Type:2C
  TVRIntegerString        ReferencedSourceNumber;    //VR:IS Tag:(300C,000E) Type:1
  TVRDecimalString        FinalCumulativeTimeWeight; //VR:DS Tag:(300A,02C8) Type:1C
  TVRIntegerString        NumberOfControlPoints;     //VR:IS Tag:(300A,0110) Type:1
  TDcmBrachyControlPoint* BrachyControlPoints;
} TDcmBrachyChannel; //PS3.3 C.8.8.15 //added in V1.6

typedef struct {
  const char *             ChannelNumber;
  const char *             ChannelLength;
  const char *             ChannelTotalTime;
  const char *             SourceMovementType;
  const char *             SourceApplicatorStepSize;
  const char *             TransferTubeNumber;
  const char *             TransferTubeLength;
  const char *             ReferencedSourceNumber;
  const char *             FinalCumulativeTimeWeight;
  const char *             NumberOfControlPoints;
  TDcmBrachyControlPointR* BrachyControlPoints;
} TDcmBrachyChannelR; //added in V1.6

typedef struct {
  TVRCodeString      ApplicationSetupType;   //VR:CS Tag:(300A,0232) Type:1
  TVRIntegerString   ApplicationSetupNumber; //VR:IS Tag:(300A,0234) Type:1
  TVRDecimalString   TotalReferenceAirKerma; //VR:DS Tag:(300A,0250) Type:1
  unsigned char      NumOfBrachyChannels;
  TDcmBrachyChannel* BrachyChannels;
} TDcmBrachyAppSetup; //PS3.3 C.8.8.15 //added in V1.6

typedef struct {
  const char *        ApplicationSetupType;
  const char *        ApplicationSetupNumber;
  const char *        TotalReferenceAirKerma;
  unsigned char       NumOfBrachyChannels;
  TDcmBrachyChannelR* BrachyChannels;
} TDcmBrachyAppSetupR; //added in V1.6

typedef struct {
  TVRCodeString           BrachyTreatmentTechnique; //VR:CS Tag:(300A,0200) Type:1
  TVRCodeString           BrachyTreatmentType;      //VR:CS Tag:(300A,0202) Type:1
  unsigned char           NumOfTreatmentMachines;
  unsigned char           NumOfBrachySources;
  unsigned char           NumOfApplicationSetups;
  TDcmBrachyTreatMachine* TreatmentMachines;
  TDcmBrachySource*       BrachySources;
  TDcmBrachyAppSetup*     ApplicationSetups;
} TDcmBrachyAppSetups; //PS3.3 C.8.8.15 //added in V1.6

//-------------------------------------------------------------------
typedef struct {
  TVRDecimalString BeamDose;             //VR:DS Tag:(300A,0084) Type:3
  TVRDecimalString BeamMeterset;         //VR:DS Tag:(300A,0086) Type:3
  TVRIntegerString ReferencedBeamNumber; //VR:IS Tag:(300C,0006) Type:1C
} TDcmFractionReferBeam; //PS3.3 C.8.8.13 //added in V1.2

typedef struct {
  const char * BeamDose;
  const char * BeamMeterset;
  const char * ReferencedBeamNumber;
} TDcmFractionReferBeamR; //added in V1.2

typedef struct {
  TVRIntegerString ReferencedBrachyAppSetupNumber; //VR:IS Tag:(300C,000C) Type:1C
} TDcmFractionReferBrachyAppSetup; //PS3.3 C.8.8.13 //added in V1.6

typedef struct {
  const char * ReferencedBrachyAppSetupNumber;
} TDcmFractionReferBrachyAppSetupR; //added in V1.6

typedef struct {
  TVRIntegerString                 FractionGroupNumber;                 //VR:IS Tag:(300A,0071) Type:1
  TVRIntegerString                 NumberOfFractionsPlanned;            //VR:IS Tag:(300A,0078) Type:2
  //added in V1.4 begin
  TVRIntegerString                 NumberOfFractionPatternDigitsPerDay; //VR:IS Tag:(300A,0079) Type:3
  TVRIntegerString                 RepeatFractionCycleLength;           //VR:IS Tag:(300A,007A) Type:3
  TVRLongString                    FractionPattern;                     //VR:LO Tag:(300A,007B) Type:3
  //added in V1.4 end
  TVRIntegerString                 NumberOfBeams;                       //VR:IS Tag:(300A,0080) Type:1
  TVRIntegerString                 NumberOfBrachyApplicationSetups;     //VR:IS Tag:(300A,00A0) Type:1
  TDcmFractionReferBeam*           ReferencedBeams;
  TDcmFractionReferBrachyAppSetup* ReferencedBrachyAppSetups; //added in V1.6
} TDcmRTFraction; //PS3.3 C.8.8.13 //added in V1.2

typedef struct {
  const char *                      FractionGroupNumber;
  const char *                      NumberOfFractionsPlanned;
  //added in V1.4 begin
  const char *                      NumberOfFractionPatternDigitsPerDay;
  const char *                      RepeatFractionCycleLength;
  const char *                      FractionPattern;
  //added in V1.4 end
  const char *                      NumberOfBeams;
  const char *                      NumberOfBrachyApplicationSetups;
  TDcmFractionReferBeamR*           ReferencedBeams;
  TDcmFractionReferBrachyAppSetupR* ReferencedBrachyAppSetups; //added in V1.6
} TDcmRTFractionR; //added in V1.2

//-------------------------------------------------------------------
typedef struct {
  TVRCodeString ApprovalStatus; //VR:CS Tag:(300E,0002) Type:1
  TVRDate       ReviewDate;     //VR:DA Tag:(300E,0004) Type:2C
  TVRTime       ReviewTime;     //VR:TM Tag:(300E,0005) Type:2C
  TVRPersonName ReviewerName;   //VR:PN Tag:(300E,0008) Type:2C
} TDcmApproval; //PS3.3 C.8.8.16 //added in V1.2

typedef struct {
  TVRCodeString    PatientOrientation;          //VR:CS Tag:(0020,0020) Type:2C
  TVRDecimalString RadiationMachineSSD;         //VR:DS Tag:(3002,0024) Type:3  //added in V1.2
  TVRDecimalString SourceToReferObjectDistance; //VR:DS Tag:(3002,0028) Type:3  //added in V1.2
} TModifiedRIItem; //PS3.3 C.7.6.1, C.8.8.2

typedef struct {
  TVRUniqueIdentifier SOPInstanceUID;                //VR:UI Tag:(0008,0018) Type:1
  //C.12.1 --^
  TVRPersonName       PatientsName;                  //VR:PN Tag:(0010,0010) Type:2
  TVRLongString       PatientID;                     //VR:LO Tag:(0010,0020) Type:2
  TVRDate             PatientsBirthDate;             //VR:DA Tag:(0010,0030) Type:2
  TVRCodeString       PatientsSex;                   //VR:CS Tag:(0010,0040) Type:2 //M|F|O
  //C.7.1.1 --^
  TVRUniqueIdentifier StudyInstanceUID;              //VR:UI Tag:(0020,000D) Type:1
  //C.7.2.1 --^
  TVRUniqueIdentifier SeriesInstanceUID;             //VR:UI Tag:(0020,000E) Type:1
  //C.8.8.1 --^
  TVRCodeString       PatientOrientation;            //VR:CS Tag:(0020,0020) Type:2C
  //C.7.6.1 --^
  TVRDecimalString    ImagePlanePixelSpacing[2];     //VR:DS Tag:(3002,0011) Type:2
  TVRDecimalString    RadiationMachineSAD;           //VR:DS Tag:(3002,0022) Type:2
  TVRDecimalString    RadiationMachineSSD;           //VR:DS Tag:(3002,0024) Type:3  
  TVRDecimalString    RTImageSID;                    //VR:DS Tag:(3002,0026) Type:2
  TVRDecimalString    SourceToReferObjectDistance;   //VR:DS Tag:(3002,0028) Type:3  
  //added in V1.5.3 begin
  TVRDecimalString    GantryAngle;                   //VR:DS Tag:(300A,011E) Type:3 
  TVRDecimalString    BeamLimitingDeviceAngle;       //VR:DS Tag:(300A,0120) Type:3 
  //added in V1.5.3 end
  //C.8.8.2 --^
  unsigned char       UpdateSOPInstanceUID;
  unsigned char       UpdatePatientsName;
  unsigned char       UpdatePatientID;
  unsigned char       UpdatePatientsBirthDate;
  unsigned char       UpdatePatientsSex;
  unsigned char       UpdateStudyInstanceUID;
  unsigned char       UpdateSeriesInstanceUID;
  unsigned char       UpdatePatientOrientation;
  unsigned char       UpdateImagePlanePixelSpacing;
  unsigned char       UpdateRadiationMachineSAD;
  unsigned char       UpdateRadiationMachineSSD;
  unsigned char       UpdateRTImageSID;
  unsigned char       UpdateSourceToReferObjectDistance;
  unsigned char       UpdateGantryAngle;
  unsigned char       UpdateBeamLimitingDeviceAngle;
  unsigned char       Reserved;
} TUpdateRIItem; //added in V1.5.1

//-------------------------------------------------------------------
typedef struct {
  TVRIntegerString InstanceNumber; //VR:IS Tag:(0020,0013) Type:1
  TVRDate          TreatmentDate;  //VR:DA Tag:(3008,0250) Type:2
  TVRTime          TreatmentTime;  //VR:TM Tag:(3008,0251) Type:2
} TDcmRTGeneralTreatRecord; //PS3.3 C.8.8.17 //added in V1.3

typedef struct {
  TVRShortString    TreatmentMachineName;   //VR:SH Tag:(300A,00B2) Type:2
  TVRLongString     Manufacturer;           //VR:LO Tag:(0008,0070) Type:2
  TVRLongString     InstitutionName;        //VR:LO Tag:(0008,0080) Type:2
  TVRLongString     ManufacturersModelName; //VR:LO Tag:(0008,1090) Type:2
  TVRLongString     DeviceSerialNumber;     //VR:LO Tag:(0018,1000) Type:2
} TDcmRTTreatMachineRecord; //PS3.3 C.8.8.18 //added in V1.3

typedef struct {
  TVRIntegerString NumberOfFractionsPlanned; //VR:IS Tag:(300A,0078) Type:2
  TVRCodeString    PrimaryDosimeterUnit;     //VR:CS Tag:(300A,00B3) Type:1
} TDcmRTBeamsSessionRecord; //PS3.3 C.8.8.21 //added in V1.3

typedef struct {
  TVRDate           TreatmentControlPointDate;          //VR:DA Tag:(3008,0024) Type:1
  TVRTime           TreatmentControlPointTime;          //VR:TM Tag:(3008,0025) Type:1
  TVRDecimalString  SpecifiedMeterset;                  //VR:DS Tag:(3008,0042) Type:2
  TVRDecimalString  DeliveredMeterset;                  //VR:DS Tag:(3008,0044) Type:1
  TVRDecimalString  DoseRateSet;                        //VR:DS Tag:(300A,0115) Type:2
  TVRDecimalString  DoseRateDelivered;                  //VR:DS Tag:(3008,0048) Type:2
  TVRDecimalString  GantryAngle;                        //VR:DS Tag:(300A,011E) Type:1C
  TVRCodeString     GantryRotationDirection;            //VR:CS Tag:(300A,011F) Type:1C
  TVRDecimalString  BeamLimitDeviceAngle;               //VR:DS Tag:(300A,0120) Type:1C
  TVRCodeString     BeamLimitDeviceRotationDirection;   //VR:CS Tag:(300A,0121) Type:1C
  TVRDecimalString  PatientSupportAngle;                //VR:DS Tag:(300A,0122) Type:1C
  TVRCodeString     PatientSupportRotationDirection;    //VR:CS Tag:(300A,0123) Type:1C
  TVRDecimalString  TabletopEccentricAngle;             //VR:DS Tag:(300A,0125) Type:1C
  TVRCodeString     TabletopEccentricRotationDirection; //VR:CS Tag:(300A,0126) Type:1C
  TVRDecimalString  TabletopVertPosition;               //VR:DS Tag:(300A,0128) Type:2C
  TVRDecimalString  TabletopLongPosition;               //VR:DS Tag:(300A,0129) Type:2C
  TVRDecimalString  TabletopLatPosition;                //VR:DS Tag:(300A,012A) Type:2C
  //added in V1.7 begin
  TVRIntegerString  ControlPointIndex;                  //VR:IS Tag:(300C,00F0) Type:3
  TVRDecimalString  NominalBeamEnergy;                  //VR:DS Tag:(300A,0114) Type:3
  TVRCodeString     NominalBeamEnergyUnit;              //VR:CS Tag:(300A,0015) Type:1C
  //added in V1.7 end
  //added in V2.0 begin
  TVRFloatingPointSingle TableTopPitchAngle;             //VR:FL Tag:(300A,0140) Type:1C
  TVRCodeString          TableTopPitchRotationDirection; //VR:CS Tag:(300A,0142) Type:1C
  TVRFloatingPointSingle TableTopRollAngle;              //VR:FL Tag:(300A,0144) Type:1C
  TVRCodeString          TableTopRollRotationDirection;  //VR:CS Tag:(300A,0146) Type:1C
  //added in V2.0 end 
  unsigned char     NumOfBeamLimitDevices;
  TBeamLimitDevice* BeamLimitDevicePositions;
} TTreatControlPoint; //PS3.3 C.8.8.21 //added in V1.3

typedef struct {
  const char *     TreatmentControlPointDate;
  const char *     TreatmentControlPointTime;
  const char *     SpecifiedMeterset;
  const char *     DeliveredMeterset;
  const char *     DoseRateSet;
  const char *     DoseRateDelivered;
  const char *     GantryAngle;
  const char *     GantryRotationDirection;
  const char *     BeamLimitDeviceAngle;
  const char *     BeamLimitDeviceRotationDirection;
  const char *     PatientSupportAngle;
  const char *     PatientSupportRotationDirection;
  const char *     TabletopEccentricAngle;
  const char *     TabletopEccentricRotationDirection;
  const char *     TabletopVertPosition;
  const char *     TabletopLongPosition;
  const char *     TabletopLatPosition;
  const char *     ControlPointIndex;
  const char *     NominalBeamEnergy;
  const char *     NominalBeamEnergyUnit;
  //added in V2.0 begin
  const char *     TableTopPitchAngle;
  const char *     TableTopPitchRotationDirection;
  const char *     TableTopRollAngle;
  const char *     TableTopRollRotationDirection;
  //added in V2.0 end 
  unsigned char    NumOfBeamLimitDevices;
  TBeamLimitDeviceR* BeamLimitDevicePositions;
} TTreatControlPointR; //added in V1.7

//-------------------------------------------------------------------
typedef struct {
  TVRLongString       BeamName;                    //VR:LO Tag:(300A,00C2) Type:3
  TVRCodeString       BeamType;                    //VR:CS Tag:(300A,00C4) Type:1
  TVRCodeString       RadiationType;               //VR:CS Tag:(300A,00C6) Type:1
  TVRDecimalString    SourceAxisDistance;          //VR:DS Tag:(300A,00B4) Type:3
  TVRIntegerString    CurrentFractionNumber;       //VR:IS Tag:(3008,0022) Type:2
  TVRCodeString       TreatmentDeliveryType;       //VR:CS Tag:(300A,00CE) Type:2
  TVRCodeString       TreatmentTerminationStatus;  //VR:CS Tag:(3008,002A) Type:1
  TVRShortString      TreatmentTerminationCode;    //VR:SH Tag:(3008,002B) Type:3
  TVRCodeString       TreatmentVerificationStatus; //VR:CS Tag:(3008,002C) Type:2
  TVRIntegerString    NumberOfWedges;              //VR:IS Tag:(300A,00D0) Type:1
  TVRIntegerString    NumberOfCompensators;        //VR:IS Tag:(300A,00E0) Type:2  //set to 0
  TVRIntegerString    NumberOfBoli;                //VR:IS Tag:(300A,00ED) Type:2  //set to 0
  TVRIntegerString    NumberOfBlocks;              //VR:IS Tag:(300A,00F0) Type:2
  TVRIntegerString    NumberOfControlPoints;       //VR:IS Tag:(300A,0110) Type:1
  unsigned char       NumOfBeamLimitDevices;
  TWedge*             Wedges;
  TBlock*             Blocks;
  TTreatControlPoint* ControlPoints;
  TBeamLimitDevice*   BeamLimitDevices;
  unsigned char       NumOfApplicators; //added in V1.8
  TApplicator*        Applicators;      //added in V1.8
} TDcmTreatSessionBeam; //PS3.3 C.8.8.21 //added in V1.3

typedef struct {
  const char *         BeamName;
  const char *         BeamType;
  const char *         RadiationType;
  const char *         SourceAxisDistance;
  const char *         CurrentFractionNumber;
  const char *         TreatmentDeliveryType;
  const char *         TreatmentTerminationStatus;
  const char *         TreatmentTerminationCode;
  const char *         TreatmentVerificationStatus;
  const char *         NumberOfWedges;
  const char *         NumberOfBlocks;
  const char *         NumberOfControlPoints;
  unsigned char        NumOfBeamLimitDevices;
  TWedgeR*             Wedges;
  TBlockR*             Blocks;
  TTreatControlPointR* ControlPoints;
  TBeamLimitDeviceR*   BeamLimitDevices;
  unsigned char        NumOfApplicators; //added in V1.8
  TApplicatorR*        Applicators;      //added in V1.8
} TDcmTreatSessionBeamR;  //added in V1.7

//added in V3.0 begin
//-------------------------------------------------------------------
typedef struct {
  TVRIntegerString NumberOfCopies;   //VR:IS Tag:(2000,0010)
  TVRCodeString    PrintPriority;    //VR:CS Tag:(2000,0020)
  TVRCodeString    MediumType;       //VR:CS Tag:(2000,0030)
  TVRCodeString    FilmDestination;  //VR:CS Tag:(2000,0040)
  //TVRLongString    FilmSessionLabel; //VR:LO Tag:(2000,0050)
  //TVRIntegerString MemoryAllocation; //VR:IS Tag:(2000,0060)
  //TVRShortString   OwnerID;          //VR:SH Tag:(2100,0160)
} TDcmFilmSession; //PS3.3 C.13.1 

typedef struct {
  TVRPersonName    PatientsName;              //VR:PN Tag:(0010,0010) //added 2019.3.24
  TVRLongString    PatientID;                 //VR:LO Tag:(0010,0020) //added 2019.3.24
  TVRShortText     ImageDisplayFormat;        //VR:ST Tag:(2010,0010)
  TVRCodeString    AnnotationDisplayFormatID; //VR:CS Tag:(2010,0030)
  TVRCodeString    FilmOrientation;           //VR:CS Tag:(2010,0040)
  TVRCodeString    FilmSizeID;                //VR:CS Tag:(2010,0050)
  TVRCodeString    MagnificationType;         //VR:CS Tag:(2010,0060)
  TVRCodeString    SmoothingType;             //VR:CS Tag:(2010,0080)
  TVRCodeString    BorderDensity;             //VR:CS Tag:(2010,0100)
  TVRCodeString    EmptyImageDensity;         //VR:CS Tag:(2010,0110)
  TVRUnsignedShort MinDensity;                //VR:US Tag:(2010,0120)
  TVRUnsignedShort MaxDensity;                //VR:US Tag:(2010,0130)
  TVRCodeString    Trim;                      //VR:CS Tag:(2010,0140)
  //TVRShortText     ConfigurationInformation;  //VR:ST Tag:(2010,0150)
  //TVRUnsignedShort Illumination;              //VR:US Tag:(2010,015E)
  //TVRUnsignedShort ReflectedAmbientLight;     //VR:US Tag:(2010,0160)
  //TVRCodeString    RequestedResolutionID;     //VR:CS Tag:(2020,0050)
} TDcmFilmBox; //PS3.3 C.13.3 

typedef struct {
  TVRUnsignedShort    ImageBoxPosition;              //VR:US Tag:(2020,0010)
  TVRCodeString       Polarity;                      //VR:CS Tag:(2020,0020)
  TVRCodeString       MagnificationType;             //VR:CS Tag:(2010,0060)
  TVRCodeString       SmoothingType;                 //VR:CS Tag:(2010,0080)
  //TVRShortText        ConfigurationInformation;      //VR:ST Tag:(2010,0150)
  //TVRDecimalString    RequestedImageSize;            //VR:DS Tag:(2020,0030)
  //TVRCodeString       RequestedDecimateCropBehavior; //VR:CS Tag:(2020,0040)
  TVRUniqueIdentifier ImageSopInstanceUID;
  TVRCodeString       PhotometricInterpretation;
  TFileName           ImageFileName;
  double              MagnificationFactor;
  long                LeftPos;
  long                TopPos;
} TDcmImageBox; //PS3.3 C.13.5 

typedef struct {
  TVRUnsignedShort    AnnotationPosition; //VR:US Tag:(2030,0010)
  TVRLongString       TextString;         //VR:LO Tag:(2030,0020)
  TVRUniqueIdentifier AnnotationSopInstanceUID;
} TDcmAnnotation; //PS3.3 C.13.7 

typedef struct {
  TVRCodeString        ExecutionStatus;     //VR:CS Tag:(2100,0020)
  TVRCodeString        ExecutionStatusInfo; //VR:CS Tag:(2100,0030)
  TVRDate              CreationDate;        //VR:DA Tag:(2100,0040)
  TVRTime              CreationTime;        //VR:TM Tag:(2100,0050)
  TVRCodeString        PrintPriority;       //VR:CS Tag:(2000,0020)
  TVRLongString        PrinterName;         //VR:LO Tag:(2110,0030)
  TVRApplicationEntity Originator;          //VR:AE Tag:(2100,0070)
} TDcmPrintJob; //PS3.3 C.13.8 

typedef struct {
  TVRCodeString PrinterStatus;         //VR:CS Tag:(2110,0010)
  TVRCodeString PrinterStatusInfo;     //VR:CS Tag:(2110,0020)
  TVRLongString PrinterName;           //VR:LO Tag:(2110,0030)
  TVRLongString Manufacturer;          //VR:LO Tag:(0008,0070)
  TVRLongString ManufacturerModelName; //VR:LO Tag:(0008,1090)
  TVRLongString DeviceSerialNumber;    //VR:LO Tag:(0018,1000)
  TVRLongString SoftwareVersions;      //VR:LO Tag:(0018,1020)
  TVRDate       DateOfLastCalibration; //VR:DA Tag:(0018,1200)
  TVRTime       TimeOfLastCalibration; //VR:TM Tag:(0018,1201)
} TDcmPrinter; //PS3.3 C.13.9 

typedef struct {
  TDcmFilmBox       FilmBox;
  unsigned char     NumOfReferImageBoxes; //1..n
  TDcmImageBox*     ReferImageBoxes;
  unsigned char     NumOfReferAnnotations; //0..n
  TDcmAnnotation*   ReferAnnotations;
} TDcmFilmBoxIOD; //PS3.3 B.8.2

//-------------------------------------------------------------------
typedef struct {
  //Scheduled Procedure Step
  TVRApplicationEntity ScheduledStationAETitle;           //VR:AE Tag:(0040,0001) R/1
  TVRQryDate           ScheduledProcedureStepStartDate;   //VR:DA Tag:(0040,0002) R/1
  TVRQryTime           ScheduledProcedureStepStartTime;   //VR:TM Tag:(0040,0003) R/1
  TVRCodeString        Modality;                          //VR:CS Tag:(0008,0060) R/1
  TVRPersonName        ScheduledPerformingPhysiciansName; //VR:PN Tag:(0040,0006) R/2
  TVRLongString        ScheduledProcedureStepDescription; //VR:LO Tag:(0040,0007) O/1C
  TVRShortString       ScheduledStationName;              //VR:SH Tag:(0040,0010) O/2
  //Imaging Service Request
  TVRShortString       AccessionNumber;                   //VR:SH Tag:(0008,0050) O/2
  //Patient Identification
  TVRPersonName        PatientsName;                      //VR:PN Tag:(0010,0010) R/1
  TVRLongString        PatientID;                         //VR:LO Tag:(0010,0020) R/1
  //Patient Demographic
  TVRDate              PatientsBirthDate;                 //VR:DA Tag:(0010,0030) O/2
  TVRCodeString        PatientsSex;                       //VR:CS Tag:(0010,0040) O/2
} TDcmModalityWorklist; //PS3.4 K.6.1.2.2

typedef struct {
  //Scheduled Procedure Step
  const char * ScheduledStationAETitle;           
  const char * ScheduledProcedureStepStartDate;   
  const char * ScheduledProcedureStepStartTime;   
  const char * Modality;                          
  const char * ScheduledPerformingPhysiciansName; 
  const char * ScheduledProcedureStepDescription; 
  const char * ScheduledStationName;              
  //Imaging Service Request
  const char * AccessionNumber;                   
  //Patient Identification
  const char * PatientsName;                      
  const char * PatientID;                         
  //Patient Demographic
  const char * PatientsBirthDate;                 
  const char * PatientsSex;                       
} TDcmModalityWorklistInfo; 
//added in V3.0 end

//-------------------------------------------------------------------
typedef struct {
  TDcmSOPCommon        SOPCommon;
  TDcmPatient          Patient;
  TDcmGeneralStudy     GeneralStudy;
  TDcmRTSeries         RTSeries;
  TDcmGeneralEquipment GeneralEquipment;
  TDcmGeneralImage     GeneralImage;
  TDcmImagePixel       ImagePixel;
  TDcmRTImage          RTImage;
  TDcmVOILUT           VOILUT;
} TDcmRTImageIOD; //PS3.3 A.17

typedef struct {
  ////General Image
  const char *       InstanceNumber;
  const char *       PatientOrientation;
  const char *       ContentDate;
  const char *       ContentTime;
  const char *       ImageType;
  ////Image Pixel
  const char *       SamplesPerPixel;
  const char *       PhotometricInterpretation;
  const char *       Rows;
  const char *       Columns;
  const char *       BitsAllocated;
  const char *       BitsStored;
  const char *       HighBit;
  const char *       PixelRepresentation;
  const char *       PixelAspectRatio;
  ////VOI LUT
  const char *       WindowCenter;
  const char *       WindowWidth;
  ////RT Image
  const char *       RTImageLabel;
  const char *       OperatorsName;
  const char *       ConversionType;
  const char *       ReportedValuesOrigin;
  const char *       RTImagePlane;
  const char *       XRayImageReceptorAngle;
  const char *       ImagePlanePixelSpacing;
  const char *       RTImagePosition;
  const char *       RadiationMachineName;
  const char *       PrimaryDosimeterUnit;
  const char *       RadiationMachineSAD;
  const char *       RadiationMachineSSD;
  const char *       RTImageSID;
  const char *       SourceToReferObjectDistance;
  const char *       GantryAngle;
  const char *       BeamLimitingDeviceAngle;
  const char *       PatientSupportAngle;
  const char *       TableTopEccentricAxisDistance;
  const char *       TableTopEccentricAngle;
  const char *       TableTopVerticalPosition;
  const char *       TableTopLongitudinalPosition;
  const char *       TableTopLateralPosition;
  ////Exposure Item
  const char *       KVP;
  const char *       ExposureTime;
  const char *       XRayTubeCurrent;
  const char *       DiaphragmPosition;
  unsigned char      NumOfBeamLimitDevices;
  TBeamLimitDeviceR* BeamLimitDevices;
} TDcmRTImageInfo; //added in V1.2

//-------------------------------------------------------------------
typedef struct {
  TDcmSOPCommon        SOPCommon;
  TDcmPatient          Patient;
  TDcmGeneralStudy     GeneralStudy;
  TDcmRTSeries         RTSeries;
  TDcmGeneralEquipment GeneralEquipment;
  TDcmRTGeneralPlan    RTGeneralPlan;
  TDcmApproval         Approval; //added in V1.2
  TDcmRTBeam*          RTBeams;
  TDcmRTFraction*      RTFractions; //added in V1.2
  TDcmRTPatientSetup*  RTPatientSetups; //added in V1.4
  unsigned char        NumOfRTBeams;
  unsigned char        NumOfRTFractions; //added in V1.2
  unsigned char        NumOfRTPatientSetups; //added in V1.4
} TDcmRTPlanIOD; //PS3.3 A.20

typedef struct {
  ////RT General Plan
  const char *         RTPlanLabel;
  const char *         RTPlanDate;
  const char *         RTPlanTime;
  const char *         RTPlanGeometry; //set to TREATMENT_DEVICE
  ////Approval
  const char *         ApprovalStatus; //added in V1.2
  const char *         ReviewDate; //added in V1.2
  const char *         ReviewTime; //added in V1.2
  const char *         ReviewerName; //added in V1.2
  ////Others
  unsigned char        NumOfRTBeams;
  unsigned char        NumOfRTFractions; //added in V1.2
  unsigned char        NumOfRTPatientSetups; //added in V1.4
  TDcmRTBeamR*         RTBeams;
  TDcmRTFractionR*     RTFractions; //added in V1.2
  TDcmRTPatientSetupR* RTPatientSetups; //added in V1.4
} TDcmRTPlanInfo;

//-------------------------------------------------------------------
typedef struct {
  TDcmSOPCommon         SOPCommon;
  TDcmPatient           Patient;
  TDcmGeneralStudy      GeneralStudy;
  TDcmRTSeries          RTSeries;
  TDcmGeneralEquipment  GeneralEquipment;
  TDcmRTGeneralPlan     RTGeneralPlan;
  TDcmApproval          Approval;
  TDcmBrachyAppSetups   BrachyAppSetups;
  TDcmRTFraction*       RTFractions;
  TDcmRTPatientSetup*   RTPatientSetups;
  unsigned char         NumOfRTFractions;
  unsigned char         NumOfRTPatientSetups;
} TDcmBrachyPlanIOD; //PS3.3 A.20 //added in V1.6

typedef struct {
  ////RT General Plan
  const char *             RTPlanLabel;
  const char *             RTPlanDate;
  const char *             RTPlanTime;
  const char *             RTPlanGeometry;
  ////Approval
  const char *             ApprovalStatus;
  const char *             ReviewDate;
  const char *             ReviewTime;
  const char *             ReviewerName;
  ////BrachyAppSetups
  const char *             BrachyTreatmentTechnique;
  const char *             BrachyTreatmentType;
  ////Others
  unsigned char            NumOfTreatmentMachines;
  unsigned char            NumOfBrachySources;
  unsigned char            NumOfApplicationSetups;
  unsigned char            NumOfRTFractions;
  unsigned char            NumOfRTPatientSetups;
  TDcmBrachyTreatMachineR* TreatmentMachines;
  TDcmBrachySourceR*       BrachySources;
  TDcmBrachyAppSetupR*     ApplicationSetups;
  TDcmRTFractionR*         RTFractions;
  TDcmRTPatientSetupR*     RTPatientSetups;
} TDcmBrachyPlanInfo; //added in V1.6

//-------------------------------------------------------------------
typedef struct {
  TDcmSOPCommon            SOPCommon;
  TDcmPatient              Patient;
  TDcmGeneralStudy         GeneralStudy;
  TDcmRTSeries             RTSeries;
  TDcmGeneralEquipment     GeneralEquipment;
  TDcmRTGeneralTreatRecord RTGeneralTreatRecord;
  TDcmRTTreatMachineRecord RTTreatMachineRecord;
  TDcmRTBeamsSessionRecord RTBeamsSessionRecord;
  TDcmTreatSessionBeam*    TreatSessionBeams;
  unsigned char            NumOfTreatSessionBeams;
} TDcmRTBeamsTreatRecordIOD;  //PS3.3 A.29 //added in V1.3

typedef struct {
  ////RT General Treat Record
  const char *           InstanceNumber;
  const char *           TreatmentDate;
  const char *           TreatmentTime;
  ////RT Treat Machine Record
  const char *           TreatmentMachineName;
  const char *           Manufacturer;
  const char *           InstitutionName;
  const char *           ManufacturersModelName;
  const char *           DeviceSerialNumber;
  ////RT Beams Session Record
  const char *           OperatorsName;
  const char *           NumberOfFractionsPlanned;
  const char *           PrimaryDosimeterUnit;
  ////Others
  TDcmTreatSessionBeamR* TreatSessionBeam;
  unsigned char          NumOfTreatSessionBeams;
} TDcmRTBeamsTreatRecordInfo;  //added in V1.7

typedef struct {
  ////Image Plane
  const char * PixelSpacing;
  const char * ImageOrientationPatient;
  const char * ImagePositionPatient;
  const char * SliceThickness;
  const char * SliceLocation;
  ////RT Dose
  const char * DoseUnits;
  const char * DoseType;
  const char * NormalizationPoint;
  const char * DoseSummationType;
  const char * DoseGridScaling;
  ////
  const unsigned short*  PixelData;
} TDcmRTDoseInfo; //added in V1.5

//-------------------------------------------------------------------
typedef struct {
  TDcmSOPCommon        SOPCommon;
  TDcmPatient          Patient;
  TDcmGeneralStudy     GeneralStudy;
  TDcmGeneralSeries    GeneralSeries;
  TDcmFrameOfReference FrameOfReference;
  TDcmGeneralEquipment GeneralEquipment;
  TDcmGeneralImage     GeneralImage;
  TDcmImagePlane       ImagePlane;
  TDcmImagePixel       ImagePixel;
  TDcmCTImage          CTImage;
  TDcmVOILUT           VOILUT;
} TDcmCTImageIOD;  //PS3.3 A.3 //added in V2.1

//-------------------------------------------------------------------
typedef struct {
  TDcmSOPCommon        SOPCommon;
  TDcmPatient          Patient;
  TDcmGeneralStudy     GeneralStudy;
  TDcmGeneralSeries    GeneralSeries;
  TDcmDXSeries         DXSeries;
  TDcmGeneralEquipment GeneralEquipment;
  TDcmGeneralImage     GeneralImage;
  TDcmImagePixel       ImagePixel;
  TDcmDXAnatomyImaged  DXAnatomyImaged;
  TDcmDXImage          DXImage;
  TDcmDXDetector       DXDetector;
  TDcmVOILUT           VOILUT;
} TDcmDXImageIOD;  //PS3.3 A.26 //added in V3.0

typedef struct {
  ////DXSeries
  const char *	PresentationIntentType;
  ////DXAnatomyImaged
  const char *	ImageLaterality;
  ////DXImage
  const char *	PixelIntensityRelationship;
  const char *	PixelIntensityRelationshipSign;
  const char *	RescaleIntercept;
  const char *	RescaleSlope;
  const char *	RescaleType;
  const char *	LossyImageCompression;
  const char *	BurnedInAnnotation;
  const char *	PresentationLUTShape;
  ////DXDetector
  const char *	ImagerPixelSpacing;
  const char *	DetectorType;
} TDcmDXImageInfo; //added in V3.0

typedef struct {
  ////Patient
  const char *	PatientID;
  const char *	PatientName;
  const char *	PatientSex;
  const char *	PatientBirthDate;
  //const char *	PatientBirthTime;
  //const char *	PatientAge;
  ////General Study
  const char *	StudyInstanceUID;
  const char *	StudyID;
  const char *	StudyDate;
  const char *	StudyTime;
  const char *  StudyDescript;
  const char *  AccessionNo;
  const char *  ReferPhysician;
  ////Series
  const char *	SeriesInstanceUID; //General Series | RT Series
  const char *  Modality;          //General Series | RT Series
  const char *  SeriesNo;          //General Series | RT Series
  const char *  SeriesDate;        //General Series
  const char *  SeriesTime;        //General Series
  const char *  SeriesDescript;    //General Series
  const char *  BodyPartExam;      //General Series
                                   ////General Equipment
  const char *  StationName;
  const char *  InstituteName;
  const char *  Manufacturer;
  const char *  ModelName;
  ////SOP Common
  const char *	SOPClassUID;
  const char *	SOPClassName; //added in V1.4
  const char *	SOPInstanceUID;
  const char *  InstanceNo;
  ////
  const char *  DcmFileName;
} TDcmInfoHeader;

typedef struct {
  unsigned long	Size;
  unsigned long	FrameCount;
  unsigned long	FrameIndex;
  unsigned long	Width;
  unsigned long	Height;
  long		      Depth;
  double	      MinValue;
  double	      MaxValue;
  double	      AspectRatio;
  long		      Monochrome;
  unsigned long	WindowCount;
  double	      WinCenter;    //added in V1.4
  double	      WinWidth;     //added in V1.4
  const char *  PixelSpacing; //added in V1.4
  const char *  PhotometricInterpretation; //added in V3.0
} TDcmImageInfo;


#pragma pack(pop)
