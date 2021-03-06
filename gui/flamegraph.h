/*
 * Copyright 2015 Milian Wolff <mail@milianw.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef FLAMEGRAPH_H
#define FLAMEGRAPH_H

#include <QWidget>
#include <QVector>

#include "treemodel.h"

class QGraphicsScene;
class QGraphicsView;
class QComboBox;
class QLabel;

class FrameGraphicsItem;

class FlameGraph : public QWidget
{
    Q_OBJECT
public:
    FlameGraph(QWidget* parent = nullptr, Qt::WindowFlags flags = 0);
    ~FlameGraph();

    void setTopDownData(const TreeData& topDownData);
    void setBottomUpData(const TreeData& bottomUpData);

    void setDisplayText(const QString& text);

protected:
    bool eventFilter(QObject* object, QEvent* event) override;

private slots:
    void setData(FrameGraphicsItem* rootItem);

private:
    void navigateBack();
    void navigateForward();
    void showData();
    void selectItem(FrameGraphicsItem* item);

    TreeData m_topDownData;
    TreeData m_bottomUpData;

    QComboBox* m_costSource;
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
    QLabel* m_displayLabel;
    FrameGraphicsItem* m_rootItem;
    QVector<FrameGraphicsItem*> m_selectionHistory;
    int m_selectedItem = -1;
    int m_minRootWidth = 0;
    bool m_showBottomUpData = false;
    // cost threshold in percent, items below that value will not be shown
    double m_costThreshold = 0.1;
};

#endif // FLAMEGRAPH_H
