#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/mucroomhandler.h>
#include <gloox/mucroom.h>
#include <gloox/disco.h>
#include <gloox/presence.h>
#include <gloox/message.h>
#include <gloox/dataform.h>
#include <gloox/gloox.h>
#include <gloox/lastactivity.h>
#include <gloox/loghandler.h>
#include <gloox/logsink.h>
#include <stdio.h>
#include <locale.h>
#include <string>
#ifdef WIN32
#include <windows.h>
#endif
#include "ChatGroup.h"

void ChatGroup::handleMUCParticipantPresence( MUCRoom * /*room*/, const MUCRoomParticipant participant,
                                        Presence::PresenceType presence )
{
  if( presence == Presence::Available )
    printf( "!!!!!!!!!!!!!!!! %s is in the room, too\n", participant.nick->resource().c_str() );
  else if( presence == Presence::Unavailable )
    printf( "!!!!!!!!!!!!!!!! %s left the room\n", participant.nick->resource().c_str() );
  else
    printf( "Presence is %d of %s\n", presence, participant.nick->resource().c_str() );
}

void ChatGroup::handleMUCMessage( MUCRoom* /*room*/, const Message& msg, bool priv )
{
  printf( "%s said: '%s' (history: %s, private: %s)\n", msg.from().resource().c_str(), msg.body().c_str(),
          msg.when() ? "yes" : "no", priv ? "yes" : "no" );
}

void ChatGroup::handleMUCSubject( MUCRoom * /*room*/, const std::string& nick, const std::string& subject )
{
  if( nick.empty() )
    printf( "Subject: %s\n", subject.c_str() );
  else
    printf( "%s has set the subject to: '%s'\n", nick.c_str(), subject.c_str() );
}

void ChatGroup::handleMUCError( MUCRoom * /*room*/, StanzaError error )
{
  printf( "!!!!!!!!got an error: %d", error );
}

void ChatGroup::handleMUCInfo( MUCRoom * /*room*/, int features, const std::string& name,
                                const DataForm* infoForm )
{
  printf( "features: %d, name: %s, form xml: %s\n",
          features, name.c_str(), infoForm->tag()->xml().c_str() );
}

void ChatGroup::handleMUCItems( MUCRoom * /*room*/, const Disco::ItemList& items )
{
  Disco::ItemList::const_iterator it = items.begin();
  for( ; it != items.end(); ++it )
  {
    printf( "%s -- %s is an item here\n", (*it)->jid().full().c_str(), (*it)->name().c_str() );
  }
}

void ChatGroup::handleMUCInviteDecline( MUCRoom * /*room*/, const JID& invitee, const std::string& reason )
{
  printf( "Invitee %s declined invitation. reason given: %s\n", invitee.full().c_str(), reason.c_str() );
}

bool ChatGroup::handleMUCRoomCreation( MUCRoom *room )
{
  printf( "room %s didn't exist, beeing created.\n", room->name().c_str() );
  return true;
}
