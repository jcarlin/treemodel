
import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

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
      //model: tModel.hasChildren()
      TableViewColumn { role: "sdf"; title: "Type";}
      TableViewColumn { role: "cohead_id"; title: "Type";}
    }

    ListView {
      Layout.fillHeight: true
      //model: tModel
      delegate: Text {
        text: tModel.data()
      }
    }
  }
}

