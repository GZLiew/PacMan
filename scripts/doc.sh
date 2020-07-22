cmake -Hdocumentation -Bbuild/doc
cmake --build build/doc --target GenerateDocs
open build/doc/doxygen/html/index.html