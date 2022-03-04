#include "xnsnd.h"
#include <sys/_ipc.h>
#include <stdlib.h>
#include <sys/_term.h>
#include <sys/_file.h>


static xnsnd_t *snd = NULL;
/**
 * xn_snd_initialize -- initialize the clients sound
 * @param event_fd -- pri_loop event file descriptor
 */
void xn_snd_initialize (int event_fd) {
	int sound_fd = sys_open_file("/dev/snd",NULL);
	snd = (xnsnd_t*)malloc(sizeof(xnsnd_t));
	snd->sound_fd = sound_fd;
	ioquery(sound_fd,SOUND_CREATE_CLIENT,NULL);
}

/**
 * xn_snd_write -- Write PCM samples to sound buffer
 * @param buffer -- buffer to write
 * @param buffer_size -- Maximum buffer limit { 512 }
 */
void xn_snd_write (uint8_t* buffer, uint32_t buffer_size){
	if (buffer_size > 512)
		buffer_size = 512;
	UFILE f;
	f.flags = NULL;
	f.size = buffer_size;
	sys_write_file(snd->sound_fd,buffer,&f);
}

/**
 * xn_snd_add_data -- adds sound to the buffer
 * @param data -- the raw PCM data
 * @param length -- length of the file
 */
void xn_snd_add_data (unsigned char* data, uint32_t length) {
}

/**
 * xn_snd_add_pcm -- adds PCM data to sound service
 * @param event_fd -- event file descriptor to use
 */
void xn_snd_add_pcm (int event_fd) {
	pri_event_t e;
	e.to_id = 1;
	e.from_id = get_current_pid();
	e.type = SND_SRV_ADD_PCM;
	ioquery (event_fd, PRI_LOOP_PUT_EVENT,&e);
}


/**
 * xn_snd_start -- start output stream
 */
void xn_snd_start () {
	ioquery(snd->sound_fd,SOUND_PLAY,NULL);
}

/*
 * xn_snd_get_buffer -- returns current
 * buffer
 * @return buffer_pointer -- pointer to the buffer
 */
uint32_t *xn_snd_get_buffer () {
	return 0; //snd->buffer_pointer;
}

