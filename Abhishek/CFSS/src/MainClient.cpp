/**********************************************************************************
                       INCLUSION HEADER FILES
***********************************************************************************/

#include <common.h>
#include <logger.h>


int main(int argc, char *argv[])
{	
	logfile.open(clientlog, ios::out|ios::app);
	log(3, INFO, "Entering", "Main");

	CFSS_SOCKET S;
	string cmsg;
	string sstr;
	int ServerFD = S.ConnectClient(argv);  //client connection
	//read&write
	char msg[MAX_BUFF];
	int counter=1;
	for(int i=1;i<3;i++){
	sstr = S.ReceiveFromS();
	cout<<sstr<<endl;
	}

	while(counter)
	{
		//system("CLS");
		sstr = S.ReceiveFromS();
		cout<<sstr<<endl;
		cin>>msg;
		//fgets(msg,MAX_BUFF,stdin);
		S.SendToS(msg);
		int option = stoi(msg);
		switch (option)
		{
			case 1:
			{
			log(3, INFO, "Entering Registration", "Main");
			char callst[2],phone[10],type[2],dest[10],ser[2],status[2];
			char enPh[11],enPw[20];
			char *pass;
			Registration r;
			encdec ed;
			//cout<<"Enter username"<<endl;
			//cin>>user;
			//r.setusername(user);
			sleep(1);
			cout << "\033[2J\033[1;1H"; // to clear output screen
			cout<<"/***************************************************************************************************************"<<endl;
			cout<<"---------------------------------------------------Registering---------------------------------------------------"<<endl;
			cout<<"***************************************************************************************************************/"<<endl;

			cout<<"\n Enter phone No"<<endl;
			cin>>phone;
			r.setphoneNo(phone);

			string encry;
			encry=ed.encryption(phone);
			cout<<"encry="<<encry<<endl;
			strcpy(enPh,encry.c_str());
			cout<<"enPh="<<enPh<<endl;
			r.setencPhone(enPh);
		
			//cout<<"Enter password"<<endl;
			pass = getpass("Enter password");
			r.setpasswd(pass);

			encry=ed.encryption(pass);
			cout<<"encry in pass="<<encry<<endl;
			strcpy(enPw,encry.c_str());
			cout<<"enPw="<<enPw<<endl;
			r.setencPass(enPw);

			cout<<"Enter type of call forwarding \n 1.Unconditional \n 2.Busy \n 3.No reply"<<endl;
			cin>>type;
			r.settype(type);
			cout<<"What will be your current call status \n 1.Unconditional \n 2.Busy \n 3.No reply "<<endl;
			cin>>callst;
			r.setcallstatus(callst);
			cout<<"Enter number to be call forwarded to"<<endl;
			cin>>dest;
			r.setdest(dest);
			cout<<"Press 1 if you want service to be enable or press 0 to disable "<<endl;
			cin>>ser;
			r.setservice(ser);
			strcpy(status,"1");
			r.setclientst(status);	
			cout<<"Successfully Registered"<<endl;								
			send(ServerFD,&r,sizeof(r),0);

			break;
			}

			case 2:
			{
			log(3, INFO, "Entering Login", "Main");
			sleep(1);
			cout << "\033[2J\033[1;1H"; // to clear output screen
			cout<<"/***************************************************************************************************************"<<endl;
			cout<<"-----------------------------------------------------Login------------------------------------------------------"<<endl;
			cout<<"***************************************************************************************************************/"<<endl;

				char pass[20],phone[10];
				Existing l;
				cout<<"Enter phone No"<<endl;
				cin>>phone;
				string mob(phone);

				int f1 = l.IsRegistered(mob);
				if(f1==0)
				{
					log(3, DEBUG, "DO NOT EXIST", "IsRegistered");
					cout<<"Do not exist"<<endl;
					cout<<"Failed to Login"<<endl;
					
					send(ServerFD,&l,sizeof(l),0);
					break;
				}
				
				cout<<"Enter password"<<endl;
				cin>>pass;
				string pw(pass);
				int f2 = l.PassCheck(mob,pw);
				if(f2==0)
				{	
					log(3, DEBUG, "INVALID", "PassCheck");
					cout<<"Incorrect password"<<endl;
					cout<<"Failed to Login"<<endl;
					send(ServerFD,&l,sizeof(l),0);
					break;
				}
				//break;
				//}
			sleep(1);
				cout << "\033[2J\033[1;1H"; // to clear output screen
				cout<<"/***************************************************************************************************************"<<endl;
				cout<<"-----------------------------------------------------Updation----------------------------------------------------"<<endl;
				cout<<"***************************************************************************************************************/"<<endl;

				int ch;
				cout<<"Press - for choices \n 1 - Enable or Disable the call forwarding service \n 2 - Deregister from our services "<<endl;
				cout<<" 3 - Changing the types of call forwarding "<<endl;
				cin>>ch;
				//string mob(phone);
				//cout<<"mob1 = "<<mob<<endl;
				switch(ch) 
				{
				case 1:   
		            l.EnableDis(mob);
					break;
				case 2:	
					l.Deregister(mob);
					break;
				case 3:	
					l.TypesRequest(mob);
					break;
				default	:	cout << "Invalid Choice!" << endl;
					break;				
				}

				send(ServerFD,&l,sizeof(l),0);
				break;
			}
		case 3:
			log(3, INFO, "Entering Call Process", "Main");
			sleep(1);
				cout << "\033[2J\033[1;1H"; // to clear output screen
				cout<<"/***************************************************************************************************************"<<endl;
				cout<<"----------------------------------------------------Make Call---------------------------------------------------"<<endl;
				cout<<"***************************************************************************************************************/"<<endl;
			
			char phone[20];
			Makecall m;
			cout<<"Enter the number you want to call"<<endl;
			cin>>phone;
			m.setphone(phone);
			send(ServerFD,&m,sizeof(m),0);
			sstr = S.ReceiveFromS();
			cout<<sstr<<endl;
			break;
		default:
			cout<<"Closing!!"<<endl;
			log(3, INFO, "Closing", "Main");
			counter=0;
			break;
		}
	sleep(2);
	cout << "\033[2J\033[1;1H"; // to clear output screen

	}
	logfile.close();
	S.ClosesServer();  //closing the connection
	return 0;
}
