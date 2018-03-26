#include <iostream>
#include <windows.h>
#include <bitset>
#include "USART.h"
#define byte 8
using namespace std;
bool Comm::bSend_Package()
{
	Package ToSend;
}
BYTE Comm::Send_Byte(BYTE DAT_8bit)
{
	BYTE buf;//	ReadFile(hCom, &buf, 1, NULL, NULL);
			 //cout << "����" << bitset<byte>(DAT_8bit)<<"...";
	if (!WriteFile(hCom, &DAT_8bit, 1, NULL, NULL))
	{
		system("COLOR 0c");
		//cout << "ʧ��" << endl;
		return 0;
	}
	else
		//cout << "�ɹ�" << endl;
		return DAT_8bit;
}

bool Comm::bInitPort(LPCSTR sSerialPort)
{
	//���Դ򿪴���
	hCom = CreateFileA(sSerialPort,		//���ں�
		GENERIC_READ | GENERIC_WRITE,	//�����д
		0,								//ͨѶ�豸�����Զ�ռ��ʽ��
		0,								//�ް�ȫ����
		OPEN_EXISTING,					//ͨѶ�豸�Ѵ���
		0,								//ͬ��I/O
		0);								//ͨѶ�豸������ģ���
	if (hCom == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hCom);
		cout << "INVALID SERIAL PORT:" << sSerialPort << endl;
		return false;
	}
	else
		cout << "SERIAL PORT " << sSerialPort << " IS OPEN" << endl;
	//��ʼ������
	DCB dcb;
	dcb.BaudRate = 115200; //������Ϊ9600
	dcb.ByteSize = 8; //����λ��Ϊ8λ
	dcb.Parity = NOPARITY; //��У��
	dcb.StopBits = ONESTOPBIT; //1��ֹͣλa
	if (!SetCommState(hCom, &dcb)) //����DCB
	{
		cout << "SET DCB ERROR" << endl;
		return false;
	}
	else
	{

		dcb.StopBits = ONESTOPBIT; //1��ֹͣλa
		cout << "BAULD RATE = " << dcb.BaudRate << endl;
	}
	if (!SetupComm(hCom, 1024, 1024)) //���û�����
	{
		cout << "SET QUEUE ERROR" << endl;
		return false;
	}
	else
	{
		cout << "OUT QUEUE = " << 1024 << endl;
		cout << "IN QUEUE = " << 1024 << endl;
	}

	COMMTIMEOUTS TimeOuts;
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout = 1000;
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	TimeOuts.ReadTotalTimeoutConstant = 5000;
	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	if (!SetCommTimeouts(hCom, &TimeOuts)) //���ó�ʱ
	{
		cout << "SET TIMEOUT ERROR" << endl;
		return false;
	}
	else
	{
		cout << "ReadIntervalTimeout = " << TimeOuts.ReadIntervalTimeout << "ms" << endl;
		cout << "ReadTotalTimeoutMultiplier = " << TimeOuts.ReadTotalTimeoutMultiplier << "X" << endl;
		cout << "ReadTotalTimeoutConstant = " << TimeOuts.ReadTotalTimeoutConstant << "ms" << endl;
		cout << "WriteTotalTimeoutMultiplier = " << TimeOuts.WriteTotalTimeoutMultiplier << "X" << endl;
		cout << "WriteTotalTimeoutConstant = " << TimeOuts.WriteTotalTimeoutConstant << "ms" << endl;
	}
	if (!PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR))
	{
		cout << "PURGE ERROR FAILED" << endl;
		return false;
	}
	else
	{
		cout << "PURGE ERROR SUCCESS" << endl;
		cout << "INIT SUCCESS" << endl;
		cout << "-----------------------------------------------------" << endl;
		return true;
	}
}
