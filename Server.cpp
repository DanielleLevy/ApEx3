//
// Created by danie on 25/12/2022.
//

#include "Server.h"


Server::Server(int clinet, string file) {
    server_port = clinet;
    db = ReadFromFile(file);
    sock = socket(AF_INET, SOCK_STREAM, 0);
}

int Server::CheckServer() {
    if (sock < 0){
        cout<<"error creating socket"<<endl;
        return -1;
    }
    return 0;
}

int Server::BindServer() {
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout << "error binding socket" << endl;
        return -1;
    }
    return 0;
}

int Server::ListenServer() {
    if (listen(sock, 5) < 0) {
        cout << "error listening to a socket" << endl;
        return -1;
    }
    while (true) {
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            cout << "error accepting client" << endl;
            return -2;
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            cout << "connection is closed" << ;
            return -3;
        } else if (read_bytes < 0) {
            cout << "error receive" << endl;
            return -4;
        } else {
            if (CheckFromClient(buffer)) {
                answer = CalcServer(vectorToClass, distanceM, k);
                int sent_bytes = send(client_sock, answer.c_str(), answer.length(), 0);
                if (sent_bytes < 0) {
                    cout << "error sending to client" << endl;
                    return -6;
                }
                close(client_sock);
            } else {
                cout << "the message wasnt good" << endl;
                return -5;
            }
        }
    }
    close(sock);
    return 0;
}


bool Server::CheckFromClient(string message) {
    if(message.size()==0){//check if the str empty
        cout<<"the message is empty"<<endl;
        return false;
    }
    string messages[3];
    string messageFromUser="";
    int index=0;
    for (int i=0;i<message.size();i++) {// Go through each character in the string
        if (message[i] != ',') {
            messageFromUser = messageFromUser + message[i];
        } else {
            messages[index] = messageFromUser;
            index++;
            messageFromUser.empty();
        }
    }
    vectorToClass= CreateVector(messages[0],' ');
    distanceM=messages[1];
    k= stod(messages[2]);
    return true;
}

string Server::CalcServer(vector<double> vectorfromuser, string distance, int k) {
    Knn answer(db, distance, k, vectorfromuser);
    return  answer.findTheLabel();
}



