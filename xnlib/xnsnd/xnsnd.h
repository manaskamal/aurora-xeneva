#include <stdint.h>
#include <sys/_ipc.h>
#include <sys/_process.h>
#include <sys/ioquery.h>
#include <string.h>


/* Messages that needed to send to server */
#define SND_SRV_REQUEST_BUFFER  0x1
/* Sound Buffer add pcm */
#define SND_SRV_ADD_PCM  0x2
/* Play Sound */
#define SND_SRV_PLAY_AUDIO  0x3


/* Messages that are being send by server */
#define SND_SRV_BUFFER_READY  0x1

typedef struct _xnsnd_ {
	int sound_fd;
}xnsnd_t;


/**
 * xn_snd_initialize -- initialize the clients sound
 * @param event_fd -- pri_loop event file descriptor
 */
extern void xn_snd_initialize (int event_fd);

/**
 * xn_snd_write -- Write PCM samples to sound buffer
 * @param buffer -- buffer to write
 * @param buffer_size -- Maximum buffer limit { 512 }
 */
extern void xn_snd_write (uint8_t* buffer, uint32_t buffer_size);


/**
 * xn_snd_add_data -- adds sound to the buffer
 * @param data -- the raw PCM data
 * @param length -- length of the file
 */
extern void xn_snd_add_data (unsigned char* data, uint32_t length);

/**
 * xn_snd_add_pcm -- adds PCM data to sound service
 * @param event_fd -- event file descriptor to use
 */
extern void xn_snd_add_pcm (int event_fd);

/**
 * xn_snd_play_audio -- play audio 
 * @param event_fd -- event file descriptor to use
 */
extern void xn_snd_start ();

/*
 * xn_snd_get_buffer -- returns current
 * buffer
 * @return buffer_pointer -- pointer to the buffer
 */
extern uint32_t *xn_snd_get_buffer ();