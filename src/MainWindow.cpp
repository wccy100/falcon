// =====================================================================================
// 
//       Filename:  MainWindow.cpp
//
//    Description:  主窗口的类实现文件
//
//        Version:  1.0
//        Created:  2013年08月18日 21时11分08秒
//       Revision:  none
//       Compiler:  cl
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "MainWindow.h"
#include "LinkTreeWidget.h"
#include "MainStackWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)	
{
	// 设置窗口大小
	resize(1000, 650);
	createMainWeiget();
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	setWindowIcon(QIcon(":/res/ico/main.ico"));
	setWindowTitle(FALCAN_TITLE);
}

MainWindow::~MainWindow()	
{

}

void MainWindow::connectInfo()
{
	(mainStackWidget->getStackLayout())->setCurrentIndex(0);
}

void MainWindow::screenShot()
{
	(mainStackWidget->getStackLayout())->setCurrentIndex(1);
}

void MainWindow::flux()
{
	(mainStackWidget->getStackLayout())->setCurrentIndex(2);
}

void MainWindow::process()
{
	(mainStackWidget->getStackLayout())->setCurrentIndex(3);
}

void MainWindow::control()
{
	(mainStackWidget->getStackLayout())->setCurrentIndex(4);
}

void MainWindow::cmd()
{
	(mainStackWidget->getStackLayout())->setCurrentIndex(5);
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("关于 Falcan"),
			tr("<h2>Falcon 企业网络监控系统</h2>"
				"<p>Safe  Stable  Sharp (安全，稳定，敏捷)"
				"<p><h3>一个基于 Windows NT 平台的局域网络管理控制软件，GUI By Qt 4.X 。</h3>"
				"<p>严正声明：本程序仅用于技术研究，任何集体和个人使用该"
				"程序造成的任何违法后果由使用者个人承担！"
				"<p>Copyright (C) 2013 Hunters "));
}

void MainWindow::createMainWeiget()
{
	currLinkLabel = new QLabel(tr("正向连接主机"));
	currPortLabel = new QLabel(tr("  连接端口"));
	passwordLabel = new QLabel(tr("  连接密码"));
	
	currLinkIPEdit = new QLineEdit();

	QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
	currLinkIPEdit->setValidator(new QRegExpValidator(regExp, this));
	currLinkIPEdit->setText("127.0.0.1");
	currLinkIPEdit->setMaxLength(15);

	currPortSpin = new QSpinBox();
	currPortSpin->setRange(1, 65535);
	currPortSpin->setValue(5921);

	passwordEdit = new QLineEdit();
	passwordEdit->setEchoMode(QLineEdit::Password);

	linkButton = new QPushButton(tr("正向连接"));

	topLayout = new QHBoxLayout();
	topLayout->addWidget(currLinkLabel);
	topLayout->addWidget(currLinkIPEdit);
	topLayout->addWidget(currPortLabel);
	topLayout->addWidget(currPortSpin);
	topLayout->addWidget(passwordLabel);
	topLayout->addWidget(passwordEdit);
	topLayout->addWidget(linkButton);
	topLayout->addStretch();
	
	mainStackWidget = new MainStackWidget();
	linkTreeWidget = new LinkTreeWidget();

	bottomSplitter = new QSplitter(Qt::Horizontal);
	bottomSplitter->addWidget(linkTreeWidget);
	bottomSplitter->addWidget(mainStackWidget);
	bottomSplitter->setStretchFactor(1, 1); 

	mainLayout = new QVBoxLayout();
	mainLayout->addLayout(topLayout);
	mainLayout->addWidget(bottomSplitter);

	mainWigget = new QWidget();
	mainWigget->setLayout(mainLayout);

	this->setCentralWidget(mainWigget);
}

