#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <deque>
#include "MMatchItem.h"
#include "MUID.h"
#include "MObject.h"
#include "MMatchGlobal.h"
#include "MMatchFriendInfo.h"
#include "MMatchClan.h"
#include "MMatchChannel.h"
#include "MSmartRefreshImpl.h"
#include "MQuestItem.h"
#include "MMatchAntiHack.h"
#include "MMatchHShield.h"
#include "GlobalTypes.h"
#include "BasicInfoHistory.h"
#include "HitRegistration.h"

enum MMatchUserGradeID : i32
{
	MMUG_FREE			= 0,
	MMUG_REGULAR		= 1,
	MMUG_STAR			= 2,

	MMUG_CRIMINAL		= 100,
	MMUG_WARNING_1		= 101,
	MMUG_WARNING_2		= 102,
	MMUG_WARNING_3		= 103,
	MMUG_CHAT_LIMITED	= 104,
	MMUG_PENALTY		= 105,

	MMUG_EVENTMASTER	= 252,
	MMUG_BLOCKED		= 253,
	MMUG_DEVELOPER		= 254,
	MMUG_ADMIN			= 255
};

enum MMatchDisconnectStatus
{
	MMDS_CONNECTED = 1,
	MMDS_DISCONN_WAIT,
	MMDS_DISCONNECT,

	MMDS_END,
};

enum MMatchPremiumGradeID
{
	MMPG_FREE			= 0,
	MMPG_PREMIUM_IP		= 1
};

enum MMatchSex
{
	MMS_MALE = 0,
	MMS_FEMALE = 1
};

enum MMatchBlockType
{
	MMBT_NO = 0,
	MMBT_BANNED,
	MMBT_MUTED,

	MMBT_END,
};


struct MMatchAccountInfo
{
	int						m_nAID;
	char					m_szUserID[32];
	MMatchUserGradeID		m_nUGrade;
	MMatchPremiumGradeID	m_nPGrade;
	MMatchBlockType			m_BlockType;
	SYSTEMTIME				m_EndBlockDate;

	MMatchAccountInfo() : m_nAID(-1), m_nUGrade(MMUG_FREE),
		m_nPGrade(MMPG_FREE), m_BlockType(MMBT_NO), m_szUserID()
	{}
};

// �÷��̾ ���� ��ġ�ϰ� �ִ� ��
enum MMatchPlace
{
	MMP_OUTSIDE	= 0,
	MMP_LOBBY = 1,
	MMP_STAGE	= 2,
	MMP_BATTLE	= 3,
	MMP_END
};

enum MMatchObjectStageState
{
	MOSS_NONREADY	= 0,
	MOSS_READY		= 1,
	MOSS_SHOP		= 2,
	MOSS_EQUIPMENT	= 3,
	MOSS_END
};

#define DEFAULT_CHAR_HP				100
#define DEFAULT_CHAR_AP				0

#define DBCACHING_REQUEST_POINT		40
struct DBCharCachingData
{
	int	nAddedXP;
	int	nAddedBP;
	int	nAddedKillCount;
	int	nAddedDeathCount;
	void Reset()
	{
		nAddedXP = 0;
		nAddedBP = 0;
		nAddedKillCount = 0;
		nAddedDeathCount = 0;
	}
	bool IsRequestUpdate()
	{
		if ((nAddedKillCount > DBCACHING_REQUEST_POINT) || (nAddedDeathCount > DBCACHING_REQUEST_POINT))
			return true;

		return false;
	}
};


// ĳ������ Ŭ������
struct MMatchCharClanInfo
{
	int					m_nClanID;							// db���� Ŭ�� ID
	char				m_szClanName[CLAN_NAME_LENGTH];		// Ŭ�� �̸�
	MMatchClanGrade		m_nGrade;							// Ŭ�������� ����
	int					m_nContPoint;						// Ŭ�� �⿩��
	string				m_strDeleteDate;

	MMatchCharClanInfo() {  Clear(); }
	void Clear()
	{
		m_nClanID = 0; 
		m_szClanName[0] = 0; 
		m_nGrade=MCG_NONE;
		m_nContPoint = 0;
		m_strDeleteDate.clear();
	}
	bool IsJoined() { return (m_nClanID == 0) ? false : true; }
};


#define DEFAULT_CHARINFO_MAXWEIGHT		100
#define DEFAULT_CHARINFO_SAFEFALLS		0
#define DEFAULT_CHARINFO_BONUSRATE		0.0f
#define DEFAULT_CHARINFO_PRIZE			0


