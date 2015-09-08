#!/bin/bash

set -e

if ! [ -e capdDynSys4 ]; then
  ln -s capdDynSys capdDynSys4 # it is required in Doxyfile
fi

(cd capdMake/docs && doxygen Doxyfile)

(cd capdDynSys/docs && make doc)
tar czf capdDynSys-docs.tar.gz capdDynSys/docs/html

(cd capdRedHom/docs && make doc)
tar czf capdRedHom-docs.tar.gz capdRedHom/docs/html
