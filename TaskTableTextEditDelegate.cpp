#include <QPlainTextEdit>

#include "TaskTableTextEditDelegate.h"

TaskTableTextEditDelegate::TaskTableTextEditDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget * TaskTableTextEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);

    QPlainTextEdit *editor = new QPlainTextEdit(parent);

    return editor;
}

void TaskTableTextEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString textInModel = index.model()->data(index).toString();

    QPlainTextEdit *textEdit = static_cast<QPlainTextEdit*>(editor);

    textEdit->document()->setPlainText(textInModel);
}

void TaskTableTextEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QPlainTextEdit *textEdit = static_cast<QPlainTextEdit*>(editor);

    QString currentText = textEdit->toPlainText();

    model->setData(index, currentText);
}

void TaskTableTextEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    QRect cellRect = option.rect;
    cellRect.setWidth(cellRect.width() + 200);
    cellRect.setHeight(cellRect.height() + 200);

    editor->setGeometry(cellRect);
}
