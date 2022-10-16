
/**********************************************************************************
                       INCLUSION HEADER FILES
***********************************************************************************/

#include <common.h>
#include <logger.h>

void CFSS_SOCKET::IPValidation(string ip)
{
	string validIp = ip;
	int i;
	int count = 0;
	int len=validIp.length();
	for(int j = 0; j<len;j++)
	{
		if(validIp[j] == '.')
			count++;
	}
	if(count != 3)
	{
		cout<<"Invalid IP"<<endl;
		_exit(EXIT_FAILURE);
	}
	else
	{
	
		int p = validIp.find(".");
		string a = validIp.substr(0,p);
		int q = validIp.find(".", p+1);
		int r = validIp.find(".",q+1);
		string b= validIp.substr(p+1, q-p-1);
		string c = validIp.substr(q+1,r-q-1);
		string d = validIp.substr(r+1);
		vector<string> val;
		val.push_back(a);
		val.push_back(b);
		val.push_back(c);
		val.push_back(d);
		
		for(auto e: val)
		{
			int siz=e.length();
			for (i = 0; i < siz; i++)
			{
				if(!isdigit(e[i]))
				{
					cout<<"Invalid IP"<<endl;
					_exit(EXIT_FAILURE);
					break;
				}
				else if(stoi(e) <0 ||stoi(e)>255)
				{		
					cout<<"Invalid IP"<<endl;
					_exit(EXIT_FAILURE);
					break;
				}
			}
		}
	}      	

}
void CFSS_SOCKET::PortValidation(char* portN)
{
	int n = strlen(portN);
	for(int i = 0; i<n; i++)
	{
		if(isdigit(portN[i])==0)
		{
			cout<<"Invalid Port Number"<<endl;
			//return false;
			_exit(EXIT_FAILURE);
			break;
		}
		else if(stoi(portN) < 0 || stoi(portN) >65535)
		{
			cout<<"Invalid port number"<<endl;
			//return false;
			_exit(EXIT_FAILURE);
			break;
		}
		//else
		//	return true;
	}
}

//constructor to set default values
CFSS_SOCKET::CFSS_SOCKET()
{	
	ServerFD=0;
	strcpy(ipaddr,"0.0.0.0");
	portNo = 0;
}

CFSS_SOCKET::~CFSS_SOCKET()
{
	
}

//connection of client to server 
int CFSS_SOCKET::ConnectClient(char **argv)
{
	len = sizeof(server_addr);
	client_len = sizeof(client_addr);
	ServerFD = socket(AF_INET, SOCK_STREAM, 0);
	if(ServerFD<0)
	{
		perror("socket() ");
		log(3, ERROR, "socket creation", "ConnectClient");
		_exit(EXIT_FAILURE);
	}
	bzero(&server_addr, sizeof(SA_IN));

	portNo = atoi(argv[2]);
	strcpy(ipaddr, argv[1]);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNo);
	server_addr.sin_addr.s_addr = inet_addr(ipaddr);

	cout<<"Client Socket Created Successfully!!!!"<<endl;

	if(connect(ServerFD, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in))<0)
	{
		perror("connect() here ");
		log(3, ERROR, "Connection failure", "ConnectClient");
		exit(EXIT_FAILURE);
	}

	cout<<"New client connected to the Server"<<endl;

	return ServerFD;
}


//connection to the client 
void CFSS_SOCKET::ConnectServer(char **argv)
{	
	log(3, INFO, "Entering", "OpenSocket");
	len = sizeof(server_addr);
	client_len = sizeof(client_addr);
	ServerFD = socket(AF_INET, SOCK_STREAM, 0);
	if(ServerFD<0)
	{	
		log(3, ERROR, "socket creation", "ConnectServer");
		perror("socket() ");
		_exit(EXIT_FAILURE);
	}
	bzero(&server_addr, sizeof(SA_IN));

	portNo = atoi(argv[2]);
	strcpy(ipaddr, argv[1]);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNo);
	server_addr.sin_addr.s_addr = inet_addr(ipaddr);

	cout<<"Server Socket Created Successfully!!!!"<<endl;

	if(bind(ServerFD,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in))<0)
	{
		perror("bind() ");
		log(3, ERROR, "Binding failed", "ConnectServer");
		exit(EXIT_FAILURE);
	}
	log(3, INFO, "Entering", "BindData");
	cout<<"Binding done"<<endl;

	if(listen(ServerFD, 5)==0)
		cout<<"Listening...."<<endl;
	else
		{
			cout<<"Error in listening...."<<endl;
			log(3, ERROR, "Listening failed", "ConnectServer");
		}
	log(3, INFO, "Entering", "Listen");
	//return ServerFD;
}
//create a new socket descriptor and  and this sd is returned to the caller 
int CFSS_SOCKET::ClientAccept()
{	
	log(3, INFO, "Entering", "Accept");
	int clientfd = accept(ServerFD,(struct sockaddr*)&client_addr, &client_len);
	if(clientfd < 0)
	{
		perror("accept() ");
		log(3, ERROR, "Accepting client failed", "ConnectServer");
		exit(EXIT_FAILURE);
	}
	cout<<"Server accepted the new Client"<<endl;
	ClientFD=clientfd;
	return clientfd;

}

