#!/bin/sh

make all                                                                 || exit 1

./mandelbrot                                                             || exit 1

cat head.pnm mandelbrotset.raw > mandelbrotset.pnm                   	 || exit 1

rm head.pnm mandelbrotset.raw                                            || exit 1

exit 0
