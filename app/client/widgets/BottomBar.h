/***************************************************************************
 *   Copyright 2005-2008 Last.fm Ltd.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QWidget>
#include "widgets/ImageButton.h"
class BottomBarButton;
class ScrobbleButton;


class BottomBar : public QWidget
{
public:
	BottomBar();

    struct {
        BottomBarButton* radio;
        BottomBarButton* sources;
        BottomBarButton* friends;
        BottomBarButton* library;
        ScrobbleButton* scrobble;
    } ui;
    
    
private:
    QPoint m_mouseDownPos;
    QPoint m_offset;
};


class BottomBarButton : public ImageButton
{
    Q_OBJECT
    
    QWidget* m_widget;
    
public:    
    BottomBarButton();
    
    void setWidget( QWidget* );
    
private slots:
    void onToggled( bool );
    
private:
    bool eventFilter( QObject*, QEvent* );
};

#endif //LAUNCHER_H