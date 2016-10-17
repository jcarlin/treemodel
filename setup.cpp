#include "setup.h"
#include "treemodel.h"
#include "treeitem.h"

#include <QFile>
#include <QTreeView>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

Setup::Setup(QObject *parent) : QObject(parent)
{
  // Window, layout
  Q_INIT_RESOURCE(simpletreemodel);
  QWidget *window = new QWidget;
  window->setMinimumSize(600, 600);
  QGridLayout *layout = new QGridLayout(window);

  /*
   * simpletreemodel qt example steps:
   * - create root TreeItem
   * - create TreeModel with root tree item
   * - call setupModelData to create TreeItems based on text file text indentation
   *
   */
  QFile file(":/default.txt");
  file.open(QIODevice::ReadOnly);
  QString readAll = file.readAll();
  file.close();

  QList<QVariant> rootData;
  rootData << "Title" << "Summary";
  TreeItem *root1 = new TreeItem(rootData);
  treeModelExample = new TreeModel(root1, readAll);

  const QStringList &lines = readAll.split(QString("\n"));
  treeModelExample->setupModelData(lines, treeModelExample->rootItem);

  treeViewExample = new QTreeView();
  treeViewExample->setModel(treeModelExample);

  layout->addWidget(new QLabel("QTreeView"), 0, 0);
  layout->addWidget(treeViewExample, 1, 0);

  /*
   * JC
   * TBD - The method of construction of TreeItems in qml (xtmi)
   * The above steps, plus a blob of code to provide a 2 level heirarchy (to prove sql data can be displayed).
   * - create root TreeItem
   * - sql query Shipping Activities. Iterate through sql records from results, and for each:
   *    - create a order TreeItem with sql row passed as QList<QVariant> data, and root tree item as parent tree item
   *    - sql query Line Items. Iterate through sql records from results, and for each:
   *      - create a TreeItem with sql row passed as QList<QVariant> data, and order tree item as parent tree item
   * - create treeModel TreeModel with root tree item
   *
   */

  QList<QVariant> rootData2;
  rootData2 << "orderNumber" << "billTo";
  TreeItem *rootItem = new TreeItem(rootData2);

  // orders
  QSqlQuery orderSql;
  orderSql.prepare("SELECT cohead_id, cohead_number, cohead_billtoname FROM cohead");
  orderSql.exec();
  int i = 0;
  while (orderSql.next()) {
    QList<QVariant> rowData;
    rowData << orderSql.value("cohead_number");
    rowData << orderSql.value("cohead_billtoname");

    TreeItem *order = new TreeItem(rowData, rootItem);
    rootItem->appendChild(order);

    // line items
    int coheadId = orderSql.value("cohead_id").toInt();
    QSqlQuery lineItemsSql;
    lineItemsSql.prepare("SELECT "
                         "  coitem_linenumber, item_number, item_descrip1, coitem_qtyord "
                         "FROM "
                         "  coitem "
                         "  JOIN itemsite on coitem_itemsite_id = itemsite_id "
                         "  JOIN item on itemsite_item_id = item_id "
                         "WHERE coitem_cohead_id = :coheadId "
                         "ORDER BY coitem_linenumber");
    lineItemsSql.bindValue(":coheadId", coheadId);
    lineItemsSql.exec();

    int l = 0;
    while (lineItemsSql.next()) {
      QList<QVariant> rowData;
      rowData << lineItemsSql.value("coitem_linenumber");
      rowData << lineItemsSql.value("item_number");
      rowData << lineItemsSql.value("item_descrip1");
      rowData << lineItemsSql.value("coitem_qtyord");
      TreeItem *lineItem = new TreeItem(rowData, order);
      order->appendChild(lineItem);
      l++;
    }
    i++;
  }

  // JC - Qt ui treemodel/treeview
  treeModel = new TreeModel(rootItem, QString());
  treeView = new QTreeView();
  treeView->setModel(treeModel);
  layout->addWidget(new QLabel("QTreeView"), 0, 1);
  layout->addWidget(treeView, 1, 1);

  // JC - Qt ui treemodel/tableview
  //QTableView *tableView = new QTableView();
  //tableView->setModel(treeModel);
  //layout->addWidget(new QLabel("QTableView"), 0, 2);
  //layout->addWidget(tableView, 1, 2);

  // Display window
  window->setWindowTitle("Qt/QWidget UI");
  // TODO - troubleshoot and correct bug causing crash... Likely memory leak from pointers not
  // being deleted in this class.
  //window->show();
}

