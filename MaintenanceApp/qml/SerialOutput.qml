import QtQuick 2.15
import Felgo
import QtQuick.Controls 2.15
import com.fawkesengineering.MaintenanceApp 1.0

Item {
	visible: true

	property string deviceName: ''

	SerialMonitor {
		id: serialMonitor
	}

	//	AppText {
	//		id: connectionStatus
	//		text: serialMonitor.connected ? 'CONNECTED' : 'NOT CONNECTED'
	////		text: 'ok'
	//	}
	Column {

		Row {
			AppText {
				text: 'Connect to ' + deviceName
			}

			AppSwitch {
				id: connectedSwitch
				checked: serialMonitor.connected

				onToggled: {
					if (serialMonitor.connected) {
						serialMonitor.closeSerialPort()
					} else {
						serialMonitor.openSerialPort(deviceName, 115200)
					}
					setChecked(serialMonitor.connected)
				}
			}
		}

		ScrollView {
//			width: parent.width - 20
//			height: parent.height - 80
//			anchors.centerIn: parent
//			anchors.top: connectionStatus.bottom
			TextEdit {
				id: textBox
				anchors.fill: parent
				wrapMode: TextEdit.Wrap
				readOnly: true
				text: ''
				selectByMouse: true

				Connections {
					target: serialMonitor
					onConnected: {
						isConnected = true
					}
					onTextUpdated: newText => textBox.text += newText
				}

				Component.onCompleted: {
					serialMonitor.openSerialPort(deviceName, 115200)
				}
			}
		}
	}
}
