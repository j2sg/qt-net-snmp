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
* @file qmibtree.h
* @brief QMIBTree class definition
* @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
*/

#ifndef QMIBTREE_H
#define QMIBTREE_H

#include <QVector>

namespace QtNetSNMP
{
    // Forward declarations
    class QSNMPObject;

    /**
     * @brief QMIBTree class that implements a MIB tree
     */
    class QMIBTree
    {
    public:
        /**
         * @brief QMIBTree constructor
         * @param object SNMP object
         * @param parent parent node, the root node has no parent
         */
        QMIBTree(QSNMPObject *object = 0, QMIBTree *parent = 0);

        /**
         * @brief QMIBTree copy constructor
         * @param mibTree QMIBTree instance
         */
        QMIBTree(const QMIBTree& mibTree);

        /**
         * @brief Overloaded assignment operator
         * @param mibTree QMIBTree instance
         * @return reference to own object instance
         */
        QMIBTree& operator=(const QMIBTree& mibTree);

        /**
         * @brief QMIBTree destructor
         */
        ~QMIBTree();

        /**
         * @brief Set SNMP object
         * @param object SNMP object
         */
        void setObject(QSNMPObject *object);

        /**
         * @brief Get SNMP object
         * @return pointer to SNMP object
         */
        QSNMPObject *object();

        /**
         * @brief Set parent node
         * @param parent parent node
         */
        void setParent(QMIBTree *parent);

        /**
         * @brief Get parent node
         * @return pointer to parent node
         */
        QMIBTree *parent();

        /**
         * @brief Get vector of child nodes
         * @return reference to vector of child nodes
         */
        QVector<QMIBTree *>& childs();
    private:

        /**
         * @brief _object SNMP object
         */
        QSNMPObject *_object;

        /**
         * @brief _parent parent node
         */
        QMIBTree *_parent;

        /**
         * @brief _childs vector of child nodes
         */
        QVector<QMIBTree *> _childs;
    };
}

#endif // QMIBTREE_H
