// =====================================================================================
// 
//       Filename:  FluxWidget.cpp
//
//    Description:  流量显示
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

#include "FluxWidget.h"

FluxWidget::FluxWidget()
{
	QFont legendFont = QFont("微软雅黑");

	this->setBackground(QBrush(QColor("gray")));
	this->plotLayout()->insertRow(0);
	QCPPlotTitle *title= new QCPPlotTitle(this, tr("客户端流量变化图"));
	title->setTextColor(QColor("white"));
	legendFont.setPointSize(18);
	title->setFont(legendFont);
	this->plotLayout()->addElement(0, 0, title);

	this->xAxis->setRange(0, 20);
	this->yAxis->setRange(0, 4000);
	//this->axisRect()->setBackground(QBrush(QColor("white")));

	this->xAxis->setTickLabelColor(QColor("white"));
	this->xAxis->setLabelColor(QColor("white"));
	this->yAxis->setTickLabelColor(QColor("white"));
	this->yAxis->setLabelColor(QColor("white"));
	this->xAxis->setLabel("时间 / s");
	this->yAxis->setLabel("流量 / KB");

	this->legend->setVisible(true);
	legendFont.setPointSize(10);
	this->legend->setFont(legendFont);
	this->legend->setSelectedFont(legendFont);
	this->legend->setSelectableParts(QCPLegend::spItems);

	// graph(0) 上传速率
	this->addGraph();
	QCPScatterStyle upScatter;
	upScatter.setShape(QCPScatterStyle::ssCircle);
	upScatter.setPen(QPen(QColor(240, 173, 7)));
	upScatter.setBrush(Qt::white);
	upScatter.setSize(8);
	this->graph(0)->setScatterStyle(upScatter);
	this->graph(0)->setName(QString("上传速率"));
	QPen upPen(QColor(240, 173, 7));
	upPen.setWidth(2);
	this->graph(0)->setPen(upPen);

	// graph(1) 下载速率
 	this->addGraph();	
	QCPScatterStyle downScatter;
	downScatter.setShape(QCPScatterStyle::ssCircle);
	downScatter.setPen(QPen(QColor(197,238,79)));
	downScatter.setBrush(Qt::white);
	downScatter.setSize(8);
	this->graph(1)->setScatterStyle(downScatter);
	this->graph(1)->setName(QString("下载速率"));
	QPen downPen(QColor(197,238,79));
	downPen.setWidth(2);
	this->graph(1)->setPen(downPen);
}

FluxWidget::~FluxWidget()
{

}