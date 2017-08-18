/*
The MIT License (MIT)

Copyright (c) 2017 Patrick Scheibe

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/*
 * This is a wrapper of the Faddeeva package (http://ab-initio.mit.edu/wiki/index.php/Faddeeva_Package) for Mathematica
 *
 * The wrapper definitions below can be loaded compiled and loaded as Mathematica LibraryLink functions giving a vast
 * performance speed compared to using the a standard definition of the Faddeeva function:
 *
 * w[z_] := Exp[-z^2] (1 - Erf[-I*z]);
 *
 * for more information please see the README file that comes with this package.
 */

#include "WolframLibrary.h"
#include "Faddeeva.h"

inline complex double fromMComplex(mcomplex z) {
    return mcreal(z)+I*mcimag(z);
}

inline mcomplex toMComplex(complex double z) {
    mcomplex result = {creal(z), cimag(z)};
    return result;
}

DLLEXPORT mint WolframLibrary_getVersion() {
    return WolframLibraryVersion;
}


DLLEXPORT int WolframLibrary_initialize(WolframLibraryData libData) {
    return 0;
}

DLLEXPORT void WolframLibrary_uninitialize(WolframLibraryData libData) {}

// compute w(z) = exp(-z^2) erfc(-iz) [ Faddeeva / scaled complex error func ]

// calling extern double complex Faddeeva_w(double complex z,double relerr);
EXTERN_C DLLEXPORT int m_Faddeeva_w(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mcomplex z = MArgument_getComplex(args[0]);
    MArgument_setComplex(res, toMComplex(Faddeeva_w(fromMComplex(z), 0)));
    return LIBRARY_NO_ERROR;
}

// calling extern double Faddeeva_w_im(double x); // special-case code for Im[w(x)] of real x
EXTERN_C DLLEXPORT int m_Faddeeva_w_im(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mreal x = MArgument_getReal(args[0]);
    MArgument_setReal(res, Faddeeva_w_im(x));
    return LIBRARY_NO_ERROR;
}

// Various functions that we can compute with the help of w(z)

// calling extern double complex Faddeeva_erfcx(double complex z, double relerr);
EXTERN_C DLLEXPORT int m_Faddeeva_erfcx(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mcomplex z = MArgument_getComplex(args[0]);
    MArgument_setComplex(res, toMComplex(Faddeeva_erfcx(fromMComplex(z), 0)));
    return LIBRARY_NO_ERROR;
}

// extern double Faddeeva_erfcx_re(double x); // special case for real x
EXTERN_C DLLEXPORT int m_Faddeeva_erfcx_re(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mreal x = MArgument_getReal(args[0]);
    MArgument_setReal(res, Faddeeva_erfcx_re(x));
    return LIBRARY_NO_ERROR;
}

// compute erf(z), the error function of complex arguments

// calling extern double complex Faddeeva_erf(double complex z, double relerr);
EXTERN_C DLLEXPORT int m_Faddeeva_erf(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mcomplex z = MArgument_getComplex(args[0]);
    MArgument_setComplex(res, toMComplex(Faddeeva_erf(fromMComplex(z), 0)));
    return LIBRARY_NO_ERROR;
}

// calling extern double Faddeeva_erf_re(double x); // special case for real x
EXTERN_C DLLEXPORT int m_Faddeeva_erf_re(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mreal x = MArgument_getReal(args[0]);
    MArgument_setReal(res, Faddeeva_erf_re(x));
    return LIBRARY_NO_ERROR;
}

// compute erfi(z) = -i erf(iz), the imaginary error function

// calling extern double complex Faddeeva_erfi(double complex z, double relerr);
EXTERN_C DLLEXPORT int m_Faddeeva_erfi(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mcomplex z = MArgument_getComplex(args[0]);
    MArgument_setComplex(res, toMComplex(Faddeeva_erfi(fromMComplex(z), 0)));
    return LIBRARY_NO_ERROR;
}

// calling extern double Faddeeva_erfi_re(double x); // special case for real x
EXTERN_C DLLEXPORT int m_Faddeeva_erfi_re(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mreal x = MArgument_getReal(args[0]);
    MArgument_setReal(res, Faddeeva_erf_re(x));
    return LIBRARY_NO_ERROR;
}

// compute erfc(z) = 1 - erf(z), the complementary error function

// calling extern double complex Faddeeva_erfc(double complex z, double relerr);
EXTERN_C DLLEXPORT int m_Faddeeva_erfc(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mcomplex z = MArgument_getComplex(args[0]);
    MArgument_setComplex(res, toMComplex(Faddeeva_erfc(fromMComplex(z), 0)));
    return LIBRARY_NO_ERROR;
}

// calling extern double Faddeeva_erfc_re(double x); // special case for real x
EXTERN_C DLLEXPORT int m_Faddeeva_erfc_re(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mreal x = MArgument_getReal(args[0]);
    MArgument_setReal(res, Faddeeva_erfc_re(x));
    return LIBRARY_NO_ERROR;
}

// compute Dawson(z) = sqrt(pi)/2  *  exp(-z^2) * erfi(z)

// calling extern double complex Faddeeva_Dawson(double complex z, double relerr);
EXTERN_C DLLEXPORT int m_Faddeeva_Dawson(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mcomplex z = MArgument_getComplex(args[0]);
    MArgument_setComplex(res, toMComplex(Faddeeva_Dawson(fromMComplex(z), 0)));
    return LIBRARY_NO_ERROR;
}

// extern double Faddeeva_Dawson_re(double x); // special case for real x
EXTERN_C DLLEXPORT int m_Faddeeva_Dawson_re(WolframLibraryData libData, mint argc, MArgument *args, MArgument res) {
    mreal x = MArgument_getReal(args[0]);
    MArgument_setReal(res, Faddeeva_Dawson_re(x));
    return LIBRARY_NO_ERROR;
}
