#include "item.h"

Item::Item()
{

}

Item::~Item()
{
    int num=children_.length();
    for(int i=0;i<num;i++)
    {
        children_.at(0)->setParent(0);
        delete children_.takeAt(0);
    }

    if(parent_!=0)
    {
        parent_->takeChild(parent_->indexOf(this));
    }
    setParent(0);
}

Item *Item::parent()
{
    return parent_;
}

void Item::setParent(Item *par)
{
    parent_=par;
}

void Item::insertChild(Item *ch, int pos)
{
    children_.insert(pos,ch);
    ch->setParent(this);
}

Item *Item::takeChild(int ind)
{
    return children_.takeAt(ind);
}

Item *Item::childAt(int ind) const
{
    return children_.at(ind);
}

int Item::indexOf(Item *it) const
{
    return children_.indexOf(it);
}

int Item::childCount() const
{
    return children_.length();
}

Artist *Item::toArtist()
{
    return NULL;
}

Album *Item::toAlbum()
{
    return NULL;
}

Track *Item::toTrack()
{
    return NULL;
}

QString Item::name() const
{
    return name_;
}

void Item::setName(const QString &n)
{
    name_ = n;
}

QString Item::description() const
{
    return description_;
}

void Item::setDescription(const QString &d)
{
    description_=d;
}
