#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/signal.h>
#include<string.h>
#include<fstream>
#include<ctime>
#include<vector>
#include<string>

#define MAX_BUFF 1024
#define PORT 4005
#include <cppunit/extensions/HelperMacros.h>


using namespace std;
class CFSS_SOCKET:public CPPUNIT_NS::TestFixture //using textfixture class, inheriting class of text fixture
{

        CPPUNIT_TEST_SUITE( CFSS_SOCKET ); //name of class has to be passed
        CPPUNIT_TEST( IPValidation_UT_01 );
        CPPUNIT_TEST( IPValidation_UT_02 );
        CPPUNIT_TEST( IPValidation_UT_03 );
        CPPUNIT_TEST( IPValidation_UT_04 );
        CPPUNIT_TEST( IPValidation_UT_05 );
        CPPUNIT_TEST( PortValidation_UT_01 );
        CPPUNIT_TEST( PortValidation_UT_02 );
	CPPUNIT_TEST( PortValidation_UT_03 );

        CPPUNIT_TEST_SUITE_END();
	protected:
		void PortValidation_UT_01();
		void PortValidation_UT_02();
		void PortValidation_UT_03();
		void IPValidation_UT_01();
		void IPValidation_UT_02();
		void IPValidation_UT_03();
		void IPValidation_UT_04();
		void IPValidation_UT_05();

	public:
		bool IPValidation(string);
		bool PortValidation(char *);
};

class Registration: public CPPUNIT_NS::TestFixture  //using textfixture class, inheriting class of text fixture
{

        CPPUNIT_TEST_SUITE( Registration ); //name of class has to be passed
        CPPUNIT_TEST( setphonenumber_UT_01 );  // we have to write those methods
        CPPUNIT_TEST( setphonenumber_UT_02 );
        CPPUNIT_TEST( setphonenumber_UT_03 );
        CPPUNIT_TEST( setphonenumber_UT_04 );
	CPPUNIT_TEST( settype_UT_01 );
	CPPUNIT_TEST( settype_UT_02 );
	CPPUNIT_TEST( settype_UT_03 );
	CPPUNIT_TEST( settype_UT_04 );
	//CPPUNIT_TEST( settype_UT_05 );
	//CPPUNIT_TEST( settype_UT_06 );
	CPPUNIT_TEST( setservice_UT_01 );
	CPPUNIT_TEST( setservice_UT_02 );
	CPPUNIT_TEST( setservice_UT_03 );
	//CPPUNIT_TEST( setservice_UT_04 );
	//CPPUNIT_TEST( setservice_UT_05 );
	CPPUNIT_TEST( setcallstatus_UT_01 );
	CPPUNIT_TEST( setcallstatus_UT_02 );
	CPPUNIT_TEST( setcallstatus_UT_03 );
	CPPUNIT_TEST( setcallstatus_UT_04 );
	CPPUNIT_TEST( setdest_UT_01 );
	CPPUNIT_TEST( setdest_UT_02 );
	CPPUNIT_TEST( setdest_UT_03 );
	CPPUNIT_TEST( setdest_UT_04 );
	CPPUNIT_TEST( setpasswd_UT_01 );
	CPPUNIT_TEST( setpasswd_UT_02 );
	CPPUNIT_TEST( setpasswd_UT_03 );
	CPPUNIT_TEST( setpasswd_UT_04 );
	CPPUNIT_TEST( setpasswd_UT_05 );
	CPPUNIT_TEST( setpasswd_UT_06 );
	CPPUNIT_TEST( setpasswd_UT_07 );
	CPPUNIT_TEST( setpasswd_UT_08 );

        //CPPUNIT_TEST();
        CPPUNIT_TEST_SUITE_END();
protected:
       //char username[20];
        
		char passwd[20],phoneNo[12],type[2],desti[11],serv[2],clientst[2],callstatus[2];
protected:
        // usually it returns void kind of stuffs
        void setphonenumber_UT_01();
        void setphonenumber_UT_02();
        void setphonenumber_UT_03();
        void setphonenumber_UT_04();
	void settype_UT_01();
	void settype_UT_02();
	void settype_UT_03();
	void settype_UT_04();
	//void settype_UT_05();
	//void settype_UT_06();
	void setservice_UT_01();
	void setservice_UT_02();
	void setservice_UT_03();
	//void setservice_UT_04();
	//void setservice_UT_05();
	void setcallstatus_UT_01();
	void setcallstatus_UT_02();
	void setcallstatus_UT_03();
	void setcallstatus_UT_04();
	void setdest_UT_01();
	void setdest_UT_02();
	void setdest_UT_03();
	void setdest_UT_04();
	void setpasswd_UT_01();
	void setpasswd_UT_02();
	void setpasswd_UT_03();
	void setpasswd_UT_04();
	void setpasswd_UT_05();
	void setpasswd_UT_06();
	void setpasswd_UT_07();
	void setpasswd_UT_08();

public:
	Registration(){}
	~Registration(){}
        void registeruser();

		//void setusername(char * u){strcpy(username,u);}
		bool setpasswd(char *);
		bool setphoneNo(char *);
		bool settype(char *);
		bool setservice(char *);
		bool setdest(char *);
		bool setclientst(char *);
		bool setcallstatus(char *);
		bool clientstatus();
};
