#include "ratingdelegate.h"
#include "artist.h"
#include <QModelIndex>
#include <QPainter>

RatingDelegate::RatingDelegate()
{

}

RatingDelegate::RatingDelegate(QAbstractItemView *view)
{
    view_=view;
}

QSize RatingDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &ind) const
{
    return QSize(100,20);
}

void RatingDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &ind) const
{
    int rating = 0;
    int top, left;
    QBrush b_in(Qt::yellow);
    QBrush b_out(Qt::NoBrush);
    if(ind.isValid() == false)
    {
        return;
    }
    if(ind.parent().isValid() == false)
    {
        return;
    }
    top = option.rect.top();
    left = option.rect.left();
    painter->setPen(QPen(Qt::black, 1));
    Item *item = static_cast<Item *>(ind.internalPointer());

    if(ind.column() == 2)
    {
        if(!item->toTrack()){
            return;
        }
        rating = ind.data().toInt();
        if(rating > 5) rating = 5;
        if(rating < 0) rating = 0;
        for(int counter = 0; counter < 5; counter++)
        {
            if(rating > 0 && counter < rating)
                painter->setBrush(b_in);
            else
                painter->setBrush(b_out);
            painter->drawEllipse(QPoint(left + 10, top + 10), 8, 8);
            left += 20;
        }
    }
}

QWidget *RatingDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &ind) const
{
    if(!ind.isValid())
    {
        return QStyledItemDelegate::createEditor(parent, option, ind);
    }
    if(!ind.parent().isValid())
    {
        return  QStyledItemDelegate::createEditor(parent, option, ind);
    }
    Item *item = static_cast<Item *>(ind.internalPointer());
    if(!item->parent()->toAlbum()){
        return QStyledItemDelegate::createEditor(parent, option, ind);
    }
    if(!item->toTrack()){
        return QStyledItemDelegate::createEditor(parent, option, ind);
    }
    RatingWidget *editor = new RatingWidget(parent);
    connect(editor, SIGNAL(editingFinished()),SLOT(commitAndCloseEditor()));
    return editor;
}

void RatingDelegate::setEditorData(QWidget *editor, const QModelIndex &ind) const
{
    Item *item;
    int rating=0;
    if(!ind.isValid())
    {
        QStyledItemDelegate::setEditorData(editor, ind);
        return;
    }
    if(!ind.parent().isValid())
    {
        QStyledItemDelegate::setEditorData(editor, ind);
        return;
    }
    item = static_cast<Item *>(ind.internalPointer());
    if(!item->toTrack()){
        QStyledItemDelegate::setEditorData(editor, ind);
        return;
    }
    if(ind.column() == 2)
    {
        rating = ind.data().toInt();
        RatingWidget *Editor = qobject_cast<RatingWidget *>(editor);
        connect(editor, SIGNAL(editingFinished()),SLOT(commitAndCloseEditor()));
        Editor->setRate(rating);
    }
    else
        QStyledItemDelegate::setEditorData(editor, ind);
}

void RatingDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &ind) const
{
    Item *item;
    int rating;
    if(!ind.isValid())
    {
        QStyledItemDelegate::setModelData(editor, model, ind);
        return;
    }
    if(!ind.parent().isValid())
    {
        QStyledItemDelegate::setModelData(editor, model, ind);
        return;
    }
    item = static_cast<Item *>(ind.internalPointer());
    if(!item->parent()->toAlbum()){
        QStyledItemDelegate::setModelData(editor, model, ind);
        return;
    }
    if(!item->toTrack()){
        QStyledItemDelegate::setModelData(editor, model, ind);
        return;
    }
    if(ind.column() == 2)
    {
        RatingWidget *Editor = qobject_cast<RatingWidget *>(editor);
        connect(editor, SIGNAL(editingFinished()),SLOT(commitAndCloseEditor()));
        item->toTrack()->setRating(Editor->rate());
    }
    else
        QStyledItemDelegate::setModelData(editor, model, ind);
}

void RatingDelegate::commitAndCloseEditor()
{
    RatingWidget *editor = qobject_cast<RatingWidget *>(sender());
    connect(editor, SIGNAL(editingFinished()),SLOT(commitAndCloseEditor()));
    emit commitData(editor);
    emit closeEditor(editor);
}