//Send message form client to server 
int CFSS_SOCKET::SendToS(char *msg)
{	

	int ret =sendto(ServerFD,msg,MAX_BUFF,0,(struct sockaddr*)&server_addr,len); 
	if(ret<0)
        {
            perror("sendto() ");
			log(3, ERROR, "Message not send", "SendToS");

		exit(EXIT_FAILURE);
        }
	cout<<"Message sent to the server"<<endl;
return 1;
}

//Server receives message form Client 
string CFSS_SOCKET::ReceiveFromC()
{	
	log(3, INFO, "Entering", "ReadData");
	char msg[MAX_BUFF]={'\0',};
	int ret=recvfrom(ClientFD,msg,MAX_BUFF, 0, (struct sockaddr*)&client_addr, &len);
	
	if(ret<0)
        {
            perror("recvfrom() ");
			log(3, ERROR, "Message not received", "ReceiveFromC");
			exit(EXIT_FAILURE);
		}

	cout<<"Client: "<<msg<<endl;
	return string(msg);
}
//Send message form Server to client 
int CFSS_SOCKET::SendToC(char *msg)
{
	int ret =sendto(ClientFD,msg,MAX_BUFF,0,(struct sockaddr*)&server_addr,len); 
	if(ret<0)
        {
            perror("sendto() ");
			log(3, ERROR, "Message not send", "SendToC");
       		exit(EXIT_FAILURE);
       	}
	cout<<"Server: "<<msg<<endl;
return 1;
}

//Client received message form server  
string CFSS_SOCKET::ReceiveFromS()
{
	char msg[MAX_BUFF]={'\0',};
	int ret=recvfrom(ServerFD,msg,MAX_BUFF, 0, (struct sockaddr*)&client_addr, &len);
	
	if(ret<0)
    {
        perror("recvfrom() ");
		log(3, ERROR, "Message not received", "ReceiveFromS");
		exit(EXIT_FAILURE);
	}

	//cout<<"Client: Messgae form server: "<<msg<<endl;
	return string(msg);
	
}


void CFSS_SOCKET::ClosesServer()
{
	close(ServerFD);
}

void CFSS_SOCKET::ClosesClientFD()
{
	close(ClientFD);
}

void Login::createLogin(Login &L)
{
	fstream fs;
	fs.open(LOGIN,ios::app|ios::out|ios::binary);
	if(!fs){
		cout<<"Login file open error"<<endl;
	}
	else{
		fs.write(reinterpret_cast<char*>(&L), sizeof(L));
		fs.close();
	}
}

void Login::setmobNo(char *ph)
{

int len = strlen(ph);
int flag = 1;

for(int i=0;i<len;i++){
	if(isdigit(ph[i])==0){

		cout<<"Invalid input. Enter digits only"<<endl;
		flag=0;
		break;
	}
	else if(len!=10){
		cout<<"Invalid mobile number"<<endl;
		flag=0;
		break;
		
	}
	else{
		continue;
	}

}


if(flag==0){

	char phone[11];
	cout<<"Renter the number"<<endl;
	cin>>phone;
	setmobNo(phone);

}
else{
	strcpy(mobNo,ph);
}
}

