#include <iostream>
#include <windows.h>
#include <fstream>
#include "httpImageReader.h"

#define BUFFERSIZE 1024

std::string GetImage(std::string card) {
    std::string request;
    std::string response = "";
    int resp_leng;

    char buffer[BUFFERSIZE];
    struct sockaddr_in serveraddr;
    int sock;

    WSADATA wsaData;
    const char *ipaddress = "104.89.244.74";
    int port = 80;

    //http://wow.zamimg.com/images/hearthstone/cards/enus/original/EX1_116.png
    ///http://wow.zamimg.com/images/hearthstone/cards/enus/animated/EX1_116_premium.gif
    //http://media.services.zam.com/v1/media/byName/hs/cards/enus/CFM_616.png
    request+="GET /images/hearthstone/cards/enus/original/"+card+".png HTTP/1.0\r\n";
    request+="Host: wow.zamimg.com\r\n";
    request+="\r\n";

    //initiates use of the Winsock DLL by a process.
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
        std::cerr << "[WSAStartup() Error]: " << WSAGetLastError() << std::endl;
    }
    //open socket
    else if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        std::cerr << "[socket() Error]: " << WSAGetLastError() << std::endl;
    }
    else {
        //connect   
        memset(&serveraddr, 0, sizeof(serveraddr));
        serveraddr.sin_family      = AF_INET;
        serveraddr.sin_addr.s_addr = inet_addr(ipaddress);
        serveraddr.sin_port        = htons((unsigned short) port);

        if (connect(sock, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
            std::cerr << "[socket.connect() Error]: " << WSAGetLastError() << std::endl;
        }

        //send request
        else if (send(sock, request.c_str(), request.length(), 0) != request.length()) {
             std::cerr << "[socket.send() Error]: " << WSAGetLastError() << std::endl;
        }
        else {
            //get response
            resp_leng = BUFFERSIZE;
            while (true) {
                resp_leng= recv(sock, (char*)&buffer, BUFFERSIZE, 0);
                if (resp_leng <= 0) {
                    break;
                }
                response+= std::string(buffer,resp_leng);
            }

            std::ofstream myfile;
            myfile.open ("C:\\Users\\shido\\Desktop\\teste\\teste.gif",std::ofstream::binary | std::ofstream::out);

            //display response
            response = response.substr(response.find("\r\n\r\n")+4);
            //cout << response << endl;

            //display response
            //cout << response << endl;


            myfile << response;
            myfile.close();

            //disconnect
            closesocket(sock);

            //cleanup
            WSACleanup();
        }
    }
    return response;
} 