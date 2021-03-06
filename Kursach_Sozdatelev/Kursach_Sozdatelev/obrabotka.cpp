#include "stdafx.h"
#include "Kursach_Sozdatelev.h"
fstream tmp;
BOOL sovpad(TCHAR* str1, TCHAR* str2)
{
	TCHAR* p=str1;
	TCHAR* pp=str2;
	if(!p) return 0;
	for(;*p;p++,pp++)
		if(*p!=*pp)
			return 0;
	return 1;
}
STUD Get(HWND hDlg)
{
	STUD stud;
	TCHAR buf[300]=TEXT("");
	BOOL lp1=TRUE,lp2=TRUE,lp4;
	GetDlgItemText(hDlg,IDC_FAM,stud.fam,20);
	if(*stud.fam==0)
	{
		wcscpy(buf,TEXT("Ошибка ввода фамилии"));
		lp1=FALSE;
	}
	GetDlgItemText(hDlg,IDC_SHI,stud.shi,10);
	if(*stud.shi==0)
	{
		wcscpy(buf,TEXT("Ошибка ввода шифра"));
		lp2=FALSE;
	}
	stud.nb=GetDlgItemInt(hDlg,IDC_NB,&lp4,FALSE);
	if(lp4==FALSE)
		wcscpy(buf+wcslen(buf),TEXT("ошибка ввода баллов"));
	stud.delpol='+';
	if(lp1==FALSE||lp2==FALSE||lp4==FALSE)
	{
		MessageBox(hDlg,buf,TEXT("Сообщение об ошибке ввода"),MB_OK);
		*stud.fam=0;
		*stud.shi=0;
		stud.nb=0;
	}
		{
		TCHAR buff[20];
		GetDlgItemText(hDlg,IDC_SPEC,buff,20);
	if(sovpad(buff,TEXT("Программист")))
	{
		stud.spec=0;
	}
	else
		if(sovpad(buff,TEXT("Юрист")))
		{
		stud.spec=1;		
		}
		else
			if(sovpad(buff,TEXT("Переводчик")))
			{
				stud.spec=2;
			}
			else
			   stud.spec=3;
	}
	return stud;
}
void PutToStr(STUD& stud,TCHAR* buff)
{
	TCHAR buf[20]=TEXT("");
	if(stud.spec==0)
		swprintf(buf,TEXT("%-10s"),TEXT("Программист"));
	else
		if(stud.spec==1)
		swprintf(buf,TEXT("%-10s"),TEXT("Юрист"));
	else
		if(stud.spec==2)
		swprintf(buf,TEXT("%-10s"),TEXT("Переводчик"));
	else
		swprintf(buf,TEXT("%-10s"),TEXT("Инженер"));
	swprintf(buff,TEXT("%-10s║%-10s║%-12s║%-10d║%-2c║"),
		stud.fam,stud.shi,buf,stud.nb,stud.delpol);
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
		if(stud.delpol=='+')
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
				stud.delpol='-';
				break;
			case 2:
				stud.delpol='+';
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