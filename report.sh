#!/bin/bash

cd $(dirname $0)
mkdir -p build
if pdflatex -output-directory=build report/course-work.tex && pdflatex -output-directory=build report/course-work.tex && mv build/course-work.pdf course-work.pdf; then
    printf "\033[1;35mpdf report successfully moved to the project root directory\n"
else
    printf "\033[1;31mpdf report couldn't be moved to the project root directory: no such file\n"
fi
