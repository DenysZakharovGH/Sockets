#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
//��������� �����������, ��������� ������������ �������� ���������� � ������ ������������
using namespace std;
//---------------------------------------------------------------------------
SOCKET sConnention;
#pragma argsused

void ClientHandler()
{
        char msg[256];
        while(true)
        {
                recv(sConnention,msg,sizeof(msg),NULL);
                cout<<msg<<endl;
        }
}

int main(int argc, char* argv[])
{
char msg[256];
        WSAData wsaData;
        WORD DLLVersion = MAKEWORD(2,1);
        if(WSAStartup(DLLVersion,&wsaData) !=0)
        {
                cout<<"Error"<<endl;
                exit(1);  // ���������� ���������� ���������
        }
        SOCKADDR_IN addr;  //��������� �������������� ��� �������� ������
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");// ��������� ��� �������� �� ������
        addr.sin_port = htons(1111);// ���� ��� �������������� ��������� � ������������ �������
        addr.sin_family =  AF_INET; //��������� ���������� ��� �������� ���������� AF_INET

        sConnention = socket(AF_INET,SOCK_STREAM,NULL);

         if (connect(sConnention,(SOCKADDR*)&addr,sizeof(addr)) !=0)
         {
                cout<<"Error/ not connected to server"<<endl;
                return 1;
         }

         cout<<"Connected to server"<<endl;

         CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ClientHandler,NULL,NULL,NULL);

         while(true)
         {
                cin.getline(msg,sizeof(msg));
                send(sConnention,msg,sizeof(msg),NULL);
                Sleep(10);
         }


        system("pause");
        return 0;
}
//---------------------------------------------------------------------------

 