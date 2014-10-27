#pragma once

DWORD MyPow(DWORD x, DWORD y);
DWORD CharToDword(TCHAR* start, DWORD length);
BOOL baidu_download(CString dfile, CString token, CString fname,DWORD *process);
BOOL baidu_upload(CString sfile, CString token, CString fname,DWORD *process);