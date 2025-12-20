// import QtQuick
// import QtQuick.Controls 2.15
// import QtQuick.Layouts

// // 完全适配Main.qml的Delegate，仅做显示和信号触发
// Rectangle {
//     id: delegateItem
//     height: 60
//     width: parent.width  // 继承父容器宽度（Main.qml中已指定）

//     // 前端高亮样式：完全绑定主QML控制的isSelected
//     color: {
//         let baseColor = index % 2 === 0 ? "white" : "#f8f9fa";
//         // 悬停效果：未选中时才生效
//         if (mouseArea.containsMouse && !isSelected) {
//             return "#f0f0f0";
//         }
//         // 选中样式：主QML控制isSelected，这里仅做显示
//         return isSelected ? "#e8f4fc" : baseColor;
//     }
//     border.color: isSelected ? "#3498db" : "#e9ecef"
//     border.width: isSelected ? 2 : 1

//     // 主QML传入的属性：数据+选中状态（核心绑定）
//     property var itemData: ({})
//     property bool isSelected: false  // 由Main.qml的selectedItems控制

//     // 对外暴露的信号：与Main.qml的监听对应
//     signal selected()
//     signal doubleClicked()
//     signal rightClicked()
//     signal toggleCompletion()
//     signal editRequested()
//     signal deleteRequested()
//     signal exportRequested()

//     // 内容布局：与Main.qml的itemData字段完全匹配
//     RowLayout {
//         anchors.fill: parent
//         anchors.margins: 10
//         spacing: 15

//         // 选择框：绑定isSelected，点击触发selected信号
//         CheckBox {
//             checked: delegateItem.isSelected
//             onClicked: delegateItem.selected()
//             Layout.alignment: Qt.AlignVCenter
//         }

//         // ID显示
//         Text {
//             Layout.preferredWidth: 60
//             text: itemData.id || ""
//             font.bold: true
//             color: "#2c3e50"
//             horizontalAlignment: Text.AlignHCenter
//         }

//         // 名称显示（逾期标红）
//         Text {
//             Layout.preferredWidth: 200
//             text: itemData.name || ""
//             elide: Text.ElideRight
//             font.bold: true
//             color: itemData.isOverdue ? "#e74c3c" : "#2c3e50"
//         }

//         // 状态模块（颜色+文字由itemData提供）
//         Rectangle {
//             Layout.preferredWidth: 100
//             Layout.preferredHeight: 30
//             radius: 4
//             color: itemData.statusColor || "#e9ecef"

//             RowLayout {
//                 anchors.fill: parent
//                 anchors.margins: 5
//                 spacing: 5

//                 Text {
//                     text: itemData.statusText || ""
//                     color: "white"
//                     font.bold: true
//                     font.pixelSize: 12
//                     Layout.fillWidth: true
//                     horizontalAlignment: Text.AlignHCenter
//                 }

//                 // 快速完成按钮（状态非已完成时显示）
//                 Button {
//                     width: 20
//                     height: 20
//                     padding: 0
//                     visible: itemData.status !== 1  // 1=已完成（Main.qml状态定义）

//                     background: Rectangle {
//                         radius: 10
//                         color: parent.hovered ? "#ffffff" : "transparent"
//                         border.color: "white"
//                         border.width: 1
//                     }

//                     contentItem: Text {
//                         text: "✓"
//                         color: "white"
//                         font.pixelSize: 12
//                         font.bold: true
//                         horizontalAlignment: Text.AlignHCenter
//                         verticalAlignment: Text.AlignVCenter
//                     }

//                     onClicked: delegateItem.toggleCompletion()
//                     ToolTip.text: "标记为完成"
//                 }
//             }
//         }

//         // 优先级模块
//         Rectangle {
//             Layout.preferredWidth: 80
//             Layout.preferredHeight: 30
//             radius: 4
//             color: itemData.priorityColor || "#e9ecef"

