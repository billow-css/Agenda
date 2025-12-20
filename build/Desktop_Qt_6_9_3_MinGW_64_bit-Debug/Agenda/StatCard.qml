// StatCard.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    // 公共属性
    property string title: ""
    property string value: "0"
    property color color: "#3498db"
    property string icon: ""
    property color textColor: "white"
    property color titleColor: Qt.lighter(color, 1.8)
    property int fontSize: 24
    property int titleSize: 12
    property int iconSize: 28
    property int radius: 12
    property int spacing: 6

    // 尺寸属性
    property int preferredWidth: 150
    property int preferredHeight: 120

    width: preferredWidth
    height: preferredHeight

    // 主卡片
    Rectangle {
        id: card
        anchors.fill: parent
        radius: root.radius
        color: root.color

        // 图标区域
        Rectangle {
            id: iconContainer
            width: iconSize + 16
            height: iconSize + 16
            radius: (iconSize + 16) / 2
            color: Qt.lighter(root.color, 1.4)
            anchors {
                top: parent.top
                topMargin: 16
                left: parent.left
                leftMargin: 16
            }

            Text {
                id: iconText
                anchors.centerIn: parent
                text: root.icon
                font.pixelSize: root.iconSize
                color: root.color
            }
        }

        // 数值显示
        Text {
            id: valueText
            anchors {
                top: iconContainer.bottom
                topMargin: root.spacing
                left: parent.left
                leftMargin: 16
            }
            text: root.value
            font {
                pixelSize: root.fontSize
                bold: true
                family: Qt.application.font.family
            }
            color: root.textColor
        }

        // 标题
        Text {
            id: titleText
            anchors {
                top: valueText.bottom
                topMargin: root.spacing / 6
                left: parent.left
                leftMargin: 16
            }
            text: root.title.toUpperCase()
            font {
                pixelSize: root.titleSize
                letterSpacing: 1
                family: Qt.application.font.family
            }
            color: root.titleColor
        }
    }

}
