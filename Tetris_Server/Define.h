//---------------------------------------------------------------------------

#ifndef DefineH
#define DefineH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
//#include <winsock2.h>

#define TCP_SERVER_IP	"192.168.0.51"
#define TCP_SERVER_PORT		14759

#define MAX_TCP_CLIENT_LISTENING_COUNT	10
#define MAX_TCP_CLIENT_USER_COUNT		60

#define MAX_PACKET_SIZE		300

#define SECURE_CODE_C_TO_S 0x47
#define SECURE_CODE_S_TO_C 0x59

// MESSAGE ID
#define MSG_MEMO	40000
#define MSG_NEW_CONNECTION	40001

// THREAD STATUS
enum ThreadWorkingType
{
	THREAD_STOP = 0,
	THREAD_RUNNING = 1,
	THREAD_TERMINATED = 2,
};
//---------------------------------------------------------------------------

// CLIENT INFORMATION
typedef struct ST_CLIENTINFO {
	int ClientIndex;
	TDateTime ConnectionDateTime;
	struct sockaddr_in ClientSockAddrIn;

} CLIENTINFO;
//---------------------------------------------------------------------------

typedef struct ST_CLIENTMESSAGE {
	CLIENTINFO ClientInfo;
	BYTE Data[MSG_NEW_CONNECTION];
} CLIENTMSG;







//---------------------------------------------------------------------------
#endif
