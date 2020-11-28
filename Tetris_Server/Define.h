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

// MESSAGE ID
#define MSG_MEMO	40000
#define MSG_NEW_CONNECTION	40001

// CLIENT INFORMATION
typedef struct ST_CLIENTINFO {
	int ClientIndex;
	TDateTime ConnectionDateTime;
	struct sockaddr_in ClientSockAddrIn;

} CLIENTINFO;





//---------------------------------------------------------------------------
#endif
