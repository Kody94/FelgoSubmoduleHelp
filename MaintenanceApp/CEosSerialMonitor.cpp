//------------------------------------------------------------------------------------------------|
// CEosSerialMonitor
//
// Copyright (c) 2023 Fawkes Engineering, Inc.
// Proprietary and Confidential
// All Rights Reserved
//------------------------------------------------------------------------------------------------|
// Class Definition
//------------------------------------------------------------------------------------------------|
#include "CEosSerialMonitor.h"


//------------------------------------------------------------------------------------------------|
// Constructor
//------------------------------------------------------------------------------------------------|
CEosSerialMonitor::CEosSerialMonitor(QObject *parent)
    : QObject(parent)
{

}

//------------------------------------------------------------------------------------------------|
// public slot
//------------------------------------------------------------------------------------------------|
void
CEosSerialMonitor::openSerialPort(const QString &portName, int baudRate)
{
	if (m_ptrSerialPort) {
		closeSerialPort();
	}

	const auto serialPortInfos = QSerialPortInfo::availablePorts();
	for (const QSerialPortInfo &portInfo : serialPortInfos) {
		if (portInfo.portName() == portName) {
			m_portInfo = portInfo;
			break;
		}

	}

	m_ptrSerialPort = new QSerialPort(this);
	if (!m_portInfo.isNull()) {
		m_ptrSerialPort->setPort(m_portInfo);
		emit portFound(m_portInfo.portName());
	}
	m_ptrSerialPort->setBaudRate(baudRate);
	if (m_ptrSerialPort->open(QIODevice::ReadOnly)) {
		connect(m_ptrSerialPort, &QSerialPort::readyRead, this, &CEosSerialMonitor::handleReadyRead);
		update_connected(true);
	}
}

//------------------------------------------------------------------------------------------------|
// public slot
//------------------------------------------------------------------------------------------------|
void
CEosSerialMonitor::closeSerialPort()
{
	if (m_ptrSerialPort && m_ptrSerialPort->isOpen()) {
		disconnect(m_ptrSerialPort, &QSerialPort::readyRead, this, &CEosSerialMonitor::handleReadyRead);
		m_ptrSerialPort->close();
		delete m_ptrSerialPort;
		m_ptrSerialPort = nullptr;
		update_connected(false);
	}
}

//------------------------------------------------------------------------------------------------|
// private slot
//------------------------------------------------------------------------------------------------|
void
CEosSerialMonitor::handleReadyRead()
{
	if (m_ptrSerialPort) {
		QByteArray data = m_ptrSerialPort->readAll();
		QString newText = QString::fromUtf8(data);
		emit textUpdated(newText);
	}
}
