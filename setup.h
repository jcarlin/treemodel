#ifndef SETUP_H
#define SETUP_H

#include <QObject>
#include <QGridLayout>
#include <QWidget>
#include <QTableView>
#include <QTreeView>
#include <QLabel>

#include "treemodel.h"

class Setup : public QObject
{
  Q_OBJECT
public:
  explicit Setup(QObject *parent = 0);

  TreeModel *treeModelExample;
  TreeModel *treeModel;
  QTreeView *treeViewExample;
  QTreeView *treeView;


public slots:
};

#endif // SETUP_H