/// ĳ���� ����
class MMatchCharInfo
{
public:
	unsigned long int	m_nCID;
	int					m_nCharNum;
	char				m_szName[MATCHOBJECT_NAME_LENGTH];
	int					m_nLevel;
	MMatchSex			m_nSex;			// ����
	int					m_nHair;		// �Ӹ�
	int					m_nFace;		// ��
	unsigned long int	m_nXP;
	int					m_nBP;
	float				m_fBonusRate;
	int					m_nPrize;
	int					m_nHP;
	int					m_nAP;
	int					m_nMaxWeight;
	int					m_nSafeFalls;
	int					m_nFR;
	int					m_nCR;
	int					m_nER;
	int					m_nWR;
	unsigned long int	m_nEquipedItemCIID[MMCIP_END];
	MMatchItemMap		m_ItemList;			// ������ ����
	MMatchEquipedItem	m_EquipedItem;		// ����ϰ� �ִ� ������ ����
	MMatchCharClanInfo	m_ClanInfo;			// Ŭ�� ����

	// ����Ʈ ������.
	MQuestItemMap		m_QuestItemList;
	DBQuestCachingData	m_DBQuestCachingData;
	DBQuestCachingData& GetDBQuestCachingData() { return m_DBQuestCachingData; }


	// ���� ���̺�
	MQuestMonsterBible	m_QMonsterBible;


	unsigned long int	m_nTotalPlayTimeSec;	// �÷��� �ð�
	u64					m_nConnTime;			// ������ �ð�(1�� = 1000)

	unsigned long int	m_nTotalKillCount;			// ��ü ų��
	unsigned long int	m_nTotalDeathCount;			// ��ü ������
	unsigned long int	m_nConnKillCount;			// �������ķ� ������ ų��
	unsigned long int	m_nConnDeathCount;			// �������ķ� ������ ������
	unsigned long int   m_nConnXP;					// �������ķ� ������ ����ġ

protected:
	DBCharCachingData	m_DBCachingData;
public:
	MMatchCharInfo() : m_nCID(0), m_nCharNum(0), m_nLevel(0), m_nSex(MMS_MALE), m_nFace(0),
		               m_nHair(0), m_nXP(0), m_nBP(0), m_fBonusRate(DEFAULT_CHARINFO_BONUSRATE), m_nPrize(DEFAULT_CHARINFO_PRIZE), m_nHP(0),
					   m_nAP(0), m_nMaxWeight(DEFAULT_CHARINFO_MAXWEIGHT), m_nSafeFalls(DEFAULT_CHARINFO_SAFEFALLS),
					   m_nFR(0), m_nCR(0), m_nER(0), m_nWR(0),
					   m_nConnTime(0), m_nTotalKillCount(0), m_nTotalDeathCount(0), m_nConnKillCount(0), m_nConnDeathCount(0), 
					   m_nConnXP(0)
	{
		memset(m_szName, 0, sizeof(m_szName));
		memset(m_nEquipedItemCIID, 0, sizeof(m_nEquipedItemCIID));
		memset(&m_DBCachingData, 0, sizeof(m_DBCachingData));
		memset(&m_QMonsterBible, 0, sizeof(MQuestMonsterBible) );

		m_QuestItemList.Clear();
		m_DBQuestCachingData.Reset();
	}
	void EquipFromItemList();
	void ClearItems();
	void Clear();
	void GetTotalWeight(int* poutWeight, int* poutMaxWeight);


	// db caching���� �Բ� �����ش�.
	void IncKill()
	{ 
		m_nTotalKillCount += 1;
		m_nConnKillCount += 1;
		m_DBCachingData.nAddedKillCount += 1;
	}
	void IncDeath()
	{ 
		m_nTotalDeathCount += 1;
		m_nConnDeathCount += 1;
		m_DBCachingData.nAddedDeathCount += 1;
	}
	void IncBP(int nAddedBP)		
	{ 
		m_nBP += nAddedBP;
		m_DBCachingData.nAddedBP += nAddedBP;
	}
	void DecBP(int nDecBP)
	{ 
		m_nBP -= nDecBP;
		m_DBCachingData.nAddedBP -= nDecBP;
	}
	void IncXP(int nAddedXP)
	{ 
		m_nConnXP += nAddedXP;
		m_nXP += nAddedXP;
		m_DBCachingData.nAddedXP += nAddedXP;
	}
	void DecXP(int nDecXP)
	{ 
		m_nConnXP -= nDecXP; 
		m_nXP -= nDecXP; 
		m_DBCachingData.nAddedXP -= nDecXP; 
	}

