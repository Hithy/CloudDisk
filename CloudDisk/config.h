//  CItem用来储存一个文件所有tokne
//成员 CString *token 储存token
//		CString filename 储存文件名
//		int piecenum 储存token数目
//		CItem * pnextfile 指向下一个文件
//可调用成员函数:
// int  appendToken(CString newtoken) 添加新token，返回目前的touken数目；
// bool saveitem(LPCTSTR lpszfilename/*文件路径*/,int mode=0/*保存方式 0表示追加 1表示新建*/) 储存一个文件所有token，就是文件中的一行，格式为： 文件名 token数目 token1 token2...


class CItem
{
public:
	int piecenum;//分片数目
	CString *token;//token表
	CString filename;//文件名
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


//CLogfile 用来加载整个配置文件，用CItem 类型 filehead链表储存每一行
// 成员函数 
//long loadlog(LPCTSTR lpszfilename/*文件路径*/) 加载配置文件,返回加载文件数
//long getfilenum(void) 返回对象文件数目
//CItem * getAT(int index) 获取第 index个文件信息，失败返回 NULL，index从1开始，不是从0
//long appendFile(CItem * item) 将新的文件信息加入对象中
//bool  savelog(LPCTSTR lpszfilename/*文件路径*/,int mode=0/*保存方式 0表示追加 1表示新建*/)保存整个文件配置到指定目录
//CItem *CLogfile::search(CString filename)搜素目录中特定文件，成功放回CItem *指针，失败返回NULL
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
