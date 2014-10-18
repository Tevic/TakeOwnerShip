#include "StdAfx.h"
#include "RegFile.h"


///��ָ����ֵ·��
////��������:��
CRegFile::CRegFile(void)
{
	this->m_hKey=NULL;
	this->m_hSubKey=NULL;
	this->hKey=NULL;
}

////////��ʼ��ָ����ֵ·��
////////��������HKEY TCHAR
CRegFile::CRegFile(HKEY hKey,TCHAR*hSubKey)
{
	this->m_hKey=hKey;
	this->m_hSubKey=hSubKey;
	this->hKey=NULL;
}
/////////��ʼ��ָ����ֵ·��
////////��������HKEY mstring
CRegFile::CRegFile(HKEY hKey,mstring& hSubKey)
{
	this->m_hKey=hKey;
	this->m_hSubKey=((LPTSTR)(hSubKey.c_str()));
	this->hKey=NULL;
}
///////////�����Ӽ�
bool  CRegFile::CreateKeyReg()
{
LONG ret=NULL;
if(NULL==this->m_hKey||NULL==this->m_hSubKey)
{
	return false;
}
else
{
	ret=::RegCreateKeyEx(this->m_hKey,this->m_hSubKey,0,NULL,REG_OPTION_NON_VOLATILE
					 ,KEY_ALL_ACCESS,NULL,&this->hKey,NULL);
if(ERROR_SUCCESS==ret)
{
	this->CloseKeyReg();
	return true;
}
else
{
	
	return false;
}
}
}
/////////////////ɾ���Ӽ�
bool CRegFile::DeleteKeyReg()
{
	if(ERROR_SUCCESS!=::RegDeleteKey(this->m_hKey,this->m_hSubKey))
	{
		return false;
	}
return true;
}
/////////////�򿪼�
bool CRegFile::OpenKeyReg()
{
	if(NULL==this->m_hKey&&NULL==this->m_hSubKey)
	{
		return false;
     }
	else if(NULL==this->m_hSubKey||TEXT("")==this->m_hSubKey)
	{
		this->hKey=this->m_hKey;
	return true;
	}
	else
	{
	if(ERROR_SUCCESS==::RegOpenKeyEx(this->m_hKey,this->m_hSubKey,0,KEY_ALL_ACCESS,&this->hKey))
		{
			return true;
		}
	}
return false;
}
////////////�رռ�	
bool CRegFile::CloseKeyReg()
{
	if(NULL==this->hKey)
		return false;
	if(ERROR_SUCCESS!=::RegCloseKey(this->hKey))
		return false;
	this->hKey=NULL;
	return true;
}
//////////���ü�ֵ
/////////������TCHAR�ε�
bool CRegFile::SetValueReg(TCHAR* lpData,TCHAR* lpValueName,DWORD dwType)
{
	if(!this->OpenKeyReg())
		return false;
	DWORD cbData=0;
	switch(dwType)
	{
	case REG_SZ:
cbData=lstrlen(lpData)+1;
break;
	case REG_DWORD:
cbData=4;
break;
	case REG_MULTI_SZ:
cbData=lstrlen(lpData)+2;
break;
	default:
		cbData=lstrlen(lpData)+1;
	}
	if(ERROR_SUCCESS!=::RegSetValueEx(this->hKey,lpValueName,0,dwType,(const BYTE*)lpData,cbData))
	{
	this->CloseKeyReg();
	return false;
	}
	return this->CloseKeyReg();
}
//////////���ü�ֵ
/////////������mstring�ε�
bool CRegFile::SetValueReg(mstring& lpData,mstring& lpValueName,DWORD dwType)
{
	if(!this->OpenKeyReg())
		return false;
	DWORD cbData=0;
	switch(dwType)
	{
	case REG_SZ:
		cbData=lstrlen(lpData.c_str())+1;
break;
	case REG_DWORD:
cbData=4;
break;
	case REG_MULTI_SZ:
		cbData=lstrlen(lpData.c_str())+2;
break;
	default:
		cbData=lstrlen(lpData.c_str())+1;
	}

	if(ERROR_SUCCESS!=::RegSetValueEx(this->hKey,(LPTSTR)(lpValueName.c_str()),0,dwType,((const BYTE*)(lpData.c_str())),cbData))
	{
		this->CloseKeyReg();
		return false;
	}
	return this->CloseKeyReg();

}
//////////��ȡ��ֵ
////////��������mstring TCAHR
bool CRegFile::QueryValueReg(mstring& lpData/*��ȡ��ֵ*/,TCHAR* lpValueName/*ֵ������*/,DWORD* dwType)
{

	DWORD cbData;
	if(!this->OpenKeyReg())
		return false;
	if(ERROR_SUCCESS!=::RegQueryValueEx(this->hKey,(LPCTSTR)lpValueName,0,dwType,NULL,&cbData))
	{
		this->CloseKeyReg();
	return false;
	}

		 TCHAR*pBuf=new TCHAR[cbData];
		if(ERROR_SUCCESS!=::RegQueryValueEx(this->hKey,(LPCTSTR)lpValueName,0,dwType,(LPBYTE)pBuf,&cbData))
		{
		delete[] pBuf;
		pBuf=NULL;
		this->CloseKeyReg();
		return false;
	}

		lpData=pBuf;
		delete[] pBuf;
		pBuf=NULL;
		return this->CloseKeyReg();

}

