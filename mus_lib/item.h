#ifndef ITEM_H
#define ITEM_H
#include <QString>
#include <QList>

class Artist;
class Album;
class Track;
class Item {
public:
    Item();
    ~Item();
    Item *parent();
    virtual void setParent(Item *par);
    virtual void insertChild(Item * ch, int pos = 0);
    Item *takeChild(int);
    Item *childAt(int) const;
    int indexOf(Item*) const;
    int childCount() const;

    virtual Artist* toArtist();
    virtual Album* toAlbum();
    virtual Track* toTrack();

    QString name() const;
    void setName(const QString &n);

    QString description() const;
    void setDescription(const QString &d);

protected:
    Item *parent_=0;
    QList<Item*> children_;
    QString name_;
    QString description_;
};

#endif // ITEM_H
