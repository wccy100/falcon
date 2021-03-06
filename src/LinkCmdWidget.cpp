// =====================================================================================
// 
//       Filename:  LinkCmdWidget.cpp
//
//    Description:  cmd 管理标签 Widget
//
//        Version:  1.0
//        Created:  2013年08月21日 09时34分08秒
//       Revision:  none
//       Compiler:  cl
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "LinkCmdWidget.h"
#include "MainWindow.h"
#include "ControlSocket.h"

LinkCmdWidget::LinkCmdWidget(MainWindow *mainWindow)
{
	qDebug() << "LinkCmdWidget 控件初始化\r\n";
	this->mainWindow = mainWindow;
	setStyleSheet("QGroupBox {border-width:1px; border-style:solid; border-color:gray;}");
	createMainWeiget();
}

LinkCmdWidget::~LinkCmdWidget()
{

}

/*================================================================
*  函 数 名： LinkCmdWidget::createMainWeiget
*
*  功能描述： 创建主显示控件
*
*  参    数： 无
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void LinkCmdWidget::createMainWeiget()
{
	cmdText = new QTextBrowser();
	cmdText->setStyleSheet("QTextBrowser{ background-color:black; }");
	cmdText->setTextColor(Qt::green);
	cmdText->setCurrentFont(QFont("新宋体", 10));

	cmdText->setFocusPolicy(Qt::NoFocus);

	resetCmdInfo();

	cmdLabel = new QLabel(tr("命令输入"));

	cmdInputEdit = new QLineEdit();
	cmdInputEdit->setFocusPolicy(Qt::StrongFocus);
	cmdInputEdit->installEventFilter(this);

	sendButton = new QPushButton(tr("远程执行"));
	connect(sendButton, SIGNAL(clicked()), this, SLOT(sendCMDCommand()));

	cmdLayout = new QVBoxLayout();
	cmdButtonLayout = new QHBoxLayout();

	cmdButtonLayout->addWidget(cmdLabel);
	cmdButtonLayout->addWidget(cmdInputEdit);
	cmdButtonLayout->addWidget(sendButton);

	cmdLayout->addWidget(cmdText);
	cmdLayout->addLayout(cmdButtonLayout);

	setLayout(cmdLayout);
}


/*================================================================
*  函 数 名： LinkCmdWidget::resetCmdInfo
*
*  功能描述： 重置显示控件
*
*  参    数： 无
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void LinkCmdWidget::resetCmdInfo()
{
	cmdText->clear();
	cmdText->append(tr("Microsoft Windows \n版权所有 (c) Microsoft Corporation。保留所有权利。\n\n$> "));
}

/*================================================================
*  函 数 名： LinkCmdWidget::cmdViewAddInfo
*
*  功能描述： cmd 显示增加信息
*
*  参    数： 无
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void LinkCmdWidget::cmdViewAddInfo(QString strInfo)
{
	cmdText->setTextColor(Qt::green);
	cmdText->setCurrentFont(QFont("新宋体", 10));
	cmdText->append(QString("$> ") + strInfo);
}

/*================================================================
*  函 数 名： LinkCmdWidget::sendCMDCommand
*
*  功能描述： 向服务器发送Cmd指令
*
*  参    数： 无
*			  
*  返 回 值： 无
*
*  作    者：刘欢 2013/8
================================================================*/
void LinkCmdWidget::sendCMDCommand()
{
	if (cmdInputEdit->text().size() == 0) {
		return;
	}
	if (cmdInputEdit->text() == "cls") {
		resetCmdInfo();
		return;
	}

	cmdViewAddInfo(cmdInputEdit->text());
	cmdUpStack.push(cmdInputEdit->text());
	mainWindow->getConnSocket()->sendControlCommand(RunCMDCommand, cmdInputEdit->text());
	cmdInputEdit->setFocus();
	cmdInputEdit->clear();
}

bool LinkCmdWidget::eventFilter(QObject *target, QEvent *event)
{
	if (target == cmdInputEdit) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *k = static_cast<QKeyEvent *>(event);
			if (k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter) {
				sendCMDCommand();
				return true;
			} else if (k->key() == Qt::Key_Up) {
				if (!cmdUpStack.empty()) {
					QString strCMD = cmdUpStack.pop();
					cmdInputEdit->setText(strCMD);
					cmdInputEdit->setFocus();
					cmdDownStack.push(strCMD);
				}
				return true;
			} else if (k->key() == Qt::Key_Down) {
				if (!cmdDownStack.empty()) {
					QString strCMD = cmdDownStack.pop();
					cmdInputEdit->setText(strCMD);
					cmdInputEdit->setFocus();
					cmdUpStack.push(strCMD);
				}
				return true;
			} 
		}
	}

	return QWidget::eventFilter(target, event);
}
