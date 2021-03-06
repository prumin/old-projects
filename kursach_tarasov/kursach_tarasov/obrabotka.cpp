#include "stdafx.h"
#include "kursach_tarasov.h"
fstream tmp;
STRACT Get(HWND hDlg)
{
	STRACT stract;
	TCHAR buf[300]=TEXT("");
	BOOL lp1,lp2=TRUE,lp3=TRUE;
	stract.sh=GetDlgItemInt(hDlg,IDC_NUMBER,&lp1,FALSE);
	if(lp1==FALSE)
		wcscpy(buf+wcslen(buf),TEXT("Ошибка ввода номера билета!"));
	GetDlgItemText(hDlg,IDC_FAM,stract.fam,20);
	if(*stract.fam==0)
	{
		wcscpy(buf+wcslen(buf),TEXT("Ошибка ввода номера билета!"));
		lp2=FALSE;
	}
	GetDlgItemText(hDlg,IDC_BREK,stract.blu,20);
	if(*stract.blu==0)
	{
		wcscpy(buf+wcslen(buf),TEXT("Ошибка ввода номера билета!"));
		lp3=FALSE;
	}
	stract.delpol='+';
	if(lp1==FALSE||lp2==FALSE||lp3==FALSE)
	{
		MessageBox(hDlg,buf,TEXT("Сообщение об ошибке ввода"),MB_OK);
		stract.sh=0;
		*stract.fam=0;
		*stract.blu=0;
	}
	return stract;
}
void PutToStr(STRACT& stract,TCHAR* buff)
{
	swprintf(buff,TEXT("%-10d║%-10s║%-10s║%-2c║"),
		stract.sh,stract.fam,stract.blu,stract.delpol);
}
fstream& del(fstream& file)
{
	
	tmp.open("tmp.txt",ios::app);
	tmp.clear();
	file.clear();
	file.seekg(0,ios::beg);
	tmp.seekg(0,ios::beg);
	STRACT stract={};
	for(;read(file,stract);)
	{
		if(stract.delpol=='+')
			write(tmp,stract);
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
		STRACT stract;
		file.clear();
		if(read(file,stract,curItem+1))
		{
			switch(n)
			{
			case 1:
				stract.delpol='-';
				break;
			case 2:
				stract.delpol='+';
				break;
			}
			write(file,stract,curItem+1);
			SendMessage(hListBox,LB_RESETCONTENT,0,0);
		}
		else
			MessageBox(0,TEXT("Ошибка чтения записи!"),TEXT("Ошибка!"),MB_OK);
	}
	else
		MessageBox(hDlg,TEXT("Выделите запись!"),TEXT("Ошибка!"),MB_OK);
}
void serche(fstream& file,HWND hDlg, HWND hListBox)
{
	STRACT stract;
	TCHAR buff[300]=TEXT("");
	TCHAR sr[20]=TEXT("");
	BOOL lp;
	int k=0;
	GetDlgItemText(hDlg,IDC_SERCHBUT,sr,20);
	if(*sr==0)
		MessageBox(0,TEXT("Неверный ввод завтрака"),TEXT("Ошибка"),MB_OK);
	else
	{
		STRACT mas[100];
		file.clear();
		file.seekg(0,ios::beg);
		while(read(file,stract))
		{
			if(wcscmp(stract.blu,sr)==0)
			{
				mas[k]=stract;
				k++;
			}
		}
		if(k==0)
			MessageBox(0,TEXT("Неверный ввод завтрака"),TEXT("Ошибка!"),MB_OK);
		else
		{
			for(int i=0;i<k;i++)
			{
				PutToStr(mas[i],buff);
				SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)buff);
			}
		}

	}
}