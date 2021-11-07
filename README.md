# VM Translator

### Binary Info

```
Language: C++
Platform: x86_64
Compiler: g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
OS: Linux/MacOS
Tested On: Ubuntu 20.04 on WSL
```


### Class Architecture

```text
VMTranslator (Codebase)
    |___ Parser (class)
    |___ Code Generator (class)
    |___ Driver (main)
```

### C++ Concepts Covered

- STL Vector (`vector`)
- File Handling (`fstream`)
- String Tokenization using String Streams (`sstring`)
- C++ Enums