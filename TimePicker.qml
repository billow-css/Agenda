import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: timePicker
    width: 200
    height: 300
    modal: true
    focus: true

    property int selectedHour: 12
    property int selectedMinute: 0

    signal timeSelected(string timeString)

    onOpened: {
        hourListView.positionViewAtIndex(selectedHour, ListView.Center)
        minuteListView.positionViewAtIndex(selectedMinute, ListView.Center)
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 5

        // 当前选择的时间
        Rectangle {
            Layout.fillWidth: true
            height: 50
            color: "#3498db"

            Label {
                anchors.centerIn: parent
                text: padZero(selectedHour) + ":" + padZero(selectedMinute)
                color: "white"
                font.pixelSize: 24
                font.bold: true
            }
        }

        // 小时和分钟选择器
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            // 小时选择
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Label {
                    text: "时"
                    font.bold: true
                    color: "#3498db"
                    horizontalAlignment: Text.AlignHCenter
                }

                ListView {
                    id: hourListView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    model: 24
                    spacing: 5
                    highlightRangeMode: ListView.ApplyRange
                    preferredHighlightBegin: height / 2 - 20
                    preferredHighlightEnd: height / 2 + 20

                    delegate: Rectangle {
                        width: hourListView.width
                        height: 40
                        color: ListView.isCurrentItem ? "#3498db" :
                               mouseArea.containsMouse ? "#f0f0f0" : "transparent"
                        radius: 5

                        Label {
                            anchors.centerIn: parent
                            text: padZero(modelData)
                            color: ListView.isCurrentItem ? "white" : "#2c3e50"
                            font.bold: ListView.isCurrentItem
                            font.pixelSize: ListView.isCurrentItem ? 16 : 14
                        }

                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                hourListView.currentIndex = index
                                timePicker.selectedHour = index
                            }
                        }
                    }

                    onCurrentIndexChanged: {
                        if (currentIndex >= 0) {
                            timePicker.selectedHour = currentIndex
                        }
                    }
                }
            }

            // 分钟选择
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Label {
                    text: "分"
                    font.bold: true
                    color: "#3498db"
                    horizontalAlignment: Text.AlignHCenter
                }

                ListView {
                    id: minuteListView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    model: 60
                    spacing: 5
                    highlightRangeMode: ListView.ApplyRange
                    preferredHighlightBegin: height / 2 - 20
                    preferredHighlightEnd: height / 2 + 20

                    delegate: Rectangle {
                        width: minuteListView.width
                        height: 40
                        color: ListView.isCurrentItem ? "#3498db" :
                               mouseArea.containsMouse ? "#f0f0f0" : "transparent"
                        radius: 5

                        Label {
                            anchors.centerIn: parent
                            text: padZero(modelData)
                            color: ListView.isCurrentItem ? "white" : "#2c3e50"
                            font.bold: ListView.isCurrentItem
                            font.pixelSize: ListView.isCurrentItem ? 16 : 14
                        }

                        MouseArea {
                            id: mouseArea1
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                minuteListView.currentIndex = index
                                timePicker.selectedMinute = index
                            }
                        }
                    }

                    onCurrentIndexChanged: {
                        if (currentIndex >= 0) {
                            timePicker.selectedMinute = currentIndex
                        }
                    }
                }
            }
        }

        // 底部操作
        RowLayout {
            Layout.fillWidth: true

            Button {
                text: "确定"
                Layout.fillWidth: true
                onClicked: {
                    timePicker.timeSelected(
                        padZero(timePicker.selectedHour) + ":" +
                        padZero(timePicker.selectedMinute)
                    )
                    timePicker.close()
                }
            }

            Button {
                text: "取消"
                Layout.fillWidth: true
                onClicked: timePicker.close()
            }
        }
    }

    function padZero(num) {
        return num < 10 ? "0" + num : num
    }
}
