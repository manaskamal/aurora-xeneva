/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * gmr.cpp -- Think it by yourself
 *
 * /PROJECT - Aurora {Xeneva}
 * /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#include <drivers\svga\gmr.h>
#include <drivers\svga\vmsvga.h>
#include <pmmngr.h>
#include <mm.h>

gmr_state gmr;

void gmr_init () {

	if (svga_dev.capabilities & SVGA_CAP_GMR) {
		gmr.max_ids = svga_read_reg (SVGA_REG_GMR_MAX_IDS);
		gmr.max_descriptor_len = svga_read_reg (SVGA_REG_GMR_MAX_DESCRIPTOR_LENGTH);
	} else {
		printf ("Virtual device does not have GMR support\n");
	}
}

void gmr2_init (void) {
	
	if (svga_dev.capabilities & SVGA_CAP_GMR2) {
		gmr.max_ids = svga_read_reg (SVGA_REG_GMR_MAX_IDS);
		gmr.max_pages = svga_read_reg (SVGA_REG_GMRS_MAX_PAGES);
	} else {
		printf ("Virtual device does not have GMR v2 support\n");
	}
}

ppn gmr_alloc_descriptor (SVGAGuestMemDescriptor *desc_array, uint32_t num_descriptor) {

	const uint32_t desc_per_page = PAGE_SIZE / sizeof (SVGAGuestMemDescriptor) - 1;
	SVGAGuestMemDescriptor *desc = NULL;
	ppn first_page ; //= (ppn)pmmngr_alloc();
	ppn page = 0;

	int i = 0;
	printf ("Desc Array -> %x\n", desc_array);

	while (num_descriptor) {
		if (!first_page) {
			first_page = page = (ppn)pmmngr_alloc();//malloc(4096); //pmmngr_alloc();
			printf ("First page -> %x\n", page);
		}

		desc = (SVGAGuestMemDescriptor *)page; //PPN_POINTER(page);

		if (i == desc_per_page) {

			page = (ppn)pmmngr_alloc();   //malloc(4096)
			desc[i].ppn = page;
			desc[i].numPages = 0;
			i = 0; 
			continue;
		}

		desc[i] = *desc_array;
		i++;
		desc_array++;
		num_descriptor--;
	}

	if (desc) {
		desc[i].ppn = 0;
		desc[i].numPages = 0;
	}
	return first_page;
}

void gmr_define(uint32 gmrId,
           SVGAGuestMemDescriptor *descArray,
           uint32 numDescriptors)
{
   ppn desc = gmr_alloc_descriptor(descArray, numDescriptors);

   /*
    * Define/undefine the GMR. Defining an empty GMR is equivalent to
    * undefining a GMR.
    */

   svga_write_reg(SVGA_REG_GMR_ID, gmrId);
   svga_write_reg(SVGA_REG_GMR_DESCRIPTOR, desc);
   printf ("REGISTER WRITTEN\n");
   //if (desc) {
      /*
       * Clobber the first page, to verify that the device reads our
       * descriptors synchronously when we write the GMR registers.
       */
      //Heap_DiscardPages(desc, 1);
  // }
}



ppn gmr_define_contiguous(uint32 gmrId, uint32 numPages){
   SVGAGuestMemDescriptor desc;
    desc.ppn = (ppn)pmmngr_alloc(); //malloc(numPages),
    desc.numPages = numPages,
	printf ("PPN iiiii -> %x\n", desc.ppn);

    gmr_define(gmrId, &desc, 1);
	printf ("returning\n");
   return desc.ppn;
}


ppn gmr_define_even_pages(uint32 gmrId, uint32 numPages)
{
   SVGAGuestMemDescriptor *desc;
   ppn region = (ppn)pmmngr_alloc();   //malloc(numPages * 2);
 
   int i;

   desc = (SVGAGuestMemDescriptor *)pmmngr_alloc();//malloc(sizeof(desc) * numPages);
   printf ("Desc allocated %x\n", desc);
   for (i = 0; i < numPages; i++) {
      desc[i].ppn = region + i * 4096;
      desc[i].numPages = 1;
   }

   gmr_define(gmrId, desc, numPages);

   return region;
}


void gmr_free_all(void)
{
   uint32 id;

   for (id = 0; id < gmr.max_ids; id++) {
      gmr_define(id, NULL, 0);
   }
}