	DBCharCachingData* GetDBCachingData() { return &m_DBCachingData; }
};

class MMatchTimeSyncInfo final {
protected:
	int				m_nFoulCount = 0;
	u64				m_nLastSyncClock = 0;
public:
	int GetFoulCount()					{ return m_nFoulCount; }
	void AddFoulCount()					{ m_nFoulCount++; }
	void ResetFoulCount()				{ m_nFoulCount = 0; }
	auto GetLastSyncClock() const { return m_nLastSyncClock; }
	void Update(u64 nClock)				{ m_nLastSyncClock = nClock; }
};

// MatchObject�� ���Ӿȿ��� ����ϴ� ������
struct MMatchObjectGameInfo
{
	bool		bJoinedGame;		// ���ӿ� ���������� ���� - �������� ����������
};


class MMatchDisconnStatusInfo
{
public :
	MMatchDisconnStatusInfo() 
	{
		m_DisconnStatus						= MMDS_CONNECTED;
		m_dwLastDisconnStatusUpdatedTime	= GetGlobalTimeMS();
		m_bIsSendDisconnMsg					= false;
		m_dwDisconnSetTime					= 0;
		m_bIsUpdateDB						= false;
	}

	~MMatchDisconnStatusInfo() {}

	auto GetStatus() const { return m_DisconnStatus; }
	auto GetLastUpdatedTime() const { return m_dwLastDisconnStatusUpdatedTime; }
	auto GetMsgID() const { return m_dwMsgID; }
	auto GetBlockType() const { return m_BlockType; }
	auto GetBlockLevel() const { return m_BlockLevel; }
	auto& GetEndDate() const { return m_strEndDate; }
	auto& GetComment() const { return m_strComment; }
		
	const bool	IsSendDisconnMsg()	{ return m_bIsSendDisconnMsg; }
	void		SendCompleted()		{ m_bIsSendDisconnMsg = false; }	// MMatchServer���� Ŀ�ǵ� ó���� ���ؼ� ���...
																		// IsSendDisconnMsg�� ���� ���� �޽����� ������ �ϴ��� �˻���,
																		// Ŀ�ǵ带 �����Ŀ��� SendCompleted()�� ȣ���Ͽ� ������ �ߺ����� ������ ���� ���´�.
																		// �� ���� ����� ������ ���� ��. -by SungE. 2006-03-07.

	const bool IsUpdateDB()			{ return m_bIsUpdateDB; }
	void UpdateDataBaseCompleted()	{ m_bIsUpdateDB = false; } // Update�Ǹ��� ���� BlockType�� ���������� false�� ����.

	const bool IsDisconnectable( const u64 dwTime = GetGlobalTimeMS() )
	{
		if( (MMDS_DISCONNECT == GetStatus()) && (MINTERVAL_DISCONNECT_STATUS_MIN < (dwTime - m_dwDisconnSetTime)) )
			return true;
		return false;
	}
	
	void SetStatus( const MMatchDisconnectStatus Status )	
	{
		m_DisconnStatus = Status; 
		if( MMDS_DISCONN_WAIT == Status )
			SendDisconnMsgPrepared();

		if( MMDS_DISCONNECT == Status )
			m_dwDisconnSetTime = (GetGlobalTimeMS() - 2000);
		
	}
	void SetUpdateTime(u64 dwTime) { m_dwLastDisconnStatusUpdatedTime = dwTime; }
	void SetMsgID(u32 dwMsgID) { m_dwMsgID = dwMsgID; }
	void SetBlockType(MMatchBlockType BlockType) { m_BlockType = BlockType; m_bIsUpdateDB = true; }
	void SetBlockLevel(MMatchBlockLevel BlockLevel) { m_BlockLevel = BlockLevel; }
	void SetEndDate(const std::string& strEndDate) { m_strEndDate = strEndDate; }
	void SetComment(const std::string& strComment) { m_strComment = strComment; }

