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

#define MAX_SENDER_THREAD_COUNT	10

#define MAX_RECV_PACKET_SIZE		300
#define MAX_SEND_PACKET_SIZE		1300

#define SECURE_CODE_C_TO_S 0x47
#define SECURE_CODE_S_TO_C 0x59

// MESSAGE ID
#define MSG_MEMO	40000
#define MSG_NEW_CONNECTION	40001
#define MSG_CLIENT_MESSAGE 40002

// DATA TYPE
#define DATA_TYPE_SIGN_UP			1
#define DATA_TYPE_SIGN_IN			2
#define DATA_TYPE_SIGN_OUT			3
#define DATA_TYPE_LOBBY_CHATTING	4
#define DATA_TYPE_INGAME_CHATTING	5
#define DATA_TYPE_CHANGE_USER_INFO	6
#define DATA_TYPE_INGAME_CMD		7
#define DATA_TYPE_ENTER_GAME_ROOM	8
#define DATA_TYPE_ESCAPE_GAME_ROOM	9
#define DATA_TYPE_HEART_BEAT		10
#define DATA_TYPE_INGAME_DATA		11

// LOG-IN ERROR TYPE
#define ERR_LOGIN_OK	0
#define ERR_LOGIN_PW	1
#define ERR_LOGIN_ID	2


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
	SOCKET ClientSocket;
} CLIENTINFO;
//---------------------------------------------------------------------------

// Client -> Server Message
typedef struct ST_CLIENTMESSAGE {
	CLIENTINFO ClientInfo;
	BYTE Data[MAX_RECV_PACKET_SIZE];
} CLIENTMSG;
//---------------------------------------------------------------------------

// Server -> Client Messate
typedef struct ST_SERVERMESSAGE {
	CLIENTINFO ClientInfo;
	BYTE Data[MAX_SEND_PACKET_SIZE];
} SERVERMSG;
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
#endif
