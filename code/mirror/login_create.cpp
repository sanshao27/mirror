#include "login_create.h"
#include "RoleDefine.h"
#include <QMessageBox>
#include <QFile>

login_create::login_create(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	vocation = 1;
	gender = 1;
	bCreate = false;
}

login_create::~login_create()
{

}

void login_create::changePhoto()
{
	qint32 headNo = ((vocation - 1) * 2 + gender) * 10;
	QString photo = (":/role/Resources/role/") + QString::number(headNo) + ".png";
	ui.lbl_role_photo->setPixmap(QPixmap(photo));
}
void login_create::on_btn_vocation_1_clicked()
{
	vocation = 1;
	changePhoto();
}
void login_create::on_btn_vocation_2_clicked()
{
	vocation = 2;
	changePhoto();
}
void login_create::on_btn_vocation_3_clicked()
{
	vocation = 3;
	changePhoto();
}
void login_create::on_btn_gender_m_clicked()
{
	gender = 1;
	changePhoto();
}
void login_create::on_btn_gender_f_clicked()
{
	gender = 2;
	changePhoto();
}
void login_create::on_btn_ok_clicked()
{
	QString strTmp = ui.edit_role_name->text();
	if (strTmp.isEmpty())
	{
		QString title = QStringLiteral("��ʾ");
		QString message = QStringLiteral("�û�������Ϊ�ա�");
		QMessageBox msgBox(QMessageBox::Question, title, message);
		msgBox.addButton(QStringLiteral(" �� "), QMessageBox::AcceptRole);
		msgBox.exec();
	}
	else
	{
		bCreate = CreateRole(strTmp);
		if (!bCreate)
		{
			
		}
		else
		{
			done(QDialog::Accepted);
		}
	}
}

bool login_create::CreateRole(const QString &name)
{
	RoleInfo myRole;

	myRole.reputation = myRole.exp = 0;
	myRole.strength = myRole.wisdom = myRole.spirit = myRole.life = myRole.agility = myRole.potential = 0;

	myRole.vocation = vocation;
	myRole.gender = gender;
	myRole.level = 1;
	myRole.coin = 20000;
	myRole.gold = 1000;
#ifdef _DEBUG
	myRole.exp = 9000000;
#endif

	QFile file(SaveFileName);
	if (!file.open(QIODevice::WriteOnly))
	{
		return false;
	}

	QDataStream out(&file);
	out << SaveFileVer;
	//������Ϣ
	out << name << myRole.vocation << myRole.gender;
	out << myRole.coin << myRole.gold << myRole.reputation << myRole.exp << myRole.level;
	out << myRole.strength << myRole.wisdom << myRole.spirit << myRole.life << myRole.agility << myRole.potential;
	//��ɫ���ϵ�װ����Ϣ
	for (quint32 i = 0; i < MaxEquipCountForRole; i++)
	{
		out << 0;
	}

	//���߱��������ֿ߲⡢װ��������װ���ֿ��Ϊ�ա�
	quint32 bag_item_size, bag_equip_size, store_item_size, store_equip_size;
	bag_item_size = bag_equip_size = store_item_size = store_equip_size = 0;
	out << bag_item_size << bag_equip_size << store_item_size << store_equip_size;
	file.close();
	return true;
}