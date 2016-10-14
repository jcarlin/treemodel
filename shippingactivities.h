#ifndef SHIPPINGACTIVITIES_H
#define SHIPPINGACTIVITIES_H

#include "treeitem.h"

#include <QObject>

class ShippingActivities : public TreeItem
{
public:
  ShippingActivities(const QList<QVariant> &data, TreeItem *parent);

  void refresh();
  QHash<int, QByteArray> roleNames() const;
  enum RoleNames {
    orderNumber = Qt::UserRole + 1,
    billTo = Qt::UserRole + 2
  };

signals:

public slots:

private:
  QHash<int, QByteArray> m_roleNames;
};

#endif // SHIPPINGACTIVITIES_H
