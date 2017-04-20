#pragma once

// First the fonts
// Comment out to not use the font, saves a lot of memory not including them
// DejaVuSans18 is the DEFAULT font
// If you comment it out, make sure ALL your other fonts you use are included, as DejaVu is the fallback
// If you dont, you *WILL* get runtime errors
#define useDejaVu18

// The rest are strictly optional
#define useCourier10
#define useCourier14
#define useCourier24
#define useCourier36
#define useCourierB10
#define useCourierB14
#define useCourierB24
#define useCourierB36
#define useAlef10
#define useAlef14
#define useAlef24
#define useAlef36
#define useAlefB10
#define useAlefB14
#define useAlefB24
#define useAlefB36
#define useQuivira10
#define useQuivira14
#define useQuivira24
#define useQuivira36
#define useQuiviraB10
#define useQuiviraB14
#define useQuiviraB24
#define useQuiviraB36

//TODO: IFDEF enable all UIElements except windows
#define useButtons
#define useText