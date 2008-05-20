/*
Copyright (C) 2003-2006 Andrey Nazarov

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#define MAX_LOCAL_SERVERS 16
#define MAX_DEMOINFO_CLIENTS	20
#define MAX_STATUS_PLAYERS	64

typedef enum {
	ca_uninitialized,
	ca_disconnected, 	// not talking to a server
	ca_challenging,		// sending getchallenge packets to the server
	ca_connecting,		// sending connect packets to the server
	ca_connected,		// netchan_t established, waiting for svc_serverdata
	ca_loading,			// loading level data
    ca_precached,       // loaded level data, waiting for svc_frame
	ca_active			// game views should be displayed
} connstate_t;

typedef struct {
	char name[MAX_CLIENT_NAME];
	int ping;
	int score;
} playerStatus_t;

typedef struct {
	char	address[MAX_QPATH];
	char	infostring[MAX_STRING_CHARS]; // BIG infostring
	playerStatus_t	players[MAX_STATUS_PLAYERS];
	int	numPlayers;
	int ping;
} serverStatus_t;

typedef struct {
	char map[MAX_QPATH];
    char pov[MAX_CLIENT_NAME];
} demoInfo_t;


qboolean CL_SendStatusRequest( char *buffer, size_t size );
demoInfo_t *CL_GetDemoInfo( const char *path, demoInfo_t *info );