	void Update( u64 dwTime )
	{
		if( (dwTime - GetLastUpdatedTime()) > MINTERVAL_DISCONNECT_STATUS_MIN ) 
		{
			if( MMDS_DISCONN_WAIT == GetStatus() )
				SetStatus( MMDS_DISCONNECT );
			
			SetUpdateTime( dwTime );
		}
	}

private :
	void SendDisconnMsgPrepared()	{ m_bIsSendDisconnMsg = true; }

private :
	MMatchDisconnectStatus	m_DisconnStatus;
	u64						m_dwLastDisconnStatusUpdatedTime;
	u64						m_dwDisconnSetTime;
	DWORD					m_dwMsgID;
	MMatchBlockType			m_BlockType;
	MMatchBlockLevel		m_BlockLevel;
	string					m_strEndDate;
	string					m_strComment;
	bool					m_bIsSendDisconnMsg;
	bool					m_bIsUpdateDB;

	const static DWORD MINTERVAL_DISCONNECT_STATUS_MIN;
};


struct MMatchObjectChannelInfo
{
	MUID			uidChannel;
	MUID			uidRecentChannel;
	bool			bChannelListTransfer;
	MCHANNEL_TYPE	nChannelListType;
	unsigned long	nChannelListChecksum;
	u64				nTimeLastChannelListTrans;
	void Clear()
	{
		uidChannel = MUID(0,0);
		uidRecentChannel = MUID(0,0);
		bChannelListTransfer = false;
		nChannelListType = MCHANNEL_TYPE_PRESET;
		nChannelListChecksum = 0;
		nTimeLastChannelListTrans = 0;
	}
};

struct ClientSettings
{
	bool DebugOutput;
};


class MMatchObject : public MObject {
protected:
	MMatchAccountInfo			m_AccountInfo;		// ���� ����
	MMatchCharInfo*				m_pCharInfo;		// ĳ���� ����
	MMatchFriendInfo*			m_pFriendInfo;		// ģ������
	MMatchPlace					m_nPlace;			// ��ġ ����
	MMatchTimeSyncInfo			m_nTimeSyncInfo;	// ���ǵ��� ����	
	MMatchObjectChannelInfo		m_ChannelInfo;		// ä�� ����
	MMatchObjectGameInfo		m_GameInfo;			// ���Ӿȿ����� ����
	MMatchObjectAntiHackInfo	m_AntiHackInfo;		// XTrap���� ����ϴ� �͵� ����
	MMatchDisconnStatusInfo		m_DisconnStatusInfo;// �������� �������� ���� ����.
	MMatchObjectHShieldInfo		m_HSieldInfo;

	bool			m_bHacker;
	bool			m_bBridgePeer;
	bool			m_bRelayPeer;
	MUID			m_uidAgent;
	MMatchTeam		m_nTeam;

	DWORD			m_dwIP;
	char 			m_szIP[64];
	unsigned int	m_nPort;
	bool			m_bFreeLoginIP;

	unsigned char	m_nPlayerFlags;
	unsigned long	m_nUserOptionFlags;

	MUID			m_uidStage;
	MUID			m_uidChatRoom;

	bool			m_bStageListTransfer;
	unsigned long	m_nStageListChecksum;
	unsigned long	m_nStageListLastChecksum;
	u64				m_nTimeLastStageListTrans;
	int				m_nStageCursor;

	MRefreshClientChannelImpl		m_RefreshClientChannelImpl;
	MRefreshClientClanMemberImpl	m_RefreshClientClanMemberImpl;

	MMatchObjectStageState	m_nStageState;
	int				m_nLadderGroupID;
	bool			m_bLadderChallenging;

	bool			m_bEnterBattle;
	bool			m_bAlive;
	u64				m_nDeadTime;

	bool			m_bNewbie;
	bool			m_bForcedEntried;
	bool			m_bLaunchedGame;

	unsigned int			m_nKillCount;
	unsigned int			m_nDeathCount;
	unsigned long int		m_nAllRoundKillCount;
	unsigned long int		m_nAllRoundDeathCount;

	bool			m_bWasCallVote;

	bool			m_bDBFriendListRequested;
	u64				m_nTickLastPacketRecved;
	u64				m_nLastHShieldMsgRecved;
	bool			m_bHShieldMsgRecved;
	std::string				m_strCountryCode3;

	u64		m_dwLastHackCheckedTime;
	u64		m_dwLastRecvNewHashValueTime;
	bool	m_bIsRequestNewHashValue;

	u64		LastSpawnTime;

	u64 m_nLastPingTime;
	mutable unsigned long int m_nQuestLatency;
	
	// This is awkward.
	std::deque<int> Pings;
	int AveragePing;

	int MaxHP, MaxAP;
	int HP, AP;

	u64 LastHPAPInfoTime = 0;

