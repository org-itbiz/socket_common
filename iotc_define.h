//---------------------------------------------------------------------------
//define default port
#define SERVER_365_DOMAIN   "iotech.iptime.org"
#define UDP_SERVER_PORT		11000


//excel sheet
#define SHEET_SERVER  			"SERVER"
#define SHEET_CALL    			"콜센터"
#define SHEET_LOCALE  			"현장"
#define SHEET_CAMERA  			"카메라"
#define SHEET_CAMERA_CONFIG  	"카메라_설정"
#define SHEET_DEVICE  			"현장장비"

//domain * local ip address
#define SERVER_DOMAIN		2   //서버, 현장 DDNS
//camera info
#define _C_DOMAIN			3   //공유기 다를때 ?
#define _C_RTST_PORT       	4
#define _C_USER				5
#define _C_PASSWORD       	6

//#define CAMERA_DOMAIN		3

//

/*

현장명,
현장 도메인
카메라 도메인??? 현장 도메인

*/
//---------------------------------------------------------------------------
#ifndef _WINDOWS_
	#if (defined(_WIN32) || defined(_WIN64))
		#include <windows.h>
	#endif
#endif

#define NAME_LEN            	12     //
#define PASSWD_LEN				16      //
#define MAX_PASSWD_LEN_EX       64      //
#define SERIALNO_LEN            20      //
#define MACADDR_LEN             6       //
#define MAX_SENCE_NUM           16      //
#define URL_LEN             	128     //
#define FILE_PATH_LEN       	32     //
#define MAX_FILE_PATH_LEN       128     //

#define IPV4_LEN            16      //
#define IPV6_LEN            64      //
#define MACADDR_LEN         17
#define GUID_LEN			64

//param
class DVR_PARAM
{
  public:
	WORD		nStreamType;		//type: 0-main, 1-sub
	WORD		nLinkMode;			//link mode: 0- TCP, 1- UDP, 2- multi, 3- RTP, 4-RTP/RTSP, 5-RSTP/HTTP
	bool		bBlocked;			//0- Non-blocking flow, 1- blocking flow
	WORD		nDisplayBufNum;		//maximum buffering frames
};

//영역
class DVR_POSITION
{
  public:
	WORD x, y;
	WORD px, py;
};

//camera class
class DVR_CAMERA
{
  public:
	char	sUserName[NAME_LEN];
	char	sPassword[PASSWD_LEN];
	char	sIPAddress[IPV4_LEN];
	char    sMemDrive[FILE_PATH_LEN];
	char    sHDDDrive[FILE_PATH_LEN];
	char    sNASDrive[FILE_PATH_LEN];

//	DVR_PARAM		DVRParam;
	DVR_POSITION	Position[3];

	char    sSaveType[1];
	char 	sUseYN[1];

	WORD    nIndex;
	WORD	nDVRPort;           		//port
	WORD	nChannel;

};

//추가 할 class

//ALL CONFIG class
class IOTC_CONFIG
{
  public:
	//BASE
	char sLocaleName[NAME_LEN];		//현장명
	char sSerialNo[SERIALNO_LEN];   //시리얼번호

	DVR_CAMERA	Camera[10];      //카메라 정보
    //기타 세팅관련 추가


};


class IOTC_DEVICE
{
  public:
	//BASE
	String	sConfigPath;
	String	sLocaleName;	//현장명
	String	sSerialNo;		//시리얼번호
	String	sDeviceGuid;	//guid
	String	sDeviceName;	//디바이스 명
	WORD	nUDPPort;

	String	sIPAddress;
	String	sMacAddress;

	String	sOsType;        //os
	String	sDeviceType;    //장비 타입
    String  sRequestUrl;
	String	sWebUrl;

    //기타 세팅관련 추가


};
IOTC_DEVICE * ioDevice;

//cmd
const String CMD_GET_CONFIG = "GET_CONFIG";
const String CMD_SET_CONFIG = "SET_CONFIG";
const String CMD_RETURN_CONFIG = "RETURN_CONFIG";

#define URL_DEVICE_BASE          "http://api.iotc365.cn/api/device/get/base"
#define URL_GET_LOCALE_SETTING     "http://iotc365.com/test_locale/muin_set3/muin_set3.json"

#define APK_INFO_ColCount 4
#define APK_INFO_LineCount 3

#define _C_NAME			1
#define _C_WEB_URL		2
#define _C_UDP_PORT		3
#define _C_MACADDR		4

#define _L_CUSTOM       1
#define _C_DISC			2

String APK_INFO[APK_INFO_LineCount][APK_INFO_ColCount];

#define CFG_MAX_COLUMN      50
#define CFG_MAX_RECORD      50

//---------------------------------------------------------------------------