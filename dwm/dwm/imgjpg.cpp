/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  imgjpg.h -- Image JPEG codec format
 *
 *  /PROJECT - DWM {Aurora Xeneva v1.0}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#include <imgjpg.h>
#include <stdtypes.h>
#include <allocator.h>
#include <sys.h>

extern "C" uint16_t swap_word (uint16_t variable);

#define H_Y_BLOCKSPERMCU    jpg->hvBlocksPerMcu[0]
#define V_Y_BLOCKSPERMCU    jpg->hvBlocksPerMcu[1]
#define H_CB_BLOCKSPERMCU   jpg->hvBlocksPerMcu[2]
#define V_CB_BLOCKSPERMCU   jpg->hvBlocksPerMcu[3]
#define H_CR_BLOCKSPERMCU   jpg->hvBlocksPerMcu[4]
#define V_CR_BLOCKSPERMCU   jpg->hvBlocksPerMcu[5]
#define Y_BLOCKSPERMCU      jpg->blocksPerMcu[0]
#define CB_BLOCKSPERMCU     jpg->blocksPerMcu[1]
#define CR_BLOCKSPERMCU     jpg->blocksPerMcu[2]

//!YCbCr->RGB conversion
#define rgbR(y, cr)  (((y << 16) + (91881 * (cr - 128))) >> 16)
#define rgbG(y, cb, cr) (((y << 16) - (22544 * (cb - 128)) - \
	(46793 * (cr - 128))) >> 16)
#define rgbB(y, cb) (((y << 16) + (116129 * (cb - 128))) >> 16)


static unsigned short read_bits (unsigned char* data_pointer, unsigned *bit_position, int bits,
								 int consume) {
}


static int decode (jpg_data* jpg, uint32_t pixel) {

	short *yCoeff = nullptr;
	short *cbCoeff = nullptr;
	short *crCoeff = nullptr;
	int xCoord = 0;
	int yCoord = 0;
	int mcuCount = 0;
	int restartCount = 0;
	unsigned char marker = 0;
	int count;

	yCoeff = (short*)dalloc ((Y_BLOCKSPERMCU * 64) * sizeof (short));
	cbCoeff = (short*)dalloc((Y_BLOCKSPERMCU * 64) * sizeof(short));
	crCoeff = (short*)dalloc((Y_BLOCKSPERMCU * 64) * sizeof(short));
	if (!yCoeff || !cbCoeff || !crCoeff)
		return -1;

	print_text ("Y_BLOCKS_PER_MCU=%d, CB_BLOCKS_PER_MCU=%d\n",Y_BLOCKSPERMCU,CB_BLOCKSPERMCU);

	/*for (yCoord = 0; yCoord < jpg->frame_header->height; yCoord += (V_Y_BLOCKSPERMCU * 8)) {
		for (xCoord = 0; xCoord < jpg->frame_header->width; xCoord += (H_Y_BLOCKSPERMCU * 8), mcuCount += 1) {
			if (jpg->restart_header && jpg->restart_header->interval) {

		}
	}*/
	return 1;
}


