//
// Created by Or Gabay on 27/12/2022.
//

#include "Client.h"
#include "Header.h"
#include "Knn.h"


Client::Client(char * ip, int port) {
    serverIp = ip;
    clientPort=port;
    sockFD=socket(AF_INET, SOCK_STREAM, 0);
}

bool Client::checkingIp(){
    char * analyzeIp = new char[32];
    string ipSection[4];
    int theIndex = 0;
    for (int i = 0; i< strlen(serverIp); i++){
        if (serverIp[i]=='.'){
            theIndex++;
            continue;
        }
        ipSection[theIndex] += serverIp[i];
    }

    for (int j = 0; j<4; j++) {
        int digitsIp;
        try { digitsIp = stoi (ipSection[j]);}
        catch (...){return false;}
        if (digitsIp <0 || digitsIp >255) return false;
    }
    char buffer1[32];
    sprintf(buffer1, "%d", std::stoi(ipSection[0]));
    char buffer2[32];
    sprintf(buffer2, "%d", std::stoi(ipSection[1]));
    char buffer3[32];
    sprintf(buffer3, "%d", std::stoi(ipSection[2]));
    char buffer4[32];
    sprintf(buffer4, "%d", std::stoi(ipSection[3]));
    strcpy(analyzeIp, buffer1);
    strcat(analyzeIp, ".");
    strcat(analyzeIp, buffer2);
    strcat(analyzeIp, ".");
    strcat(analyzeIp, buffer3);
    strcat(analyzeIp, ".");
    strcat(analyzeIp, buffer4);

    return true;
}

bool Client::checkingPort(){
    if (clientPort <1024 || clientPort>65535) return false;
    return true;
}

int Client::initClient(){
    while (true) {

        string inputFromUser;
        getline (cin, inputFromUser);
        if (sockFD < 0){
            cout<<"error creating socket"<<endl;
            return -1;
        }
        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));

        sin.sin_family= AF_INET;
        sin.sin_addr.s_addr = inet_addr(serverIp);
        sin.sin_port = htons(clientPort);
        if (connect(sockFD, (struct sockaddr*)&sin, sizeof(sin))<0)
        {
            cout<<"error connecting to server"<< endl;
            return -1;
        }

        int answerCheck = CheckFromUser(inputFromUser);
        if (answerCheck == 0) {
            int sent_bytes = send (sockFD, inputFromUser.c_str(), inputFromUser.length(), 0);
            if (sent_bytes < 0) {
                cout << "error sending to server" << endl;
                return -1;
            }
        } else if (answerCheck == 1) {
            break;
        }

        char buffer [4096];

        int read_bytes = recv(sockFD, buffer, sizeof(buffer), 0);
        if (read_bytes == 0) {
            cout << "connection is closed" << endl;
            break;
        }
        else if (read_bytes < 0) {
            cout<<"error receiving message" << endl;
            return -1;
        }
        else{
            cout << buffer << endl;
        }

        close (sockFD);
    }
    return 0;
}

int Client::CheckFromUser(string message){
    if(message.size()==0){//check if the str empty
        cout<<"the message is empty"<<endl;
        return -1;
    }
    else if(message=="-1"){
        return 1;
    } else{
        string messages[3];
        string messageFromUser="";
        for (int i=0;i<message.size();i++) {// Go through each character in the string
            if (isalpha(message[i])){
              messages[0] = messageFromUser;
              messageFromUser.empty();
              messageFromUser = messageFromUser +message[i] + message [i+1] + message[i+2];
              messages[1] = messageFromUser;
              messageFromUser.empty();
              messageFromUser = messageFromUser + message [i+4];
              messages [2] = messageFromUser;
              break;
            }
            else {
                messageFromUser = messageFromUser + message[i];
            }
        }
        vector<double> a = CreateVector(messages[0], ' ');
        string distance = messages[1];
        int k = stoi(messages[2]);
        argumentsCheckClient(distance, k);
        return 0;
    }

}

int main(int argc, char* argv[]) {

    Client myClient = Client(argv[1], stoi(argv[2]));
    if (!myClient.checkingIp()) {
        cout << "invalid input";
        exit(0);
    }
    if (!myClient.checkingPort()) {
        cout << "invalid input";
        exit(0);
    }
    while (true){
        int talkWServer=myClient.initClient();
        if(talkWServer<0){
            continue;
        }
    }
}