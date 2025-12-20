import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml

Popup {
    id: datePicker
    width: 350
    height: 400
    modal: true
    focus: true

    property date selectedDate: new Date()
    property string dateFormat: "yyyy/MM/dd"

    signal dateSelected(string dateString)

    onOpened: {
        calendar.selectedDate = selectedDate
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        // 顶部工具栏
        RowLayout {
            Layout.fillWidth: true

            Button {
                text: "◀"
                onClicked: calendar.showPreviousMonth()
                ToolTip.text: "上一月"
            }

            Label {
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                text: calendar.monthNames[calendar.month] + " " + calendar.year
                font.bold: true
                font.pixelSize: 16
            }

            Button {
                text: "▶"
                onClicked: calendar.showNextMonth()
                ToolTip.text: "下一月"
            }

            Button {
                text: "今天"
                onClicked: calendar.showToday()
                ToolTip.text: "跳转到今天"
            }
        }

        // 星期标题
        RowLayout {
            Layout.fillWidth: true

            Repeater {
                model: ["日", "一", "二", "三", "四", "五", "六"]
                Label {
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignHCenter
                    text: modelData
                    font.bold: true
                    color: "#3498db"
                }
            }
        }

        // 日历网格
        GridLayout {
            id: calendarGrid
            Layout.fillWidth: true
            Layout.fillHeight: true
            columns: 7
            rows: 6

            property int firstDayOfMonth: new Date(calendar.year, calendar.month, 1).getDay()

            // 上个月的日期
            Repeater {
                model: calendarGrid.firstDayOfMonth

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"

                    Label {
                        anchors.centerIn: parent
                        text: new Date(calendar.year, calendar.month, 0).getDate() - (calendarGrid.firstDayOfMonth - index - 1)
                        color: "#95a5a6"
                        opacity: 0.5
                    }
                }
            }

            // 本月日期
            Repeater {
                model: new Date(calendar.year, calendar.month + 1, 0).getDate()

                Rectangle {
                    id: dayCell
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 5

                    property bool isSelected: calendar.selectedDate.getFullYear() === calendar.year &&
                                              calendar.selectedDate.getMonth() === calendar.month &&
                                              calendar.selectedDate.getDate() === (index + 1)
                    property bool isToday: {
                        var today = new Date()
                        return today.getFullYear() === calendar.year &&
                               today.getMonth() === calendar.month &&
                               today.getDate() === (index + 1)
                    }

                    color: dayCell.isSelected ? "#3498db" :
                           dayCell.isToday ? "#e8f4fc" :
                           mouseArea.containsMouse ? "#f0f0f0" : "transparent"

                    Label {
                        anchors.centerIn: parent
                        text: index + 1
                        color: dayCell.isSelected ? "white" :
                               dayCell.isToday ? "#e74c3c" : "#2c3e50"
                        font.bold: dayCell.isSelected || dayCell.isToday
                    }

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            calendar.selectedDate = new Date(calendar.year, calendar.month, index + 1)
                            datePicker.dateSelected(Qt.formatDate(calendar.selectedDate, dateFormat))
                            datePicker.close()
                        }
                    }
                }
            }
        }

        // 底部操作
        RowLayout {
            Layout.fillWidth: true

            Button {
                text: "今天"
                Layout.fillWidth: true
                onClicked: {
                    var today = new Date()
                    calendar.selectedDate = today
                    calendar.year = today.getFullYear()
                    calendar.month = today.getMonth()
                    datePicker.dateSelected(Qt.formatDate(today, dateFormat))
                    datePicker.close()
                }
            }

            Button {
                text: "取消"
                Layout.fillWidth: true
                onClicked: datePicker.close()
            }
        }
    }

    QtObject {
        id: calendar

        property int year: new Date().getFullYear()
        property int month: new Date().getMonth()
        property date selectedDate: new Date()

        readonly property var monthNames: ["一月", "二月", "三月", "四月", "五月", "六月",
                                          "七月", "八月", "九月", "十月", "十一月", "十二月"]

        function showPreviousMonth() {
            if (month === 0) {
                month = 11
                year--
            } else {
                month--
            }
        }

        function showNextMonth() {
            if (month === 11) {
                month = 0
                year++
            } else {
                month++
            }
        }

        function showToday() {
            var today = new Date()
            year = today.getFullYear()
            month = today.getMonth()
            selectedDate = today
        }
    }
}