int Login::signin(char *ph,char *pw)
{
	fstream fs;
	Login L;
	int flag=0;
	fs.open(LOGIN,ios::in|ios::binary);
	if(!fs){
		cout<<"Login file open error"<<endl;
		return 0;
	}
	else{
	while(!fs.eof()){

		fs.read(reinterpret_cast<char*>(&L), sizeof(L));
		cout<<getmobNo()<<endl;
		cout<<getpasswd()<<endl;
		
		if(strcmp(L.getmobNo(),ph)==0 && strcmp(L.getpasswd(),pw)==0)
		{
				cout<<"Login class confirm succesful login"<<endl;
				flag=1;
				break;
		}
		else{
			flag=0;
		}

	}

	fs.close();
	}
	return flag;
	
}

void Registration::registeruser()
{
	fstream fs;

	/*fs.open(LOGIN,ios::app);
	if(!fs)
	{
		cout<<"Login file open error"<<endl;

	}
	else{

		fs<<phoneNo<<","<<passwd<<endl;
	}
	fs.close();*/

	fs.open(Database,ios::app);
	if(!fs)
	{
		cout<<"databse file open error"<<endl;

	}
	else
	{
		
		fs<<phoneNo<<","<<serv<<","<<type<<","<<callstatus<<","<<desti<<endl;
	}
	fs.close();



}

void Registration::clientstatus(){

	fstream fs;
	fs.open(Clientstatus,ios::app|ios::out);
	if(!fs)
	{
		log(3, ERROR, "File not opened", "clientstatus");
		cout<<"Client status file open error"<<endl;
	}
	else{

		fs<<phoneNo<<","<<clientst<<endl;
	}

}
void Registration::settype(char *t)
{
	int ty = stoi(t);
	if(ty >3 || ty <1 )
	{
		cout<<"Invalid Entry. Re-enter"<<endl;
		char typ[2];
		cin>>typ;
		settype(typ);
																
	}
	else
		strcpy(type, t);
}

void Registration::setcallstatus(char *st)
{
	int sta = stoi(st);	
	if(sta > 3 || sta <1)
	{
		cout<<"Invalid Entry. Re-enter"<<endl;
		char stat[2];
		cin>>stat;
		setcallstatus(stat);
	}
	else
		strcpy(callstatus, st);
}
void Registration::setservice(char* ser)
{
	int se = stoi(ser);		
	if(se < 0 || se > 1)
	{
		cout<<"Invalid Entry. Re-enter"<<endl;
		char _s[2];
		cin>>_s;
		setservice(_s);
	}	
	else
	{
		strcpy(serv,ser);
	}
}

void Login::setpasswd(char *pass)
{

	int n = strlen(pass);

	bool hasLower = false, hasUpper = false;
	bool hasDigit = false;

	for (int i = 0; i < n; i++)
	{
		if (islower(pass[i]))
		hasLower = true;
		if (isupper(pass[i]))
		hasUpper = true;
		if (isdigit(pass[i]))
		hasDigit = true;
													
	}
	if(hasLower && hasUpper && hasDigit && (n >= 7))
	{
		strcpy(passwd, pass);
	}
	else
	{
		char *p ;
		p = getpass("Enter a Strong Password(Atleast 7 charecters long and should include atleast one Uppercase, Lowercase and a numerical)\n");
													
		setpasswd(p);
	}
						
}

void Registration::setclientst(char* st)
{
	int sta = stoi(st);
	if(sta < 0 || sta > 1)
	{
		cout<<"Invalid Entry. Re-enter"<<endl;
		char _cs[2];
		cin>>_cs;
		setclientst(_cs);
	}	
	else
		strcpy(clientst,st);
}

void Registration::setdest(char *dest)
{

	int len = strlen(dest);
	int flag = 1;

	for(int i=0;i<len;i++)
	{
		if(isdigit(dest[i])==0)
		{

			cout<<"Invalid input. Enter digits only"<<endl;
			flag=0;
			break;
		}
		else if(len!=10)
		{
			cout<<"Invalid mobile number"<<endl;
			flag=0;
			break;
													
		}
		else
		{
			continue;
		}

	}


	if(flag==0)
	{

		char des[11];
		cout<<"Renter the number"<<endl;
		cin>>des;
		setdest(des);

	}
	else
	{
		strcpy(desti,dest);
	}

}

