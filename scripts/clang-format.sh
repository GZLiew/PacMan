cmake -Htest -Bbuild/test
cmake --build build/test --target format
cmake --build build/test --target fix-format