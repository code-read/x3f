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
#include "x3f_io.h"

#include <stdlib.h>
#include <tiffio.h>

/* extern */
x3f_return_t x3f_dump_raw_data_as_tiff(x3f_t *x3f, char *outfilename, x3f_color_encoding_t encoding,
                                       int crop, int denoise, int apply_sgain, char *wb, int compress) {
    x3f_area16_t image;
    TIFF *f_out = TIFFOpen(outfilename, "w");
    int row;

    if (f_out == NULL) return X3F_OUTFILE_ERROR;

    if (!x3f_get_image(x3f, &image, NULL, encoding, crop, denoise, apply_sgain, wb)) {
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
    x3f_area16_t image;
    uint32_t dim       = entry->matrix_dim; // How many dimensions this matrix has (always 2 for us)

    // Sanity check: we only write a 2d table of unsigned int (i.e., spatial gain table):
    if ((entry->matrix_decoded_type != M_UINT) || (dim != 2)) {
        return X3F_ARGUMENT_ERROR;
    }

    image.channels   = 1;
    image.rows       = entry->matrix_dim_entry[0].size;
    image.columns    = entry->matrix_dim_entry[1].size;
    image.row_stride = image.columns * entry->matrix_element_size;

    TIFF *f_out = TIFFOpen(outfilename, "w");
    if (f_out == NULL) return X3F_OUTFILE_ERROR;

    x3f_printf(DEBUG, "dump_sgain_table_as_tiff matrix_element_size = %d\n",
               entry->matrix_element_size);

    TIFFSetField(f_out, TIFFTAG_IMAGEWIDTH, image.columns);
    TIFFSetField(f_out, TIFFTAG_IMAGELENGTH, image.rows);
    TIFFSetField(f_out, TIFFTAG_ROWSPERSTRIP, 32);
    TIFFSetField(f_out, TIFFTAG_SAMPLESPERPIXEL, image.channels);
    // From my DP2M, _MOD_ and _INF_ tables are 8 bit, others are 16 bit - crw:
    TIFFSetField(f_out, TIFFTAG_BITSPERSAMPLE, entry->matrix_element_size * 8);
    TIFFSetField(f_out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(f_out, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
    TIFFSetField(f_out, TIFFTAG_PHOTOMETRIC, image.channels == 1 ?
                                             PHOTOMETRIC_MINISBLACK : PHOTOMETRIC_RGB);
    TIFFSetField(f_out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(f_out, TIFFTAG_XRESOLUTION, 72.0);
    TIFFSetField(f_out, TIFFTAG_YRESOLUTION, 72.0);
    TIFFSetField(f_out, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);

    int row;
    for (row = 0; row < image.rows; row++) {
        // int TIFFWriteScanline(TIFF* tif, tdata_t buf, uint32 row, tsample_t sample)
        if(TIFFWriteScanline(f_out, entry->matrix_data + (image.row_stride * row), row, 0) < 0) {
            x3f_printf(ERR, "error writing SGAIN file %s: %d\n", outfilename, errno);
            TIFFClose(f_out);
            break;
        }
    }

    TIFFWriteDirectory(f_out);
    TIFFClose(f_out);
    free(image.buf);

    return X3F_OK;
}
