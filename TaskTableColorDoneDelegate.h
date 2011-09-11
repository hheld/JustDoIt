#ifndef TASKTABLECOLORDONEDELEGATE_H
#define TASKTABLECOLORDONEDELEGATE_H

#include <QStyledItemDelegate>

class TaskTableColorDoneDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TaskTableColorDoneDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TASKTABLECOLORDONEDELEGATE_H
