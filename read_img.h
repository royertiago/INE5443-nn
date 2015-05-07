#ifndef READ_IMG_H
#define READ_IMG_H

/* Wrapper for the only functionality we use from opencv:
 * the ability of reading several different image formats.
 */

#include <string>
#include <vector>

/* Returns a vector with all the pixels in the image.
 * The image is interpreted in grayscale;
 * a pixel value of 0 (black) results in a 1.0 entry in the returned vector
 * and 255 (white) yields 0.0.
 *
 * The pixels are returned in row major order;
 * that is, first, all pixels of the first row,
 * then, all pixels of the second row,
 * and so on.
 *
 * Throws std::runtime_error if the file could not be read.
 */
std::vector<float> read_pixels( std::string filename );

#endif // READ_IMG_H
