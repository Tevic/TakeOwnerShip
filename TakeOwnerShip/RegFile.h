/*///////////////////////本类是操作注册表使用
有以下几个功能:
1.直接添加启动项；
2.直接删除启动项;
注意这两个功能必须使用不带参数对象初始化;

对大众函数进行操作必须使用
带参初始化其中是注册表指向和注册表子项
///////////////////
*/
#pragma once
#include"windows.h"
#include"iostream"
#include"vector"
#include"string"
using namespace std;
#ifdef UNICODE
 typedef basic_string< wchar_t > mstring; 
#else
 typedef basic_string< char > mstring;
#endif
typedef struct reg
{
	mstring strValue;
	SYSTEMTIME ftime;
}KeyData;

typedef struct value
{
	mstring strName;
	mstring strValue;
	DWORD nType;
}ValueData;

////////////////////////
typedef vector<KeyData> VKeyData;
typedef vector<KeyData>::iterator VKeyDatai;
typedef vector<ValueData> VValueData;
typedef vector<ValueData>::iterator VValueDatai;
/////////////////
class CRegFile
{
public:
	CRegFile(void);	/////////////只提供给启动项使用
   /*A handle to an open registry key
   it can be one of the following predefined keys: 
   HKEY_CLASSES_ROOT 
   HKEY_CURRENT_CONFIG 
   HKEY_CURRENT_USER 
   HKEY_LOCAL_MACHINE 
   HKEY_USERS 
   */
	CRegFile(HKEY hKey,TCHAR*hSubKey=NULL);/////////////提供给任何键
	CRegFile(HKEY hKey,mstring& hSubKey);
private:
	HKEY m_hKey;
	TCHAR* m_hSubKey;
	HKEY hKey;//////////////打开后句柄
//	TCHAR*pEnumValueBuf;//////////枚举键值字符串
//	TCHAR*pEnumRegBuf;////////////枚举子键字符串
private:
bool OpenKeyReg();
bool CloseKeyReg();
public:

bool CreateKeyReg();
bool DeleteKeyReg();
bool IsExistKeyReg();
bool SetValueReg(TCHAR* lpData,TCHAR* lpValueName=NULL, DWORD dwType=REG_SZ);
bool SetValueReg(mstring& lpData,mstring& lpValueName, DWORD dwType=REG_SZ);
bool QueryValueReg(mstring& lpData,TCHAR* lpValueName=NULL,DWORD*dwType=NULL);
bool QueryValueReg(mstring& lpData,mstring& lpValueName,DWORD* dwType);
bool DeleteValueReg(TCHAR* lpValueName=NULL);
bool DeleteValueReg(mstring& lpValueName);
bool IsExistValueReg(TCHAR* lpValueName=NULL);
bool IsExistValueReg(mstring& lpValueName);
bool EnumAllKeyReg(vector<KeyData>&  stData);
bool EnumAllValueReg(vector<ValueData>& stData);
//////////////////启动项操作函数
bool AddRunValueReg(TCHAR* lpData,TCHAR* lpValueName=NULL, DWORD dwType=REG_SZ);
bool AddRunValueReg(mstring& lpData,mstring& lpValueName, DWORD dwType=REG_SZ);
bool DeleteRunValueReg(TCHAR* lpValueName=NULL);
bool DeleteRunValueReg(mstring& lpValueName);
bool IsExistRunValue(TCHAR* lpValueName=NULL);
bool IsExistRunValue(mstring& lpValueName);
bool EnumRunValueReg(vector<ValueData>& stData);
bool QueryRunValueReg(mstring& lpData,TCHAR* lpValueName=NULL,DWORD*dwType=NULL);
bool QueryRunValueReg(mstring& lpData,mstring& lpValueName,DWORD* dwType);
	~CRegFile(void);
private:
void InitRun(); 
void EndRun();
};

