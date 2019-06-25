#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
//директива компил€тора, указивает компоновщику добовить библиотеку в список зависимостей
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
                exit(1);  // завершение выполнени€ программы
        }
        SOCKADDR_IN addr;  //структура предназначени€ дл€ хранени€ адреса
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");// структура дл€ хранени€ ≥р адреса
        addr.sin_port = htons(1111);// порт дл€ аутендефикации программи с поступающеми данними
        addr.sin_family =  AF_INET; //семейство протоколов дл€ интернет протоколов AF_INET

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

 