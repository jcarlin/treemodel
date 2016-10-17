
import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQml 2.2

ApplicationWindow {
  id: window
  visible: true
  width: 800
  height: 600
  title: "QML UI"
  //property var mModel: tModel

  Component.onCompleted: { console.log("Rectangle main.qml completed"); }

  GridLayout {
    anchors.fill: parent
    columns: 2
    Label {
      text: "TableView"
    }
    Label {
      text: "TreeView"
    }

    TableView {
      Component.onCompleted: { console.log("tableView main.qml completed"); }
      id: tableView
      Layout.fillHeight: true
      Layout.fillWidth: true
      model: tModel
      TableViewColumn { role: "orderNumber"; title: "Order #";}
      TableViewColumn { role: "billTo"; title: "Bill To";}
    }

    TreeView {
      model: tModel
      Layout.fillHeight: true
      Layout.fillWidth: true
      TableViewColumn { role: "orderNumber"; title: "Order #";}
      TableViewColumn { role: "billTo"; title: "Bill To";}
    }
  }
}

