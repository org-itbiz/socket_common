//---------------------------------------------------------------------------

#pragma hdrstop

#include "iotc_helper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TIotcHelper *IotcHelper;

//---------------------------------------------------------------------------

__fastcall TIotcHelper::TIotcHelper()
{
//
}
//---------------------------------------------------------------------------

__fastcall TIotcHelper::~TIotcHelper()
{
//
}
//---------------------------------------------------------------------------

String __fastcall TIotcHelper::DateTimeToStrFormatFunc(TDateTime dtime)
{
	return dtime.FormatString("yyyymmddhhnn");
}
//---------------------------------------------------------------------------

char * __fastcall TIotcHelper::GetLocalIP()
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
    ip = "";
	#endif
	return ip;
}
//---------------------------------------------------------------------------