void Registration::setphoneNo(char *ph)
{

int len = strlen(ph);
int flag = 1;

for(int i=0;i<len;i++){
	if(isdigit(ph[i])==0){

		cout<<"Invalid input. Enter digits only"<<endl;
		log(3, DEBUG, "Invalid Input", "setphoneNo");
		flag=0;
		break;
	}
	else if(len!=10){
		cout<<"Invalid mobile number"<<endl;
		log(3, DEBUG, "Invalid mobile number", "setphoneNo");
		flag=0;
		break;
		
	}
	else{
		continue;
	}

}


if(flag==0){

	char phone[11];
	cout<<"Renter the number"<<endl;
	cin>>phone;
	setphoneNo(phone);

}
else{
	strcpy(phoneNo,ph);
}

}
int Existing::IsRegistered(string mob)
{
	log(3, INFO, "Entering", "IsRegistered");
	int isRegistered = 0;
	string msg;

    fstream fd;
	// Opening the File
	fd.open(Database,ios::in);
	if(!fd)
	{
		cout<<"Cant open file!"<<endl;
		log(3, ERROR, "File not opened", "IsRegistered");
		exit(EXIT_FAILURE);
	}


	string line;
	string mnumber;
	
	while(getline(fd,line))
	{
		//cout<<"displaying data"<<line<<endl;
		int a= line.find(",");
		mnumber= line.substr(0,a);

		//cout<<mnumber<<endl;
	// Compare Mobile Number with each Number in File
		if(mob == mnumber) {
			isRegistered = 1;
		}
	}
	
	if (isRegistered == 1) {
		
		// If Number is Registered
		fd.close();
		return 1;
	
	} 
	else if (isRegistered == 0) {

		// If Number is Not Registered
		log(3, WARNING, "Number is Not Registered", "isRegistered");
		fd.close();
		return 0;
	}
	return 1;
}

int Existing::PassCheck(string user, string pw)
{	
	log(3, INFO, "Entering", "PassCheck");
		
	int isCorrect = 0;

    fstream fd;
	// Opening the File
	fd.open(LOGIN,ios::in);
	if(!fd)
	{
		cout<<"Cant open file!"<<endl;
		log(3, ERROR, "File not opened", "PassCheck");
		exit(EXIT_FAILURE);
	}


	string line;
	string usr,pass;
	
	while(getline(fd,line))
	{
		int a= line.find(",");
		usr= line.substr(0,a);
	
		if(user == usr) 
		{
			pass=line.substr(a+1);
			if(pw == pass)
				isCorrect = 1;
		}
	}
	
	if (isCorrect== 0) {
		
		// incorrect password
		log(3, WARNING, "Incorrect Password", "Passcheck");
		fd.close();
		return 0;
	
	} 
	else if (isCorrect == 1) 
	{

		// correct
		fd.close();
		return 1;
	}
	return 1;
}

