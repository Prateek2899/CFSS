//////////////////////////////////////////////////////
// Copyright(C)Future Software Limited,2022
// Licensee Future Communications Software,2022
// File/Class Name : CFSS.h
// Principal Author : Prateek Sharma, Abhishek Kumar Gupta, Alok Kumar, Jinse Thomas, Rahul Dey
// Subsystem Name : Call Forwarding System Simulator
// Module Name : Final Sprint
// Language :C++
// Target Environment : Linux/Windows
// Date of First Release : 02-10-2022
// Author : Prateek Sharma, Abhishek Kumar Gupta, Alok Kumar, Jinse Thomas, Rahul Dey
// Description : Header file for all our classes and functions
// Change History: 2
// Version:v2
// Date(DD/MM/YYYY): 07-10-2022
// Modified By: Prateek Sharma, Abhishek Kumar
// Description of change: Integrating Registration, Existing, MakeCall and Client Server Modules. 
// Change History : 3
// Version : v3
// Date(DD/MM/YYYY) : 10-10-2022
// Modified by : Alok Kumar
// Description of change : Complying code with Coding Guidelines.
///////////////////////////////////////////////////////

/************************************************************************************
							STANDARD HEADER FILES
*************************************************************************************/
#include <iostream>	//Input output purposes
#include <cstring>	//required for string functions
#include <sys/socket.h>	//define the sockaddr structure that includes at least the following members: sa_family_t sa_family Address family
#include <sys/types.h>	//contains a number of basic derived types
#include <netinet/in.h>	//contains definitions for the internet protocol family
#include <arpa/inet.h>	//define the INET_ADDRSTRLEN and INET6_ADDRSTRLEN macros
#include <unistd.h>	//entry point to various constant, type and function declarations
#include <sys/signal.h>	//for signal handling
#include<string.h>	//contain classes that are used for exception handling
#include<fstream>	// Stream class to both read and write from/to files
#include<ctime>	//used for timestamp
#include<vector>	//dynamic arrays with the ability to resize itself 
#include<string>	//for string
#include<stdlib.h> 
#include <bits/stdc++.h>

/************************************************************************************
								MACROS
*************************************************************************************/

#define MAX_BUFF 1024
#define PORT 4005
#define LOGIN "./data/Login.txt"  //stores clients login data
#define Clientstatus "./data/Clientstatus.txt"  //stores clients service status
#define Database "./data/Database.txt"  //stores client information
#define Logger "./data/Logger.txt"
#define clientlog "./data/clientlog.txt"
#define serverlog "./data/serverlog.txt"

using namespace std;
typedef struct sockaddr_in SA_IN;


/************************************************************************************
								 CLASS DECALARATION
*************************************************************************************/

class CFSS_SOCKET
{
public:
	CFSS_SOCKET();
	~CFSS_SOCKET();
	void ConnectServer(char **);   //create connection for server
	int ConnectClient(char **);   //create connection for client
	// SA_IN getServerAddr();  
	// SA_IN getClientAddr();   
	// socklen_t getLengthAddr(); 
	string ReceiveFromS();  //Client receive message from server
	int SendToS(char *);  //Client send message to server
	string ReceiveFromC();  // Server receives message form client
	int SendToC(char *);  //server sends message to client
	int getClientSfd();    
	int ClientAccept();        //accepting the connection
	void ClosesServer();     //close server
	void ClosesClientFD();    //close client
private:
	int ServerFD;	//server descriptor
	int ClientFD;   //client descriptor 
	int portNo;  
	char ipaddr[20];
	struct sockaddr_in server_addr;  //server address
	struct sockaddr_in client_addr;	//client address
	socklen_t len, client_len;
};

class Registration	//for registering a client
{

	public:

		void registeruser();	//registers client
		//void setusername(char * u){strcpy(username,u);}
		void setpasswd(char *);	//sets password of client
		void setphoneNo(char *);	//sets phone number of client
		void settype(char *);	//sets call forwarding type(unconditional, no reply or busy)
		void setservice(char *);	//unables or disables services
		void setdest(char *);	//sets phone number to which call will be forwarding
		void setencPhone(char *p){strcpy(enPhone,p);}
		void setencPass(char *p){strcpy(enPass,p);}

		void setclientst(char *);	//sets client status to registered or deregistered
		void setcallstatus(char *); 	//sets call status
		void clientstatus();	//shows client status
	
	private:

		//char username[20];
		char passwd[20],phoneNo[11],type[2],desti[11],serv[2],clientst[2],callstatus[2];
		char enPhone[15],enPass[20];
};

class Existing //for existing client
{
	public:
		int IsRegistered(string);	//check for is the client already registered or not
		int PassCheck(string,string);	//validates password
		void TypesRequest(string);	//asks for call forwarding type(no reply, busy, unconditional)
		void EnableDis(string);	//enables or disables services
		void Deregister(string);	//deregisters the client

	private:
		char user_mob[11];
};

class Makecall  // for making call
{

	public:

		string makeCall();
		void setphone(char *p){strcpy(receviver,p);}
		void logger(string);

	private:

		char receviver[20];
			


};

class encdec // for encryption and description
{
	public:
   		string encryption(string );
		string decryption(string );
};