//             Text {
//                 anchors.centerIn: parent
//                 text: itemData.priorityText || ""
//                 color: "white"
//                 font.bold: true
//                 font.pixelSize: 12
//             }
//         }

//         // 截止日期+时间
//         ColumnLayout {
//             Layout.preferredWidth: 150
//             spacing: 2

//             Text {
//                 text: itemData.ddl || ""
//                 color: itemData.isToday || itemData.isOverdue ? "#e74c3c" : "#2c3e50"
//                 font.bold: itemData.isToday || itemData.isOverdue
//                 horizontalAlignment: Text.AlignHCenter
//             }

//             Text {
//                 text: itemData.time || ""
//                 color: "#7f8c8d"
//                 font.pixelSize: 12
//                 horizontalAlignment: Text.AlignHCenter
//             }
//         }

//         // 描述（超出省略）
//         Text {
//             Layout.preferredWidth: 300
//             text: itemData.description || ""
//             elide: Text.ElideRight
//             color: "#7f8c8d"
//         }
//     }

//     // 鼠标交互：仅触发信号，逻辑由Main.qml处理
//     MouseArea {
//         id: mouseArea
//         anchors.fill: parent
//         acceptedButtons: Qt.LeftButton | Qt.RightButton
//         hoverEnabled: true

//         onClicked: function(mouse) {
//             if (mouse.button === Qt.LeftButton) {
//                 delegateItem.selected()  // 触发信号，主QML处理选中逻辑
//             } else if (mouse.button === Qt.RightButton) {
//                 delegateItem.rightClicked()
//             }
//         }

//         onDoubleClicked: delegateItem.doubleClicked()
//     }

//     // 右键菜单：与Main.qml的itemContextMenu对应
//     Menu {
//         id: itemContextMenu
//         property int itemId: itemData.id || -1
//         property string itemName: itemData.name || ""

