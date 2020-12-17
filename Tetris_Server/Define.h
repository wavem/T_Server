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
#define DATA_TYPE_MAKE_GAME_ROOM	8
#define DATA_TYPE_ENTER_GAME_ROOM	9
#define DATA_TYPE_ESCAPE_GAME_ROOM	10
#define DATA_TYPE_HEART_BEAT		11
#define DATA_TYPE_INGAME_DATA		12

#define DATA_TYPE_LOBBY_ROOMSTATUS	0xF1
#define DATA_TYPE_LOBBY_PLAYERLIST	0xF2

// LOG-IN ERROR TYPE
#define ERR_LOGIN_OK	0
#define ERR_LOGIN_PW	1
#define ERR_LOGIN_ID	2



// MAX ROOM COUNT
#define MAX_GAMEROOM_COUNT	24

// CLIENT SCREEN STATUS
#define CLIENT_SCREEN_IS_LOGIN		0
#define CLIENT_SCREEN_IS_LOBBY  	1
#define CLIENT_SCREEN_IS_GAME		2
#define CLIENT_SCREEN_IS_ROOM_01	101
#define CLIENT_SCREEN_IS_ROOM_02	102
#define CLIENT_SCREEN_IS_ROOM_03	103
#define CLIENT_SCREEN_IS_ROOM_04	104
#define CLIENT_SCREEN_IS_ROOM_05	105
#define CLIENT_SCREEN_IS_ROOM_06	106
#define CLIENT_SCREEN_IS_ROOM_07	107
#define CLIENT_SCREEN_IS_ROOM_08	108
#define CLIENT_SCREEN_IS_ROOM_09	109
#define CLIENT_SCREEN_IS_ROOM_10	110
#define CLIENT_SCREEN_IS_ROOM_11	111
#define CLIENT_SCREEN_IS_ROOM_12	112
#define CLIENT_SCREEN_IS_ROOM_13	113
#define CLIENT_SCREEN_IS_ROOM_14	114
#define CLIENT_SCREEN_IS_ROOM_15	115
#define CLIENT_SCREEN_IS_ROOM_16	116
#define CLIENT_SCREEN_IS_ROOM_17	117
#define CLIENT_SCREEN_IS_ROOM_18	118
#define CLIENT_SCREEN_IS_ROOM_19	119
#define CLIENT_SCREEN_IS_ROOM_20	120
#define CLIENT_SCREEN_IS_ROOM_21	121
#define CLIENT_SCREEN_IS_ROOM_22	122
#define CLIENT_SCREEN_IS_ROOM_23	123
#define CLIENT_SCREEN_IS_ROOM_24	124

// USER LEVEL
#define USER_LEVEL_0	0 // 신입
#define USER_LEVEL_1	1 // 루키
#define USER_LEVEL_2	2 // 초보
#define USER_LEVEL_3	3 // 하수
#define USER_LEVEL_4	4 // 중수
#define USER_LEVEL_5	5 // 고수
#define USER_LEVEL_6	6 // 초고수
#define USER_LEVEL_7	7 // 영웅
#define USER_LEVEL_8	8 // 전설
#define USER_LEVEL_9	9 // 신






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

// ROOM INFORMATION
typedef struct ST_ROOM {
	BYTE No;
	BYTE State;
	BYTE TeamType;
	BYTE ItemType;
	UnicodeString Title;
	UnicodeString MasterID;
	BYTE PlayerCount;
	bool IsPrivate;
	BYTE ClientID[6];
} ROOM;
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
