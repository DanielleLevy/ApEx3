//
// Created by danie on 25/12/2022.
//

#include "Server.h"


Server::Server(int port, string file) {
    server_port=port;
    db= readFromFile(file);
    sockFD=socket(AF_INET, SOCK_STREAM, 0);
}
int Server:: initServer(){
    if (sockFD < 0){
        cout<<"error creating socket"<<endl;
        return -1;
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sockFD, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout << "error binding socket" << endl;
        return -1;
    }
    return 0;

}



int Server::handleClientServer() {
    int sent_bytes;
    if (listen(sockFD, 0) < 0) {
        cout << "error listening to a socket" << endl;
        return -1;
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sockFD, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        cout << "error accepting client" << endl;
        return -1;
    }
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    while (true) {
        bzero(buffer, expected_data_len);
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            cout << "connection is closed" << endl;
            break;
        } else if (read_bytes < 0) {
            cout << "error receive" << endl;
            return -1;
        } else {
            int answerCheck = CheckFromClient(buffer);
            if (answerCheck == 0) {
                answer = CalcServer(vectorToClass, distanceM, k);
            } else if (answerCheck == -1) {
                answer = "invalid input";
            } else if (answerCheck == 1) {
                break;
            }
            sent_bytes = send(client_sock, answer.c_str(), answer.length(), 0);
            if (sent_bytes < 0) {
                cout << "error sending to client" << endl;
                return -1;
            }
        }
    }
    close(client_sock);
    return 0;
}



int Server::CheckFromClient(string message) {

    int index;
    if(message.size()==0){//check if the str empty
        cout<<"the message is empty"<<endl;
        return -1;
    }
    else if(message=="-1"){
        return 1;
    } else{
        for (int i=0;i<message.size();i++) {// Go through each character in the string
            if (isalpha(message[i])){
                index=i;
                break;
            }
        }
        string vectorTemp=message.substr(0,index);
        distanceM= message.substr(index,3);
        string kTemp=message.substr(index+4,message.size()-vectorTemp.size()-distanceM.size());
        vectorToClass = CreateVector(vectorTemp, ' ');
        try {
            k = stoi(kTemp);
        }
        catch (...){
            return -1;
        }
        if(k>db.size()){
            return -1;
        }
        return 0;
    }

}

string Server::CalcServer(vector<double> vectorfromuser, string distance, int k) {
    Knn answer(db, distance, k, vectorfromuser);
    return  answer.findTheLabel();
}

int main(int argc, char *argv[]){
    int port;
    try{
      port= stoi(argv[2]);
    }
    catch(...) {
        cout<<"invalid input"<<endl;
    }
    if(port<1024 || port>65535){
        cout<<"invalid input"<<endl;
    }
    Server myServer=Server(port,argv[1]);
    int initAns=myServer.initServer();
    if (initAns==0){
        while (true){
            int talkWClient=myServer.handleClientServer();
            if(talkWClient<0){
                continue;
            }
        }
    }

}







