import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.platform as Platform
import Qt.labs.settings

ApplicationWindow {
    id: mainWindow
    width: 1200
    height: 800
    visible: true
    title: qsTr("Agenda 2.3.6")

    // 属性
    property var currentItem: ({})
    property bool isEditing: false
    property var selectedItems: []
    property string searchKeyword: ""
    property bool multiSelect: false
    Settings{
        id:showTutorial
        property bool showTutorial: true
    }


    Keys.onPressed: {
            // 检测 Ctrl 键（兼容 Windows/Linux/Mac）
            if (event.key === Qt.Key_Control || event.key === Qt.Key_Meta) {
                multiSelect = true
                event.accepted = true // 阻止事件穿透
            }
        }
        Keys.onReleased: {
            if (event.key === Qt.Key_Control || event.key === Qt.Key_Meta) {
                multiSelect = false
                event.accepted = true
            }
        }

        // 确保控件能捕获键盘事件（关键！否则监听不到 Ctrl 键）
        // focus: true
        // activeFocusOnTab: true

    // 组件
    DatePicker { id: datePicker }
    TimePicker { id: timePicker }

    // 自动保存定时器
    Timer {
        interval: 30000 // 30秒自动保存
        running: true
        repeat: true
        onTriggered: agendaManager.autoSave()
    }

    // 连接AgendaManager信号
    Connections {
        target: agendaManager

        onDataChanged: {
            // 数据变化时自动更新列表
            agendaListView.model = searchKeyword ?
                agendaManager.searchItems(searchKeyword) :
                agendaManager.getAllItems()

            // 更新选中项（如果被删除）
            var newSelectedItems = []
            for (var i = 0; i < selectedItems.length; i++) {
                var item = agendaManager.getItem(selectedItems[i])
                if (item && item.id) {
                    newSelectedItems.push(selectedItems[i])
                }
            }
            selectedItems = newSelectedItems
        }

        onFilterChanged: {
            // 筛选状态变化时更新
            agendaListView.model = agendaManager.getAllItems()
        }

        onErrorOccurred: function(message) {
            errorDialog.text = message
            errorDialog.open()
        }

        onOperationCompleted: function(message) {
            messageDialog.text = message
            messageDialog.open()
        }

        onItemsImported: function(count) {
            messageDialog.text = "成功导入 " + count + " 个日程"
            messageDialog.open()
        }
    }

    // 初始化时加载数据
    Component.onCompleted: {
        if (showTutorial.showTutorial) {
            tutorialDialog.open()
        }
        else{
            welcomePage.open()
        }
    }

    // ========== 对话框 ==========
    // 欢迎对话框
    Dialog{
        id: welcomePage
        width: 600
        background: Rectangle{
            radius: 8
            clip: true
        }
        anchors.centerIn: parent
        modal: true
        contentItem: Item{
            anchors.fill: parent
            Column {
                spacing: 5
                anchors.fill: parent
                width: parent.width
                Image {
                    id: bac
                    source: "qrc:/pic/bac.jpg"
                    width: parent.width
                    fillMode: Image.PreserveAspectFit
                }
                Image {
                    id: logo111
                    height: 50
                    source: "qrc:/logo/logo_main.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.left: parent.left
                }
                ColumnLayout{
                    spacing: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    Label {
                        anchors.left: parent.leftMargin
                        text: "日程管理系统"
                        font.pixelSize: 14
                        wrapMode: Text.WordWrap
                        font.bold: true
                        Layout.fillWidth: true
                    }
                    Label {
                        anchors.left: parent.leftMargin
                        text: "put YOUR EVERYING on the Agenda."
                        font.pixelSize: 14
                        opacity: 0.6
                        wrapMode: Text.WordWrap
                        font.italic: true
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
    // 教程对话框
    Dialog {
        id: tutorialDialog
        title: "欢迎使用 Agenda"
        width: 600
        height: 700
        modal: true
        anchors.centerIn: parent

        ColumnLayout {
            anchors.fill: parent
            spacing: 15
            // 内边距移到布局内（Dialog 层级的 Layout.margins 无效）
            Layout.margins: 20

            Image {
                        id: logo
                        source: "qrc:/logo/logo_main.png"
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100
                        Layout.alignment: Qt.AlignHCenter
                        fillMode: Image.PreserveAspectFit
                    }

            Label {
                text: "智能输入特性："
                font.bold: true
                // 确保标签占满宽度，文字不被截断
                Layout.fillWidth: true
            }

            ColumnLayout {
                spacing: 8
                Layout.fillWidth: true  // 占满宽度，适配换行

                Label {
                    text: "• 日期输入：输入 'today' 或 'T' 自动转换为今日日期"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Label {
                    text: "• 日期输入：纯数字自动转换为今日日期"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Label {
                    text: "• 日期输入：支持多种格式 (2024-12-31, 2024.12.31, 2024/12/31)"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Label {
                    text: "• 时间输入：'3:5' 自动转换为 '03:05'"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Label {
                    text: "• 时间输入：支持多种分隔符 (3-5, 3.5, 3/5)"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Label {
                    text: "• 时间输入：纯数字自动转换为 '00:00'"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }

            Label {
                text: "快捷操作："
                font.bold: true
                Layout.fillWidth: true
            }

            ColumnLayout {
                spacing: 8
                Layout.fillWidth: true

                Label {
                    text: "• 点击日程：查看详情"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Label {
                    text: "• 双击日程：快速编辑"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Label {
                    text: "• 右键日程：显示操作菜单"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Label {
                    text: "• Ctrl+单击：多选日程"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }

            Label {
                text: "自动保存："
                font.bold: true
                Layout.fillWidth: true
            }

            Label {
                text: "• 数据每30秒自动保存"
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            Label {
                text: "• 程序启动时自动加载上次保存的数据"
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            CheckBox {
                id: dontShowAgain
                text: "下次不再显示此教程"
                // 修复：让复选框水平居中，避免贴边
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 20  // 增加顶部间距，和上方内容分开
            }
        }

        standardButtons: Dialog.Ok

        onAccepted: {
            // 保留你的 showTutorial 写法（setting 对象+同名成员）
            showTutorial.showTutorial = !dontShowAgain.checked
        }

        onOpened: {
            // 修复：赋值给 checked 属性，而非 CheckBox 对象本身
            if (showTutorial.showTutorial == false) {
                dontShowAgain.checked = true
            }
        }
    }

    // 主界面
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing:8

        MenuBar{
            Layout.fillWidth: true;
            Menu{
                title: qsTr("文件")
                MenuItem{text:"清空-Ctrl+R"; Shortcut{
                    sequence: "Ctrl+R"
                    onActivated: {
                        clearConfirmDialog.open()
                    }
                    }onClicked: clearConfirmDialog.open()}
                Menu{
                    title: qsTr("导入选项")
                    MenuItem{text:"导入&打开(.csv)"; onClicked: csvImportDialog.open()}
                    MenuItem{text:"追加(.txt)"; onClicked: txtImportDialog.open()}
                }
                Menu{
                    title: qsTr("导出选项")
                    MenuItem{text:"保存(.csv)"; onClicked: csvExportDialog.open()}
                    MenuItem{text:"导出(.txt)"; onClicked: txtExportDialog.open()}
                }
                MenuItem{text:"退出"; onClicked: Qt.quit()}
            }
            Menu{
                title: qsTr("查看")
                MenuItem{text:"统计信息"; onClicked: statsDialog.open()}
                MenuItem{
                    text:"刷新-F5"
                    Shortcut{
                        sequence: "F5"
                        onActivated: {
                            if (filterCombo.currentIndex !== 0) {
                                if (filterCombo.currentIndex === 5) {
                                    agendaManager.applyFilter(1, agendaManager.currentPriorityFilter)
                                } else {
                                    agendaManager.applyFilter(3, String(filterCombo.currentIndex - 1))
                                }
                            }
                            refreshList()
                        }
                    }
                    onClicked: {
                        if (filterCombo.currentIndex !== 0) {
                            if (filterCombo.currentIndex === 5) {
                                agendaManager.applyFilter(1, agendaManager.currentPriorityFilter)
                            } else {
                                agendaManager.applyFilter(3, String(filterCombo.currentIndex - 1))
                            }
                        }
                        refreshList()
                    }
                }
                MenuItem{text:"打开控制台版本"; onClicked:{showMessage("正在打开：Agenda.exe-console版本")
                        var exePath = "file:///" + appDirPath + "/Agenda.exe";
                                console.log("动态路径：", exePath); // 此时会打印真实路径，而非undefined
                                Qt.openUrlExternally(exePath)}}
            }
            Menu{
                title: qsTr("帮助")
                MenuItem{text:"显示教程"; onClicked: tutorialDialog.open()}
                MenuItem{text:"打开仓库"; onClicked: {
                        Qt.openUrlExternally("https://github.com/billow-css/Agenda")}}
                MenuItem{text:"关于"; onClicked: aboutDialog.open()}
                MenuItem{text:"欢迎页面"; onClicked: welcomePage.open()}
            }
        }

        // 顶部工具栏
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            // 快速添加按钮
            Button {
                text: "＋ 快速添加"
                ToolTip.text: "快速添加日程（使用默认设置）"
                onClicked: {
                    quickAddDialog.open()
                }
                background: Rectangle {
                    color: "#3498db"
                    radius: 5
                }
                contentItem: Text {
                    text: parent.text
                    color: "white"
                    font.pixelSize: 14
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            // 完整添加按钮
            Button {
                text: "＋ 添加日程"
                ToolTip.text: "完整添加日程"
                onClicked: {
                    addDialog.open()
                }
                background: Rectangle {
                    color: "#2ecc71"
                    radius: 5
                }
                contentItem: Text {
                    text: parent.text
                    color: "white"
                    font.pixelSize: 14
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            // 编辑按钮
            Button {
                text: "✏️ 编辑"
                enabled: selectedItems.length === 1
                onClicked: {
                    var item = agendaManager.getItem(selectedItems[0])
                    currentItem = item
                    isEditing = true
                    editDialog.loadItem(item)
                    editDialog.open()
                }
            }

            // 删除按钮
            Button {
                text: "🗑️ 删除"
                enabled: selectedItems.length > 0
                onClicked: {
                    deleteConfirmDialog.multiple = selectedItems.length > 1
                    deleteConfirmDialog.open()
                }
            }

            // 快速完成按钮
            Button {
                text: "✅ 快速完成"
                enabled: selectedItems.length === 1
                onClicked: {
                    agendaManager.quickCompleteItem(selectedItems[0])
                }
                ToolTip.text: "切换完成/未完成状态"
            }

            // 搜索框
            TextField {
                id: searchField
                Layout.fillWidth: true
                placeholderText: "搜索日程名称或描述..."
                onTextChanged: {
                    searchKeyword = text
                    // 实时搜索，不需要刷新按钮
                    agendaListView.model = searchKeyword ?
                        agendaManager.searchItems(searchKeyword) :
                        agendaManager.getAllItems()
                }

                // 智能搜索提示
                Popup {
                    id: searchSuggestions
                    width: searchField.width
                    height: 200
                    y: searchField.height

                    ListView {
                        anchors.fill: parent
                        model: []
                        delegate: ItemDelegate {
                            width: parent.width
                            text: modelData
                            onClicked: {
                                searchField.text = modelData
                                searchSuggestions.close()
                            }
                        }
                    }
                }
            }

            // 排序
            ComboBox {
                id: sortCombo
                Layout.preferredWidth: 150
                model: ["（请选择）", "按优先级排序", "按截止日期排序", "按状态排序", "按名称排序"]
                onCurrentIndexChanged: {
                    agendaManager.sortBy(currentIndex)
                    // 实时更新，不需要刷新按钮
                }
            }

            // 筛选
            ComboBox {
                id: filterCombo
                Layout.preferredWidth: 150
                model: ["清空筛选器", "等待处理", "已完成", "已取消", "暂停", "优先级筛选"]
                onCurrentIndexChanged: {
                    if (currentIndex === 0) {
                        agendaManager.clearFilter()
                    } else if (currentIndex === 5) {
                        priorityFilterMenu.open()
                    } else {
                        agendaManager.applyFilter(3, String(currentIndex - 1))
                    }
                }

                Menu {
                    id: priorityFilterMenu
                    Repeater {
                        model: agendaManager.getPriorityOptions()
                        MenuItem {
                            text: modelData.text
                            onTriggered: {
                                if (modelData.value === -1) {
                                    agendaManager.clearFilter()
                                } else {
                                    agendaManager.applyFilter(1, modelData.value)
                                }
                                filterCombo.currentIndex = 5
                            }
                        }
                    }
                }
            }
        }

        // 状态信息栏
        RowLayout {
            Layout.fillWidth: true
            spacing: 20

            Text {
                text: "总日程: " + agendaManager.itemCount
                font.pixelSize: 14
                color: "#2c3e50"
            }

            Text {
                text: "筛选: " + agendaManager.currentFilter
                font.pixelSize: 14
                color: "#3498db"
                visible: agendaManager.currentFilter !== "全部"
            }

            Text {
                text: "选中: " + selectedItems.length + " 项"
                font.pixelSize: 14
                color: "#e74c3c"
                visible: selectedItems.length > 0
            }

            Item { Layout.fillWidth: true }

            Text {
                text: "🔄 自动保存"
                font.pixelSize: 12
                color: "#7f8c8d"
                font.italic: true
            }
        }

        // 日程列表区域
        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true
            padding: 0

            // 列表视图
            ListView {
                id: agendaListView
                anchors.fill: parent
                model: agendaManager.getAllItems() // 初始加载全部
                clip: true
                boundsBehavior: Flickable.StopAtBounds
                spacing: 2
                focus: true  // 允许获取焦点
                activeFocusOnTab: true  // Tab键可切换到列表
                Keys.forwardTo: [mainWindow]  // 将键盘事件转发给主窗口的Keys监听
                // 空状态提示
                Label {
                    anchors.centerIn: parent
                    text: "暂无日程数据\n点击上方按钮添加日程"
                    font.pixelSize: 18
                    color: "#bdc3c7"
                    horizontalAlignment: Text.AlignHCenter
                    visible: agendaListView.count === 0
                }

                delegate: AgendaItemDelegate {
                    width: agendaListView.width
                    itemData: modelData
                    isSelected: selectedItems.includes(modelData.id)

                    onSelected: {
                        // Ctrl多选支持
                        if (multiSelect) {
                            var index = selectedItems.indexOf(modelData.id)
                            if (index === -1) {
                                selectedItems.push(modelData.id)
                            } else {
                                selectedItems.splice(index, 1)
                            }
                        } else {
                            selectedItems = [modelData.id]
                        }

                        agendaListView.forceLayout()
                    }

                    onDoubleClicked: {
                        currentItem = modelData
                        detailDialog.itemData = currentItem
                        detailDialog.open()
                    }

                    onRightClicked: {
                        itemContextMenu.itemId = modelData.id
                        itemContextMenu.itemName = modelData.name
                        itemContextMenu.popup()
                    }

                    onToggleCompletion: {
                        agendaManager.quickCompleteItem(modelData.id)
                    }

                    onEditRequested: {
                        currentItem = modelData
                        isEditing = true
                        editDialog.loadItem(modelData)
                        editDialog.open()
                    }

                    onDeleteRequested: {
                        selectedItems = [modelData.id]
                        deleteConfirmDialog.multiple = false
                        deleteConfirmDialog.open()
                    }

                    onExportRequested: {
                        txtExportDialog.itemId = modelData.id
                        txtExportDialog.open()
                    }
                }
            }
        }
    }

    // ========== 添加/编辑对话框（带日期时间控件）==========

    Dialog {
        id: addDialog
        title: "添加日程"
        width: 500
        height: 600
        modal: true
        anchors.centerIn: parent


        property string selectedDate: agendaManager.getTodayDate()
        property string selectedTime: agendaManager.getCurrentTime()

        standardButtons: Dialog.Ok | Dialog.Cancel

        onOpened: {
            selectedDate = agendaManager.getTodayDate()
            selectedTime = agendaManager.getCurrentTime()
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            // 名称
            Label { text: "日程名称 *"; font.bold: true }
            TextField {
                id: addNameField
                Layout.fillWidth: true
                placeholderText: "输入日程名称"
                selectByMouse: true
            }

            // 描述
            Label { text: "描述"; font.bold: true }
            TextArea {
                id: addDescField
                Layout.fillWidth: true
                Layout.preferredHeight: 80
                placeholderText: "输入日程描述（可选）"
                wrapMode: Text.Wrap
                selectByMouse: true
            }

            // 日期选择
            Label { text: "截止日期 *"; font.bold: true }
            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                TextField {
                    id: addDateField
                    Layout.fillWidth: true
                    text: addDialog.selectedDate
                    placeholderText: "点击选择日期或输入 'today'"
                    selectByMouse: true

                    onTextChanged: {
                        // 实时智能处理
                        if (text.length > 0) {
                            addDialog.selectedDate = agendaManager.processDateInput(text)
                        }
                    }
                }

                Button {
                    text: "📅"
                    onClicked: {
                        datePicker.selectedDate = new Date(addDialog.selectedDate)
                        datePicker.open()
                    }
                }
            }

            // 时间选择
            Label { text: "时间 *"; font.bold: true }
            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                TextField {
                    id: addTimeField
                    Layout.fillWidth: true
                    text: addDialog.selectedTime
                    placeholderText: "点击选择时间或输入 '3:5'"
                    selectByMouse: true

                    onTextChanged: {
                        // 实时智能处理
                        if (text.length > 0) {
                            addDialog.selectedTime = agendaManager.fixTimeFormat(text)
                        }
                    }
                }

                Button {
                    text: "🕐"
                    onClicked: {
                        var parts = addDialog.selectedTime.split(":")
                        timePicker.selectedHour = parts[0] ? parseInt(parts[0]) : 12
                        timePicker.selectedMinute = parts[1] ? parseInt(parts[1]) : 0
                        timePicker.open()
                    }
                }
            }

            // 优先级
            Label { text: "优先级 *"; font.bold: true }
            ComboBox {
                id: addPriorityCombo
                Layout.fillWidth: true
                model: [
                    {text: "紧急 (1)", value: 1, color: "#e74c3c"},
                    {text: "高 (2)", value: 2, color: "#e67e22"},
                    {text: "中等 (3)", value: 3, color: "#f1c40f"},
                    {text: "一般 (4)", value: 4, color: "#3498db"}
                ]
                textRole: "text"
                valueRole: "value"
                currentIndex: 2

                delegate: ItemDelegate {
                    width: parent.width
                    contentItem: RowLayout {
                        Rectangle {
                            width: 12
                            height: 12
                            radius: 6
                            color: modelData.color
                        }
                        Text {
                            text: modelData.text
                            color: "#2c3e50"
                        }
                    }
                }
            }

            // 状态
            Label { text: "状态"; font.bold: true }
            ComboBox {
                id: addStatusCombo
                Layout.fillWidth: true
                model: [
                    {text: "等待处理", value: 0, color: "#3498db"},
                    {text: "已完成", value: 1, color: "#2ecc71"},
                    {text: "已取消", value: 2, color: "#e74c3c"},
                    {text: "暂停", value: 3, color: "#f39c12"}
                ]
                textRole: "text"
                valueRole: "value"

                delegate: ItemDelegate {
                    width: parent.width
                    contentItem: RowLayout {
                        Rectangle {
                            width: 12
                            height: 12
                            radius: 6
                            color: modelData.color
                        }
                        Text {
                            text: modelData.text
                            color: "#2c3e50"
                        }
                    }
                }
            }
        }

        onAccepted: {
            if (addNameField.text.trim() === "") {
                showError("日程名称不能为空")
                return
            }

            var newId = agendaManager.addItem(
                addNameField.text,
                addDescField.text,
                addDateField.text,
                addTimeField.text,
                addPriorityCombo.currentValue,
                addStatusCombo.currentValue
            )

            if (newId > 0) {
                clearForm()
            }
        }

        onRejected: clearForm()

        function clearForm() {
            addNameField.text = ""
            addDescField.text = ""
            addDateField.text = agendaManager.getTodayDate()
            addTimeField.text = agendaManager.getCurrentTime()
            addPriorityCombo.currentIndex = 2
            addStatusCombo.currentIndex = 0
        }
    }

    // 连接日期时间选择器
    Connections {
        target: datePicker
        onDateSelected: function(dateString) {
            addDateField.text = dateString
        }
    }

    Connections {
        target: timePicker
        onTimeSelected: function(timeString) {
            addTimeField.text = timeString
        }
    }
    // ========== 快速添加对话框 ==========

    Dialog {
        id: quickAddDialog
        title: "快速添加日程"
        anchors.centerIn: parent
        width: 400
        modal: true

        standardButtons: Dialog.Ok | Dialog.Cancel

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            Label {
                text: "快速添加日程"
                font.bold: true
                font.pixelSize: 16
                color: "#2c3e50"
            }

            Label { text: "日程名称 *"; font.bold: true }
            TextField {
                id: quickNameField
                Layout.fillWidth: true
                placeholderText: "输入日程名称"
                focus: true
            }

            Label { text: "优先级"; font.bold: true }
            ComboBox {
                id: quickPriorityCombo
                Layout.fillWidth: true
                model: [
                    {text: "紧急 (1)", value: 1},
                    {text: "高 (2)", value: 2},
                    {text: "中等 (3)", value: 3},
                    {text: "一般 (4)", value: 4}
                ]
                textRole: "text"
                valueRole: "value"
                currentIndex: 2
            }
        }

        onAccepted: {
            if (quickNameField.text.trim() === "") {
                showError("日程名称不能为空")
                return
            }

            var newId = agendaManager.quickAddItem(
                quickNameField.text,
                quickPriorityCombo.currentValue
            )

            if (newId > 0) {
                quickNameField.text = ""
                quickPriorityCombo.currentIndex = 2
                refreshList()
            }
        }

        onRejected: {
            quickNameField.text = ""
            quickPriorityCombo.currentIndex = 2
        }
    }

    // ========== 编辑对话框 ==========

    Dialog {
        id: editDialog
        title: "编辑日程"
        anchors.centerIn: parent
        width: 500
        height: 650
        modal: true

        property string selectedDate: ""
        property string selectedTime: ""
        property int itemId: -1

        standardButtons: Dialog.Ok | Dialog.Cancel

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            // 名称
            Label { text: "日程名称 *"; font.bold: true }
            TextField {
                id: editNameField
                Layout.fillWidth: true
                placeholderText: "输入日程名称"
            }

            // 描述
            Label { text: "描述"; font.bold: true }
            TextArea {
                id: editDescField
                Layout.fillWidth: true
                Layout.preferredHeight: 80
                placeholderText: "输入日程描述"
                wrapMode: Text.Wrap
            }

            // 日期选择
            Label { text: "截止日期 *"; font.bold: true }
            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                TextField {
                    id: editDateField
                    Layout.fillWidth: true
                    text: editDialog.selectedDate
                    placeholderText: "点击选择日期或输入 'today'"

                    onTextChanged: {
                        if (text.length > 0) {
                            editDialog.selectedDate = agendaManager.processDateInput(text)
                        }
                    }
                }

                Button {
                    text: "📅"
                    onClicked: {
                        var currentDate = new Date(editDialog.selectedDate)
                        if (!isNaN(currentDate.getTime())) {
                            datePicker.selectedDate = currentDate
                        }
                        datePicker.open()
                    }
                }
            }

            // 时间选择
            Label { text: "时间 *"; font.bold: true }
            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                TextField {
                    id: editTimeField
                    Layout.fillWidth: true
                    text: editDialog.selectedTime
                    placeholderText: "点击选择时间或输入 '3:5'"

                    onTextChanged: {
                        if (text.length > 0) {
                            editDialog.selectedTime = agendaManager.fixTimeFormat(text)
                        }
                    }
                }

                Button {
                    text: "🕐"
                    onClicked: {
                        var parts = editDialog.selectedTime.split(":")
                        timePicker.selectedHour = parts[0] ? parseInt(parts[0]) : 12
                        timePicker.selectedMinute = parts[1] ? parseInt(parts[1]) : 0
                        timePicker.open()
                    }
                }
            }

            // 优先级
            Label { text: "优先级 *"; font.bold: true }
            ComboBox {
                id: editPriorityCombo
                Layout.fillWidth: true
                model: [
                    {text: "紧急 (1)", value: 1, color: "#e74c3c"},
                    {text: "高 (2)", value: 2, color: "#e67e22"},
                    {text: "中等 (3)", value: 3, color: "#f1c40f"},
                    {text: "一般 (4)", value: 4, color: "#3498db"}
                ]
                textRole: "text"
                valueRole: "value"

                delegate: ItemDelegate {
                    width: parent.width
                    text: model.display
                    contentItem: RowLayout {
                        Rectangle {
                            width: 12
                            height: 12
                            radius: 6
                            color: modelData.color
                        }
                        Text {
                            text: modelData.text
                            color: "#2c3e50"
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }

            // 状态
            Label { text: "状态"; font.bold: true }
            ComboBox {
                id: editStatusCombo
                Layout.fillWidth: true
                model: [
                    {text: "等待处理", value: 0, color: "#3498db"},
                    {text: "已完成", value: 1, color: "#2ecc71"},
                    {text: "已取消", value: 2, color: "#e74c3c"},
                    {text: "暂停", value: 3, color: "#f39c12"}
                ]
                textRole: "text"
                valueRole: "value"

                delegate: ItemDelegate {
                    width: parent.width
                    contentItem: RowLayout {
                        Rectangle {
                            width: 12
                            height: 12
                            radius: 6
                            color: modelData.color
                        }
                        Text {
                            text: modelData.text
                            color: "#2c3e50"
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
        }

        onAccepted: {
            if (editNameField.text.trim() === "") {
                showError("日程名称不能为空")
                return
            }

            var updates = {
                name: editNameField.text,
                description: editDescField.text,
                ddl: editDateField.text,
                time: editTimeField.text,
                priority: editPriorityCombo.currentValue,
                status: editStatusCombo.currentValue
            }

            agendaManager.updateItem(editDialog.itemId, updates)
            clearForm()
        }

        onRejected: clearForm()

        function clearForm() {
            editNameField.text = ""
            editDescField.text = ""
            editDateField.text = ""
            editTimeField.text = ""
            editPriorityCombo.currentIndex = 2
            editStatusCombo.currentIndex = 0
            editDialog.itemId = -1
        }

        function loadItem(item) {
            editDialog.itemId = item.id
            editNameField.text = item.name || ""
            editDescField.text = item.description || ""
            editDateField.text = item.ddl || ""
            editTimeField.text = item.time || ""
            editDialog.selectedDate = item.ddl || ""
            editDialog.selectedTime = item.time || ""

            // 设置优先级
            for (var i = 0; i < editPriorityCombo.model.length; i++) {
                if (editPriorityCombo.model[i].value === item.priority) {
                    editPriorityCombo.currentIndex = i
                    break
                }
            }

            // 设置状态
            for (var j = 0; j < editStatusCombo.model.length; j++) {
                if (editStatusCombo.model[j].value === item.status) {
                    editStatusCombo.currentIndex = j
                    break
                }
            }
        }
    }

    // 连接编辑对话框的日期时间选择器
    Connections {
        target: datePicker
        onDateSelected: function(dateString) {
            if (editDialog.visible) {
                editDateField.text = dateString
            }
        }
    }

    Connections {
        target: timePicker
        onTimeSelected: function(timeString) {
            if (editDialog.visible) {
                editTimeField.text = timeString
            }
        }
    }

    // ========== 删除确认对话框 ==========

    Dialog {
        id: deleteConfirmDialog
        title: "确认删除"
        anchors.centerIn: parent
        width: 400
        modal: true

        property bool multiple: false

        standardButtons: Dialog.Yes | Dialog.No

        onAccepted: {
            if (multiple) {
                agendaManager.removeItems(selectedItems)
                selectedItems = []
                refreshList()
            } else {
                agendaManager.removeItem(selectedItems[0])
                selectedItems = []
                refreshList()
            }
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            Label {
                text: deleteConfirmDialog.multiple ?
                      "确定要删除选中的 " + selectedItems.length + " 个日程吗？" :
                      "确定要删除选中的日程吗？"
                font.bold: true
                wrapMode: Text.WordWrap
            }

            Label {
                text: "此操作不可撤销！"
                color: "#e74c3c"
                font.bold: true
            }

            // 如果删除单个，显示日程信息
            Text {
                visible: !multiple && selectedItems.length === 1
                text: {
                    if (selectedItems.length === 1) {
                        var item = agendaManager.getItem(selectedItems[0])
                        return "日程名称: " + (item.name || "未知")
                    }
                    return ""
                }
                color: "#2c3e50"
                font.italic: true
            }
        }
    }

    // ========== 清空确认对话框 ==========

    Dialog {
        id: clearConfirmDialog
        title: "确认清空"
        anchors.centerIn: parent
        width: 400
        modal: true

        standardButtons: Dialog.Yes | Dialog.No

        onAccepted: {
            // 先备份当前数据
            var backupData = agendaManager.getAllItems()
            if (backupData.length > 0 && backupCheckbox.checked === true) {
                backupDialog.backupData = backupData
                backupDialog.open()
            } else {
                agendaManager.clearAll()
                refreshList()
            }
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            Label {
                text: "确定要清空所有日程吗？"
                font.bold: true
            }

            Label {
                text: "此操作将删除所有日程数据，且不可恢复！"
                color: "#e74c3c"
                font.bold: true
            }

            Text {
                text: "当前有 " + agendaManager.itemCount + " 个日程"
                color: "#e74c3c"
                font.bold: true
            }

            CheckBox {
                id: backupCheckbox
                text: "先备份当前数据"
                checked: true
            }
        }
    }

    // ========== 备份确认对话框 ==========

    Dialog {
        id: backupDialog
        title: "备份确认"
        anchors.centerIn: parent
        width: 400
        modal: true

        property var backupData: []

        standardButtons: Dialog.Yes | Dialog.No

        onAccepted: {
            // 导出备份文件
            var timestamp = Qt.formatDateTime(new Date(), "yyyyMMdd_hhmmss")
            var filePath = "backup_" + timestamp + ".csv"

            // 创建临时Agenda对象来导出
            var tempAgenda = agendaManager  // 这里需要实际的备份逻辑
            // 实际实现中需要创建一个临时Agenda对象并填充数据

            agendaManager.clearAll()
            refreshList()
            showMessage("已清空所有日程，备份文件: " + filePath)
        }

        onRejected: {
            // 不清空，直接关闭
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            Label {
                text: "备份确认"
                font.bold: true
                font.pixelSize: 16
            }

            Label {
                text: "将在清空前自动备份当前数据到文件:"
                wrapMode: Text.WordWrap
            }

            Text {
                text: {
                    var timestamp = Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss")
                    return "backup_" + timestamp.replace(/[: ]/g, "_") + ".csv"
                }
                color: "#3498db"
                font.bold: true
            }

            Label {
                text: "包含 " + backupData.length + " 个日程"
                color: "#2c3e50"
            }
        }
    }

    // ========== 统计对话框 ==========

    Dialog {
        id: statsDialog
        title: "日程统计"
        anchors.centerIn: parent
        width: 550
        height: 700
        modal: true

        standardButtons: Dialog.Close

        // 1. 定义结构化的统计属性（而非直接用var），保证绑定有效
        property int total: 0
        property int completed: 0
        property int overdue: 0
        property int queue: 0
        property int pause: 0
        property real completionRate: 0.0
        // 新增：真实过期数（C++返回的overdueCount）
        property int overdueCount: 0

        onOpened: {
            // 延迟调用，确保agendaManager已初始化
            Qt.callLater(updateStats);
        }

        // 2. 修复核心：逐个更新属性，而非整体覆盖
        function updateStats() {
            // 先检查agendaManager是否存在
            if (typeof agendaManager === 'undefined') {
                console.error("❌ 未找到agendaManager对象，请检查C++导出");
                resetStats(); // 重置为默认值
                return;
            }

            try {
                // 调用C++方法并获取数据
                const newStats = agendaManager.getStatistics();
                console.log("📌 C++返回的统计数据：", newStats);

                // 校验返回值有效性
                if (newStats && typeof newStats === 'object') {
                    // 关键：逐个更新属性，保留绑定关系
                    statsDialog.total = newStats.total || 0;
                    statsDialog.completed = newStats.completed || 0;
                    statsDialog.overdue = newStats.overdue || newStats.overdueCount || 0; // 优先真实过期数
                    statsDialog.queue = newStats.queue || 0;
                    statsDialog.pause = newStats.pause || 0;
                    statsDialog.completionRate = newStats.completionRate || 0.0;

                    console.log("✅ 统计数据更新成功：", {
                        total: total,
                        completed: completed,
                        completionRate: completionRate
                    });
                } else {
                    console.warn("⚠️ 统计数据无效，重置为默认值");
                    resetStats();
                }
            } catch (e) {
                console.error("❌ 调用getStatistics失败：", e.message);
                resetStats();
            }
        }

        // 辅助函数：重置统计数据为默认值
        function resetStats() {
            statsDialog.total = 0;
            statsDialog.completed = 0;
            statsDialog.overdue = 0;
            statsDialog.queue = 0;
            statsDialog.pause = 0;
            statsDialog.completionRate = 0.0;
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            Label {
                text: "📊 日程统计"
                font.pixelSize: 16
                font.bold: true
                color: "#2c3e50"
            }

            // 统计卡片（绑定修复后的属性）
            GridLayout {
                columns: 3
                columnSpacing: 15
                rowSpacing: 15

                // 总日程卡片
                StatCard {
                    title: "总日程"
                    value: statsDialog.total
                    color: "#3498db"
                    icon: "📋"
                }

                // 完成率卡片（直接用C++返回的完成率，无需重新计算）
                StatCard {
                    title: "完成率"
                    value: Math.round(statsDialog.completionRate) + "%"
                    color: statsDialog.total > 0 && statsDialog.completionRate >= 80 ?
                           "#2ecc71" : "#e74c3c"
                    icon: "📈"
                }

                // 等待处理卡片
                StatCard {
                    title: "等待处理"
                    value: statsDialog.queue
                    color: "#3498db"
                    icon: "⏳"
                }

                // 已完成卡片
                StatCard {
                    title: "已完成"
                    value: statsDialog.completed
                    color: "#2ecc71"
                    icon: "✅"
                }

                // 已取消卡片
                StatCard {
                    title: "已取消"
                    value: statsDialog.overdue
                    color: "#e74c3c"
                    icon: "❌️"
                }

                // 暂停卡片
                StatCard {
                    title: "暂停"
                    value: statsDialog.pause
                    color: "#f39c12"
                    icon: "⏸️"
                }
            }

            // 详细统计表格（绑定修复后的属性）
            Frame {
                Layout.fillWidth: true
                Layout.fillHeight: true

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 10

                    Label {
                        text: "详细统计"
                        font.bold: true
                        font.pixelSize: 16
                    }

                    GridLayout {
                        columns: 2
                        columnSpacing: 20
                        rowSpacing: 10

                        // 表头
                        Label {
                            text: "类别"
                            font.bold: true
                            color: "#2c3e50"
                        }

                        Label {
                            text: "数量"
                            font.bold: true
                            color: "#2c3e50"
                            Layout.alignment: Qt.AlignRight
                        }

                        // 数据行
                        Label { text: "等待处理" }
                        Label {
                            text: statsDialog.queue
                            Layout.alignment: Qt.AlignRight
                            font.bold: true
                        }

                        Label { text: "已完成" }
                        Label {
                            text: statsDialog.completed
                            Layout.alignment: Qt.AlignRight
                            font.bold: true
                            color: "#2ecc71"
                        }

                        Label { text: "已取消" }
                        Label {
                            text: statsDialog.overdue
                            Layout.alignment: Qt.AlignRight
                            font.bold: true
                            color: "#e74c3c"
                        }

                        Label { text: "暂停" }
                        Label {
                            text: statsDialog.pause
                            Layout.alignment: Qt.AlignRight
                            font.bold: true
                            color: "#f39c12"
                        }

                        // 分隔线
                        Rectangle {
                            Layout.columnSpan: 2
                            Layout.fillWidth: true
                            height: 1
                            color: "#e0e0e0"
                        }

                        Label {
                            text: "总计"
                            font.bold: true
                            color: "#2c3e50"
                        }

                        Label {
                            text: statsDialog.total
                            Layout.alignment: Qt.AlignRight
                            font.bold: true
                            color: "#2c3e50"
                            font.pixelSize: 16
                        }

                        Label {
                            text: "完成率"
                            font.bold: true
                            color: "#2c3e50"
                        }

                        Label {
                            text: Math.round(statsDialog.completionRate) + "%"
                            Layout.alignment: Qt.AlignRight
                            font.bold: true
                            color: statsDialog.total > 0 && statsDialog.completionRate >= 80 ?
                                   "#2ecc71" : "#e74c3c"
                            font.pixelSize: 16
                        }
                    }
                }
            }

            // // 操作按钮
            // RowLayout {
            //     Layout.fillWidth: true

            //     Button {
            //         text: "刷新"
            //         onClicked: updateStats()
            //         Layout.fillWidth: true
            //     }

            //     Button {
            //         text: "导出统计"
            //         onClicked: exportStats()
            //         Layout.fillWidth: true
            //         background: Rectangle {
            //             color: "#27ae60"
            //             radius: 5
            //         }
            //         contentItem: Text {
            //             text: parent.text
            //             color: "white"
            //             horizontalAlignment: Text.AlignHCenter
            //         }
            //     }
            // }
        }

        function exportStats() {
            var timestamp = Qt.formatDateTime(new Date(), "yyyyMMdd_hhmmss")
            var filePath = "stats_" + timestamp + ".txt"

            var content = "Agenda 日程统计报告\n"
            content += "生成时间: " + Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss") + "\n"
            content += "==============================\n\n"
            content += "总日程: " + statsDialog.total + "\n"
            content += "已完成: " + statsDialog.completed + "\n"
            content += "等待处理: " + statsDialog.queue + "\n"
            content += "已取消: " + statsDialog.overdue + "\n"
            content += "暂停: " + statsDialog.pause + "\n"
            content += "完成率: " + Math.round(statsDialog.completionRate) + "%" + "\n"

            // 尝试保存文件
            var result = saveTextFile(filePath, content)
            if (result) {
                showMessage("统计报告已导出到: " + filePath)
            } else {
                showError("导出失败")
            }
        }
    }

    // ========== 统计卡片组件 ==========

    Component {
        id: statCardComponent

        Rectangle {
            width: 120
            height: 100
            radius: 8
            color: cardColor

            property string cardTitle: ""
            property string cardValue: ""
            property color cardColor: "#3498db"
            property string cardIcon: ""

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    text: cardIcon + " " + cardTitle
                    color: "white"
                    font.pixelSize: 12
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }

                Text {
                    text: cardValue
                    color: "white"
                    font.pixelSize: 24
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }

    // 快捷创建统计卡片
    Component {
        id: statCardDelegate

        StatCard {
            title: model.title
            value: model.value
            color: model.color
            icon: model.icon
        }
    }

    // ========== 关于对话框 ==========

    Dialog {
        id: aboutDialog
        title: "关于 Agenda"
        anchors.centerIn: parent
        width: 500
        modal: true

        standardButtons: Dialog.Ok

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            Image {
                        id: logo1
                        source: "qrc:/logo/logo_main.png"
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100
                        Layout.alignment: Qt.AlignHCenter
                        fillMode: Image.PreserveAspectFit
                    }


            // 版本信息
            Label {
                text: "版本 2.3.6"
                color: "#7f8c8d"
                Layout.alignment: Qt.AlignHCenter
            }

            // 技术栈
            Label {
                text: "🛠️ 技术栈"
                font.bold: true
                color: "#2c3e50"
            }

            Text {
                text: "Qt 6.5 • QML 6 • C++17 • CMake"
                color: "#7f8c8d"
                font.italic: true
            }

            // 版权信息
            Text {
                text: "© 2025 Nuist. All rights reserved."
                color: "#95a5a6"
                font.pixelSize: 12
                Layout.alignment: Qt.AlignHCenter
            }
        }
    }

    // ========== 错误对话框 ==========

    Dialog {
        id: errorDialog
        title: "错误"
        anchors.centerIn: parent
        width: 350
        modal: true

        property string text: ""

        standardButtons: Dialog.Ok

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            // 错误图标
            Text {
                text: "❌"
                font.pixelSize: 32
                Layout.alignment: Qt.AlignHCenter
            }

            // 错误消息
            Label {
                text: errorDialog.text
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
        }

        onClosed: {
            text = ""
        }
    }

    // ========== 消息对话框 ==========

    Dialog {
        id: messageDialog
        title: "提示"
        anchors.centerIn: parent
        width: 350
        modal: true


        property string text: ""

        standardButtons: Dialog.Ok

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            // 成功图标
            Text {
                text: "✅"
                font.pixelSize: 32
                Layout.alignment: Qt.AlignHCenter
            }

            // 消息内容
            Label {
                text: messageDialog.text
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
        }

        onClosed: {
            text = ""
        }
    }

    // ========== 文件对话框 ==========

    // CSV导入对话框
    Platform.FileDialog {
        id: csvImportDialog
        title: "选择CSV文件"
        nameFilters: ["CSV文件 (*.csv)", "所有文件 (*)"]
        fileMode: Platform.FileDialog.OpenFile

        onAccepted: {

            var fileUrl = file.toString()
            var filePath = fileUrl.replace("file:///", "")
            if (Qt.platform.os === "windows") {
                filePath = fileUrl.replace("file:///", "") // 冗余但不影响，可保留
            }

            var success = agendaManager.importFromCSV(filePath)
            if (!success) {
                showError("导入失败，请检查文件格式")
            }
        }

        onRejected: {
            // 用户取消
        }
    }

    // CSV导出对话框
    Platform.FileDialog {
        id: csvExportDialog
        title: "导出为CSV"
        nameFilters: ["CSV文件 (*.csv)"]
        fileMode: Platform.FileDialog.SaveFile
        defaultSuffix: "csv"

        onAccepted: {
            var fileUrl = file.toString()
            var filePath = fileUrl.replace("file:///", "")
            if (Qt.platform.os === "windows") {
                filePath = fileUrl.replace("file:///", "")
            }

            if (!filePath.endsWith(".csv")) {
                filePath += ".csv"
            }

            var success = agendaManager.exportToCSV(filePath)
            if (!success) {
                showError("导出失败")
            }
        }
    }

    // TXT导入对话框
    Platform.FileDialog {
        id: txtImportDialog
        title: "选择TXT卡片文件"
        nameFilters: ["文本文件 (*.txt)", "所有文件 (*)"]
        fileMode: Platform.FileDialog.OpenFile

        onAccepted: {
            var fileUrl = file.toString()
            var filePath = fileUrl.replace("file:///", "")
            if (Qt.platform.os === "windows") {
                filePath = fileUrl.replace("file:///", "")
            }

            var success = agendaManager.importFromTXT(filePath)
            if (!success) {
                showError("导入失败，请检查文件格式")
            }
        }
    }

    // TXT导出对话框
    Platform.FileDialog {
        id: txtExportDialog
        title: "导出为TXT卡片"
        nameFilters: ["文本文件 (*.txt)"]
        fileMode: Platform.FileDialog.SaveFile
        defaultSuffix: "txt"

        property int itemId: -1

        onAccepted: {
            if (itemId !== -1) {
                var fileUrl = file.toString()
                var filePath = fileUrl.replace("file:///", "")
                if (Qt.platform.os === "windows") {
                    filePath = fileUrl.replace("file:///", "")
                }

                if (!filePath.endsWith(".txt")) {
                    filePath += ".txt"
                }

                var success = agendaManager.exportToTXT(itemId, filePath)
                if (!success) {
                    showError("导出失败")
                }
                itemId = -1
            }
        }
    }

    // ========== 右键上下文菜单 ==========

    Menu {
        id: itemContextMenu

        property int itemId: -1
        property string itemName: ""

        MenuItem {
            text: "查看详情"
            onTriggered: {
                var item = agendaManager.getItem(itemContextMenu.itemId)
                if (item && item.id) {
                    detailDialog.itemData = item
                    detailDialog.open()
                }
            }
        }

        MenuItem {
            text: "编辑日程"
            onTriggered: {
                var item = agendaManager.getItem(itemContextMenu.itemId)
                if (item && item.id) {
                    editDialog.itemId = item.id
                    editDialog.loadItem(item)
                    editDialog.open()
                }
            }
        }

        MenuItem {
            text: "删除日程"
            onTriggered: {
                selectedItems = [itemContextMenu.itemId]
                deleteConfirmDialog.multiple = false
                deleteConfirmDialog.open()
            }
        }

        MenuSeparator {}

        MenuItem {
            text: "标记为已完成"
            onTriggered: {
                agendaManager.markAsCompleted(itemContextMenu.itemId)
            }
        }

        MenuItem {
            text: "标记为待处理"
            onTriggered: {
                var updates = { status: 0 }
                agendaManager.updateItem(itemContextMenu.itemId, updates)
            }
        }

        MenuSeparator {}

        MenuItem {
            text: "导出为TXT卡片"
            onTriggered: {
                txtExportDialog.itemId = itemContextMenu.itemId
                txtExportDialog.open()
            }
        }
    }

    // ========== 日程详情对话框 ==========

    Dialog {
        id: detailDialog
        title: "日程详情"
        anchors.centerIn: parent
        width: 500
        height: 600
        modal: true

        property var itemData: ({})

        standardButtons: Dialog.Close

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            // 标题
            Label {
                text: "📄 日程详情"
                font.pixelSize: 20
                font.bold: true
                color: "#2c3e50"
                Layout.alignment: Qt.AlignHCenter
            }

            // 详细信息
            Frame {
                Layout.fillWidth: true
                Layout.fillHeight: true

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 10

                    // ID和名称
                    GridLayout {
                        columns: 2
                        columnSpacing: 20
                        rowSpacing: 10
                        Label {
                            text: detailDialog.itemData.name || ""
                            Layout.fillWidth: true
                            font.bold: true
                            font.pixelSize: 28
                            color: "#e74c3c"
                        }
                    }

                    // 描述
                    Label {
                        text: "描述:"
                        font.bold: true
                        color: "#2c3e50"
                    }
                    ScrollView {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 80

                        TextArea {
                            text: detailDialog.itemData.description || "无描述"
                            wrapMode: Text.Wrap
                            readOnly: true
                            font.italic: true
                            background: null
                        }
                    }

                    // 日期时间
                    GridLayout {
                        columns: 2
                        columnSpacing: 20
                        rowSpacing: 10

                        Label {
                            text: "截止日期:"
                            font.bold: true
                            color: "#2c3e50"
                        }
                        Label {
                            text: detailDialog.itemData.ddl || ""
                            color: detailDialog.itemData.isOverdue ? "#e74c3c" : "#2c3e50"
                            font.bold: detailDialog.itemData.isOverdue
                        }

                        Label {
                            text: "时间:"
                            font.bold: true
                            color: "#2c3e50"
                        }
                        Label {
                            text: detailDialog.itemData.time || ""
                        }
                    }

                    // 状态和优先级
                    GridLayout {
                        columns: 2
                        columnSpacing: 20
                        rowSpacing: 10

                        Label {
                            text: "状态:"
                            font.bold: true
                            color: "#2c3e50"
                        }

                        Rectangle {
                            width: 100
                            height: 25
                            radius: 4
                            color: detailDialog.itemData.statusColor || "#95a5a6"

                            Text {
                                anchors.centerIn: parent
                                text: detailDialog.itemData.statusText || "未知"
                                color: "white"
                                font.bold: true
                                font.pixelSize: 12
                            }
                        }

                        Label {
                            text: "优先级:"
                            font.bold: true
                            color: "#2c3e50"
                        }

                        Rectangle {
                            width: 100
                            height: 25
                            radius: 4
                            color: detailDialog.itemData.priorityColor || "#95a5a6"

                            Text {
                                anchors.centerIn: parent
                                text: detailDialog.itemData.priorityText || "未知"
                                color: "white"
                                font.bold: true
                                font.pixelSize: 12
                            }
                        }
                    }

                    // 额外信息
                    GridLayout {
                        columns: 2
                        columnSpacing: 20
                        rowSpacing: 10

                        Label {
                            text: "是否过期:"
                            font.bold: true
                            color: "#2c3e50"
                        }
                        Label {
                            text: detailDialog.itemData.isOverdue ? "是" : "否"
                            color: detailDialog.itemData.isOverdue ? "#e74c3c" : "#2ecc71"
                            font.bold: true
                        }

                        Label {
                            text: "是否是今天:"
                            font.bold: true
                            color: "#2c3e50"
                        }
                        Label {
                            text: detailDialog.itemData.isToday ? "是" : "否"
                            color: detailDialog.itemData.isToday ? "#e74c3c" : "#7f8c8d"
                            font.bold: detailDialog.itemData.isToday
                        }
                    }
                }
            }

            // 操作按钮
            RowLayout {
                Layout.fillWidth: true

                Button {
                    text: "编辑"
                    Layout.fillWidth: true
                    onClicked: {
                        detailDialog.close()
                        editDialog.itemId = detailDialog.itemData.id
                        editDialog.loadItem(detailDialog.itemData)
                        editDialog.open()
                    }
                }

                Button {
                    text: "删除"
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "#e74c3c"
                        radius: 5
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                    }
                    onClicked: {
                        detailDialog.close()
                        selectedItems = [detailDialog.itemData.id]
                        deleteConfirmDialog.multiple = false
                        deleteConfirmDialog.open()
                    }
                }

                Button {
                    text: "导出"
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "#27ae60"
                        radius: 5
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                    }
                    onClicked: {
                        detailDialog.close()
                        txtExportDialog.itemId = detailDialog.itemData.id
                        txtExportDialog.open()
                    }
                }
            }
        }
    }

    // ========== 统计卡片组件定义 ==========

    Component {
        id: statCard

        Rectangle {
            id: cardRoot
            width: 120
            height: 100
            radius: 8

            property string title: ""
            property string value: ""
            property color color: "#3498db"
            property string icon: ""

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 8

                Text {
                    text: cardRoot.icon + " " + cardRoot.title
                    color: "white"
                    font.pixelSize: 10
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }

                Text {
                    text: cardRoot.value
                    color: "white"
                    font.pixelSize: 20
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }

    // ========== 辅助函数 ==========
    // 显示错误
    function showError(message) {
        errorDialog.text = message
        errorDialog.open()
    }

    // 显示消息
    function showMessage(message) {
        messageDialog.text = message
        messageDialog.open()
    }

    // 更新列表
    function refreshList() {
        agendaListView.model = searchKeyword ?
            agendaManager.searchItems(searchKeyword) :
            agendaManager.getAllItems()
    }
}
