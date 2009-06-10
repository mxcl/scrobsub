/*
   Copyright 2009 Last.fm Ltd.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
   IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
   NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
   THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __SCROBSUB_H__
#define __SCROBSUB_H__

#if _MSC_VER <= 1400
 #define SCROBSUB_NO_C99 1
#endif

#if SCROBSUB_NO_C99
 #if !__cplusplus
  #define bool int
  #define false 0
  #define true 1
 #endif
#else
 #include <stdbool.h>
#endif


#if __cplusplus
extern "C" {
#endif

/** the callback must be set, when the callback is called, you get one of the
  * SCROBSUB_ values. */
void scrobsub_init(void(*callback)(int event, const char* message));

/** you need to call scrobsub_auth, but you can do it whenever you want,
  * although, no scrobbling will happen until then */
#define SCROBSUB_AUTH_REQUIRED 0
/** the char* paramater will be the error string */
#define SCROBSUB_ERROR_RESPONSE 1


/** the user needs to visit @p url within one hour for authentication to succeed */
void scrobsub_auth(char url[110]);

/** once the user has visited the above page, we need to request their session
  * key, you can either do this yourself, or scrobsub will do it as required,
  * mostly you won't need to call this function
  * @returns true if authentication was successful */
bool scrobsub_finish_auth();


/** A new track started. scrobsub takes copies of the strings. All strings must
  * be UTF8. 
  * artist, track and duration are mandatory
  * album and mbid can be "" (do not pass NULL or 0)
  * if track_number is 0 it is ignored (yes, we know some albums have a zeroth track)
  * valid MBIDs are always 38 characters, be wary of that
  */
void scrobsub_start(const char* artist, const char* track, unsigned int duration, const char* album, unsigned int track_number, const char* mbid);
/** the thing that we're scrobbling got paused. This is not a toggle, when/if
  * the track is unpaused, call resume. We insist on this distinction because
  * we want you to be exact! */
void scrobsub_pause();
/** the thing that we're scrobbling was unpaused */
void scrobsub_resume();
/** only call this when playback stops, if a new track is about to start, call
  * scrobsub_start() instead */
void scrobsub_stop();

    
/** marks the current track as loved, it is worth noting, you also have to call
  * the Last.fm track.love webservice separately (scrobsub doesn't do it for 
  * you). This stupid system will be like this forever prolly. Sorry about that.
  */
void scrobsub_love();

/** support this if you can and it is appropriate */
void scrobsub_change_metadata(const char* artist, const char* track, const char* album);


#define SCROBSUB_STOPPED 0
#define SCROBSUB_PLAYING 1
#define SCROBSUB_PAUSED 2

int scrobsub_state();


/** returns 0 if you need to auth, or the user still hasn't allowed the auth 
  * attempt */
extern char* scrobsub_session_key;
extern char* scrobsub_username;


/** for your convenience, we need it, so maybe you can use it too, we use the
  * platform native library to generate this md5 */
void scrobsub_md5(char out[33], const char* in);


#define SCROBSUB_VERSION 0x00020000
#define SCROBSUB_MAJOR_VERSION 2
#define SCROBSUB_MINOR_VERSION 0
#define SCROBSUB_PATCH_VERSION 0

#if __cplusplus
}
#endif
#endif
