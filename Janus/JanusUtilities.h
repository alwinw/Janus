#ifndef JANUSUTILITIES_H_
#define JANUSUTILITIES_H_

//
// DST Janus Library (Janus DAVE-ML Interpreter Library)
//
// Defence Science and Technology (DST) Group
// Department of Defence, Australia.
// 506 Lorimer St
// Fishermans Bend, VIC
// AUSTRALIA, 3207
//
// Copyright 2005-2021 Commonwealth of Australia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
// OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//

//------------------------------------------------------------------------//
// Title:      Janus/JanusUtilities
// Class:      Janus
// Module:     JanusUtilities.cpp
// First Date: 2015-02-12
// Reference:  Janus Reference Manual
//------------------------------------------------------------------------//

#include <vector>

#include <Ute/aString.h>

namespace janus {

  bool isNumericTable( const char* data)
  {
    size_t length = 50;
    if ( length > strlen( data ) ) {
      length = strlen( data );
    }
    for ( size_t i = 0; i < length; ++i) {
      char x = tolower( data[ i ] );
      if ( isalpha( x ) && 'e' != x && 'd' != x && 'g' != x
           && '+' != x  && '-' != x && '.' != x ) {
        return false;
      }
    }
    return true;
  }

} // namespace janus

#endif /* JANUSUTILITIES_H_ */
