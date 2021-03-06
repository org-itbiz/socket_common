//---------------------------------------------------------------------------

#ifndef iotc_helperH
#define iotc_helperH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
#include <System.StrUtils.hpp>
#include <System.DateUtils.hpp>
#include <System.Types.hpp>

//---------------------------------------------------------------------------

#if defined(_PLAT_ANDROID)
//_PLAT_MSWINDOWS
#endif
#if defined(_PLAT_IOS)
//_PLAT_IOS
#else
#if defined(_PLAT_MACOS)
//_PLAT_MACOS
#endif
#endif
#if defined(_PLAT_MSWINDOWS)
//_PLAT_MSWINDOWS
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
class TIotcHelper: public System::TObject {
  private:

	#if defined(_PLAT_MSWINDOWS)
	HANDLE MapHandle;
	#endif
  public:
	bool __fastcall OpenSharedHandle(char **shMem, char* mappingName);
	void __fastcall CloseSharedHandle(char *shMem);

	String __fastcall DateTimeToStrFormatFunc(TDateTime dtime);
	char * __fastcall GetLocalIP();
//	String __fastcall GetComputerName(AnsiString localIp);
//	String __fastcall GetIpByDomainName(char *szHost);
//	bool __fastcall GetIpByDomainName2(char *szHost, char szIp[10][256], int *nCount);
//	String __fastcall GetInternetIP(String szHost);
//	int __fastcall GetIPAddressEndPoint(AnsiString localIp);

	__fastcall TIotcHelper();
	__fastcall virtual ~TIotcHelper();
};
//---------------------------------------------------------------------------
extern PACKAGE TIotcHelper *IotcHelper;
//---------------------------------------------------------------------------

#endif
