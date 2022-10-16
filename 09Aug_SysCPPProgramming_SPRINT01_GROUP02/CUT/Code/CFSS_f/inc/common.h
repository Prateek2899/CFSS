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

/************************************************************************************
								MACROS
*************************************************************************************/

#define MAX_BUFF 1024
#define PORT 4005
#define LOGIN "./data/Login.dat"  //stores clients login data
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

	////////////////////////////////////////////////////
	// Function Name: ReceiveFromS
	// Description : Client receive message from server
	// Use of Recursion : NA
	// Returns : string return type
	////////////////////////////////////////////////////	

	string ReceiveFromS();

	////////////////////////////////////////////////////
	// Function Name: SendToS
	// Description : Client send message to server.
	// Use of Recursion : NA
	// Returns : integer return type
	////////////////////////////////////////////////////

	int SendToS(char *);

	////////////////////////////////////////////////////
	// Function Name: ReceiveFromC
	// Description : Server receives message form client
	// Use of Recursion : NA
	// Returns : string return type
	////////////////////////////////////////////////////

	string ReceiveFromC();

	////////////////////////////////////////////////////
	// Function Name: SendToC
	// Description : server sends message to client
	// Use of Recursion : NA
	// Returns : integer return type
	////////////////////////////////////////////////////

	int SendToC(char *);
	int getClientSfd();

	////////////////////////////////////////////////////
	// Function Name: ClientAccept
	// Description : accepting the connection
	// Use of Recursion : NA
	// Returns : integer return type
	////////////////////////////////////////////////////	

	int ClientAccept();

	////////////////////////////////////////////////////
	// Function Name: ClosesServer
	// Description : close client
	// Use of Recursion : NA
	// Returns : void
	////////////////////////////////////////////////////

	void ClosesServer();

	////////////////////////////////////////////////////
	// Function Name: ClosesClientFD
	// Description : close server
	// Use of Recursion : NA
	// Returns : void
	////////////////////////////////////////////////////

	void ClosesClientFD();

	////////////////////////////////////////////////////
	// Function Name: PortValidation
	// Description : validates the port number
	// Use of Recursion : NA
	// Returns : void
	////////////////////////////////////////////////////
	
	void PortValidation(char *);

	////////////////////////////////////////////////////
	// Function Name: IPValidation
	// Description : validates the IP address
	// Use of Recursion : NA
	// Returns : void
	////////////////////////////////////////////////////

	void IPValidation(string);

private:
	int ServerFD;	//server descriptor
	int ClientFD;   //client descriptor 
	int portNo;  
	char ipaddr[20];
	struct sockaddr_in server_addr;  //server address
	struct sockaddr_in client_addr;	//client address
	socklen_t len, client_len;
};

class Login{

	public:

		////////////////////////////////////////////////////
		// Function Name: setmobNo
		// Description : sets phone number
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void setmobNo(char *);

		////////////////////////////////////////////////////
		// Function Name: setpasswd
		// Description : sets password
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void setpasswd(char *);

		////////////////////////////////////////////////////
		// Function Name: createLogin
		// Description : writes slient data in the file 
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void createLogin(Login &);

		////////////////////////////////////////////////////
		// Function Name: signin
		// Description : signin slient 
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		int signin(char* ,char*);

		////////////////////////////////////////////////////
		// Function Name: getmobNo
		// Description : gets mobile number
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		char* getmobNo(){return mobNo;}

		////////////////////////////////////////////////////
		// Function Name: getpasswd
		// Description : gets password
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		char* getpasswd(){return passwd;}

	private:

		char mobNo[11]={'\0'},passwd[20]={'\0'};

};

class Existing:public Login //for existing client
{
	public:


		////////////////////////////////////////////////////
		// Function Name: IsRegistered
		// Description : check for is the client already registered or not
		// Use of Recursion : NA
		// Returns : integer
		////////////////////////////////////////////////////

		int IsRegistered(string);

		////////////////////////////////////////////////////
		// Function Name: PassCheck
		// Description : validates password
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : integer
		////////////////////////////////////////////////////

		int PassCheck(string,string);

		////////////////////////////////////////////////////
		// Function Name: CurrStatus
		// Description : to display status of user
		// Use of Recursion : NA
		// Returns : void
		////////////////////////////////////////////////////
		void CurrStatus(string);

		////////////////////////////////////////////////////
		// Function Name: TypesRequest
		// Description : asks for call forwarding type(no reply, busy, unconditional)
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void TypesRequest(string);

		////////////////////////////////////////////////////
		// Function Name: EnableDis
		// Description : enables or disables services
		// Use of Recursion : NA
		// Returns : void
		////////////////////////////////////////////////////

		void EnableDis(string);	//enables or disables services

		////////////////////////////////////////////////////
		// Function Name: Deregister
		// Description : deregisters the client
		// Use of Recursion : NA
		// Returns : void
		////////////////////////////////////////////////////

		void Deregister(string);

	private:
		int mobile ;
};

class Registration:public Existing	//for registering a client
{

	public:

		////////////////////////////////////////////////////
		// Function Name: registeruser
		// Description : registers client
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void registeruser();
		//void setusername(char * u){strcpy(username,u);}
		//void setpasswd(char *);	//sets password of client

		////////////////////////////////////////////////////
		// Function Name: setphoneNo
		// Description : sets phone number
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void setphoneNo(char *);

		////////////////////////////////////////////////////
		// Function Name: settype
		// Description : sets call forwarding type(unconditional, no reply or busy)
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void settype(char *);

		////////////////////////////////////////////////////
		// Function Name: setservice
		// Description : unables or disables services
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void setservice(char *);

		////////////////////////////////////////////////////
		// Function Name: setdest
		// Description : sets phone number to which call will be forwarding
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void setdest(char *);

		////////////////////////////////////////////////////
		// Function Name: setclientst
		// Description : sets client status to registered or deregistered
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void setclientst(char *);

		////////////////////////////////////////////////////
		// Function Name: setcallstatus
		// Description : sets call status
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void setcallstatus(char *);

		////////////////////////////////////////////////////
		// Function Name: clientstatus
		// Description : shows client status
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void clientstatus();
	
	private:

		//char username[20];
		char phoneNo[11]={'\0'},type[2]={'\0'},desti[11]={'\0'},serv[2]={'\0'},clientst[2]={'\0'},callstatus[2]={'\0'};
};



class Makecall  // for making call
{

	public:

		////////////////////////////////////////////////////
		// Function Name: makeCall
		// Description : makes call
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : string
		////////////////////////////////////////////////////

		string makeCall();

		////////////////////////////////////////////////////
		// Function Name: setphone
		// Description : sets receivers phone number
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void setphone(char *);

		////////////////////////////////////////////////////
		// Function Name: logger
		// Description : stores INFO, DEBUG, ERROR, WARNING
		// Use of Recursion : NA
		// Exceptions or Operating System Error Handling: to be done in CPP UNIT Testing
		// Returns : void
		////////////////////////////////////////////////////

		void logger(string);

	private:

		char receviver[20]={'\0'};
			


};