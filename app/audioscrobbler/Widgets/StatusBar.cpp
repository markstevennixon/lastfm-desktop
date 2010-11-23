/*
   Copyright 2010 Last.fm Ltd.
      - Primarily authored by Jono Cole and Micahel Coffey

   This file is part of the Last.fm Desktop Application Suite.

   lastfm-desktop is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   lastfm-desktop is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with lastfm-desktop.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSizeGrip>

#include "StatusBar.h"

#include "../MediaDevices/DeviceScrobbler.h"
#include "../Application.h"

StatusBar::StatusBar( QWidget* parent )
    :StylableWidget( parent ), m_scrobbleCount(0)
{
    QHBoxLayout* layout = new QHBoxLayout( this );
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setSpacing( 0 );

    layout->addWidget( m_mainStatus = new QLabel( "", this ) );
    setStatus();
    layout->addStretch( 1 );
    layout->addWidget( m_inetStatus = new QLabel( tr(""), this ) );

    aApp->isInternetConnectionUp() ? onConnectionUp() : onConnectionDown();

    connect( aApp, SIGNAL( internetConnectionDown() ), SLOT( onConnectionDown() ) );
    connect( aApp, SIGNAL( internetConnectionUp() ), SLOT( onConnectionUp() ) );

    connect( aApp, SIGNAL( gotUserInfo(lastfm::UserDetails)), SLOT( onGotUserInfo(lastfm::UserDetails) ) );

    DeviceScrobbler* deviceScrobbler = aApp->deviceScrobbler();
    connect( deviceScrobbler, SIGNAL( detectedIPod( QString )), SLOT( onIPodDetected( QString )));
    connect( deviceScrobbler, SIGNAL( processingScrobbles()), SLOT( onProcessingScrobbles()));
    connect( deviceScrobbler, SIGNAL( foundScrobbles( QList<Track> )), SLOT( onFoundScrobbles( QList<Track> )));
    connect( deviceScrobbler, SIGNAL( noScrobblesFound()),SLOT( onNoScrobblesFound()));

    layout->addWidget( new QSizeGrip( this ), 0 , Qt::AlignBottom | Qt::AlignRight );
}

void
StatusBar::setStatus()
{
    m_mainStatus->setText( tr("Logged in as %1 (%2 scrobbles)").arg( lastfm::ws::Username, QString("%L1").arg( m_scrobbleCount ) ) );
}

void
StatusBar::onGotUserInfo(lastfm::UserDetails userDetails)
{
    m_scrobbleCount = userDetails.scrobbleCount();
    setStatus();
}

void
StatusBar::onConnectionUp()
{
    const char icon[] = {0xE3, 0x80, 0x88, 0xE2, 0x8B, 0xAF, 0xE3, 0x80, 0x89, 0x00 };
    m_inetStatus->setText( QString::fromUtf8( icon ) + tr( "Online"));
}

void
StatusBar::onConnectionDown()
{
    m_inetStatus->setText( QString::fromUtf8(":(" ) + tr( "Offline"));
}

void
StatusBar::onIPodDetected( QString iPod )
{
    m_mainStatus->setText( tr("iPod Detected... ") + iPod );
}

void
StatusBar::onProcessingScrobbles()
{
    m_mainStatus->setText( tr("Processing iPod Scrobbles...") );
}

void
StatusBar::onFoundScrobbles( QList<lastfm::Track> tracks )
{
    tracks.count() == 1 ?
        m_mainStatus->setText( tr("%1 scrobble found").arg( tracks.count() ) ):
        m_mainStatus->setText( tr("%1 scrobbles found").arg( tracks.count() ) );

    // Schedule the status message to return to normal
    QTimer::singleShot( 10 * 1000, this, SLOT(setStatus()) );
}

void
StatusBar::onNoScrobblesFound()
{
    m_mainStatus->setText( tr("No scrobbles found") );

    // Schedule the status message to return to normal
    QTimer::singleShot( 10 * 1000, this, SLOT(setStatus()) );
}

void
StatusBar::onScrobblesCached( const QList<lastfm::Track>& tracks )
{
    foreach ( lastfm::Track track, tracks )
        connect( track.signalProxy(), SIGNAL(scrobbleStatusChanged()), SLOT(onScrobbleStatusChanged()));
}

void
StatusBar::onScrobbleStatusChanged()
{
    if (static_cast<lastfm::TrackData*>(sender())->scrobbleStatus == lastfm::Track::Submitted)
    {
        ++m_scrobbleCount;
        setStatus();
    }
}