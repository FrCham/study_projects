#include "musicmodel.h"
#include "albumdialog.h"
#include <QFileDialog>
#include <QMessageBox>

MusicModel::MusicModel()
{
    root_ = new Item();
        Artist *ar=new Artist;
        Album *album=new Album;
        Album *album2=new Album;
        Track *track1=new Track;
        Track *track2=new Track;
        Track *track3=new Track;
        ar->setName("Витас");
        album->setName("Философия чуда");
        album2->setName("Мама");
        ar->setCountry("Украина");
        ar->setDescription("Мечта миллионов");
        album->setParent(ar);
        album->setDescription("Интересный");
        album->setYear(2001);
        album->setGenre("Pop");
        album2->setParent(ar);
        album2->setDescription("В дорогу");
        album2->setYear(2003);
        album2->setGenre("Pop");
            track1->setName("Опера 1");
            track1->setDescription("Шедевр");
            track2->setName("Опера 2");
            track2->setDescription("Шедевр 2");
            track1->setParent(album);
            track2->setParent(album);
            track1->setRating(5);
            track2->setRating(5);
        album->insertChild(track1);
        album->insertChild(track2);
            track3->setName("Звезда");
            track3->setDescription("Сойдёт");
            track3->setParent(album2);
            track3->setRating(3);
        album2->insertChild(track3);
        ar->insertChild(album);
        ar->insertChild(album2);
        root_->insertChild(ar);
}

QModelIndex MusicModel::parent(const QModelIndex &ind) const
{
    if(!ind.isValid()) return QModelIndex();
    else
    {
        Item *child_item = static_cast<Item*>(ind.internalPointer());
        if(child_item == root_) return QModelIndex();
        if(child_item->parent() == root_) return QModelIndex();
        if(!child_item->parent()) return QModelIndex();
        else
        {
            Item *parent = child_item->parent();
            if(!parent->parent()) return QModelIndex();
            else
            {
                Item *grandparent = parent->parent();
                return createIndex(grandparent->indexOf(parent),0,parent);
            }
        }
    }
}

QModelIndex MusicModel::index(int row, int col, const QModelIndex &par) const
{
    Item *parentItem = root_;

    if(par.isValid())
    {
        parentItem = static_cast<Item *>(par.internalPointer());
    }
    if(parentItem->childCount() > row)
        if(parentItem->childAt(row))
        {
            return createIndex(row, col, parentItem->childAt(row));
        }
    return QModelIndex();
}

int MusicModel::columnCount(const QModelIndex &par) const
{
    return 4;
}

int MusicModel::rowCount(const QModelIndex &par) const
{
    if(par.isValid())
    {
        Item *item;
        item = static_cast<Item *>(par.internalPointer());
        return item->childCount();
    }
    return root_->childCount();
}

QVariant MusicModel::data(const QModelIndex &ind, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(ind.isValid())
        {
            int coloumn = ind.column();
            Item *item = static_cast<Item*>(ind.internalPointer());
            if(item)
            {
                switch (coloumn)
                {
                case 0:
                    return item->name();
                    break;
                case 1:
                    if(item->toTrack()) return item->toTrack()->last();
                    break;
                case 2:
                    if(item->toTrack()) return item->toTrack()->rating();
                    break;
                case 3:
                    return item->description();
                    break;

                }

            }
            else return QVariant();

        }
        else return QVariant();
    }
    if (role == Qt::EditRole)
    {
        if(ind.isValid())
        {
            int coloumn = ind.column();
            Item *item = static_cast<Item*>(ind.internalPointer());
            if(item)
            {
                switch (coloumn)
                {
                case 0:
                    return item->name();
                    break;
                case 1:
                    if(item->toTrack()) return item->toTrack()->last();
                    break;
                case 2:
                    if(item->toTrack()) return item->toTrack()->rating();
                    break;
                case 3:
                     item->description();
                    break;

                }

            }
            else return QVariant();

        }
        else return QVariant();
    }
    return QVariant();
}

Qt::ItemFlags MusicModel::flags(const QModelIndex &ind) const
{
    return QAbstractItemModel::flags(ind) | Qt::ItemIsEditable;
}

bool MusicModel::setData(const QModelIndex &ind, const QVariant &val, int role)
{
    if(ind.isValid())
    {
        if(role != Qt::EditRole && role != Qt::DisplayRole)
            return false;
        int coloumn = ind.column();
        int row = ind.row();
        Item * item = static_cast<Item *>(ind.internalPointer());
        if (item)
        {
            switch (coloumn)
            {
                case 0:
                    item->setName(val.toString());
                    break;
                case 1:
                    if (item->toTrack())
                    {
                        QTime duration = QTime::fromString( val.toString(), Qt::ISODate );
                        item->toTrack()->setLast(duration);
                    }
                    if(item->toAlbum())
                    {
                        item->toAlbum()->setGenre(val.toString());
                    }
                    if(item->toArtist())
                    {
                        item->toArtist()->setCountry(val.toString());
                    }
                    break;
                case 2:
                    if (item->toTrack())
                        item->toTrack()->setRating(val.toInt());
                    if(item->toAlbum())
                    {
                        item->toAlbum()->setYear(val.toInt());
                    }

                    break;
                case 3:
                    item->setDescription(val.toString());
                    break;
                case 4:
                    if (item->toArtist()){
                        item->toArtist()->setImage(val.value<QPixmap>());
                    }
                    else if(item->toAlbum())
                    {
                        item->toAlbum()->setImage(val.value<QPixmap>());
                    }
            }
            emit dataChanged(ind, ind);
            return true;
        }
    }
    return false;
}

bool MusicModel::insertRow(int row, const QModelIndex &par)
{
    Item *pitem;
    if(par.isValid()) pitem = static_cast<Item *>(par.internalPointer());
    else pitem = root_;
    Item* item;
    if(pitem==root_) item = new Artist();
    if(pitem->toArtist()) item = new Album();
    if(pitem->toAlbum()) item = new Track();
    beginInsertRows(par, row, row);
    pitem->insertChild(item, row);
    endInsertRows();
    return true;
}

bool MusicModel::removeRow(int row, const QModelIndex &par)
{
    Item *p_item;
    if(par.isValid()) p_item = static_cast<Item *>(par.internalPointer());
    else p_item = root_;
    if(p_item)
    {
        beginRemoveRows(par, row, row);
        p_item->takeChild(row);
        endRemoveRows();
        return true;
    }
    else return false;
}

QVariant MusicModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QObject::tr("Name");
        case 1:
            return QObject::tr("Length");
        case 2:
            return QObject::tr("Rating");
        case 3:
            return QObject::tr("Notes");
        }
    }
    return QVariant();
}

QDataStream &operator<<(QDataStream &stream, Item &root)
{
    stream << root.childCount();
    for(int i=0; i < root.childCount(); i++)
    {
        Artist const* artist = root.childAt(i)->toArtist();
        if (artist) stream << *artist;
    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Item &root)
{
    int artist_count;
    Artist *art;
    stream >> artist_count;
    for (int i =0; i<artist_count; i++)
    {
        art = new Artist();
        stream >> *art;
        root.insertChild(art,i);
    }
    return stream;
}
