#include <cppunit/config/SourcePrefix.h>
#include <UT.h>

CPPUNIT_TEST_SUITE_REGISTRATION( Registration );

CPPUNIT_TEST_SUITE_REGISTRATION( CFSS_SOCKET );

bool CFSS_SOCKET::IPValidation(string ip)
{
	string validIp = ip;
	int i;
	int count = 0;
	for(int j = 0; j<validIp.length();j++)
	{
		if(validIp[j] == '.')
		count++;
	}
	if(count != 3)
	{
		//cout<<"Invalid IP"<<endl;
		return false;
		//exit(EXIT_FAILURE);
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
			for (i = 0; i < e.length(); i++)
			{
				if(!isdigit(e[i]))
				{
					//cout<<"Invalid IP"<<endl;
					return false;
					//_exit(EXIT_FAILURE);
					break;
				}
				else if(stoi(e) <0 ||stoi(e)>255)
				{		
					//cout<<"Invalid IP"<<endl;
					return false;
				//	_exit(EXIT_FAILURE);
					break;
				}
			}
																							}
																						}      
	return true;

}

bool CFSS_SOCKET::PortValidation(char* portN)
{
	int n = strlen(portN);
	for(int i = 0; i<n; i++)
	{
		if(isdigit(portN[i])==0)
		{
			//cout<<"Invalid Port Number"<<endl;
			return false;
			//_exit(EXIT_FAILURE);
			break;
		}
		else if(stoi(portN) < 0 || stoi(portN) >65535)
		{
			//cout<<"Invalid port number"<<endl;
			return false;
			//_exit(EXIT_FAILURE);
			break;
		}
		else
			return true;
	}
	//return true;
}


bool Registration::settype(char *t)
{
	int ty = stoi(t);
	if(ty >3 || ty <1 )
	{
		/*cout<<"Invalid Entry. Re-enter"<<endl;
		char typ[2];
		cin>>typ;
		settype(typ);*/
		return false;
	}
	else
	{
		strcpy(type, t);
		return true;
	}
}

bool Registration::setcallstatus(char *st)
{
	int sta = stoi(st);	
	if(sta > 3 || sta <1)
	{
		/*cout<<"Invalid Entry. Re-enter"<<endl;
		char stat[2];
		cin>>stat;
		setcallstatus(stat);*/
		return false;
	}
	else
	{
		strcpy(callstatus, st);
		return true;
	}
}
bool Registration::setservice(char* ser)
{
	int se = stoi(ser);		
	if(se < 0 || se > 1)
	{
		/*cout<<"Invalid Entry. Re-enter"<<endl;
		char _s[2];
		cin>>_s;
		setservice(_s);*/
		return false;
	}	
	else
	{
		strcpy(serv,ser);
		return true;
	}
}

bool Registration::setpasswd(char *pass)
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
		return true;
	}
	else
	{
		/*char *p ;
		p = getpass("Enter a Strong Password(Atleast 7 charecters long and should include atleast one Uppercase, Lowercase and a numerical)\n");
		setpasswd(p);*/
		return false;
	}
													
}

