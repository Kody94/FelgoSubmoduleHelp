#pragma once

//------------------------------------------------------------------------------------------------|
// Base Class
//------------------------------------------------------------------------------------------------|
#include <QObject>

//------------------------------------------------------------------------------------------------|
// Forward Declarations
//------------------------------------------------------------------------------------------------|
#include <QSerialPort>
#include <QSerialPortInfo>

#include "QQmlVarPropertyHelpers.h"

class CEosSerialMonitor : public QObject
{
	Q_OBJECT
	QML_READONLY_VAR_PROPERTY(bool, connected);

public:
	explicit					CEosSerialMonitor(QObject *parent = nullptr);

public slots:
	void						openSerialPort(const QString &portName, int baudRate);
	void						closeSerialPort();

signals:
	void						portFound(const QString &strPortName);
	void						textUpdated(const QString &newText);

private slots:
	void						handleReadyRead();

private:
	QSerialPort					*m_ptrSerialPort = nullptr;
	QSerialPortInfo				m_portInfo;
};
