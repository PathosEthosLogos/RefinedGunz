#pragma once

struct REPLAY_STAGE_SETTING_NODE_OLD
{
	MUID				uidStage;
	char				szMapName[32];	// ���̸�
	char				nMapIndex;					// ���ε���
	MMATCH_GAMETYPE		nGameType;					// ����Ÿ��
	int					nRoundMax;					// ����
	int					nLimitTime;					// ���ѽð�(1 - 1��)
	int					nLimitLevel;				// ���ѷ���
	int					nMaxPlayers;				// �ִ��ο�
	bool				bTeamKillEnabled;			// ��ų����
	bool				bTeamWinThePoint;			// ������ ����
	bool				bForcedEntryEnabled;		// ������ ���� ����
};

struct REPLAY_STAGE_SETTING_NODE_FG
{
	MUID				uidStage;
	char				szMapName[32];
	char				nMapIndex;
	MMATCH_GAMETYPE		nGameType;
	int					nRoundMax;
	int					nLimitTime;
	int					nLimitLevel;
	int					nMaxPlayers;
	bool				bTeamKillEnabled;
	bool				bTeamWinThePoint;
	bool				bForcedEntryEnabled;
	char				szStageName[64];
};

struct REPLAY_STAGE_SETTING_NODE_V11
{
	MUID				uidStage;
	char				szMapName[32];
	char unk[32];
	char				nMapIndex;
	MMATCH_GAMETYPE		nGameType;
	int					nRoundMax;
	int					nLimitTime;
	int					nLimitLevel;
	int					nMaxPlayers;
	bool				bTeamKillEnabled;
	bool				bTeamWinThePoint;
	bool				bForcedEntryEnabled;
};

#pragma pack(push)
#pragma pack(1)

struct MTD_CharInfo_V5
{
	// ĳ���� ����
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	// ������ ����
	unsigned long int	nEquipedItemDesc[12];

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;
};

struct MTD_CharInfo_V6
{
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	// ������ ����
	unsigned long int	nEquipedItemDesc[17];

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;

	MUID				uidEquipedItem[17];
	unsigned long int	nEquipedItemCount[17];
};

struct MTD_CharInfo_V11
{
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	// ������ ����
	unsigned long int	nEquipedItemDesc[17];

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;

	MUID				uidEquipedItem[17];
	unsigned long int	nEquipedItemCount[17];

	char unk[8];
};

typedef MTD_CharInfo_V6 MTD_CharInfo_FG_V7_0;

struct MTD_CharInfo_FG_V7_1
{
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	unsigned long int	nEquipedItemDesc[22];

	MMatchUserGradeID	nUGradeID;

	unsigned int		nClanCLID;

	int					nDTLastWeekGrade;

	__int64				uidEquipedItem[22];
	unsigned long int	nEquipedItemCount[22];
	unsigned long int	nEquipedItemRarity[22];
	unsigned long int	nEquipedItemLevel[22];
};

struct MTD_CharInfo_FG_V9
{
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	// ������ ����
	unsigned long int	nEquipedItemDesc[22];

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;

	DWORD unk[6];

	// ������ ���� �߰�
	__int64				uidEquipedItem[22];
	unsigned long int	nEquipedItemCount[22];
	unsigned long int	nEquipedItemRarity[22];
	unsigned long int	nEquipedItemLevel[22];

	char unk2[24];
};

struct BulletInfo
{
	int Clip;
	int Magazine;
};

#include "ZCharacterStructs.h"

template<size_t NumItems>
struct ZCharacterReplayStateImpl
{
	MUID UID;
	ZCharacterProperty Property;
	float HP;
	float AP;
	ZCharacterStatus Status;

	BulletInfo BulletInfos[NumItems];

	D3DXVECTOR3 Position;
	D3DXVECTOR3 Direction;

	MMatchTeam Team;

	bool Dead;

	bool HidingAdmin;
};

typedef ZCharacterReplayStateImpl<MMCIP_END> ZCharacterReplayState;
typedef ZCharacterReplayStateImpl<17> ZCharacterReplayState_FG_V7_0;
typedef ZCharacterReplayStateImpl<22> ZCharacterReplayState_FG_V7_1;
typedef ZCharacterReplayStateImpl<24> ZCharacterReplayState_FG_V9;
typedef ZCharacterReplayStateImpl<17> ZCharacterReplayState_Official_V6;
typedef ZCharacterReplayStateImpl<34> ZCharacterReplayState_Official_V11;

#pragma pack(pop)

struct ReplayPlayerInfo
{
	bool IsHero;
	MTD_CharInfo Info;
	ZCharacterReplayState State;
};