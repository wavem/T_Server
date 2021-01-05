//---------------------------------------------------------------------------

#ifndef DefineH
#define DefineH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
//#include <winsock2.h>

#define VERSION_MAJOR	1
#define VERSION_MINOR	1

//#define TCP_SERVER_IP	"192.168.0.51"
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
#define DATA_TYPE_INNER_ROOM_STATUS 0xF3
#define DATA_TYPE_BLOCK_ROOM_STATUS	0xF4
#define DATA_TYPE_VERSION_INFO_REQ	0xF5

// LOG-IN ERROR TYPE
#define ERR_LOGIN_OK	0
#define ERR_LOGIN_PW	1
#define ERR_LOGIN_ID	2



// MAX ROOM COUNT
#define MAX_GAMEROOM_COUNT	10

// CLIENT SCREEN STATUS
#define CLIENT_SCREEN_IS_LOGIN		11
#define CLIENT_SCREEN_IS_LOBBY  	12

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
typedef struct ST_ROOMCLIENTSTATUS {
	bool Connected;
	bool Life; // True == Alive, False == Death
	BYTE TeamIdx; // 0 == Private, 1 or 2 == Team Number
	BYTE Win; // 0 == Unknown, 1 == win, 2 == defeat
	BYTE State; // Like Blind....
} ROOMCLIENTSTATUS;
//---------------------------------------------------------------------------

typedef struct ST_ROOMSTATUS_OUTSIDE{
	// For Client (witn no entered in game room)
	BYTE RoomNumber;
	UnicodeString Title; // MAX UNICODE STRING LENGTH == 13 (Total 26 + 2 = 28 BYTE)
	BYTE State; // 0 == Empty, 1 == Wait, 2 == On Game
	BYTE TeamType; // Team or Private // 0 == Private, 1 == Team
	BYTE ItemType; // Item or NoTem // 0 == Notem, 1 == Item
	BYTE PlayerCount; // 0 ~ 6
} ROOMSTATUS_OUT;
//---------------------------------------------------------------------------

typedef struct ST_ROOMSTATUS_INSIDE {
	// For Server (for whom entered in game room)
	bool IsStart;
	BYTE ClientIdx[6];
	BYTE ClientGrade[6];
	UnicodeString ClientUserID[6];
	ROOMCLIENTSTATUS ClientStatus[6];
	BYTE SpeedLevel; // 0 ~ 9
	BYTE RoomMasterIndex;
} ROOMSTATUS_IN;
//---------------------------------------------------------------------------

typedef struct ST_ROOMBLOCK {
	BYTE BlockStatus[10][20];
} ROOMBLOCK;
//---------------------------------------------------------------------------

typedef struct ST_ROOM {
	bool IsCreated;
	ROOMSTATUS_OUT RoomStatus_Out;
	ROOMSTATUS_IN RoomStatus_In;
	ROOMBLOCK RoomBlock[6];
} ROOM;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#endif