void draw_jpg_image (unsigned char* image_data, int length) {
	jpg_data *jpg = (jpg_data*)dalloc(20);
	jpgJfifHeader *jfif_header = nullptr;
	jpgExifHeader *exif_header = nullptr;
	jpgHuffHeader *huff_header = nullptr;
	jpgHuffTableHeader *huff_table_header = nullptr;
	jpg_huff_table *huff_table = nullptr;
	jpgQuantHeader *quant_header = nullptr;

	for (int count = 0; ((count < (length - 1)) && !jpg->data_pointer); count++) {

		if ((image_data[count] != 0xFF) || !image_data[count + 1] || 
			(image_data[count + 1] == 0xFF)) {
				continue;
		}

		count += 1;

		switch (image_data[count]) {
		
		case JPG_DHT: 
			huff_header = (jpgHuffHeader*)(image_data + count + 1);
		    huff_header->length = swap_word (huff_header->length);
			huff_table_header = &huff_header->table;      //<-- SUSPECTED LINE
			print_text ("JPEG DHT Header found\n");
			for (int count2 = 0; (( huff_table_header + sizeof (jpgHuffTableHeader)) < ((jpgHuffTableHeader*) huff_header +
				huff_header->length)); count2++) {
					if (huff_table_header->classIdent == JPG_HUFF_DC_LUM_ID) {
						print_text ("Hufftable found -> %d\n", count);
						huff_table = &jpg->huff_table[JPG_HUFF_DC_LUM];
					}
			}
			count += huff_header->length;
			break;
			
		case JPG_SOF:
			print_text ("JPEG File Frame Header found\n");
			jpg->frame_header = (jpgFrameHeader*)(image_data + count + 1);
			jpg->frame_header->length = swap_word (jpg->frame_header->length);

			//jpg->frame_header->height = swap_word(jpg->frame_header->height);
			//jpg->frame_header->width = swap_word(jpg->frame_header->width);
			print_text ("JPEG Image Width -> %d, Height -> %d\n", jpg->frame_header->width, jpg->frame_header->height);
			print_text ("JPEG Bit Depth -> %d\n", jpg->frame_header->precision);
			count += jpg->frame_header->length;
			print_text ("JPEG SOF Header Num Components -> %d\n", jpg->frame_header->numComps);
			break;

		case JPG_SOS:
			jpg->scan_header = (jpgScanHeader*)(image_data + count + 1);
			jpg->scan_header->length = swap_word (jpg->scan_header->length);
			jpg->data_pointer = (image_data + count + 1 + jpg->scan_header->length);
			print_text ("JPEG Start-Of-Screen at %d length -> %d\n", count,jpg->scan_header->length);
			count += jpg->scan_header->length;
			break;
		

		case JPG_DQT: 
			quant_header = (jpgQuantHeader*)(image_data + count + 1);
			quant_header->length = swap_word(quant_header->length);
			print_text ("JPEG DQT Table found at %d length %d bytes\n", quant_header->length, count);
			//int count2 = (count + 3);
			/*while (jpg->num_quant_tables < JPG_QUANT_TABLES) 
			{*/
			count += quant_header->length;
			break;

		case JPG_DRI:
			jpg->restart_header = (jpgRestartHeader*)(image_data + count + 1);
			jpg->restart_header->length = swap_word (jpg->restart_header->length);
			print_text ("JPEG DRI Table found at -> %d, Restart interval -> %d\n",
				count, jpg->restart_header->interval);
			print_text ("JPEG DRI Table length -> %d\n", jpg->restart_header->length);
			count += jpg->restart_header->length;
			break;
			
		case JPG_SOF1:
		case JPG_SOF2:
		case JPG_SOF3:
		case JPG_SOF5:
		case JPG_SOF6:
		case JPG_SOF7:
		case JPG_SOF9:
		case JPG_SOF10:
		case JPG_SOF11:
		case JPG_SOF13:
		case JPG_SOF14:
		case JPG_SOF15:
			print_text ("Unsupported JPEG format -> sof -> %x\n", image_data[count]);
			break;

		case JPG_SOI:
			print_text ("JPEG SOI at %d\n", count);
			break;

		case JPG_APP0:
			jfif_header = (jpgJfifHeader*)(image_data + count + 1);
			jfif_header->length = swap_word (jfif_header->length);
			print_text ("JPEG APP0 Marker found -> at %d count\n", count);
			if (jfif_header->versionMajor != 0x01) {
				print_text ("Unsupported JPEG Version -> %x\n", jfif_header->versionMajor);
			}
			print_text ("JPEG Version %d.%d\n", jfif_header->versionMajor, jfif_header->versionMinor);
			count += jfif_header->length;
			break;
		
		case JPG_APP2:
		case JPG_APP3:
		case JPG_APP4:
		case JPG_APP5:
		case JPG_APP6:
		case JPG_APP7:
		case JPG_APP8:
		case JPG_APP9:
		case JPG_APP10:
		case JPG_APP11:
		case JPG_APP12:
		case JPG_APP13:
		case JPG_APP14:
		case JPG_APP15:
			jfif_header = (jpgJfifHeader*)(image_data + count + 1);
			jfif_header->length = swap_word (jfif_header->length);
			print_text ("APP%d marker at %d \n",(image_data[count] & 0xF), count);
			count += jfif_header->length;
			break;

		case JPG_EOI:
			print_text ("JPEG EOI at %d\n", count);
			break;

		default:
			print_text ("Unsupported JPEG Marker\n");
			break;
		}
	}

	for (int count = 0; count < 3; count++) {
		jpg->hvBlocksPerMcu[count * 2] = ((jpg->frame_header->comp[count].samplingFactor & 0xF0) >> 4);
		jpg->hvBlocksPerMcu[(count * 2) + 1] = (jpg->frame_header->comp[count].samplingFactor & 0x0F);
		jpg->blocksPerMcu[count] = (jpg->hvBlocksPerMcu[count * 2] * jpg->hvBlocksPerMcu[(count * 2) + 1]);
	}


	if ((Y_BLOCKSPERMCU > 4) || (CB_BLOCKSPERMCU > 2) ||
		(CB_BLOCKSPERMCU > 2)) {
			print_text ("JPEG Y/Cb/Cr blocks per MCU is not supported\n");
	}

	if ((Y_BLOCKSPERMCU == CB_BLOCKSPERMCU) &&
		(CB_BLOCKSPERMCU == CR_BLOCKSPERMCU))
	{
		for (int count = 0; count < 6; count++)
			jpg->hvBlocksPerMcu[count] = 1;
		for (int count = 0; count < 3; count++)
			jpg->blocksPerMcu[count] = 1;
	}

	for (int count = 0; count < jpg->frame_header->numComps; count++) {
		print_text ("sample Factor = %dx%d\n",jpg->hvBlocksPerMcu[count*2],jpg->hvBlocksPerMcu[(count*2)+1]);
	}


	uint32_t pixel;
	int status = decode (jpg,pixel);
	
}