//////////��ȡ��ֵ
////////��������mstring mstring
bool CRegFile::QueryValueReg(mstring& lpData/*��ȡ��ֵ*/,mstring& lpValueName/*ֵ������*/,DWORD* dwType)
{

	DWORD cbData;
	if(!this->OpenKeyReg())
		return false;
	if(ERROR_SUCCESS!=::RegQueryValueEx(this->hKey,(LPCTSTR)(lpValueName.c_str()),0,dwType,NULL,&cbData))
	{
		this->CloseKeyReg();
		return false;
	}


		 TCHAR*pBuf=new TCHAR[cbData];
		 if(ERROR_SUCCESS !=::RegQueryValueEx(this->hKey,(LPCTSTR)(lpValueName.c_str()),0,dwType,(LPBYTE)pBuf,&cbData))
		{
	delete[] pBuf;
		pBuf=NULL;
		this->CloseKeyReg();
		return false;
	}

		lpData=pBuf;
		delete[] pBuf;
		pBuf=NULL;
		return this->CloseKeyReg();
}
	
///////////ɾ����ֵ
/////////�������ͣ�TCHAR 
bool CRegFile::DeleteValueReg(TCHAR* lpValueName)
{
	if(!this->OpenKeyReg())
		return false;
	if(ERROR_SUCCESS!=::RegDeleteValue(this->hKey,(LPCTSTR)lpValueName))
	{
		this->CloseKeyReg();
		return false;
	}
	return this->CloseKeyReg();
}
bool CRegFile::DeleteValueReg(mstring& lpValueName)
{
if(!this->OpenKeyReg())
		return false;
if(ERROR_SUCCESS==::RegDeleteValue(this->hKey,(LPCTSTR)(lpValueName.c_str())))
{
		this->CloseKeyReg();
		return false;
	}
	return this->CloseKeyReg();
}
//////////�Ƿ����ĳֵ
///////�������ͣ�TCAHR
bool CRegFile::IsExistValueReg(TCHAR* lpValueName)
{
	DWORD cbData;
	if(!this->OpenKeyReg())
		return false;
		if(ERROR_SUCCESS!=::RegQueryValueEx(this->hKey,(LPCTSTR)lpValueName,0,NULL,NULL,&cbData))
		{
			this->CloseKeyReg();
		
		return false;
		}
		return this->CloseKeyReg();
}

//////////�Ƿ����ĳֵ
///////�������ͣ�mstring
bool CRegFile::IsExistValueReg(mstring& lpValueName)
{
	DWORD cbData;
	if(!this->OpenKeyReg())
		return false;
	if(ERROR_SUCCESS!=::RegQueryValueEx(this->hKey,(LPCTSTR)(lpValueName.c_str()),0,NULL,NULL,&cbData))
			{
			this->CloseKeyReg();
		
		return false;
		}
		return this->CloseKeyReg();
}


///////////�Ƿ���ڼ�
////////�������ͣ���
bool CRegFile::IsExistKeyReg()
{
	if(this->OpenKeyReg())
	{
		this->CloseKeyReg();
		return true;
	}
	return false;
}



/////////////ö�ټ��µ�ֵ
////////////////��������vector<KeyData>&  stData
bool CRegFile::EnumAllKeyReg(vector<KeyData>&  stData)
{
if(!this->OpenKeyReg())
		return false;


DWORD lpcSubKeys ,lpcMaxSubKeyLen;
if(ERROR_SUCCESS!=::RegQueryInfoKey(this->hKey,NULL,NULL,0,&lpcSubKeys,&lpcMaxSubKeyLen,NULL,NULL,NULL,NULL,NULL,NULL))
{
	this->CloseKeyReg();
return false;
}
//////////////
		
		FILETIME f;
	 DWORD cbBuf=lpcMaxSubKeyLen+1;
KeyData std;
TCHAR*pBuf=new TCHAR[lpcMaxSubKeyLen+1];
for(DWORD index=0L;index<lpcSubKeys;index++)
{
	cbBuf=lpcMaxSubKeyLen+1;
	if(ERROR_SUCCESS!=::RegEnumKeyEx(this->hKey,index,pBuf,&cbBuf,0,NULL,NULL,&f))
{
	delete[] pBuf;
	this->CloseKeyReg();
return false;
}
///////////////////////
	SYSTEMTIME sf;
	::FileTimeToSystemTime(&f,&sf);
	std.strValue=pBuf;
	std.ftime=sf;
	stData.push_back(std);
}
delete[] pBuf;
return this->CloseKeyReg();
}

