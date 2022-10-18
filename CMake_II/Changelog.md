.
├── client.cpp
├── CMakeLists.txt
├── common
│   ├── rmath
│   │   ├── include
│   │   │   └── robotlab
│   │   │       └── rmath.h
│   │   └── src
│   │       └── rmath.cpp
│   └── singleton
│       └── include
│           └── robotlab
│               └── singleton.hpp
├── modules
│   ├── assembly1
│   │   ├── include
│   │   │   └── robotlab
│   │   │       └── assembly1.h
│   │   ├── src
│   │   │   └── assembly1.cpp
│   │   └── test
│   │       └── assembly1_test.cpp
│   ├── assembly2
│   │   ├── include
│   │   │   └── robotlab
│   │   │       └── assembly2.h
│   │   └── src
│   │       └── assembly2.cpp
│   ├── module1
│   │   ├── include
│   │   │   └── robotlab
│   │   │       ├── module1
│   │   │       │   ├── module1a.h
│   │   │       │   └── module1b.h
│   │   │       └── module1.hpp
│   │   └── src
│   │       ├── module1a
│   │       │   ├── m1.cpp
│   │       │   ├── m2.cpp
│   │       │   ├── m3.cpp
│   │       │   └── m4.cpp
│   │       └── module1b
│   │           └── module1b.cpp
│   └── module2
│       ├── include
│       │   └── robotlab
│       │       ├── opcua_cs
│       │       │   ├── client.hpp
│       │       │   ├── server.hpp
│       │       │   └── ua_type
│       │       │       ├── argument.hpp
│       │       │       ├── object.hpp
│       │       │       ├── open62541.h
│       │       │       ├── ua_define.hpp
│       │       │       └── variable.hpp
│       │       └── opcua_cs.hpp
│       └── src
│           ├── argument.cpp
│           ├── client.cpp
│           ├── object.cpp
│           ├── open62541.c
│           ├── server.cpp
│           └── variable.cpp
├── README.md
└── server.cpp
