﻿#ifndef ROLE_SKILL_H
#define ROLE_SKILL_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "ui_role_skill.h"
#include "def_skill.h"

class role_skill : public QDialog
{
	Q_OBJECT

	const qint32 MaxFightSkill = 10;
public:
	role_skill(QWidget *parent, QLabel *DisplayCtrl_coin);
	~role_skill();

protected:
	void closeEvent(QCloseEvent * event);

private slots:
	void on_btn_ok_clicked(void);
	void on_btn_close_clicked(void);
	void on_btn_reset_clicked(void);
	void on_btn_study_clicked(void);
	void on_checkBox_used_stateChanged(int state);
	
private:
	const Info_SkillBasic *FindSkill(skillID id);

	//根据角色职业而初始化界面。函数与角色技能等相关设置紧密耦合。
	bool InitUI(Vocation voc);
	bool InitSkillTree_Warrior(const QSize& btnSize, const QSize& CheckSize);
	bool InitSkillTree_Magic(const QSize& btnSize, const QSize& CheckSize);
	bool InitSkillTree_Taoist(const QSize& btnSize, const QSize& CheckSize);

	bool CreateSkillBtn(const QSize& btnSize, const QSize& CheckSize, const QPoint *point, const QPoint &ptOffset);
	bool CreateLine_H(const QRect *rtLine, qint32 nCount);
	bool CreateLine_V(const QRect *rtLine, qint32 nCount);

	void process_btn_Tree(quint32 nIndex);

	void process_StudyInfo(qint32 lv, qint32 studyLevel, qint32 maxSkillLv);

signals:
	void UpdateCoin(void);

private:
	Ui::role_skill ui;
	qint32 btnIndex;
	qint32 si;						//已选择“使用”的技能数量。
	qint32 currentSkillID, spend;

	QVector<QPushButton *> skillBtn;
	QVector<QLabel *>lbl_SI;

	MapSkillStudy *m_skill_study;

	QLabel *lbl_coin;
};

#endif // ROLE_SKILL_H