//////////////////////ö������ֵ
/////////���� vector<ValueData>
bool CRegFile::EnumAllValueReg(vector<ValueData>&  stData)
{
	if(!this->OpenKeyReg())
		return false;

DWORD lpcValues ,lpcMaxValueLen ,lpcMaxValueNameLen;
DWORD nType;
if(ERROR_SUCCESS!=::RegQueryInfoKey(this->hKey,NULL,NULL,0,NULL,NULL,NULL,&lpcValues,&lpcMaxValueNameLen,&lpcMaxValueLen,NULL,NULL))
{
	this->CloseKeyReg();
return false;
}
//////////////
		
		TCHAR*pNameBuf=new TCHAR[lpcMaxValueNameLen+1];
		TCHAR*pValueBuf=new TCHAR[lpcMaxValueLen+1];
		FILETIME f;
		::ZeroMemory(&f,sizeof(FILETIME));
		DWORD cbNameBuf=lpcMaxValueNameLen+1;
		DWORD cbValueBuf=lpcMaxValueLen+1;
ValueData std;
for(DWORD index=0L;index<lpcValues;index++)
{
	cbNameBuf=lpcMaxValueNameLen+1;
	cbValueBuf=lpcMaxValueLen+1;
if(ERROR_SUCCESS!=::RegEnumValue(this->hKey,index,(LPTSTR)pNameBuf,&cbNameBuf,0,&nType,(LPBYTE)pValueBuf,&cbValueBuf))
{
	delete[] pValueBuf;
delete[] pNameBuf;
this->CloseKeyReg();
return false;
}
///////////////////////
std.strValue=pValueBuf;
std.strName=pNameBuf;
std.nType=nType;

stData.push_back(std);
}
delete[] pValueBuf;
delete[] pNameBuf;
return this->CloseKeyReg();
}


//////////////////////////////////
/////////////////////////
/////////////////////
/////////////�����������

////////////////��ʼ��run
////////��������:��
void CRegFile::InitRun()
{
	this->m_hKey=HKEY_CURRENT_USER;
	this->m_hSubKey=TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
}

/////////////����run
///��������:��
void CRegFile::EndRun()
{

	this->m_hKey=NULL;
	this->m_hSubKey=NULL;
	this->hKey=NULL;

}


/////////���������
///////////��������:TCHAR TCHAR DWORD
bool CRegFile::AddRunValueReg(TCHAR*lpData,TCHAR*lpValueName,DWORD dwType)
{
	this->InitRun();
		if(! this->SetValueReg(lpData,lpValueName))
	return false;
	 this->EndRun();
	 return true;

}
/////////���������
///////////��������:msring mstring DWORD 
bool CRegFile::AddRunValueReg(mstring &lpData, mstring &lpValueName, DWORD dwType)
{
	this->InitRun();
		if(! this->SetValueReg(lpData,lpValueName))
return false;
	 this->EndRun();
	 return true;
}
/////////ɾ��������
//////�������ͣ�TCHAR
bool CRegFile::DeleteRunValueReg(TCHAR* lpValueName)
{
	this->InitRun();
if(!this->DeleteValueReg(lpValueName))
return false;
	 this->EndRun();
	 return true;
}
////////ɾ��������
//////�������ͣ�mstring
bool CRegFile::DeleteRunValueReg(mstring& lpValueName)
{
	this->InitRun();
if(!this->DeleteValueReg(lpValueName))
return false;
	 this->EndRun();
	 return true;
}
/////////////////�ж��������Ƿ����
////////////��������:TCHAR
bool CRegFile::IsExistRunValue(TCHAR *lpValueName)
{
	this->InitRun();
	if(!this->IsExistValueReg(lpValueName))
return false;
	 this->EndRun();
	 return true;
}

/////////////////�ж��������Ƿ����
/////��������:mstring
bool CRegFile::IsExistRunValue(mstring& lpValueName)
{
	this->InitRun();
	if(!this->IsExistValueReg(lpValueName))
	return false;
	 this->EndRun();
	 return true;
}
/////////ö��������
/////////��������vector<ValueData>
bool CRegFile::EnumRunValueReg(vector<ValueData>& stData)
{
	this->InitRun();
	if(!this->EnumAllValueReg(stData))
	return false;
	 this->EndRun();
	 return true;
}
/////////��ȡָ����ֵ��ֵ
//////////�������ͣ�mstring TCHAR DWORD
bool CRegFile::QueryRunValueReg(mstring& lpData,TCHAR* lpValueName,DWORD*dwType)
{
this->InitRun();
if(!this->QueryValueReg(lpData,lpValueName,dwType))
	return false;
	 this->EndRun();
	 return true;
}
/////////��ȡָ����ֵ��ֵ
//////////�������ͣ�mstring mstring DWORD
bool CRegFile::QueryRunValueReg(mstring& lpData,mstring& lpValueName,DWORD* dwType)
{
	this->InitRun();
	if(!this->QueryValueReg(lpData,lpValueName,dwType))
	return false;
	 this->EndRun();
	 return true;
}
///////////��������
CRegFile::~CRegFile(void)
{
}