// to see current status in database
void Existing::CurrStatus(string phoneNo)
{
	log(3, INFO, "Entering", "CurrStatus");

	fstream fs;
	fs.open(Database,ios::in|ios::out);
	
	//int found = 0;
	
	vector<string> lines;
	string line;
	if(!fs)
	{
		cout<<"File Error"<<endl;
		log(3, ERROR, "File not opened", "EnableDis");
		//return 0;
	}
	else
	{

		//bool isFound = false;

		while(!fs.eof())
		{	

			getline(fs,line);
			int a= line.find(",");
			string PhoneN = line.substr(0,a); // user no.

			
			if(phoneNo == PhoneN)// found
				{
					int b = line.find(",",a+1);
					string en = line.substr(a+1,b-a-1);	// enable or disable

					int c =line.find(",",b+1);
					string type = line.substr(b+1,c-b-1); // type stored

					int d =line.find(",",c+1);
					string stat = line.substr(c+1,d-c-1); // current call status

					string FrdMob = line.substr(c+1); // forwarded no.
					
					if(en=="1")
						cout<<"You have enabled the services"<<endl;
					else
						cout<<"You have disabled the services"<<endl;

					cout<<"Type of Call Forwarding selected is ";

					if(type=="1")
						cout<<"Unconditional"<<endl;
					else if(type=="2")
						cout<<"Busy"<<endl;
					else
						cout<<"No Reply"<<endl;
					/*
					cout<<"Current Call status is ";

					if(stat=="1")
						cout<<"Unconditional"<<endl;
					else if(stat=="2")
						cout<<"Busy"<<endl;
					else
						cout<<"No Reply"<<endl;
					*/
				}

		}

		fs.close();
	}



}
void Existing::EnableDis(string phoneNo)
{	
	log(3, INFO, "Entering", "EnableDis");
	string en = "1";

	fstream fs;
	fs.open(Database,ios::in|ios::out);
	
	int found = 0;
	
	vector<string> lines;
	string line;

	//cout<<"out enable"<<phoneNo<<endl;

	if(!fs)
	{
		cout<<"File Error"<<endl;
		log(3, ERROR, "File not opened", "EnableDis");
		//return 0;
	}
	else
	{

		//bool isFound = false;

		while(!fs.eof())
		{	

			getline(fs,line);
			int a= line.find(",");
			string PhoneN = line.substr(0,a);
			int b = line.find(",",a+1);
			string status = line.substr(a+1,b-a-1);
			string remaining = line.substr(b+1);
			string res;
			//cout<<"in enable"<<PhoneN<<endl;
			if(phoneNo != PhoneN)
				{
					lines.push_back(line);
				}
			else if(phoneNo == PhoneN)// found
				{
					//int str;
					found = 1;
					cout<<"Enter 1 to enable or 0 to disable services"<<endl;
					cin>>en;

					res = PhoneN + "," + en + "," + remaining;

					lines.push_back(res);
				}

		}

		fs.close();

		if(found==0)
		{	
			log(3, WARNING, "Number not Registered,", "EnableDis");
			cout<<"Not a registered Number"<<endl;
		}

		else
		{	
			cout<<"Successfully Updated"<<endl;
			ofstream ofs;
			ofs.open(Database, std::ofstream::out | std::ofstream::trunc);
			ofs.close();

			ofstream file;
			file.open(Database,ios::in|ios::out);

			// writing again
			int len=lines.size();
			for (int i = 0; i < len; i++)
  			{
				file << lines[i] << endl;
			}

			file.close();
		}
	}
	//return 1;
}
void Existing::TypesRequest(string phoneNo)
{	
	log(3, INFO, "Entering", "TypesRequest");
	//string phoneNo = "5555";
	string type = "1";

	fstream fs;
	fs.open(Database,ios::in|ios::out);
	
	int found = 0;
	
	vector<string> lines;
	string line;

	if(!fs)
	{
		cout<<"File Error"<<endl;
		log(3, ERROR, "File not opened", "TypesRequest");
		//return 0;
	}
	else
	{

		while(!fs.eof())
		{	

			getline(fs,line);
			int a= line.find(",");
			string PhoneN = line.substr(0,a);

			int b = line.find(",",a+1);
			string en = line.substr(a+1,b-a-1);

			int c =line.find(",",b+1);
			string type = line.substr(b+1,c-b-1);

			string remaining = line.substr(c+1);
			string res;

			if(phoneNo != PhoneN)
				{
					lines.push_back(line);
				}
			else if(phoneNo == PhoneN)// found
				{
					//int str;
					found = 1;
					cout<<"Enter type of call forwarding \n 1.Unconditional \n 2.Busy \n 3.No reply"<<endl;
					cin>>type;

					res = PhoneN + "," + en + "," + type + "," + remaining;
					//cout<<"result ="<<res<<endl;

					lines.push_back(res);
				}

		}

		fs.close();

		if(found==0)
		{	
			log(3, WARNING, "Number not Registered,", "TypesRequest");
			cout<<"Not a registered Number"<<endl;
		}

		else
		{	
			cout<<"Successfully Updated"<<endl;
			ofstream ofs;
			ofs.open(Database, std::ofstream::out | std::ofstream::trunc);
			ofs.close();

			ofstream file;
			file.open(Database,ios::in|ios::out);

			// writing again
			int len=lines.size();
			for (int i = 0; i < len ; i++)
  			{
				file << lines[i] << endl;
			}

			file.close();
		}
	}
	//	return 0;


	
}

