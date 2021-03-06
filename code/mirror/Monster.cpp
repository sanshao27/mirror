#include "Monster.h"

CMonster::CMonster()
	:COrganisms("unKnow", 0)
{
	set_camps(2);
}

CMonster::~CMonster()
{
}

bool CMonster::ReplaceSoul(const MonsterInfo &info, bool boss)
{
	bBoss = info.boss;
	id = info.ID;
	set_BasicInfo(info.name, 0, Voc_Unknow);
	set_levelInfo(info.level, info.exp);
	set_head(info.photo);	
	set_hp_m(info.hp);
	set_mp_m(info.mp);
	set_dc(info.DC1, info.DC2);
	set_mc(info.MC1, info.MC2);
	set_sc(0, 0);
	set_ac(info.AC);
	set_mac(info.MAC);
	set_intervel(info.interval);
	set_hit(info.hit);
	set_dodge(info.dodge);

	set_rhp(info.hp >> 7);

	SkillStudy sk;
	if (info.DC2 > info.MC2) {
		sk.id = 220101;
	} else {
		sk.id = 220102;
	}
	sk.level = 1;
	sk.usdIndex = 1;

	MapSkillStudy &MapSkill = get_skill_study();
	MapSkill.clear();
	MapSkill.insert(sk.id, sk);
	InitFightSkill();
	return true;
}