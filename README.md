# Image Filters Editor

## Description
This C++ program applies 15 different filters to grayscale BMP images (256x256 pixels) with a **bonus RGB version** that can process color images. Users can apply multiple filters sequentially to the same image. The program provides a menu-driven interface for selecting and applying various image processing operations.

## Features
The program offers the following filters and operations:

### Grayscale Filters:
1. **Black and White Conversion**
2. **Image Inversion**
3. **Image Merging** (combines two images)
4. **Image Flipping** (horizontal or vertical)
5. **Image Rotation** (90°, 180°, or 270°)
6. **Darken/Lighten** (adjust image brightness)
7. **Edge Detection**
8. **Image Enlargement** (select and enlarge a quarter of the image)
9. **Image Shrinking** (to 1/2, 1/3, or 1/4 of original size)
10. **Image Mirroring** (left, right, upper, or lower half)
11. **Image Shuffling** (rearrange image quarters)
12. **Blur Effect**
13. **Image Cropping**
14. **Horizontal Skew**
15. **Vertical Skew**

### Bonus RGB Version:
The program includes a **bonus implementation** that can apply all these filters to RGB color images by processing each color channel (Red, Green, Blue) separately while maintaining color integrity.

## Requirements
- C++ compiler
- `bmplib.cpp` library (for BMP image processing)
- BMP images (256x256 pixels) - both grayscale and RGB versions supported

## Usage
1. Compile the program: `g++ filters_editor.cpp -o filters_editor`
2. Run the executable: `./filters_editor`
3. Follow the on-screen menu to:
   - Load an image (grayscale or RGB)
   - Select and apply filters
   - Save the processed image
4. For RGB processing, use the bonus version of the code (included in comments)

## File Structure
- `filters_editor.cpp`: Main program file containing all filter implementations
- `bmplib.cpp`: Library for BMP image processing (must be in the same directory)
- (Optional) `filters_editor_rgb.cpp`: Bonus RGB version (included in comments)

## RGB Implementation Notes
The bonus RGB version:
- Processes each color channel independently while maintaining color relationships
- Preserves color information through all transformations
- Includes special handling for color-specific filters (like black and white conversion)
- Maintains the same user interface but works with color images

## Example RGB Usage
1. Load "color_image.bmp" (RGB)
2. Apply black and white filter (converts to grayscale properly)
3. Apply rotation
4. Apply blur effect
5. Save as "processed_color_image.bmp"

## Limitations
- Default version works with 256x256 grayscale BMP images
- RGB version requires additional memory for color channels
- Some filters may produce different visual effects in RGB vs grayscale
- No undo functionality (save intermediate versions if needed)

For the RGB bonus code implementation, please refer to the commented sections in the source code that provide the color-aware versions of each filter.
