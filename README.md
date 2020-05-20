# Mandelbrot-Fractal-Animation

- Fractals have their existence in almost everything: leaves in a tree, veins in a hand, etc. They have numerous applications in the field of astronomy, computer science (fractal image compression), telecommunications (fractal-shaped antenna) and surface physics to name a few.
- The aim of this project is to use core C++ for generating such fractals.
- In this project, a Mandelbrot fractal image is generated each time with different coefficient values, to create appropriate zooming and panning to ensure smooth transition of images in the animation.
- The result is, a series of .ppm image files, all of which can be converted to .jpg and further combined using any video maker to form an animation.
- This simple project shows how mathematical equations with minor adjustments in the coefficient values, combined with any coding language can generate visually appealing images.

Technical Details:
  -
  - The mathematical equation for Mandelbrot fractals has 4 coefficients (cxmin, cymin) and (cxmax, cymax). These are diagonal endpoints of a complex-number rectangle. Their values can range anywhere between (-2, -1) and (1, 1) respectively.
  - These values are to be varied to create various zoom patterns of the fractal. The file input.txt contains rows of these values in   order: ‘filename  cxmin  cymin  cxmax  cymax’.
  - More values can be added to this .txt file to create even better levels of zoom patterns depending on the requirement.
  - The code generates images of resolution 320x320 which best matches the aspect ratio (cxmax-cxmin)/(cymax-cymin) for each value. The resolution must be a multiple of this ratio. Eg. If this ratio is 1.8, the resolution can be 1800x1000, 3600x2000, 900x500 and so on. This ensures that the images do not appear stretched/squashed.

Technologies Used:
  -
  - Language: C++
  - IDE: Code::Blocks
  - Graphic Viewer: IrfanView
  - GIF Creation: https://gifmaker.me/
