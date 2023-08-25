import Felgo
import QtQuick
import QtQuick.Controls 2.15

App {

	Navigation {
		NavigationItem {
			id: serialMonitor001
			property string deviceName
			title: qsTr(serialMonitor001.deviceName)
			iconType: IconType.globe

			Component.onCompleted: {
				serialMonitor001.deviceName = 'tty.usbserial-0001';
			}

			NavigationStack {
				AppPage {
					title: serialMonitor001.deviceName
					SerialOutput {
						deviceName: serialMonitor001.deviceName
					}
				}
			}
		}

		NavigationItem {
			id: serialMonitor002
			property string deviceName
			title: qsTr(serialMonitor002.deviceName)
			iconType: IconType.globe

			Component.onCompleted: {
				serialMonitor002.deviceName = 'tty.usbserial-0002';
			}


			NavigationStack {
				AppPage {
					title: serialMonitor002.deviceName
					SerialOutput {
						deviceName: serialMonitor002.deviceName
					}
				}

			}
		}
	}
}
