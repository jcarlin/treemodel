/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
    treemodel.cpp

    Provides a simple tree model to show how to create and use hierarchical
    models.
*/

#include "treeitem.h"
#include "treemodel.h"

#include <QStringList>

//! [0]
TreeModel::TreeModel(TreeItem *prototype, const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
  rootItem = prototype;
}
//! [0]

//! [1]
TreeModel::~TreeModel()
{
  delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid()) {
    return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
  }
  else {
    return rootItem->columnCount();
  }
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
  /*
   * Example: todoq
    QModelIndex index;
    if (childNodes.at(0).isText())
        index = createIndex(idx.row() + 1, 0);
    else
        index = idx;

    if (index.row() < 0 || index.row() > childNodes.count()
            || !childNodes.item(index.row()).isElement())
        return QVariant();
  */

  /*
   * Example2: foodmodel
    // Things we don't care about
    if (!index.isValid()) return QVariant();
    if (index.column() > 0) return QVariant();
    if (role != Qt::DisplayRole) return QVariant();

    // Grab the internal pointer from the index to see where we are in the tree
    ItemInfo *info = static_cast<ItemInfo*>(index.internalPointer());
    if (info->name == "root") {
        // The parent of this item is the root element
        Q_ASSERT(index.row() < modelNames_.size());
        return modelNames_.at(index.row());
    }

    // Else, grab the model for this level in the tree
    Q_ASSERT(info->row < models_.size());
    QAbstractItemModel *m = models_.at(info->row);
    return m->data(m->index(index.row(), displayColumn_), role);
   */

  if(index.isValid() && (role == Qt::DisplayRole || role > Qt::UserRole)) {
      TreeItem *treeItem = treeItemForIndex(index);
      return treeItem->data(index.column(), role);
  }
  return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
      return 0;

  return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
      return rootItem->data(section, role);

  return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
  /* JC - TODO - simplify
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  TreeItem *parentItem;

  if (!parent.isValid())
    parentItem = rootItem;
  else
    parentItem = static_cast<TreeItem*>(parent.internalPointer());

  TreeItem *childItem = parentItem->child(row);
  if (childItem)
    return createIndex(row, column, childItem);
  else
    return QModelIndex();
  */

  // Note: this works just fine - Readonlymodel from ex-treemodel example
  if(hasIndex(row, column, parent)) {
    TreeItem *parentTreeItem = treeItemForIndex(parent);
    TreeItem *childTreeItem = parentTreeItem->m_childItems.at(row);
    return createIndex(row, column, childTreeItem);
  }
  return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
  if (!index.isValid())
      return QModelIndex();

  TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
  TreeItem *parentItem = childItem->parentItem();

  if (parentItem == rootItem)
      return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
  return this->rootItem->roleNames();
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
  TreeItem *parentItem;
  if (parent.column() > 0)
      return 0;

  if (!parent.isValid())
      parentItem = rootItem;
  else
      parentItem = static_cast<TreeItem*>(parent.internalPointer());

  return parentItem->childCount();
}

// Used for simpletreemodel example only.
void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
  QList<TreeItem*> parents;
  QList<int> indentations;
  parents << parent;
  indentations << 0;

  int number = 0;

  while (number < lines.count()) {
    int position = 0;
    while (position < lines[number].length()) {
      if (lines[number].at(position) != ' ')
          break;
      position++;
    }

    QString lineData = lines[number].mid(position).trimmed();

    if (!lineData.isEmpty()) {
      // Read the column data from the rest of the line.
      QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
      QList<QVariant> columnData;
      for (int column = 0; column < columnStrings.count(); ++column)
        columnData << columnStrings[column];

      if (position > indentations.last()) {
        // The last child of the current parent is now the new parent
        // unless the current parent has no children.
        if (parents.last()->childCount() > 0) {
            parents << parents.last()->child(parents.last()->childCount()-1);
            indentations << position;
        }
      } else {
        while (position < indentations.last() && parents.count() > 0) {
            parents.pop_back();
            indentations.pop_back();
        }
      }
      // Append a new item to the current parent's list of children.
      parents.last()->appendChild(new TreeItem(columnData, parents.last()));
    }
    ++number;
  }
}

TreeItem *TreeModel::treeItemForIndex(const QModelIndex &index) const
{
  if(index.isValid()) {
    return static_cast<TreeItem*>(index.internalPointer());
  }
  return rootItem;
}