	v3 Origin;
	v3 Direction;
	v3 Velocity;

protected:
	void UpdateChannelListChecksum(unsigned long nChecksum)	{ m_ChannelInfo.nChannelListChecksum = nChecksum; }
	unsigned long GetChannelListChecksum()					{ return m_ChannelInfo.nChannelListChecksum; }

	void UpdateStageListChecksum(unsigned long nChecksum)	{ m_nStageListChecksum = nChecksum; }
	unsigned long GetStageListChecksum()					{ return m_nStageListChecksum; }
	MMatchObject() : MObject()
	{
	}
	void DeathCount()				{ m_nDeathCount++; m_nAllRoundDeathCount++; }
	void KillCount()				{ m_nKillCount++; m_nAllRoundKillCount++; }

	void CheckClientHashValue( const DWORD dwTime );
public:
	MMatchObject(const MUID& uid);
	virtual ~MMatchObject();

	ClientSettings ClientSettings;

	char* GetName() { 
		if (m_pCharInfo)
			return m_pCharInfo->m_szName; 
		else
			return "Unknown";
	}
	char* GetAccountName()			{ return m_AccountInfo.m_szUserID; }

	bool GetBridgePeer()			{ return m_bBridgePeer; }
	void SetBridgePeer(bool bValue)	{ m_bBridgePeer = bValue; }
	bool GetRelayPeer()				{ return m_bRelayPeer; }
	void SetRelayPeer(bool bRelay)	{ m_bRelayPeer = bRelay; }
	const MUID& GetAgentUID()		{ return m_uidAgent; }
	void SetAgentUID(const MUID& uidAgent)	{ m_uidAgent = uidAgent; }

	void SetPeerAddr(DWORD dwIP, char* szIP, unsigned short nPort)	{ m_dwIP=dwIP; strcpy_safe(m_szIP, szIP); m_nPort = nPort; }
	DWORD GetIP()					{ return m_dwIP; }
	char* GetIPString()				{ return m_szIP; }
	unsigned short GetPort()		{ return m_nPort; }
	bool GetFreeLoginIP()			{ return m_bFreeLoginIP; }
	void SetFreeLoginIP(bool bFree)	{ m_bFreeLoginIP = bFree; }

	void ResetPlayerFlags()						{ m_nPlayerFlags = 0; }
	unsigned char GetPlayerFlags()				{ return m_nPlayerFlags; }
	bool CheckPlayerFlags(unsigned char nFlag)	{ return (m_nPlayerFlags&nFlag?true:false); }
	void SetPlayerFlag(unsigned char nFlagIdx, bool bSet)	
	{ 
		if (bSet) m_nPlayerFlags |= nFlagIdx; 
		else m_nPlayerFlags &= (0xff ^ nFlagIdx);
	}

	void SetUserOption(unsigned long nFlags)	{ m_nUserOptionFlags = nFlags; }
	bool CheckUserOption(unsigned long nFlag)	{ return (m_nUserOptionFlags&nFlag?true:false); }

	MUID GetChannelUID()						{ return m_ChannelInfo.uidChannel; }
	void SetChannelUID(const MUID& uid)			{ SetRecentChannelUID(m_ChannelInfo.uidChannel); m_ChannelInfo.uidChannel = uid; }
	MUID GetRecentChannelUID()					{ return m_ChannelInfo.uidRecentChannel; }
	void SetRecentChannelUID(const MUID& uid)	{ m_ChannelInfo.uidRecentChannel = uid; }

	MUID GetStageUID() const			{ return m_uidStage; }
	void SetStageUID(const MUID& uid)	{ m_uidStage = uid; }
	MUID GetChatRoomUID() const			{ return m_uidChatRoom; }
	void SetChatRoomUID(const MUID& uid){ m_uidChatRoom = uid; }

	bool CheckChannelListTransfer() const { return m_ChannelInfo.bChannelListTransfer; }
	void SetChannelListTransfer(const bool bVal, const MCHANNEL_TYPE nChannelType=MCHANNEL_TYPE_PRESET);

	bool CheckStageListTransfer() const { return m_bStageListTransfer; }
	void SetStageListTransfer(bool bVal)	{ m_bStageListTransfer = bVal; UpdateStageListChecksum(0); }

	MRefreshClientChannelImpl* GetRefreshClientChannelImplement()		{ return &m_RefreshClientChannelImpl; }
	MRefreshClientClanMemberImpl* GetRefreshClientClanMemberImplement()	{ return &m_RefreshClientClanMemberImpl; }

