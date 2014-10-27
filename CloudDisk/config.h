//  CItem��������һ���ļ�����tokne
//��Ա CString *token ����token
//		CString filename �����ļ���
//		int piecenum ����token��Ŀ
//		CItem * pnextfile ָ����һ���ļ�
//�ɵ��ó�Ա����:
// int  appendToken(CString newtoken) �����token������Ŀǰ��touken��Ŀ��
// bool saveitem(LPCTSTR lpszfilename/*�ļ�·��*/,int mode=0/*���淽ʽ 0��ʾ׷�� 1��ʾ�½�*/) ����һ���ļ�����token�������ļ��е�һ�У���ʽΪ�� �ļ��� token��Ŀ token1 token2...


class CItem
{
public:
	int piecenum;//��Ƭ��Ŀ
	CString *token;//token��
	CString filename;//�ļ���
	CItem * pnextfile;
	int  appendToken(CString newtoken);
	CItem()
	{
		pnextfile = NULL;
		token = NULL;
		piecenum = 0;
	}
	~CItem()
	{
		if (token != NULL)
		{
			delete[]token;
			token = NULL;
		}
	}
};


//CLogfile �����������������ļ�����CItem ���� filehead������ÿһ��
// ��Ա���� 
//long loadlog(LPCTSTR lpszfilename/*�ļ�·��*/) ���������ļ�,���ؼ����ļ���
//long getfilenum(void) ���ض����ļ���Ŀ
//CItem * getAT(int index) ��ȡ�� index���ļ���Ϣ��ʧ�ܷ��� NULL��index��1��ʼ�����Ǵ�0
//long appendFile(CItem * item) ���µ��ļ���Ϣ���������
//bool  savelog(LPCTSTR lpszfilename/*�ļ�·��*/,int mode=0/*���淽ʽ 0��ʾ׷�� 1��ʾ�½�*/)���������ļ����õ�ָ��Ŀ¼
//CItem *CLogfile::search(CString filename)����Ŀ¼���ض��ļ����ɹ��Ż�CItem *ָ�룬ʧ�ܷ���NULL
class CLogfile :public CFile
{
public:
	CLogfile(void)
	{
		filenum = 0;
		filehead = NULL;
		tokennum = 0;
		tokenmax = 0;
		filehead = new CItem;
		ZeroMemory(filehead, sizeof(CItem));
		username = L"";
	}
	bool addtoken(LPCTSTR token);
	bool set_user_name(LPCTSTR username);
	long loadlog(LPCTSTR lpszfilename);
	long getfilenum(void);
	CItem * getAT(int index);
	long appendFile(CItem * item);
	bool  savelog(LPCTSTR lpszfilename, int mode = 0);
	CItem *CLogfile::search(CString filename);
	~CLogfile(void)
	{
		CItem* filelist = filehead;
		while (filelist != NULL)
		{
			filehead = filelist;
			filelist = filelist->pnextfile;
			delete filehead;
		}
	}
public:
	long filenum;
	long tokennum;
	long tokenmax;
	CString *token;
	CString username;
	CItem *filehead;
};



class TransFile
{
public:
	TransFile();
	CString filename;
	DWORD childprocess[20];
	DWORD childnum;
	BOOL completed;
	BOOL saved;
	BOOL error;
	
	TransFile *next;
private:

};



class TransList
{
public:
	TransList();
	~TransList();

	TransFile *head;
	int filenum;
	void addfile(TransFile *file);

private:

};
