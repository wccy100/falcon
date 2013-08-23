// =====================================================================================
// 
//       Filename:  LinkTreeWidget.cpp
//
//    Description:  自动上线主机显示
//
//        Version:  1.0
//        Created:  2013年08月20日 11时08分08秒
//       Revision:  none
//       Compiler:  cl
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "LinkTreeWidget.h"

LinkTreeWidget::LinkTreeWidget()
{
	setHeaderLabel(QString(tr("局域网主机管理")));

	addGroupItem(tr("开发组"));
	addGroupItem(tr("后勤组"));

	addComputerItem(tr("开发组"), tr("192.168.1.2"), true);
	addComputerItem(tr("开发组"), tr("192.168.1.3"), true);
	addComputerItem(tr("开发组"), tr("192.168.1.4"), false);

	addComputerItem(tr("后勤组"), tr("192.168.1.5"), true);
	addComputerItem(tr("后勤组"), tr("192.168.1.6"), false);

	//结点全部展开
	expandAll();
}

LinkTreeWidget::~LinkTreeWidget()
{

}

/*================================================================
*  函 数 名： LinkTreeWidget::addGroupItem
*
*  功能描述： 添加一个组名
*
*  参    数： QString &strTitle   组名
*			  
*			  
*  返 回 值：bool always true
*
*  作    者：刘欢 2013/8
================================================================*/
bool LinkTreeWidget::addGroupItem(QString &strTitle)
{
	QTreeWidgetItem *imageItem = new QTreeWidgetItem(this, QStringList(strTitle));
	imageItem->setIcon(0, QIcon(":/res/images/group.png"));

	return true;
}

/*================================================================
*  函 数 名： LinkTreeWidget::addComputerItem
*
*  功能描述： 列表增加一个连接计算机信息
*
*  参    数： QString &strGroup —— 要添加的组名
*			  QString &strTitle —— 要添加的计算机命名
*			  bool isOnline —— 该计算机是否连接上服务端
*  返 回 值：
*
*  作    者：刘欢 2013/8
================================================================*/
bool LinkTreeWidget::addComputerItem(QString &strGroup, QString &strTitle, bool isOnline)
{
	QTreeWidgetItemIterator it(this);

	while (*it) {
		if ((*it)->text(0) == strGroup) {
				QTreeWidgetItem *item = new QTreeWidgetItem(*it, QStringList(strTitle));
				if (isOnline) {
					item->setIcon(0, QIcon(":/res/images/computer_online.png"));
				} else {
					item->setIcon(0, QIcon(":/res/images/computer_offline.png"));
				}
				
				(*it)->addChild(item);
			return true;
		}
		++it;
	}

	return false;
}
