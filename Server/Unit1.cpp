//---------------------------------------------------------------------------
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define ClientsNumber 100
//директива компилятора, указивает компоновщику добовить библиотеку в список зависимостей
using namespace std;
//---------------------------------------------------------------------------
SOCKET Connections[ClientsNumber];
int counter =0;

void ClientHandler(int index)
{
        char msg[256];
        while(true)
        {
                recv(Connections[index],msg,sizeof(msg),NULL);
                for(int i=0;i<counter;i++)
                {
                        if(i==index)
                                continue;
                        send(Connections[i],msg,sizeof(msg),NULL);
                }
        }
}

#pragma argsused
int main(int argc, char* argv[])
{
        WSAData wsaData;
        WORD DLLVersion = MAKEWORD(2,1);
        if(WSAStartup(DLLVersion,&wsaData) !=0)
        {
                cout<<"Error"<<endl;
                exit(1);  // завершение выполнения программы
        }
        SOCKADDR_IN addr;  //структура предназначения для хранения адреса
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");// структура для хранения ір адреса
        addr.sin_port = htons(1111);// порт для аутендефикации программи с поступающеми данними
        addr.sin_family =  AF_INET; //семейство протоколов для интернет протоколов AF_INET

        SOCKET sListen = socket(AF_INET,SOCK_STREAM,NULL);
        //привязка адреса к сокету
        bind(sListen,(SOCKADDR*)&addr,sizeof(addr));
        listen(sListen,SOMAXCONN);

        int sizeofMemoryAddr = sizeof(addr);
         SOCKET newConnention;
         for(int i =0; i<ClientsNumber; i++)
         {
                newConnention = accept(sListen,(SOCKADDR*)&addr, &sizeofMemoryAddr);
                //accept возращает указатель на новий сокет для общения с клиентом
                if(newConnention == 0)
                {
                        cout<<"Error/Can't conection"<<endl;
                        exit(1);  // завершение выполнения программы
                } else
                {
                        cout<<"Client Connected"<<endl;
                        char msg[256] ="Hello client, whats doing bro?";
                        send(newConnention,msg,sizeof(msg),NULL);
                        Connections[i]=newConnention;
                        counter++;
                        CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ClientHandler,(LPVOID)(i),NULL,NULL);
                }
         }

        system("pause");
        return 0;
}
//---------------------------------------------------------------------------
