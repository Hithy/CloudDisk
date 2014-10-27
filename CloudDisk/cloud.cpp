#include "stdafx.h"
#include "cloud.h"
#include <WinInet.h>
#pragma comment(lib, "wininet.lib")


DWORD MyPow(DWORD x, DWORD y)
{
	DWORD i;
	DWORD re = 1;
	for (i = 0; i < y; i++)
	{
		re *= x;
	}
	return re;
}

DWORD CharToDword(TCHAR* start, DWORD length)
{
	TCHAR temp;
	DWORD i;
	DWORD re = 0;
	for (i = 0; i < length; i++)
	{
		temp = start[i];
		if ('0' <= temp && '9' >= temp)
		{
			re += ((temp - '0')*MyPow(10, length - i - 1));
		}
		else
		{
			return 0;
		}
	}
	return re;
}

BOOL baidu_download(CString dfile, CString token, CString fname,DWORD *process)
{
	if (dfile == L"")
	{
		MessageBox(NULL,L"文件路径不能为空", 0, 0);
		return FALSE;
	}
	if (token == L"")
	{
		MessageBox(NULL, L"token不能为空", 0, 0);
		return FALSE;
	}
	if (fname == L"")
	{
		MessageBox(NULL, L"文件名不能为空", 0, 0);
		return FALSE;
	}
	CString url(L"/rest/2.0/pcs/file?method=download&path=%2Fapps%2Fhitdisk%2F" + fname + L"&access_token=" + token);


	DWORD headlength;
	DWORD FileLength;//文件长度
	TCHAR* szBuff;//缓冲区
	DWORD bfsize = 1024 * 64;//缓冲区大小
	TCHAR* FileBuff;//解析文件长度指针

	BOOL bResult = TRUE;
	HINTERNET hRequest = NULL;
	HINTERNET hConnect = NULL;
	HINTERNET hnet = InternetOpen(TEXT("Test"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	hConnect = InternetConnect(hnet, TEXT("pcs.baidu.com"), 443, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	hRequest = HttpOpenRequest(hConnect, TEXT("GET"), url, NULL, NULL, NULL, INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_NO_UI | INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_RELOAD, 0);

	bResult = HttpSendRequest(hRequest, NULL, 0, NULL, 0);

	//解析文件长度
	DWORD i;
	szBuff = new TCHAR[bfsize];
	headlength = bfsize;
	bResult = HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, szBuff, &headlength, NULL);
	FileBuff = wcsstr(szBuff, L"Content-Length");
	FileBuff += 16;
	for (i = 0;; i++)
	{
		if (FileBuff[i] == '\r')
			break;
	}
	FileLength = CharToDword(FileBuff, i);

	CFile cfile(dfile, CFile::modeWrite | CFile::modeCreate);

	DWORD wbfclength = 0;//缓冲区当前数据长度
	DWORD wbfsize = 1024 * 1024;//缓冲区大小
	char *WriteBuffer = new char[wbfsize];//文件写入缓冲区

	CString show_process;
	DWORD dwBytesAvailable;
	DWORD FileReceived = 0;
	BOOL error = TRUE;
	BOOL cmp = 0;
	while (InternetQueryDataAvailable(hRequest, &dwBytesAvailable, 0, 0))
	{
		DWORD dwBytesRead;
		if (dwBytesAvailable <= bfsize)
		{
			bResult = InternetReadFile(hRequest, szBuff, dwBytesAvailable, &dwBytesRead);
		}
		else
		{
			bResult = InternetReadFile(hRequest, szBuff, bfsize, &dwBytesRead);
		}
		FileReceived += dwBytesRead;

		CopyMemory(WriteBuffer + wbfclength, szBuff, dwBytesRead);
		if (error)
		{
			szBuff[13] = '\0';
			cmp = _strnicmp((char *)szBuff,"{\"error_code\"" , 13);
			if (cmp == 0)
			{
				*process = 100;
				InternetCloseHandle(hRequest);
				InternetCloseHandle(hConnect);
				InternetCloseHandle(hnet);
				cfile.Close();
				cfile.Remove(dfile);
				delete[] szBuff;
				delete[] WriteBuffer;
				return FALSE;
			}
		}
		wbfclength += dwBytesRead;
		if (wbfclength > wbfsize - bfsize)
		{
			cfile.Write(WriteBuffer, wbfclength);
			wbfclength = 0;
		}
		*process = (DWORD)(100 * (double)FileReceived / FileLength);
		if (dwBytesRead == 0)
			break;  // End of File.
	}

	if (wbfclength)
		cfile.Write(WriteBuffer, wbfclength);

	InternetCloseHandle(hRequest);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hnet);
	cfile.Close();
	delete[] szBuff;
	delete[] WriteBuffer;

	return TRUE;
}

BOOL baidu_upload(CString sfile, CString token, CString fname,DWORD *process)
{
	if (sfile == L"")
	{
		MessageBox(NULL, L"文件路径不能为空", 0, 0);
		return FALSE;
	}
	if (token == L"")
	{
		MessageBox(NULL, L"token不能为空", 0, 0);
		return FALSE;
	}
	if (fname == L"")
	{
		MessageBox(NULL, L"文件名不能为空", 0, 0);
		return FALSE;
	}

	CString url(L"/rest/2.0/pcs/file?method=upload&ondup=overwrite&path=%2Fapps%2Fhitdisk%2F" + fname + L"&access_token=" + token);

	DWORD total_length = 0;//上传数据总大小
	DWORD file_length = 0;//上传文件的大小
	//DWORD read_length = 0;//已经从文件读取的大小
	DWORD sent_length = 0;//已经上传的文件的大小

	DWORD sent_bfleng = 0;//当前数据块已上传大小

	DWORD head_length = 0;//数据头大小
	DWORD tail_length = 0;//数据尾大小



	DWORD read_part = 1024 * 1024 * 2;
	DWORD send_part = 1024;

	DWORD read_tmp = 0;//当前从文件读取到缓冲区的大小
	DWORD sent_tmp = 0;//当前发送大小


	CFile cfile(sfile, CFile::modeRead);
	file_length = (DWORD)cfile.GetLength();
	CHAR *send_buffer = new CHAR[read_part];


	HINTERNET hRequest = NULL;
	HINTERNET hConnect = NULL;
	HINTERNET hnet = InternetOpen(fname, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	hConnect = InternetConnect(hnet, L"pcs.baidu.com", 443, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	hRequest = HttpOpenRequest(hConnect, L"POST", url, NULL, NULL, NULL, INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_NO_UI | INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_RELOAD, 0);

	TCHAR ct[] = L"Content-Type: multipart/form-data; boundary=--myself";
	HttpAddRequestHeaders(hRequest, ct, lstrlen(ct), HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);


	CHAR head[] = "----myself\r\nContent-Disposition: form-data; name=\"file\"; filename=\"\"\r\n\r\n";
	CHAR tail[] = "\r\n----myself--\r\n";
	head_length = strlen(head);
	tail_length = strlen(tail);

	total_length = file_length + head_length + tail_length;

	INTERNET_BUFFERS Ibuffer;
	ZeroMemory(&Ibuffer, sizeof(INTERNET_BUFFERS));
	Ibuffer.dwBufferTotal = total_length;
	Ibuffer.dwStructSize = sizeof(INTERNET_BUFFERS);

	HttpSendRequestEx(hRequest, &Ibuffer, NULL, 0, NULL);

	InternetWriteFile(hRequest, head, head_length, &sent_tmp);
	sent_length += sent_tmp;

	while (read_tmp = cfile.Read(send_buffer, read_part))
	{
		sent_bfleng = 0;
		while (sent_bfleng != read_tmp)
		{
			if (read_tmp - sent_bfleng > send_part)
			{
				InternetWriteFile(hRequest, send_buffer + sent_bfleng, send_part, &sent_tmp);
			}
			else
			{
				InternetWriteFile(hRequest, send_buffer + sent_bfleng, read_tmp - sent_bfleng, &sent_tmp);
			}
			if (sent_tmp == 0)
			{
				InternetCloseHandle(hRequest);
				InternetCloseHandle(hConnect);
				InternetCloseHandle(hnet);
				cfile.Close();
				delete[] send_buffer;
				return FALSE;
			}
			sent_bfleng += sent_tmp;
			sent_length += sent_tmp;
			*process = (DWORD)(100 * (double)sent_length / total_length);
		}
	}

	InternetWriteFile(hRequest, tail, tail_length, &sent_tmp);
	sent_length += sent_tmp;
	*process = (DWORD)(100 * (double)sent_length / total_length);

	HttpEndRequest(hRequest, NULL, 0, NULL);
	InternetCloseHandle(hRequest);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hnet);
	cfile.Close();
	delete[] send_buffer;


	return TRUE;

}