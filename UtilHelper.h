//---------------------------------------------------------------------------

#ifndef UtilHelperH
#define UtilHelperH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
#include <System.StrUtils.hpp>
#include <System.DateUtils.hpp>
#include <System.Types.hpp>
//#include <IdBaseComponent.hpp>
//#include <IdComponent.hpp>
//#include <IdGlobal.hpp>
//#include <IdSocketHandle.hpp>
//#include <IdUDPBase.hpp>
//#include <IdUDPClient.hpp>
//#include <IdHTTP.hpp>
//#include <IdTCPClient.hpp>
//#include <IdTCPConnection.hpp>

#if defined(_PLAT_IOS)
//_PLAT_IOS
#else
#if defined(_PLAT_MACOS)
//_PLAT_MACOS
#endif
#endif

#ifdef __ANDROID_API__
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Net.hpp>
#include <Androidapi.Helpers.hpp>
#include <Androidapi.JNIBridge.hpp>

#elif _WIN32
#include <Winapi.IpHlpApi.hpp>
#endif


//---------------------------------------------------------------------------
#define ENUM_CLASS_DECLARE(cls_type, enum_type)  \
	public: enum_type  m_val;  \
	public: \
	cls_type ( const enum_type& s): m_val(s) {} ;  \
	bool operator == ( const enum_type& cs ) {   \
	  if ( m_val == m_val ) return true; \
	  else return false;  }    \
	operator enum_type() { return  m_val; };

class DeviceState {
public:
	enum _deviceState {
		stateOpen
		, stateClosed
		, stateSuspended
	};
	ENUM_CLASS_DECLARE(DeviceState, _deviceState)
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class TUtilHelper: public System::TObject {
  private:

	#if defined(_PLAT_MSWINDOWS)
	HANDLE MapHandle;
    #endif
  public:
	bool __fastcall OpenSharedHandle(char **shMem, char* mappingName);
	void __fastcall CloseSharedHandle(char *shMem);
//	void __fastcall Initialize();
//	TCustomDef __fastcall GetCustomDefFromIndex(int index);
//	int __fastcall GetCustomDefLen();
	String __fastcall DateTimeToStrFormatFunc(TDateTime dtime);
	String __fastcall GetLocalIP();
	String __fastcall GetComputerName(AnsiString localIp);
	String __fastcall GetIpByDomainName(char *szHost);
	bool __fastcall GetIpByDomainName2(char *szHost, char szIp[10][256], int *nCount);
	String __fastcall GetMacAddress();
	String __fastcall GetInternetIP(String sDomain);
	int __fastcall GetIPAddressEndPoint(AnsiString localIp);

	UTF8String __fastcall GetPairToString(UTF8String strJson, UTF8String pair);
	UTF8String __fastcall GetPairToString(UTF8String strJson, UTF8String pair, UTF8String pair2);
	int __fastcall GetPairToInt(UTF8String strJson, UTF8String pair);
	int __fastcall GetPairToInt(UTF8String strJson, UTF8String pair, UTF8String pair2);
	String __fastcall CreateGuid();


	__fastcall TUtilHelper();
	__fastcall virtual ~TUtilHelper();
//	__property TCustomError Errors[int index] = { read = GetCustomDefFromIndex };
};
//---------------------------------------------------------------------------
extern PACKAGE TUtilHelper *UtilHelper;
//---------------------------------------------------------------------------
#endif

