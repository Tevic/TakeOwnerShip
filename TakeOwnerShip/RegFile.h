/*///////////////////////�����ǲ���ע���ʹ��
�����¼�������:
1.ֱ����������
2.ֱ��ɾ��������;
ע�����������ܱ���ʹ�ò������������ʼ��;

�Դ��ں������в�������ʹ��
���γ�ʼ��������ע���ָ���ע�������
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
	CRegFile(void);	/////////////ֻ�ṩ��������ʹ��
   /*A handle to an open registry key
   it can be one of the following predefined keys: 
   HKEY_CLASSES_ROOT 
   HKEY_CURRENT_CONFIG 
   HKEY_CURRENT_USER 
   HKEY_LOCAL_MACHINE 
   HKEY_USERS 
   */
	CRegFile(HKEY hKey,TCHAR*hSubKey=NULL);/////////////�ṩ���κμ�
	CRegFile(HKEY hKey,mstring& hSubKey);
private:
	HKEY m_hKey;
	TCHAR* m_hSubKey;
	HKEY hKey;//////////////�򿪺���
//	TCHAR*pEnumValueBuf;//////////ö�ټ�ֵ�ַ���
//	TCHAR*pEnumRegBuf;////////////ö���Ӽ��ַ���
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
//////////////////�������������
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

