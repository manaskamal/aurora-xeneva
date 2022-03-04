/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * svga_screen -- VMware svga screen object
 *
 * /PROJECT - Aurora {Xeneva}
 * /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#include <drivers\svga\svga_screen.h>
#include <stdio.h>

#ifdef HW_SVGA

extern svga_device svga_dev;

void svga_screen_init () {
	if (!(svga_has_fifo_cap (SVGA_FIFO_CAP_SCREEN_OBJECT) ||
		svga_has_fifo_cap (SVGA_FIFO_CAP_SCREEN_OBJECT_2))) {
			printf ("[VMware SVGA]: Virtual Device does not have screen object enabled\n");
	}
}


void svga_screen_create (SVGAScreenObject* screen) {
	if (svga_has_fifo_cap (SVGA_FIFO_CAP_SCREEN_OBJECT_2)) {
		const uint32_t pitch = screen->size.width * sizeof (uint32_t);
		const uint32_t size = screen->size.height * pitch;
		screen->structSize = sizeof (SVGAScreenObject);
		svga_alloc_gmr (size, &screen->backingStore.ptr);
		screen->backingStore.ptr.offset = 0;
		screen->backingStore.pitch = pitch;
	} else {
		screen->structSize = offsetof (SVGAScreenObject, backingStore);
	}
	svga_screen_define (screen);
}

void svga_screen_define (const SVGAScreenObject *screen) {
	SVGAFifoCmdDefineScreen *cmd = (SVGAFifoCmdDefineScreen*)svga_fifo_reserved_cmd (SVGA_CMD_DEFINE_SCREEN,
		screen->structSize);

	memcpy (cmd, (void*)screen, screen->structSize);
	svga_fifo_commit_all();
}

void svga_screen_destroy (uint32_t id) {
	SVGAFifoCmdDestroyScreen *cmd = (SVGAFifoCmdDestroyScreen *)svga_fifo_reserved_cmd (SVGA_CMD_DESTROY_SCREEN, sizeof *cmd);
	cmd->screenId = id;
	svga_fifo_commit_all();
}

void
svga_screen_define_gmrfb(SVGAGuestPtr ptr,           // IN
                   uint32 bytesPerLine,        // IN
                   SVGAGMRImageFormat format)  // IN
{
   SVGAFifoCmdDefineGMRFB *cmd = (SVGAFifoCmdDefineGMRFB*)svga_fifo_reserved_cmd(SVGA_CMD_DEFINE_GMRFB, sizeof *cmd);
   cmd->ptr = ptr;
   cmd->bytesPerLine = bytesPerLine;
   cmd->format = format;
   svga_fifo_commit_all();
}



void
svga_screen_blit_from_gmrfb(const SVGASignedPoint *srcOrigin,  // IN
                     const SVGASignedRect *destRect,    // IN
                     uint32 destScreen)                 // IN
{
	SVGAFifoCmdBlitGMRFBToScreen *cmd = (SVGAFifoCmdBlitGMRFBToScreen*)svga_fifo_reserved_cmd(SVGA_CMD_BLIT_GMRFB_TO_SCREEN,
		sizeof(SVGAFifoCmdBlitGMRFBToScreen));
   cmd->srcOrigin = *srcOrigin;
   cmd->destRect = *destRect;
   cmd->destScreenId = destScreen;
   svga_fifo_commit_all();
}


void
svga_screen_blit_to_gmrfb(const SVGASignedPoint *destOrigin,  // IN
                   const SVGASignedRect *srcRect,      // IN
                   uint32 srcScreen)                   // IN
{
   SVGAFifoCmdBlitScreenToGMRFB *cmd = (SVGAFifoCmdBlitScreenToGMRFB *)svga_fifo_reserved_cmd(SVGA_CMD_BLIT_SCREEN_TO_GMRFB,
                                                           sizeof *cmd);
   cmd->destOrigin = *destOrigin;
   cmd->srcRect = *srcRect;
   cmd->srcScreenId = srcScreen;
   svga_fifo_commit_all ();
}




void
svga_screen_annotate_fill(SVGAColorBGRX color)  // IN
{
   SVGAFifoCmdAnnotationFill *cmd = (SVGAFifoCmdAnnotationFill*)svga_fifo_reserved_cmd(SVGA_CMD_ANNOTATION_FILL,
                                                        sizeof *cmd);
   cmd->color = color;
   svga_fifo_commit_all();
}




void
svga_screen_annotate_copy(const SVGASignedPoint *srcOrigin,  // IN
                    uint32 srcScreen)                  // IN
{
   SVGAFifoCmdAnnotationCopy *cmd =(SVGAFifoCmdAnnotationCopy *)svga_fifo_reserved_cmd(SVGA_CMD_ANNOTATION_COPY,
                                                        sizeof *cmd);
   cmd->srcOrigin = *srcOrigin;
   cmd->srcScreenId = srcScreen;
   svga_fifo_commit_all ();
}


void svga_paint_screen (uint32_t color, int x_, int y_, int width, int height) {
	uint32_t *fb = (uint32_t*)svga_dev.fb_mem;
	int x, y;
	static uint32_t fence = 0;

	for (y = 0; y < height; y++) {
		uint32_t *row = &fb[(y_ + y) * svga_dev.width + x_];

		for (x = 0; x < width; x++) {
			row[x] = color;
			
		}
	}
	svga_update(x_, y_, width,height);
}

#endif