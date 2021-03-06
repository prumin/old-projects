#include "stdafx.h"
#include "Kursach_Domaev.h"

fstream tmp;
STUD Get(HWND hDlg)
{
	STUD stud;
	TCHAR buf[300]=TEXT("");
	BOOL lp1=TRUE,lp2=TRUE,lp3=TRUE,lp4=TRUE,lp5,lp6,lp7;
	GetDlgItemText(hDlg,IDC_DEK,stud.dek,10);
	if(*stud.dek==0)
	{
		wcscpy(buf,TEXT(""));
		lp1=FALSE;
	}
	GetDlgItemText(hDlg,IDC_GR,stud.gr,10);
	if(*stud.gr==0)
	{
		wcscpy(buf,TEXT(""));
		lp2=FALSE;
	}
	GetDlgItemText(hDlg,IDC_SP,stud.sp,10);
	if(*stud.sp==0)
	{
		wcscpy(buf,TEXT(""));
		lp3=FALSE;
	}
	GetDlgItemText(hDlg,IDC_ST,stud.star,10);
	if(*stud.star==0)
	{
		wcscpy(buf,TEXT(""));
		lp4=FALSE;
	}
	stud.k=GetDlgItemInt(hDlg,IDC_KR,&lp5,FALSE);
	if(lp5==FALSE)
		wcscpy(buf,TEXT(""));
	stud.s=GetDlgItemInt(hDlg,IDC_STU,&lp6,FALSE);
	if(lp6==FALSE)
		wcscpy(buf,TEXT(""));
	stud.ss=GetDlgItemInt(hDlg,IDC_STP,&lp7,FALSE);
	if(lp7==FALSE)
		wcscpy(buf,TEXT(""));
	stud.del='+';
	if(lp1==FALSE||lp2==FALSE||lp3==FALSE||lp4==FALSE||lp5==FALSE||lp6==FALSE||lp7==FALSE)
	{
		MessageBox(hDlg,buf,TEXT(""),MB_OK);
		*stud.dek=0;
		*stud.gr=0;
		*stud.sp=0;
		*stud.star=0;
		stud.k=0;
		stud.s=0;
		stud.ss=0;
	}
	return stud;
}
void PutToStr(STUD& stud,TCHAR* buff)
{
	swprintf(buff,TEXT("%-15s║%-15s║%-15s║%-15s║%-4d║%-4d║%-4d║%-2c║"),
		stud.dek,stud.gr,stud.sp,stud.star,stud.k,stud.s,stud.ss,stud.del);
}
fstream& del(fstream& file)
{
	
	tmp.open("tmp.txt",ios::app);
	tmp.clear();
	file.clear();
	file.seekg(0,ios::beg);
	tmp.seekg(0,ios::beg);
	STUD stud={};
	for(;read(file,stud);)
	{
		if(stud.del=='+')
			write(tmp,stud);
	}
	tmp.close();
	file.close();
	remove(nameFile);
	rename("tmp.txt",nameFile);
	file.open(nameFile,ios::in|ios::out|ios::ate);
	return file;
}
void mark(fstream& file,HWND hListBox, HWND hDlg, int n)
{
	int curItem=SendMessage(hListBox,LB_GETCURSEL,0,0);
	if(curItem!=LB_ERR)
	{
		STUD stud;
		file.clear();
		if(read(file,stud,curItem+1))
		{
			switch(n)
			{
			case 1:
				stud.del='-';
				break;
			case 2:
				stud.del='+';
				break;
			}
			write(file,stud,curItem+1);
			SendMessage(hListBox,LB_RESETCONTENT,0,0);
		}
		else
			MessageBox(0,TEXT("Ошибка чтения записи!"),TEXT("Ошибка!"),MB_OK);
	}
	else
		MessageBox(hDlg,TEXT("Выделите запись!"),TEXT("Ошибка!"),MB_OK);
}
