// =====================================================================================
// 
//       Filename:  FluxViewWidget.cpp
//
//    Description:  流量列表显示
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
#include <ctime>

#include "FluxViewWidget.h"
#include "FluxWidget.h"

FluxViewWidget::FluxViewWidget()
{
	setStyleSheet("QGroupBox {border-width:1px; border-style:solid; border-color:gray;}");
	
	fluxView = new FluxWidget();
	resetFluxView();

	upLabel = new QLabel(tr("上传速度：xxx KB/s"));
	downLabel = new QLabel(tr("下载速度: xxx KB/s"));
	hBoxLayout = new QHBoxLayout();

	hBoxLayout->addStretch();
	hBoxLayout->addWidget(upLabel);
	hBoxLayout->addStretch();
	hBoxLayout->addWidget(downLabel);
	hBoxLayout->addStretch();

	vBoxLayout = new QVBoxLayout();
	vBoxLayout->addWidget(fluxView);
	vBoxLayout->addLayout(hBoxLayout);
	vBoxLayout->setStretchFactor(fluxView, 1); 

	setLayout(vBoxLayout);
}

FluxViewWidget::~FluxViewWidget()
{

}

void FluxViewWidget::resetFluxView()
{
	//fluxView->
	//fluxView->
	//fluxView->
}
