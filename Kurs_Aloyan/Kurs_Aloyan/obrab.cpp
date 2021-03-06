#include "stdafx.h"
#include "Kurs_Aloyan.h"
fstream tmp;
STRACT Get(HWND hDlg)
{
	STRACT stract;
	TCHAR buf[300]=TEXT("");
	BOOL lp1,lp2,lp3,lp4;
	stract.sh=GetDlgItemInt(hDlg,IDC_SHI,&lp1,FALSE);
	if(lp1==FALSE)
		wcscpy(buf+wcslen(buf),TEXT("Ошибка ввода номера билета!"));
	stract.tr=GetDlgItemInt(hDlg,IDC_TRUD,&lp2,FALSE);
	if(lp2==FALSE)
		wcscpy(buf+wcslen(buf),TEXT("Ошибка ввода номера билета!"));
	stract.kef=GetDlgItemInt(hDlg,IDC_KEF,&lp3,FALSE);
	if(lp3==FALSE)
		wcscpy(buf+wcslen(buf),TEXT("Ошибка ввода номера билета!"));
	stract.fond=GetDlgItemInt(hDlg,IDC_PLAN,&lp4,FALSE);
	if(lp4==FALSE)
		wcscpy(buf+wcslen(buf),TEXT("Ошибка ввода номера билета!"));
	stract.delpol='+';
	if(lp1==FALSE||lp2==FALSE||lp3==FALSE||lp4==FALSE)
	{
		MessageBox(hDlg,buf,TEXT("Сообщение об ошибке ввода"),MB_OK);
		stract.sh=0;
		stract.tr=0;
		stract.kef=0;
		stract.fond=0;
	}
	return stract;
}
void PutToStr(STRACT& stract,TCHAR* buff)
{
	swprintf(buff,TEXT("%-10d║%-10d║%-10d║%-10d║%-2c║"),
		stract.sh,stract.tr,stract.kef,stract.fond,stract.delpol);
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
	int sr;
	BOOL lp;
	int k=0;
	sr=GetDlgItemInt(hDlg,IDC_POISKF,&lp,FALSE);
	if(lp==FALSE)
		MessageBox(0,TEXT("Неверный ввод шифра"),TEXT("Ошибка"),MB_OK);
	else
	{
		STRACT mas[100];
		file.clear();
		file.seekg(0,ios::beg);
		while(read(file,stract))
		{
			if(sr==stract.sh)
			{
				mas[k]=stract;
				k++;
			}
		}
		if(k==0)
			MessageBox(0,TEXT("Неверный ввод шифра"),TEXT("Ошибка!"),MB_OK);
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
void izmen(fstream& file, HWND hDlg,HWND hListBox)
{
	int sh;
	int mode;
	int zm=0;
	STRACT stract;
	BOOL lp1,lp2;
	SendMessage(hListBox,LB_RESETCONTENT,0,0);
	{
		TCHAR buff[50];
		GetDlgItemText(hDlg,IDC_EDIT,buff,50);
		if(sovp(buff,TEXT("Трудоемкость")))
		{
			zm=0;
		}
		else
			if(sovp(buff,TEXT("Коэффициент")))
			{
				zm=1;
			}
			else
				zm=2;
	}
	sh=GetDlgItemInt(hDlg,IDC_EDIT1,&lp1,FALSE);
	if(lp1==FALSE)
		MessageBox(0,TEXT("Неверный ввод шифра"),TEXT("Ошибка"),MB_OK);
	mode=GetDlgItemInt(hDlg,IDC_EDIT2,&lp2,FALSE);
	if(lp2==FALSE)
		MessageBox(0,TEXT("Введено неверное значение"),TEXT("Ошибка"),MB_OK);
	if(lp1==FALSE||lp2==FALSE)
		MessageBox(0,TEXT("Неверный ввод данных"),TEXT("Ошибка"),MB_OK);
	else
	{
		file.clear();
		file.seekg(0,ios::beg);
		for(int i=0;read(file,stract,i);i++)
			if(stract.sh==sh)
			{
				switch(zm)
				{
				case 0:
					stract.tr=mode;
					break;
				case 1:
					stract.kef=mode;
					break;
				case 2:
					stract.fond=mode;
					break;
				}
				write(file,stract,i);
				SendMessage(hListBox,LB_RESETCONTENT,0,0);
			}
	}
}
bool sovp(TCHAR*str,TCHAR*str2)
{
	TCHAR*p=str;
	TCHAR*pp=str2;
	if(!*p)return 0;
	for(;*p;p++,pp++)
		if(*p!=*pp)return 0;
	return 1;
}