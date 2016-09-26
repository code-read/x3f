/* X3F_OUTPUT_TIFF.H
 *
 * Library for writing the image as TIFF.
 *
 * Copyright 2015 - Roland and Erik Karlsson
 * BSD-style - see doc/copyright.txt
 *
 */

#ifndef X3F_OUTPUT_TIFF_H
#define X3F_OUTPUT_TIFF_H

#include "x3f_io.h"
#include "x3f_process.h"

extern x3f_return_t x3f_dump_raw_data_as_tiff(x3f_t *x3f, char *outfilename,
					      x3f_color_encoding_t encoding,
					      int crop,
					      int denoise,
					      int apply_sgain,
					      char *wb,
					      int compress);

extern x3f_return_t dump_sgain_table_as_tiff(camf_entry_t *entry, char *outfilename);

#endif