//         MenuItem { text: "编辑"; onTriggered: delegateItem.editRequested() }
//         MenuItem { text: "删除"; onTriggered: delegateItem.deleteRequested() }
//         MenuSeparator {}
//         MenuItem { text: "标记为完成"; onTriggered: delegateItem.toggleCompletion() }
//         MenuItem { text: "导出为TXT"; onTriggered: delegateItem.exportRequested() }
//         MenuSeparator {}
//         MenuItem {
//             text: "复制名称"
//             onTriggered: {
//                 Qt.application.clipboard.setText(itemData.name || "")
//             }
//         }
//     }
// }
import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle {
    id: delegateItem
    height: 60
    width: parent.width

    // 高亮样式：严格绑定主QML的selectedItems，视觉反馈清晰
    color: {
        let baseColor = index % 2 === 0 ? "#ffffff" : "#f8f9fa";
        if (isSelected) return "#e8f4fc"; // 选中色（主QML控制）
        if (mouseArea.containsMouse) return "#f0f0f0"; // 悬停色
        return baseColor;
    }
    border.color: isSelected ? "#3498db" : "#e9ecef"
    border.width: isSelected ? 2 : 1

    // 主QML传入的属性：单向绑定，不手动修改
    property var itemData: ({})
    property bool isSelected: false  // 由主QML的 selectedItems.includes(modelData.id) 控制

    // 信号：与主QML监听完全对应
    signal selected()
    signal doubleClicked()
    signal rightClicked()
    signal toggleCompletion()
    signal editRequested()
    signal deleteRequested()
    signal exportRequested()

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 15
        Layout.alignment: Qt.AlignVCenter

        // 修复：CheckBox 自定义选中样式（替换错误的 indicator.color）
        CheckBox {
            id: itemCheckBox
            checked: delegateItem.isSelected
            onClicked: delegateItem.selected()
            Layout.alignment: Qt.AlignVCenter

            // 自定义选中状态的指示器样式（兼容 Qt Quick Controls 2）
            indicator: Rectangle {
                width: 18
                height: 18
                radius: 3
                border.width: 2
                // 修复核心：用 border.color 区分选中/未选中
                border.color: itemCheckBox.checked ? "#3498db" : "#e9ecef"
                // 选中时的填充色
                color: itemCheckBox.checked ? "#3498db" : "transparent"

                // 选中时的对勾
                Text {
                    visible: itemCheckBox.checked
                    text: "✓"
                    color: "white"
                    font.pixelSize: 12
                    font.bold: true
                    anchors.centerIn: parent
                }
            }
        }

        // ID显示
        Text {
            Layout.preferredWidth: 60
            text: itemData.id || "—"
            font.bold: true
            color: "#2c3e50"
            horizontalAlignment: Text.AlignHCenter
        }

        // 名称显示（逾期标红）
        Text {
            Layout.preferredWidth: 200
            text: itemData.name || "无名称"
            elide: Text.ElideRight
            font.bold: true
            color: itemData.isOverdue ? "#e74c3c" : "#2c3e50"
        }

        // 状态模块
        Rectangle {
            Layout.preferredWidth: 100
            Layout.preferredHeight: 30
            radius: 4
            color: itemData.statusColor || "#e9ecef"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 5
                spacing: 5

                Text {
                    text: itemData.statusText || "未知"
                    color: "white"
                    font.bold: true
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignHCenter
                }

                // 快速完成按钮
                Button {
                    width: 20
                    height: 20
                    padding: 0
                    visible: itemData.status !== 1

                    background: Rectangle {
                        radius: 10
                        color: parent.hovered ? "#ffffff" : "transparent"
                        border.color: "white"
                        border.width: 1
                    }

                    contentItem: Text {
                        text: "✓"
                        color: "white"
                        font.pixelSize: 12
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    onClicked: delegateItem.toggleCompletion()
                    ToolTip.text: "标记为完成"
                }
            }
        }

        // 优先级模块
        Rectangle {
            Layout.preferredWidth: 80
            Layout.preferredHeight: 30
            radius: 4
            color: itemData.priorityColor || "#e9ecef"

            Text {
                anchors.centerIn: parent
                text: itemData.priorityText || "未知"
                color: "white"
                font.bold: true
                font.pixelSize: 12
            }
        }

        // 截止日期+时间
        ColumnLayout {
            Layout.preferredWidth: 150
            spacing: 2

            Text {
                text: itemData.ddl || "—"
                color: itemData.isToday || itemData.isOverdue ? "#e74c3c" : "#2c3e50"
                font.bold: itemData.isToday || itemData.isOverdue
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                text: itemData.time || "00:00"
                color: "#7f8c8d"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
            }
        }

        // 描述
        Text {
            Layout.preferredWidth: 300
            text: itemData.description || "无描述"
            elide: Text.ElideRight
            color: "#7f8c8d"
        }
    }

    // 鼠标交互：覆盖整个Item，确保点击无死角
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        hoverEnabled: true
        propagateComposedEvents: true

        onClicked: function(mouse) {
            if (mouse.button === Qt.LeftButton) {
                delegateItem.selected()
                mouse.accepted = false // 允许CheckBox响应点击
            } else if (mouse.button === Qt.RightButton) {
                delegateItem.rightClicked()
            }
        }

        onDoubleClicked: delegateItem.doubleClicked()
    }

    // 右键菜单
    Menu {
        id: itemContextMenu
        property int itemId: itemData.id || -1
        property string itemName: itemData.name || "无名称"

        MenuItem { text: "编辑"; onTriggered: delegateItem.editRequested() }
        MenuItem { text: "删除"; onTriggered: delegateItem.deleteRequested() }
        MenuSeparator {}
        MenuItem { text: "标记为完成"; onTriggered: delegateItem.toggleCompletion() }
        MenuItem { text: "导出为TXT"; onTriggered: delegateItem.exportRequested() }
        MenuSeparator {}
        MenuItem {
            text: "复制名称"
            onTriggered: {
                Qt.application.clipboard.setText(itemData.name || "")
            }
        }
    }
}
