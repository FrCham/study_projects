#ifndef RATINGDELEGATE_H
#define RATINGDELEGATE_H
#include <QStyledItemDelegate>
#include "ratingwidget.h"


class RatingDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    RatingDelegate();
    QAbstractItemView *view_;
    RatingDelegate(QAbstractItemView *view);
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &ind) const;
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & ind ) const ;
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &ind) const;
    void setEditorData(QWidget *editor, const QModelIndex &ind) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &ind) const;
public slots:
     void commitAndCloseEditor();
};

#endif // RATINGDELEGATE_H
