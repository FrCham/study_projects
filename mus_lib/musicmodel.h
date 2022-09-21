#ifndef MUSICMODEL_H
#define MUSICMODEL_H
#include "artist.h"
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QTime>

class MusicModel : public QAbstractItemModel
{
public:
    Item *root_;
    MusicModel();
    QModelIndex parent(const QModelIndex &ind) const;
    QModelIndex index(int row, int col, const QModelIndex &par) const;
    int columnCount(const QModelIndex &par) const;
    int rowCount(const QModelIndex &par) const;
    QVariant data(const QModelIndex &ind, int role) const;
    Qt::ItemFlags flags(const QModelIndex & ind) const;
    bool setData(const QModelIndex & ind, const QVariant & val, int role = Qt::EditRole);
    bool insertRow(int row, const QModelIndex &par = QModelIndex());
    bool removeRow(int row, const QModelIndex &par = QModelIndex());
    QModelIndex root_index();
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


};
QDataStream& operator<< (QDataStream &stream, Item &root);
QDataStream& operator>> (QDataStream &stream, Item &root);

#endif // MUSICMODEL_H
