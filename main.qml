
import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.XmlListModel 2.0
import QtQml 2.2

Rectangle {
  id: window
  width: 800
  height: 600

  property var mModel: tModel

  GridLayout {
    anchors.fill: parent
    columns: 3
    Label {
      text: "TableView"
    }
    Label {
      text: "TableView 2"
    }
    Label {
      text: "TreeView"
    }

    TableView {
      id: tableView
      Layout.fillHeight: true
      model: tModel
      TableViewColumn { role: "orderNumber"; title: "Order #";}
      TableViewColumn { role: "billTo"; title: "Bill To";}
    }

    TableView {
      id: tableView2
      Layout.fillHeight: true
      model: tModel
      TableViewColumn { role: "orderNumber"; title: "Order #";}
      TableViewColumn { role: "billTo"; title: "Bill To";}

      itemDelegate: Item {
        Text {
          text: styleData.value
        }
      }
    }
  }
}

