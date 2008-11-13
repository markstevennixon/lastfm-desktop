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

#include "MessageBar.h"
#include "widgets/ImageButton.h"
#include "common/qt/reverse.cpp"
#include <QtGui>


MessageBar::MessageBar()
{
    setFixedHeight( 0 );
    
    ui.papyrus = new QWidget( this );
    
    m_timeline = new QTimeLine( 500, this );
    m_timeline->setUpdateInterval( 10 );
    connect( m_timeline, SIGNAL(frameChanged( int )), SLOT(animate( int )) );
}


void
MessageBar::showError( const QString& message )
{
    QPalette p = palette();
    p.setColor( QPalette::Window, QColor( 0xfa, 0xfa, 0xc7 ) );
    
    QLabel* label = new QLabel( message, ui.papyrus );
    label->setPalette( p );
    label->setBackgroundRole( QPalette::Base );
    label->setMargin( 4 );
    label->setTextFormat( Qt::RichText );
    label->setOpenExternalLinks( true );
    label->setTextInteractionFlags( Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse );
    label->setAutoFillBackground( true );
    
    ImageButton* close = new ImageButton( ":/buckets/radio_clear_all_x.png" );
    QHBoxLayout* h = new QHBoxLayout( label );
    h->addStretch();
    h->addWidget( close );
    h->setMargin( 4 );
    
    label->setFixedWidth( width() );
    label->adjustSize();
    label->show();
    
    ui.papyrus->move( 0, -label->height() );
    
    int y = 0;
    foreach (QLabel* l, Qt::reverse<QLabel*>( findChildren<QLabel*>() ))
    {
        l->move( 0, y );
        y += l->height();
    }
    ui.papyrus->setFixedSize( width(), y );
        
    connect( close, SIGNAL(clicked()), label, SLOT(deleteLater()) );    
    connect( label, SIGNAL(destroyed()), SLOT(onLabelDestroyed()), Qt::QueuedConnection );
        
    m_timeline->setFrameRange( height(), ui.papyrus->height() );
    m_timeline->start();
}


void
MessageBar::showInformation( const QString& )
{}


void
MessageBar::animate( int i )
{
    setFixedHeight( i );
    ui.papyrus->move( 0, i - ui.papyrus->height() );
}


void
MessageBar::onLabelDestroyed()
{
    int h = 0;
    foreach (QLabel* l, findChildren<QLabel*>())
        h += l->height();
    
    setFixedHeight( h );
}


void
MessageBar::resizeEvent( QResizeEvent* )
{
    ui.papyrus->setFixedWidth( width() );
    foreach (QLabel* l, findChildren<QLabel*>())
        l->setFixedWidth( width() );
}