	MMatchTeam GetTeam() const { return m_nTeam; }
	void SetTeam(MMatchTeam nTeam);
	MMatchObjectStageState GetStageState() const { return m_nStageState; }
	void SetStageState(MMatchObjectStageState nStageState)	{ m_nStageState = nStageState; }
	bool GetEnterBattle() const		{ return m_bEnterBattle; }
	void SetEnterBattle(bool bEnter){ m_bEnterBattle = bEnter; }
	bool CheckAlive() const			{ return m_bAlive; }
	bool IsAlive() const			{ return m_bAlive; }
	void SetAlive(bool bVal)		{ m_bAlive = bVal; }
	void SetKillCount(unsigned int nKillCount) { m_nKillCount = nKillCount; }
	unsigned int GetKillCount()		{ return m_nKillCount; }
	void SetDeathCount(unsigned int nDeathCount) { m_nDeathCount = nDeathCount; }
	unsigned int GetDeathCount()	{ return m_nDeathCount; }
	unsigned int GetAllRoundKillCount()	{ return m_nAllRoundKillCount; }
	unsigned int GetAllRoundDeathCount()	{ return m_nAllRoundDeathCount; }
	void SetAllRoundKillCount(unsigned int nAllRoundKillCount) { m_nAllRoundKillCount = nAllRoundKillCount; }
	void SetAllRoundDeathCount(unsigned int nAllRoundDeathCount) { m_nAllRoundDeathCount = nAllRoundDeathCount; }
	void FreeCharInfo();
	void FreeFriendInfo();
	void OnDead();
	void OnKill();
	bool IsEnabledRespawnDeathTime(u64 nNowTime) const;

	void SetForcedEntry(bool bVal) { m_bForcedEntried = bVal; }
	bool IsForcedEntried() { return m_bForcedEntried; }
	void SetLaunchedGame(bool bVal) { m_bLaunchedGame = bVal; }
	bool IsLaunchedGame() { return m_bLaunchedGame; }
	void CheckNewbie(int nCharMaxLevel);
	bool IsNewbie()					{ return m_bNewbie; }
	bool IsHacker()					{ return m_bHacker; }
	void SetHacker(bool bHacker)	{ m_bHacker = bHacker; }

	inline bool WasCallVote()						{ return m_bWasCallVote; }
	inline void SetVoteState( const bool bState )	{ m_bWasCallVote = bState; }

	inline auto	GetTickLastPacketRecved()		{ return m_nTickLastPacketRecved; }
	inline auto	GetLastHShieldMsgRecved()		{ return m_nLastHShieldMsgRecved; }
	inline bool				GetHShieldMsgRecved()			{ return m_bHShieldMsgRecved; }
	inline void				SetHShieldMsgRecved(bool bSet)	{ m_bHShieldMsgRecved = bSet; }


	void UpdateTickLastPacketRecved();
	void UpdateLastHShieldMsgRecved();

	void SetLastRecvNewHashValueTime( const DWORD dwTime )	
	{ 
		m_dwLastRecvNewHashValueTime = dwTime; 
		m_bIsRequestNewHashValue = false; 
	}

	auto GetLastSpawnTime(void) const				{ return LastSpawnTime;		}
	void SetLastSpawnTime(u64 Time)					{ LastSpawnTime = Time;	}

	inline u32					GetQuestLatency() const;
	inline void					SetQuestLatency(u64 l);
	inline void					SetPingTime(u64 t);
public:
	int GetLadderGroupID()			{ return m_nLadderGroupID; }
	void SetLadderGroupID(int nID)	{ m_nLadderGroupID = nID; }
	void SetLadderChallenging(bool bVal) { m_bLadderChallenging = bVal; }
	bool IsLadderChallenging()			{ return m_bLadderChallenging; }
public:
	MMatchAccountInfo* GetAccountInfo() { return &m_AccountInfo; }
	const MMatchAccountInfo* GetAccountInfo() const { return &m_AccountInfo; }
	MMatchCharInfo* GetCharInfo() { return m_pCharInfo; }
	const MMatchCharInfo* GetCharInfo() const { return m_pCharInfo; }
	void SetCharInfo(MMatchCharInfo* pCharInfo);
	
