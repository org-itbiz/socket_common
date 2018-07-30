//---------------------------------------------------------------------------

#pragma hdrstop

#include "json.h"
#include "UtilHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#if defined(_PLAT_MSWINDOWS)
#pragma link "jsoncpp.lib"
#pragma comment(lib, "iphlpapi.lib")
#endif

TUtilHelper *UtilHelper;

//---------------------------------------------------------------------------
__fastcall TUtilHelper::TUtilHelper()
{
//
}
//---------------------------------------------------------------------------

__fastcall TUtilHelper::~TUtilHelper()
{
//
}
//---------------------------------------------------------------------------

String __fastcall TUtilHelper::DateTimeToStrFormatFunc(TDateTime dtime)
{
	return dtime.FormatString("yyyymmddhhnn");
}
//---------------------------------------------------------------------------

String __fastcall TUtilHelper::GetLocalIP()
{
	char 		*ip;
	#if defined(_PLAT_MSWINDOWS)
	WSADATA		wsaData;
	HOSTENT 	*hostEnt;
	char 		slocal[256];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return "";
	if(gethostname(slocal, sizeof(slocal)) == SOCKET_ERROR)
		return "";
	if(hostEnt = gethostbyname(slocal))
	{
//		ip = inet_ntoa(*(struct in_addr *)*hostEnt->h_addr_list);
        ip = inet_ntoa(*((in_addr*)hostEnt->h_addr_list[0]));
	}
	else
	{
        return "";
    }
	WSACleanup();
	#else
	#if defined(_PLAT_ANDROID)
	_di_JObject WifiManagerObj;
	_di_JWifiManager WifiManager;
	_di_JWifiInfo WifiInfo;

	WifiManagerObj = SharedActivityContext()->getSystemService(TJContext::JavaClass->WIFI_SERVICE);

	if( WifiManagerObj !=NULL )
	{
		WifiManager = TJWifiManager::Wrap( static_cast<_di_ILocalObject>(WifiManagerObj)->GetObjectID());
		WifiInfo = WifiManager->getConnectionInfo();

		sprintf(ip, "%s", AnsiString(WifiInfo->getIpAddress()).c_str());
	}
	else
	{
		sprintf(ip, "%s", "");
	}
	#endif
	#endif

	return ip;
}
//---------------------------------------------------------------------------

String __fastcall TUtilHelper::GetComputerName(AnsiString localIp)
{
	#if defined(_PLAT_MSWINDOWS)
	struct hostent *ClientHost;
	DWORD InetAddr = inet_addr(localIp.c_str());
	ClientHost = gethostbyaddr((char*)&InetAddr, localIp.Length(), PF_INET);

	return ClientHost->h_name;
	#else
    return "";
	#endif
}
//---------------------------------------------------------------------------
String __fastcall TUtilHelper::GetIpByDomainName(char *szHost)
{
	char		*ip;
	#if defined(_PLAT_MSWINDOWS)
	WSADATA		wsaData;
	HOSTENT		*hostEnt;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return "";

	if (hostEnt = gethostbyname(szHost))
    {
		ip = inet_ntoa(*(struct in_addr *)hostEnt->h_addr_list[0]);
	}
	else
	{
        return "";
	}
	WSACleanup();
	#else
    sprintf(ip, "%s", "0.0.0.0");
	#endif
	return ip;
}
//---------------------------------------------------------------------------
bool __fastcall TUtilHelper::GetIpByDomainName2(char *szHost, char szIp[10][256], int *nCount)
{
	#if defined(_PLAT_MSWINDOWS)
	WSADATA		wsaData;
	HOSTENT		*hostEnt;
	int			nAdapter = 0;
    struct		sockaddr_in sAddr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return false;

    if (hostEnt = gethostbyname(szHost))
    {
		while(hostEnt->h_addr_list[nAdapter])
        {
			memcpy(&sAddr.sin_addr.s_addr, hostEnt->h_addr_list[nAdapter], hostEnt->h_length);
			char szBuffer[1024] = {0};

            sprintf(szBuffer,"%s", inet_ntoa(sAddr.sin_addr));

            strcpy(szIp[nAdapter], szBuffer);
            nAdapter++;
        }

        *nCount = nAdapter;
    }
    WSACleanup();
	return true;
	#else
    return false;
	#endif

}
//---------------------------------------------------------------------------

String __fastcall TUtilHelper::GetMacAddress()
{
    String sMacAddress;
	#if defined(__ANDROID__)
	_di_JObject WifiManagerObj;
	_di_JWifiManager WifiManager;
	_di_JWifiInfo WifiInfo;

	WifiManagerObj = SharedActivityContext()->getSystemService(TJContext::JavaClass->WIFI_SERVICE);

	if( WifiManagerObj !=NULL )
	{
		WifiManager = TJWifiManager::Wrap( static_cast<_di_ILocalObject>(WifiManagerObj)->GetObjectID());
		WifiInfo = WifiManager->getConnectionInfo();

		sMacAddress = JStringToString(WifiInfo->getMacAddress());
	}

	#elif _WIN32

	IP_ADAPTER_INFO AdapterInfo[16];
	DWORD dwBufLen = sizeof(AdapterInfo);
	DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
	if (dwStatus != 0)
	{

	}
	else
	{
		PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
		sMacAddress.sprintf(L"%02x:%02x:%02x:%02x:%02x:%02x",
			pAdapterInfo->Address[0],
			pAdapterInfo->Address[1],
			pAdapterInfo->Address[2],
			pAdapterInfo->Address[3],
			pAdapterInfo->Address[4],
			pAdapterInfo->Address[5]);
	}
	#endif

	return sMacAddress;
}
//---------------------------------------------------------------------------

