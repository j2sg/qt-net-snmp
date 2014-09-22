/**
 *  This file is part of Qt-Net-SNMP.
 *
 *  Copyright (c) 2014 Juan Jose Salazar Garcia jjslzgc@gmail.com
 *
 *  Qt-Net-SNMP is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Qt-Net-SNMP is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Qt-Net-SNMP.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
* @file qmibtree.cpp
* @brief Definition for atributes and methods of QMIBTree class
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#include <qmibtree.h>
#include <qsnmpobject.h>

QtNetSNMP::QMIBTree::QMIBTree(QSNMPObject *object, QMIBTree *parent) : _object(object), _parent(parent) {}

QtNetSNMP::QMIBTree::QMIBTree(const QMIBTree& mibTree)
{
    *this = mibTree;
}

QtNetSNMP::QMIBTree& QtNetSNMP::QMIBTree::operator=(const QMIBTree& mibTree)
{
    if(_parent)
        delete _parent;

    _parent = (mibTree._parent != 0) ? new QMIBTree(*mibTree._parent) : 0;

    qDeleteAll(_childs);
    _childs.clear();

    foreach(QMIBTree *tree, mibTree._childs)
        _childs.append(new QMIBTree(*tree));

    if(_object)
        delete _object;

    _object = (mibTree._object != 0) ? new QSNMPObject(*mibTree._object) : 0;

    return *this;
}

QtNetSNMP::QMIBTree::~QMIBTree()
{
    if(_parent)
        delete _parent;

    qDeleteAll(_childs);

    if(_object)
        delete _object;
}

void QtNetSNMP::QMIBTree::setObject(QSNMPObject *object)
{
    if(_object)
        delete _object;

    _object = object;
}

QtNetSNMP::QSNMPObject *QtNetSNMP::QMIBTree::object()
{
    return _object;
}

void QtNetSNMP::QMIBTree::setParent(QMIBTree *parent)
{
    if(_parent)
        delete _parent;

    _parent = parent;
}

QtNetSNMP::QMIBTree *QtNetSNMP::QMIBTree::parent()
{
    return _parent;
}

QVector<QtNetSNMP::QMIBTree *>& QtNetSNMP::QMIBTree::childs()
{
    return _childs;
}
