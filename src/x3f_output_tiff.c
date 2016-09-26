/* X3F_OUTPUT_TIFF.C
 *
 * Library for writing the image as TIFF.
 *
 * Copyright 2015 - Roland and Erik Karlsson
 * BSD-style - see doc/copyright.txt
 *
 */

#include "x3f_output_tiff.h"
#include "x3f_process.h"
#include "x3f_printf.h"

#include <stdlib.h>
#include <tiffio.h>

/* extern */
x3f_return_t x3f_dump_raw_data_as_tiff(x3f_t *x3f,
                                       char *outfilename,
                                       x3f_color_encoding_t encoding,
                                       int crop,
                                       int denoise,
                                       int apply_sgain,
                                       char *wb,
                                       int compress) {
    x3f_area16_t image;
    TIFF *f_out = TIFFOpen(outfilename, "w");
    int row;

    if (f_out == NULL) return X3F_OUTFILE_ERROR;

    if (!x3f_get_image(x3f, &image, NULL, encoding,
                       crop, denoise, apply_sgain,
                       wb)) {
        TIFFClose(f_out);
        return X3F_ARGUMENT_ERROR;
    }

    TIFFSetField(f_out, TIFFTAG_IMAGEWIDTH, image.columns);
    TIFFSetField(f_out, TIFFTAG_IMAGELENGTH, image.rows);
    TIFFSetField(f_out, TIFFTAG_ROWSPERSTRIP, 32);
    TIFFSetField(f_out, TIFFTAG_SAMPLESPERPIXEL, image.channels);
    TIFFSetField(f_out, TIFFTAG_BITSPERSAMPLE, 16);
    TIFFSetField(f_out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(f_out, TIFFTAG_COMPRESSION, compress ? COMPRESSION_DEFLATE : COMPRESSION_NONE);
    TIFFSetField(f_out, TIFFTAG_PHOTOMETRIC, image.channels == 1 ?
                                             PHOTOMETRIC_MINISBLACK : PHOTOMETRIC_RGB);
    TIFFSetField(f_out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(f_out, TIFFTAG_XRESOLUTION, 72.0);
    TIFFSetField(f_out, TIFFTAG_YRESOLUTION, 72.0);
    TIFFSetField(f_out, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);

    for (row = 0; row < image.rows; row++)
        TIFFWriteScanline(f_out, image.data + image.row_stride * row, row, 0);

    TIFFWriteDirectory(f_out);
    TIFFClose(f_out);
    free(image.buf);

    return X3F_OK;
}

/* Write CAMF entry to TIFF file - crw */
/* extern */
x3f_return_t dump_sgain_table_as_tiff(camf_entry_t *entry, char *outfilename) {

    x3f_printf(DEBUG, "dump_sgain_table_as_tiff start\n");

    x3f_area16_t image;

    uint32_t dim       = entry->matrix_dim;
    uint32_t linesize  = entry->matrix_dim_entry[dim - 1].size;
    uint32_t blocksize = (uint32_t) (-1);
    uint32_t totalsize = entry->matrix_elements;
    int i;

    // Sanity check: we only write a 2d table of unsigned int (i.e., spatial gain table):
    if ((entry->matrix_decoded_type != M_UINT) || (dim != 2)) {
        return X3F_ARGUMENT_ERROR;
    }

    x3f_printf(DEBUG, "dump_sgain_table_as_tiff opening file %s\n", outfilename);

    TIFF *f_out = TIFFOpen(outfilename, "w");

    int row;

    if (f_out == NULL) return X3F_OUTFILE_ERROR;

    x3f_printf(INFO, "dump_sgain_table_as_tiff file open OK\n");

    TIFFSetField(f_out, TIFFTAG_IMAGEWIDTH, image.columns);
    TIFFSetField(f_out, TIFFTAG_IMAGELENGTH, image.rows);
    TIFFSetField(f_out, TIFFTAG_ROWSPERSTRIP, 32);
    TIFFSetField(f_out, TIFFTAG_SAMPLESPERPIXEL, image.channels);
    TIFFSetField(f_out, TIFFTAG_BITSPERSAMPLE, 16);
    TIFFSetField(f_out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(f_out, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
    TIFFSetField(f_out, TIFFTAG_PHOTOMETRIC, image.channels == 1 ?
                                             PHOTOMETRIC_MINISBLACK : PHOTOMETRIC_RGB);
    TIFFSetField(f_out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(f_out, TIFFTAG_XRESOLUTION, 72.0);
    TIFFSetField(f_out, TIFFTAG_YRESOLUTION, 72.0);
    TIFFSetField(f_out, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);

/* stub for now - crw
    for (i = 0; i < totalsize; i++) {
        print_matrix_element(f_out, entry, i);
        if ((i + 1) % linesize  == 0) fprintf(f_out, "\n");
        if ((i + 1) % blocksize == 0) fprintf(f_out, "\n");
    }

    for (row = 0; row < image.rows; row++)
        TIFFWriteScanline(f_out, image.data + image.row_stride * row, row, 0);
*/
    TIFFWriteDirectory(f_out);
    TIFFClose(f_out);
    free(image.buf);

    return X3F_OK;
}
