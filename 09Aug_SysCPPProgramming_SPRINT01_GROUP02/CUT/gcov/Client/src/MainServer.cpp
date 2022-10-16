/**********************************************************************************
                       INCLUSION HEADER FILES
***********************************************************************************/

#include <common.h>
#include <logger.h>

void sighandle(int signum){
	if(signum == SIGINT){
		log(3, INFO, "Closing", "Main");
		logfile.close();
		cout<<"Server Ended Successfully\n";
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char *argv[])
{	
	CFSS_SOCKET S;
	//int portN = stoi(argv[2]);
	string ipAdd = argv[1];
	try
	{
	    if(argc!=3)
    	{
	    	throw "Invalid number of argument";
	    }
    	else
    	{
			S.IPValidation(ipAdd);
			S.PortValidation(argv[2]);
			logfile.open(serverlog, ios::out|ios::app);
			log(3, INFO, "Entering", "Main");
			
			signal(SIGINT,sighandle);
			//int ServerFD = 
			S.ConnectServer(argv); //creating the connection 
			while(1){
				char msg[MAX_BUFF]={'\0',};
				int counter = 1;

				int ClientFD = S.ClientAccept();  //Accepting the connection
				strcpy(msg,"Welcome to server");
				S.SendToC(msg);   //send message to the client
				strcpy(msg,"Select the required option");
				S.SendToC(msg);

				while(counter){
				
				strcpy(msg," \n 1.Register \n 2.Existing User \n 3.Make call \n Press any other number to exit");
				S.SendToC(msg);
				string str = S.ReceiveFromC();
				int option = stoi(str);

				switch (option)
				{
				case 1:
				{	
					log(3, INFO, "Entering Registration", "Main");
					Registration reg;
					Login L;
					recv(ClientFD,&L,sizeof(L),0);
					L.createLogin(L);
					recv(ClientFD,&reg,sizeof(reg),0);//get the message sent by the client
					reg.registeruser();
					reg.clientstatus();
				
					break;
				}

				case 2:
					log(3, INFO, "Entering login", "Main");
					Existing lg;
					recv(ClientFD,&lg,sizeof(lg),0);
					break;
				
				case 3:

					{
					log(3, INFO, "Making Call", "Main");
					Makecall m;
					string tmsg;
					recv(ClientFD,&m,sizeof(m),0);
					tmsg = m.makeCall();
					strcpy(msg,tmsg.c_str());
					S.SendToC(msg);
					break;
					}

				default:
					counter = 0;
					break;
				}
			
			}
			}
			S.ClosesServer();   //close the connection

		}
	}
	catch(const char*err)
	{
	    cout<<err;
	}
	return 0;

}
