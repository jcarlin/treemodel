
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

  GridLayout {
    anchors.fill: parent
    columns: 3
    Label {
      text: "TableView"
    }
    Label {
      text: "ListView"
    }
    Label {
      text: "TreeView"
    }

    TableView {
      id: tableView
      Layout.fillHeight: true
      model: tModel
      TableViewColumn { role: "cohead_number"; title: "Order #";}
      TableViewColumn { role: "cohead_billtoname"; title: "Bill To";}
    }

    ListView {
      Layout.fillHeight: true
      model: tModel
    }
  }
}