bool Registration::setdest(char *dest)
{

	int len = strlen(dest);
	int flag = 1;
	for(int i=0;i<len;i++)
	{
		if(isdigit(dest[i])==0)	
		{

			//cout<<"Invalid input. Enter digits only"<<endl;
			flag=0;
			break;
		}
		else if(len!=10)
		{
			//cout<<"Invalid mobile number"<<endl;
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

		/*char des[11];
		cout<<"Renter the number"<<endl;
		cin>>des;
		setdest(des);*/
		return false;

	}
	else
	{
		strcpy(desti,dest);
		return true;
	}

}

bool Registration::setphoneNo(char *ph)
{

	int len = strlen(ph);
	int flag = 1;

	for(int i=0;i<len;i++)
	{
		if(isdigit(ph[i])==0)
		{

			/*cout<<"Invalid input. Enter digits only"<<endl;
			log(3, DEBUG, "Invalid Input", "setphoneNo");*/
			flag=0;
			break;
		}
		else if(len!=10)
		{
			/*cout<<"Invalid mobile number"<<endl;
			log(3, DEBUG, "Invalid mobile number", "setphoneNo");*/
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
		/*char phone[11];
		cout<<"Renter the number"<<endl;
		cin>>phone;
		setphoneNo(phone);*/
		return false;
	}
	else
	{
		strcpy(phoneNo,ph);
		return true;
	}

}


void CFSS_SOCKET::IPValidation_UT_01()
{
        //sunny test case
        string _n = "127.0.0.1";

        CPPUNIT_ASSERT_EQUAL(true, IPValidation(_n));
}

void CFSS_SOCKET::IPValidation_UT_02()
{
        //rainy test case: alphabet in ip
        char* _n = "127.a.0.1";

        CPPUNIT_ASSERT_EQUAL(false, IPValidation(_n));
}

void CFSS_SOCKET::IPValidation_UT_03()
{
        //rainy test case: less than 3 "."
        char* _n = "127.0.0";

        CPPUNIT_ASSERT_EQUAL(false, IPValidation(_n));
}
void CFSS_SOCKET::IPValidation_UT_04()
{
        //rainy test case: Out of range
        char* _n = "127.260.0.1";

        CPPUNIT_ASSERT_EQUAL(false, IPValidation(_n));
}
void CFSS_SOCKET::IPValidation_UT_05()
{
        //rainy test case: special charecters
        char* _n = "127.#.0.1";

        CPPUNIT_ASSERT_EQUAL(false, IPValidation(_n));
}

void CFSS_SOCKET::PortValidation_UT_01()
{
        //sunny test case
        char* _n = "4005";

        CPPUNIT_ASSERT_EQUAL(true, PortValidation(_n));
}
void CFSS_SOCKET::PortValidation_UT_02()
{
        //rainy test case: out of range
        char* _n = "70000";

        CPPUNIT_ASSERT_EQUAL(false, PortValidation(_n));
}

void CFSS_SOCKET::PortValidation_UT_03()
{
        //rainy test case: out of range
        char* _n = "a";

        CPPUNIT_ASSERT_EQUAL(false, PortValidation(_n));
}
void Registration::setphonenumber_UT_01()
{
        //sunny test case
        char* _n = "7077512519";

        CPPUNIT_ASSERT_EQUAL(true, setphoneNo(_n));
}

void Registration::setphonenumber_UT_02()
{
        //rainny test case - for phonenumber not equal to 10 numericals
        char* _n = "707751251";

        CPPUNIT_ASSERT_EQUAL(false, setphoneNo(_n));
}
void Registration::setphonenumber_UT_03()
{
        //rainny test case - for phonenumber containing alphabets
        char* _n = "70775a1234";

        CPPUNIT_ASSERT_EQUAL(false, setphoneNo(_n));
}
void Registration::setphonenumber_UT_04()
{
        //rainny test case - for phone number containing special charcter
        char* _n = "@70775125";

        CPPUNIT_ASSERT_EQUAL(false, setphoneNo(_n));
}
void Registration::settype_UT_01()
{
	//sunny test case
	char* _t = "1";

        CPPUNIT_ASSERT_EQUAL(true, settype(_t));
}

void Registration::settype_UT_02()
{
	//sunny test case
	char* _t = "2";

        CPPUNIT_ASSERT_EQUAL(true, settype(_t));
}
void Registration::settype_UT_03()
{
	//sunny test case
	char* _t = "3";

        CPPUNIT_ASSERT_EQUAL(true, settype(_t));
}
void Registration::settype_UT_04()
{
	//rainy test case: number other than 1,2 or 3
	char* _t = "5";

        CPPUNIT_ASSERT_EQUAL(false, settype(_t));
}
/*void Registration::settype_UT_05()
{
	//rainy test case: alphabets
	char* _t = "a";

        CPPUNIT_ASSERT_EQUAL(false, settype(_t));
}
void Registration::settype_UT_06()
{
	//rainy test case: special charecter
	char* _t = "#";

        CPPUNIT_ASSERT_EQUAL(false, settype(_t));
}*/

void Registration::setservice_UT_01()
{
	//sunny test case
	char* _s = "1";

        CPPUNIT_ASSERT_EQUAL(true, setservice(_s));
}
void Registration::setservice_UT_02()
{
	//sunny test case
	char* _s = "0";

        CPPUNIT_ASSERT_EQUAL(true, setservice(_s));
}
void Registration::setservice_UT_03()
{
	//rainy test case: number other than 1 or 0
	char* _s = "3";

        CPPUNIT_ASSERT_EQUAL(false, setservice(_s));
}
/*void Registration::setservice_UT_04()
{
	//rainy test case: alphabet
	char* _s = "a";

        CPPUNIT_ASSERT_EQUAL(false, setservice(_s));
}
void Registration::setservice_UT_05()
{
	//rainy test case: special charecter
	char* _s = "#";

        CPPUNIT_ASSERT_EQUAL(false, setservice(_s));
}*/

void Registration::setcallstatus_UT_01()
{
	//sunny test case
	char* _c = "1";

        CPPUNIT_ASSERT_EQUAL(true, setcallstatus(_c));
}
void Registration::setcallstatus_UT_02()
{
	//sunny test case
	char* _c = "2";

        CPPUNIT_ASSERT_EQUAL(true, setcallstatus(_c));
}
void Registration::setcallstatus_UT_03()
{
	//sunny test case
	char* _c = "3";

        CPPUNIT_ASSERT_EQUAL(true, setcallstatus(_c));
}
void Registration::setcallstatus_UT_04()
{
	//rainy test case: number other than 1,2 or 3
	char* _t = "4";

        CPPUNIT_ASSERT_EQUAL(false, settype(_t));
}

void Registration::setdest_UT_01()
{
        //sunny test case
        char* _n = "7077512519";

        CPPUNIT_ASSERT_EQUAL(true, setdest(_n));
}

void Registration::setdest_UT_02()
{
        //rainny test case - for phonenumber not equal to 10 numericals
        char* _n = "707751251";

        CPPUNIT_ASSERT_EQUAL(false, setdest(_n));
}
void Registration::setdest_UT_03()
{
        //rainny test case - for phonenumber containing alphabets
        char* _n = "70775a1234";

        CPPUNIT_ASSERT_EQUAL(false, setdest(_n));
}
void Registration::setdest_UT_04()
{
        //rainny test case - for phone number containing special charcter
        char* _n = "@70775125";

        CPPUNIT_ASSERT_EQUAL(false, setdest(_n));
}
void Registration::setpasswd_UT_01()
{
	//sunny test case
	char* _p = "Jinse123";

        CPPUNIT_ASSERT_EQUAL(true, setpasswd(_p));
}
void Registration::setpasswd_UT_02()
{
	//rainy test case: less than 7 charecters
	char* _p = "Kds4";

        CPPUNIT_ASSERT_EQUAL(false, setpasswd(_p));
}
void Registration::setpasswd_UT_03()
{
	//rainy test case: numerical
	char* _p = "24684868";

        CPPUNIT_ASSERT_EQUAL(false, setpasswd(_p));
}

void Registration::setpasswd_UT_04()
{
	//rainy test case: small letter alphabets
	char* _p = "aaaabbbb";

        CPPUNIT_ASSERT_EQUAL(false, setpasswd(_p));
}
void Registration::setpasswd_UT_05()
{
	//rainy test case: Capital letter alphabets
	char* _p = "AADDSSCC";

        CPPUNIT_ASSERT_EQUAL(false, setpasswd(_p));
}
void Registration::setpasswd_UT_06()
{
	//rainy test case: combination without numericals
	char* _p = "DgsdsDss";

        CPPUNIT_ASSERT_EQUAL(false, setpasswd(_p));
}

void Registration::setpasswd_UT_07()
{
	//rainy test case: combination without capital alphabets
	char* _p = "246heloo";

        CPPUNIT_ASSERT_EQUAL(false, setpasswd(_p));
}
void Registration::setpasswd_UT_08()
{
	//rainy test case: combination without small letter alphabets
	char* _p = "246GOODS";

        CPPUNIT_ASSERT_EQUAL(false, setpasswd(_p));
}