/*
String __fastcall TUtilHelper::GetInternetIP(String sDomain)
{
    UTF8String sJsonResult;

    TStringStream *ss = new TStringStream();
	TIdHTTP *idHttp = new TIdHTTP(this);
	try {
		idHttp->ProtocolVersion = pv1_1;
		idHttp->Request->Accept = "application/json";
		idHttp->Request->ContentType = "application/json";
		idHttp->ConnectTimeout = 3000;
        idHttp->ReadTimeout = 3000;
		//ssl 일경우 libeay32.dll, ssleay32.dll copy
		String request_data = request_data.sprintf(L"http://api.iotc365.com/api/get/ip_text?domain=%s&format=json", AnsiString(sDomain).c_str());

//		sJsonResult = idHttp->Get(request_data.Trim());
		idHttp->Get(request_data.Trim(), ss);
		ss->Position = 0;
		sJsonResult = ss->DataString.Trim();
        //jsonobj 로 변경
	}
	catch (Exception &e)
	{

	}

	idHttp->Free();
	delete idHttp;
    delete ss;

	return sJsonResult;
}
*/
//---------------------------------------------------------------------------

int __fastcall TUtilHelper::GetIPAddressEndPoint(AnsiString localIp)
{
	int endPoint = 0;

	DynamicArray<String> strArr = SplitString(localIp, ".");
	if(strArr.Length > 3)
	{
		endPoint = strArr[3].ToInt();
	}
	strArr.Length = 0;

	return endPoint;
}
//---------------------------------------------------------------------------

bool __fastcall TUtilHelper::OpenSharedHandle(char **shMem, char* mappingName)
{
//	MapHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, LPCTSTR(mappingName) );
//
//	if(!MapHandle)
//	{
//		MapHandle = CreateFileMapping( (void *) 0xFFFFFFFF,	//공유할 IO맵 핸들
//										NULL,               //보안속성
//										PAGE_READWRITE,		//사용할 맵파일 속성
//										0,					//자료의 상위사이즈
//										MEM1_Size,				//자료의 하위사이즈
//										LPCTSTR(mappingName));
//
//	}
//	else
//	{
//		Button1->Enabled = false;
//		Button2->Enabled = true;
//	}
//
//	if(MapHandle)
//	{
//
//		*shMem = (char *)MapViewOfFile (MapHandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
//
//		Button1->Enabled = false;
//		Button2->Enabled = true;
//
//		return true;
//
//	}
//	else
//	{
//        return false;
//    }

    return false;
}
//---------------------------------------------------------------------------

void __fastcall TUtilHelper::CloseSharedHandle(char *shMem)
{
	#if defined(_PLAT_MSWINDOWS)
	if(MapHandle)
	{
		UnmapViewOfFile(shMem);
		CloseHandle(MapHandle);

	}
	#endif
}
//---------------------------------------------------------------------------

UTF8String __fastcall TUtilHelper::GetPairToString(UTF8String strJson, UTF8String pair)
{
	#if defined(_PLAT_MSWINDOWS)
    Json::Reader jsonReader;
	Json::Value jsonVal;
	if (!jsonReader.parse(strJson.c_str(), jsonVal))
	{
        return "error";
	}
	else
	{
//        jsonReader->Free();
	}

	UTF8String return_value;
	if (!pair.IsEmpty()) {
		return_value = jsonVal[pair.c_str()].asCString();
	}
	return return_value;

	#else
    return "";
	#endif
}
//---------------------------------------------------------------------------

UTF8String __fastcall TUtilHelper::GetPairToString(UTF8String strJson, UTF8String pair, UTF8String pair2)
{
	#if defined(_PLAT_MSWINDOWS)
    Json::Reader jsonReader;
	Json::Value jsonVal;
	if (!jsonReader.parse(strJson.c_str(), jsonVal))
	{
        return "error";
	}

	UTF8String return_value;
	if (!pair.IsEmpty() && !pair2.IsEmpty()) {
        return_value = jsonVal[pair.c_str()][pair2.c_str()].asCString();
	}

    return return_value;
	#else
    return "";
	#endif
}
//---------------------------------------------------------------------------

int __fastcall TUtilHelper::GetPairToInt(UTF8String strJson, UTF8String pair)
{
	#if defined(_PLAT_MSWINDOWS)
    Json::Reader jsonReader;
	Json::Value jsonVal;
	if (!jsonReader.parse(strJson.c_str(), jsonVal))
	{
        return -1;
	}

	int scalar;
	if (!pair.IsEmpty()) {
		scalar = jsonVal[pair.c_str()].asInt();
	}
    return scalar;
	#else
    return -1;
	#endif
}
//---------------------------------------------------------------------------

int __fastcall TUtilHelper::GetPairToInt(UTF8String strJson, UTF8String pair, UTF8String pair2)
{
	#if defined(_PLAT_MSWINDOWS)
    Json::Reader jsonReader;
	Json::Value jsonVal;
	if (!jsonReader.parse(strJson.c_str(), jsonVal))
	{
        return -1;
	}

	int scalar;
	if (!pair.IsEmpty() && !pair2.IsEmpty()) {
        scalar = jsonVal[pair.c_str()][pair2.c_str()].asInt();
	}

    return scalar;
	#else
    return -1;
	#endif
}
//---------------------------------------------------------------------------
String __fastcall TUtilHelper::CreateGuid()
{
	String sGuid;
	TGUID guid;
	if (CreateGUID(guid) == 0)
	{
		sGuid = sGuid.sprintf(L"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
	}
	return sGuid;
}
//---------------------------------------------------------------------------
