#include "stdafx.h"
#include "config.h"




//���token,�ɹ�����piecenum�����򷵻�0��
int  CItem::appendToken(CString newtoken)
{
	if (token == NULL)
	{
		token = new CString[1];
		if (token == NULL)
		{
			return 0;
		}
		*token = newtoken;
		piecenum++;
		return  piecenum;
	}
	CString *token1 = NULL;
	CString *token2 = NULL;
	piecenum++;
	token1 = new CString[piecenum];
	int i;
	for (i = 0; i < piecenum - 1; i++)
	{
		token1[i] = token[i];
	}
	token1[i] = newtoken;
	token2 = token;
	token = token1;
	delete[] token2;
	return piecenum;

}




//�������ã�����ɹ������򷵻������ļ����������򷵻�0��
long CLogfile::loadlog(LPCTSTR lpszfilename)
{
	CStdioFile fin;
	fin.Open(lpszfilename, modeRead);
	if (!fin)
	{
		return 0;
	}
	//��ʼһ��һ�ж�ȡ�ļ�
	CString s;
	int length;
	CItem *filelist1 = NULL;
	CItem *filelist2 = NULL;
	filehead = new CItem;
	if (!filehead)
	{
		return 0;
	}
	filelist2 = filehead;
	fin.ReadString(s);
	username = s;
	while (fin.ReadString(s))
	{
		filenum++;//�ļ�����1��
		filelist1 = new CItem;
		if (!filelist1)
		{
			return 0;
		}
		length = s.GetLength();
		int k = 0;
		//��ȡ�ļ���
		while (k < length&&s.GetAt(k) != _T(' '))
		{
			k++;
		}
		filelist1->filename = s.Left(k);

		//��ȡ�ļ��ֿ���Ŀ
		k = k + 1;
		filelist1->piecenum = _wtoi(s.Mid(k, 1));
		k = k + 1;
		if (filelist1->piecenum == 0)
		{
			return 0;
		}

		//��ȡÿ���ֿ��token
		if ((filelist1->token = new CString[filelist1->piecenum]) == NULL)
		{
			return 0;
		}
		int j;
		for (int i = 0; i < filelist1->piecenum; i++)
		{
			j = k + 1;
			while (++k < length&&s.GetAt(k) != _T(' '));
			filelist1->token[i] = s.Mid(j, k - j);
		}

		filelist2->pnextfile = filelist1;
		filelist2 = filelist1;
	}
	fin.Close();
	if (filenum != 0)
	{
		CItem *tmp = filehead;
		CString *tokens = tmp->pnextfile->token;
		int i = tmp->pnextfile->piecenum;
		for (int j = 0; j < i; j++)
		{
			addtoken(tokens[j]);
		}
	}
	return filenum;
}


long CLogfile::getfilenum(void)
{
	return filenum;
}

bool CLogfile::set_user_name(LPCTSTR username)
{
	this->username = username;
	return TRUE;
}


//��ȡfilelist�е�index��fileָ�룬ʧ�ܷ���NULL��
CItem*  CLogfile::getAT(int index)
{
	if (filehead == NULL || index>filenum)
	{
		return  NULL;
	}
	CItem* filelist = filehead;
	for (int i = 0; i < index; i++)
	{
		filelist = filelist->pnextfile;
	}
	return filelist;
}


//�������Ŀ
long CLogfile::appendFile(CItem * item)
{
	CItem * filelist = new CItem;
	filelist->filename = item->filename;
	filelist->piecenum = item->piecenum;
	filelist->token = new CString[item->piecenum];
	for (int i = 0; i < item->piecenum; ++i)
	{
		filelist->token[i] = item->token[i];
	}
	if (filenum == 0)
	{
		filehead = new CItem;
		filehead->pnextfile = filelist;
		filenum++;
		return filenum;
	}

	CItem* filelist1 = filehead;
	while (filelist1->pnextfile != NULL)
	{
		filelist1 = filelist1->pnextfile;
	}
	filelist1->pnextfile = filelist;

	filenum++;
	return filenum;
}


//�����ļ�Ŀ¼
bool  CLogfile::savelog(LPCTSTR lpszfilename, int mode)
{
	CStdioFile fout;
	if (mode == 0)
	{
		fout.Open(lpszfilename, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	}
	else if (mode == 1)
	{
		fout.Open(lpszfilename, CFile::modeCreate | CFile::modeWrite);
	}
	else
	{
		return false;
	}
	if (!fout)
	{
		return false;
	}
	CString s;
	if (filehead == NULL || filenum == 0)
	{
		return false;
	}
	s.Format(username + L"\n");
	fout.WriteString(s);
	CItem *filelist = filehead->pnextfile;
	while (filelist != NULL)
	{
		s.Format(_T("%s %d"), filelist->filename, filelist->piecenum);
		for (int i = 0; i < filelist->piecenum; i++)
		{
			s.Format(s + _T(" %s"), filelist->token[i]);
		}
		s.Format(s + _T("\n"));
		fout.SeekToEnd();
		fout.WriteString(s);
		filelist = filelist->pnextfile;
	}
	fout.Close();
	return true;

}

//����Ŀ¼���ض��ļ����ɹ��Ż�CItem *ָ�룬ʧ�ܷ���NULL
CItem *CLogfile::search(CString filename)
{
	CItem *filelist1 = filehead->pnextfile;
	while (filelist1 != NULL)
	{
		if (filelist1->filename == filename)
		{
			return filelist1;
		}
		filelist1 = filelist1->pnextfile;
	}
	return NULL;
}

bool CLogfile::addtoken(LPCTSTR token)
{
	if (tokenmax <= tokennum)
	{
		CString *tmp = new CString[tokennum + 5];
		if (!tmp)
			return FALSE;
		for (int i = 0; i < tokennum; i++)
		{
			tmp[i] = this->token[i];
		}
		tokenmax += 5;
		if (!this->token)
			delete[] this->token;
		this->token = tmp;
	}
	this->token[tokennum].Format(token);
	tokennum++;
	return TRUE;
}


TransFile::TransFile()
{
	saved = FALSE;
	filename = L"";
	completed = FALSE;
	childnum = 0;
	error = 0;
	next = NULL;
	ZeroMemory(childprocess, 20 * sizeof(DWORD));
}


TransList::TransList()
{
	filenum = 0;
	head = new TransFile;
	head->completed = TRUE;
}

TransList::~TransList()
{
	TransFile *tmp = head->next;
	TransFile *next = NULL;
	while (tmp)
	{
		next = tmp->next;
		delete tmp;
		tmp = next;
	}
	delete head;
}

void TransList::addfile(TransFile *file)
{
	if (!file)
		return;
	TransFile *tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = file;
	filenum++;
}