void MainWindow::createActions()
{
	auto_connAction = new QAction(tr("搜索客户端"), this);
	auto_connAction->setIcon(QIcon(":/res/images/auto_conn.png"));
	auto_connAction->setStatusTip(tr("自动搜索客户端"));

	configAction = new QAction(tr("服务端配置"), this);
	configAction->setIcon(QIcon(":/res/images/config.png"));
	configAction->setStatusTip(tr("服务端配置"));

	settingAction = new QAction(tr("程序设置"), this);
	settingAction->setIcon(QIcon(":/res/images/setting.png"));
	settingAction->setStatusTip(tr("程序设置"));

	exitAction = new QAction(tr("退出程序"), this);
	exitAction->setIcon(QIcon(":/res/images/exit.png"));
	exitAction->setStatusTip(tr("退出程序"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	aboutAction = new QAction(tr("关本于程序"), this);
	aboutAction->setIcon(QIcon(":/res/images/about.png"));
	aboutAction->setStatusTip(tr("关于本程序"));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

	connectAction = new QAction(tr("连接总览"), this);
	connectAction->setIcon(QIcon(":/res/images/connect.png"));
	connectAction->setStatusTip(tr("客户端连接总览"));
	connect(connectAction, SIGNAL(triggered()), this, SLOT(connectInfo()));

	screenShotAction = new QAction(tr("屏幕捕获"), this);
	screenShotAction->setIcon(QIcon(":/res/images/screenshot.png"));
	screenShotAction->setStatusTip(tr("捕获被控端的屏幕"));
	connect(screenShotAction, SIGNAL(triggered()), this, SLOT(screenShot()));
	
	fluxAction = new QAction(tr("流量监控"), this);
	fluxAction->setIcon(QIcon(":/res/images/flux.png"));
	fluxAction->setStatusTip(tr("客户端流量监控"));
	connect(fluxAction, SIGNAL(triggered()), this, SLOT(flux()));
	
	processAction = new QAction(tr("进程管理"), this);
	processAction->setIcon(QIcon(":/res/images/process.png"));
	processAction->setStatusTip(tr("客户端进程管理"));
	connect(processAction, SIGNAL(triggered()), this, SLOT(process()));
	
	controlAction = new QAction(tr("详细控制"), this);
	controlAction->setIcon(QIcon(":/res/images/control.png"));
	controlAction->setStatusTip(tr("对于客户端的详细控制"));
	connect(controlAction, SIGNAL(triggered()), this, SLOT(control()));
	
	cmdAction = new QAction(tr("远程CMD"), this);
	cmdAction->setIcon(QIcon(":/res/images/cmd.png"));
	cmdAction->setStatusTip(tr("远程执行CMD命令"));
	connect(cmdAction, SIGNAL(triggered()), this, SLOT(cmd()));
}

void MainWindow::createMenus()
{
	fileMenu = this->menuBar()->addMenu(tr("文件"));
	fileMenu->addAction(auto_connAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	setsMenu = this->menuBar()->addMenu(tr("设置"));
	setsMenu->addAction(configAction);
	setsMenu->addSeparator();
	setsMenu->addAction(settingAction);

	helpMenu = this->menuBar()->addMenu(tr("帮助"));
	helpMenu->addAction(aboutAction);
}

void MainWindow::createToolBars()
{
	mainToolBar = addToolBar(tr("功能"));
	mainToolBar->setMovable(false);
	mainToolBar->setIconSize(QSize(60, 60));
	mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	mainToolBar->addAction(connectAction);
	mainToolBar->addSeparator();
	mainToolBar->addAction(screenShotAction);
	mainToolBar->addSeparator();
	mainToolBar->addAction(fluxAction);
	mainToolBar->addSeparator();
	mainToolBar->addAction(processAction);
	mainToolBar->addSeparator();
	mainToolBar->addAction(controlAction);
	mainToolBar->addSeparator();
	mainToolBar->addAction(cmdAction);

	aboutToolBar = addToolBar(tr("关于"));
	aboutToolBar->setMovable(false);
	aboutToolBar->setIconSize(QSize(60, 60));
	aboutToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	aboutToolBar->addAction(aboutAction);
}

void MainWindow::createStatusBar()
{
	statusLabel = new QLabel(FALCAN_TITLE);
	statusLabel->setAlignment(Qt::AlignHCenter);
	statusLabel->setMinimumSize(statusLabel->sizeHint());

	this->statusBar()->addWidget(statusLabel);
}

void MainWindow::sleep(unsigned int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);

	while( QTime::currentTime() < dieTime ) {
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}
