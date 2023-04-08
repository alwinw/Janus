# pyJanus

Janus is a Dynamic Aerospace Vehicle Exchange Mark-up Language (DAVE-ML) C++ Interpreter.

This repository contains python wrappers for the Janus library, a supporting library called Ute, and example use cases.

## Installation

pyJanus can be installed directly from [PyPI](https://pypi.python.org/pypi/python-janus) pre-built wheels using:

```console
pip install python-janus
```

## Resources

- DST Group Janus website: <https://www.dst.defence.gov.au/our-technologies/janus-dynamic-aerospace-vehicle-exchange-mark-language-dave-ml-c-interpreter>

- DAVE-ML website: <http://daveml.org/intro.html>

## Build

From within the top-level directory you can instal pyJanus with pip:

```console
export MAKEFLAGS=-j8
pip install --verbose .[test]
```

To run tests, run `python -m pytest --verbose`

If you wish to only compile the binary `pyJanus.pyd`, you can run:

```console
mkdir build
cmake . -B build -DBUILD_PYBINDINGS=ON -DPY_VERSION_INFO=dev -DBUILD_EXAMPLES=ON
cmake --build build -j8 --config Release
```

See [build.md](./BUILD.md) for other options such as building only the Janus library.

## Primary Contributers

## Janus Contributors

- Geoff Brian
- Shane Hill
- Dan Newman
- Rob Curtin
- Rob Porter
- Mike Young
- Jon Dansie
- Kylie Bedwell
- Mike Grant

## PyJanus Contributuers

- Alwin Wang

## Licences

### Janus Licence

Janus is released under the MIT licence. Licence text:

> DST Janus Library (Janus DAVE-ML Interpreter Library)
>
> Defence Science and Technology (DST) Group
> Department of Defence, Australia.
> 506 Lorimer St
> Fishermans Bend, VIC
> AUSTRALIA, 3207
>
> Copyright 2005-2021 Commonwealth of Australia
>
> Permission is hereby granted, free of charge, to any person obtaining a copy of this
> software and associated documentation files (the "Software"), to deal in the Software
> without restriction, including without limitation the rights to use, copy, modify,
> merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
> permit persons to whom the Software is furnished to do so, subject to the following
> conditions:
>
> The above copyright notice and this permission notice shall be included in all copies
> or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
> INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
> PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
> LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
> OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
> OTHER DEALINGS IN THE SOFTWARE.

### Ute Licence

Ute is released under the MIT licence. Licence text:

> DST Ute Library (Utilities Library)
>
> Defence Science and Technology (DST) Group
> Department of Defence, Australia.
> 506 Lorimer St
> Fishermans Bend, VIC
> AUSTRALIA, 3207
>
> Copyright 2005-2021 Commonwealth of Australia
>
> Permission is hereby granted, free of charge, to any person obtaining a copy of this
> software and associated documentation files (the "Software"), to deal in the Software
> without restriction, including without limitation the rights to use, copy, modify,
> merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
> permit persons to whom the Software is furnished to do so, subject to the following
> conditions:
>
> The above copyright notice and this permission notice shall be included in all copies
> or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
> INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
> PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
> LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
> OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
> OTHER DEALINGS IN THE SOFTWARE.

### pyJanus Licence

pyJanus is released under the MIT licence. Licence text:

> pyJanus (Python Bindings for Janus)
>
> Copyright (c) 2022 Alwin Wang
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE.
