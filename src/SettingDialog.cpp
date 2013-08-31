// =====================================================================================
// 
//       Filename:  SettingDialog.cpp
//
//    Description:  设置对话框
//
//        Version:  1.0
//        Created:  2013年08月31日 22时03分50秒
//       Revision:  none
//       Compiler:  cl
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "SettingDialog.h"

SettingDialog::SettingDialog()
{
	setupUi(this);

	setFixedSize(this->width(), this->height());

	QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
	editServerIP->setValidator(new QRegExpValidator(regExp, this));
	editServerIP->setMaxLength(15);

	spinServerPort->setRange(1, 65535);

	editFetionPass->setEchoMode(QLineEdit::Password);
	editFetionPass->setStyleSheet("lineedit-password-character: 42");
}

SettingDialog::~SettingDialog()
{

}