	MMatchFriendInfo* GetFriendInfo()	{ return m_pFriendInfo; }
	void SetFriendInfo(MMatchFriendInfo* pFriendInfo);
	bool DBFriendListRequested()	{ return m_bDBFriendListRequested; }
	MMatchPlace GetPlace()			{ return m_nPlace; }
	void SetPlace(MMatchPlace nPlace);
	MMatchTimeSyncInfo* GetSyncInfo()	{ return &m_nTimeSyncInfo; }
	MMatchObjectAntiHackInfo* GetAntiHackInfo()		{ return &m_AntiHackInfo; }
	MMatchDisconnStatusInfo& GetDisconnStatusInfo() { return  m_DisconnStatusInfo; }
	MMatchObjectHShieldInfo* GetHShieldInfo()		{ return &m_HSieldInfo; }

	void Tick(u64 nTime);

	void OnStageJoin();
	void OnEnterBattle();
	void OnLeaveBattle();
	void OnInitRound();

	void SetStageCursor(int nStageCursor);
	const MMatchObjectGameInfo* GetGameInfo() { return &m_GameInfo; }

	void			SetCountryCode3( const string strCountryCode3 ) { m_strCountryCode3 = strCountryCode3; }
	const string&	GetCountryCode3() const							{ return m_strCountryCode3; }

	void SetXTrapHackerDisconnectWaitInfo( const MMatchDisconnectStatus DisStatus = MMDS_DISCONN_WAIT );
	void SetHShieldHackerDisconnectWaitInfo( const MMatchDisconnectStatus DisStatus = MMDS_DISCONN_WAIT );
	void SetBadFileCRCDisconnectWaitInfo( const MMatchDisconnectStatus DisStatus = MMDS_DISCONN_WAIT );

	void AddPing(int Ping)
	{
		Pings.push_front(Ping);

		while (Pings.size() > 10)
			Pings.pop_back();

		int sum = 0;
		for (auto val : Pings)
			sum += val;

		AveragePing = sum / Pings.size();
	}

	auto GetPing() const
	{
		return AveragePing;
	}

	void GetPositions(v3* Head, v3* Foot, double Time) const;
	auto& GetPosition() const { return Origin; }
	auto& GetDirection() const { return Direction; }
	auto& GetVelocity() const { return Velocity; }

	BasicInfoHistoryManager BasicInfoHistory;

	auto GetSelectedSlot() const
	{
		if (BasicInfoHistory.empty())
			return MMCIP_PRIMARY;

		return BasicInfoHistory.front().SelectedSlot;
	}

	auto HitTest(const v3& src, const v3& dest, double Time, v3* OutPos = nullptr)
	{
		v3 Head, Foot;
		GetPositions(&Head, &Foot, Time);
		return PlayerHitTest(Head, Foot, src, dest, OutPos);
	}

	void SetMaxHPAP();
	void OnDamaged(const MMatchObject& Attacker, const v3& SrcPos,
		ZDAMAGETYPE DamageType, MMatchWeaponType WeaponType, int Damage, float PiercingRatio);
	void Heal(int Amount);
	void ResetHPAP();

public:
	enum MMO_ACTION
	{
		MMOA_STAGE_FOLLOW,
		MMOA_MAX
	};
	bool CheckEnableAction(MMO_ACTION nAction);		// �ش� �׼��� �������� ���� - �ʿ��Ҷ����� �߰��Ѵ�.

	bool m_bQuestRecvPong;
	DWORD m_dwHShieldCheckCount;
};

class MMatchObjectList : public map<MUID, MMatchObject*>{};

// ĳ���� �����Ҷ� �ִ� �⺻ ������
struct MINITIALCOSTUME
{
	// ����
	unsigned int nMeleeItemID;
	unsigned int nPrimaryItemID;
	unsigned int nSecondaryItemID;
	unsigned int nCustom1ItemID;
	unsigned int nCustom2ItemID;

	// ��� ������
	unsigned int nChestItemID;
	unsigned int nHandsItemID;
	unsigned int nLegsItemID;
	unsigned int nFeetItemID;
};