void Existing::Deregister(string phoneNo)
{
	log(3, INFO, "Entering", "Deregister");
	//string phoneNo = "5555";
	string reg = "1";

	fstream fs;
	fs.open(Clientstatus,ios::in|ios::out);
	
	int found = 0;
	
	vector<string> lines;
	string line;

	if(!fs)
	{
		cout<<"File Error"<<endl;
		log(3, ERROR, "File not opened", "Deregister");
		//return 0;
	}
	else
	{
		while(!fs.eof())
		{	
			getline(fs,line);
			int a= line.find(",");
			string PhoneN = line.substr(0,a);
			string res;

			if(phoneNo != PhoneN)
				{
					lines.push_back(line);
				}
			else if(phoneNo == PhoneN)// found
				{
					//int str;
					found = 1;
					cout<<"If you want to Deregister - Enter 0 else 1"<<endl;
					cin>>reg;

					res =PhoneN + "," + reg;

					lines.push_back(res);
				}

		}

		fs.close();

		if(found==0)
		{	
			log(3, WARNING, "Number not Registered,", "Deregister");
			cout<<"Not a registered Number"<<endl;
		}

		else
		{	
			cout<<"successfully updated"<<endl;
			ofstream ofs;
			ofs.open(Clientstatus, std::ofstream::out | std::ofstream::trunc);
			ofs.close();

			ofstream file;
			file.open(Clientstatus,ios::in|ios::out);

			// writing again
			int len=lines.size();
			for (int i = 0; i < len ; i++)
  			{
				file << lines[i] << endl;
			}

			file.close();
		}
	}
	//	return 0;


	
}

string Makecall::makeCall()
{
	log(3, INFO, "Entering", "makeCall");
	//char msg[MAX_BUFF]={'\0',};
	fstream fs;
	string msg;
	string line;
	int flag=0;

	fs.open(Clientstatus,ios::in);
	if(!fs)
	{
		cout<<"Client File error"<<endl;
		log(3, ERROR, "File not opened 1", "makecall");
		exit(EXIT_FAILURE);
	}
	else
	{
		
		while(!fs.eof())
		{	
			char phone[20];
			getline(fs,line);
			int a= line.find(",");
			string PhoneN = line.substr(0,a);
			strcpy(phone,PhoneN.c_str());
			string client_stat = line.substr(a+1);
			if(strcmp(receviver,phone)==0 && client_stat=="1"){
			flag=1;
			}
		}

	}
	fs.close();

	if(flag==1){

	fs.open(Database,ios::in);
	if(!fs)
	{
		cout<<"Datafile File Error"<<endl;
		log(3, ERROR, "File not opened 2", "makecall");
		exit(EXIT_FAILURE);
	}
	else
	{
		//bool isFound = false;
		string str;
		while(!fs.eof())
		{
			char phone[20];
			getline(fs,line);
			int a= line.find(",");
			string PhoneN = line.substr(0,a);
			strcpy(phone,PhoneN.c_str());
			int b = line.find(",",a+1);
			string serv_stat = line.substr(a+1,b-a-1);
			int c = line.find(",",b+1);
			string typ = line.substr(b+1,c-b-1);
			int d = line.find(",",c+1);
			string call_st = line.substr(c+1,d-c-1);
			string destination = line.substr(d+1);
			if(typ == "2")
				str = "Busy";

			if(typ == "3")
				str = "No Reply";

			if(typ == "1")
				str = "Unconditional";

			if(strcmp(receviver,phone)==0)
			{
				//isFound = true;
				if(serv_stat == "1")
				{	
					
					if(strcmp(typ.c_str(),call_st.c_str())==0)
					{
						msg = "Your call has been forwarded to " + destination;
						logger(destination);
						return(msg);

					}
					else
					{
						msg = "The number you are trying to contact is in " + str+" state";
						return(msg);
					}
				}
				else
				{
					msg= "Your call is getting connected";
					return(msg);
				}
			}


		}
		
	}
	}
	if(flag==0 )
		{	
			log(3, WARNING, "User is not in service", "makecall");
			msg  = "User is not in service";
			return(msg);
		}

	fs.close();
	return "";
}

void Makecall::setphone(char *p)
{
	strcpy(receviver,p);
}

void Makecall::logger(string st)
{
	log(3, INFO, "Entering", "logger");
	fstream fs;

	fs.open(Logger,ios::app);
	if(!fs)
	{
		cout<<"Login file open error"<<endl;
		log(3, ERROR, "File not opened", "logger");

	}
	else{

		time_t ttime = time(0);    
		char* dt = ctime(&ttime);

		fs<<receviver<<" call has been forwarded to "<<st<<" on "<<dt<<endl;
	}
	fs.close();
}