#define MAX_COSTUME_TEMPLATE		6
const MINITIALCOSTUME g_InitialCostume[MAX_COSTUME_TEMPLATE][2] = 
{ 
	{{1, 5001, 4001, 30301, 0,     21001, 0, 23001, 0},	{1, 5001, 4001, 30301, 0,     21501, 0, 23501, 0}},	// �ǳ���Ʈ
	{{2, 5002, 0,    30301, 0,     21001, 0, 23001, 0},	{2, 5002, 0,    30301, 0,     21501, 0, 23501, 0}},	// ��������
	{{1, 4005, 5001, 30401, 0,     21001, 0, 23001, 0},	{1, 4005, 5001, 30401, 0,     21501, 0, 23501, 0}},	// �ּ���
	{{2, 4001, 0,    30401, 0,     21001, 0, 23001, 0},	{2, 4001, 0,    30401, 0,     21501, 0, 23501, 0}},	// ��ī��Ʈ
	{{2, 4002, 0,    30401, 30001, 21001, 0, 23001, 0},	{2, 4002, 0,    30401, 30001, 21501, 0, 23501, 0}},	// ��������Ʈ
	{{1, 4006, 0,	 30101, 30001, 21001, 0, 23001, 0},	{1, 4006, 4006, 30101, 30001, 21501, 0, 23501, 0}}	// ����
};

/*
const unsigned int g_InitialHair[4][2] = 
{
	{10000, 10022},
	{10001, 10023},
	{10002, 10024},
	{10003, 10025}
};
*/

#define MAX_COSTUME_HAIR		5
const string g_szHairMeshName[MAX_COSTUME_HAIR][2] = 
{
	{"eq_head_01", "eq_head_pony"},
	{"eq_head_02", "eq_head_hair001"},
	{"eq_head_08", "eq_head_hair04"},
	{"eq_head_05", "eq_head_hair006"},
	{"eq_head_08", "eq_head_hair002"}		// �̰� ���� ������ - ���߿� �ٸ� �𵨷� ��ü�ص� ��
};

#define MAX_COSTUME_FACE		20
const string g_szFaceMeshName[MAX_COSTUME_FACE][2] = 
{
	{"eq_face_01", "eq_face_001"},
	{"eq_face_02", "eq_face_002"},
	{"eq_face_04", "eq_face_003"},
	{"eq_face_05", "eq_face_004"},
	{ "eq_face_a01", "eq_face_001" },
	{ "eq_face_newface01", "eq_face_newface01" },
	{ "eq_face_newface02", "eq_face_newface02" },
	{ "eq_face_newface03", "eq_face_newface03" },
	{ "eq_face_newface04", "eq_face_newface04" },
	{ "eq_face_newface05", "eq_face_newface05" },
	{ "eq_face_newface06", "eq_face_newface06" },
	{ "eq_face_newface07", "eq_face_newface07" },
	{ "eq_face_newface08", "eq_face_newface08" },
	{ "eq_face_newface09", "eq_face_newface09" },
	{ "eq_face_newface10", "eq_face_newface10" },
	{ "eq_face_newface11", "eq_face_newface11" },
	{ "eq_face_newface12", "eq_face_newface12" },
	{ "eq_face_newface13", "eq_face_newface13" },
	{ "eq_face_newface13", "eq_face_newface14" },
	{ "eq_face_newface13", "eq_face_newface15" },
};


// MC_MATCH_STAGE_ENTERBATTLE Ŀ�ǵ忡�� ���̴� �Ķ��Ÿ
enum MCmdEnterBattleParam
{
	MCEP_NORMAL = 0,
	MCEP_FORCED = 1,		// ����
	MCEP_END
};

// ���� �� �ִ� ���������� üũ
bool IsEquipableItem(unsigned long int nItemID, int nPlayerLevel, MMatchSex nPlayerSex);

inline bool IsEnabledObject(MMatchObject* pObject) 
{
	if ((pObject == NULL) || (pObject->GetCharInfo() == NULL)) return false;
	return true;
}

inline bool IsAdminGrade(MMatchUserGradeID nGrade) 
{
	if ((nGrade == MMUG_EVENTMASTER) || 
		(nGrade == MMUG_ADMIN) || 
		(nGrade == MMUG_DEVELOPER))
		return true;

	return false;
}

inline bool IsAdminGrade(MMatchObject* pObject) 
{
	if (pObject == NULL) return false;

	return IsAdminGrade(pObject->GetAccountInfo()->m_nUGrade);
}


//////////////////////////////////////////////////////////////////////////


u32 MMatchObject::GetQuestLatency() const
{
	auto nowTime = GetGlobalTimeMS();

	auto ret = static_cast<u32>(nowTime - m_nLastPingTime);

	if (ret > m_nQuestLatency)
		m_nQuestLatency = ret;

	return m_nQuestLatency;
}

void MMatchObject::SetQuestLatency(u64 l)
{
	m_nQuestLatency = static_cast<u32>(l - m_nLastPingTime);
}

void MMatchObject::SetPingTime(u64 t)
{
	m_nLastPingTime = t;
}