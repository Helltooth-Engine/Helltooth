# Code Style

## Includes
### External Files

```cpp
#include <ExternalDir/ExternalFile>
```

### Internal Files

```cpp
#include "InteralDir/InternalFiles"
```

## Namespaces
For namespaces I usually use lower case e.g. `graphics` or abreviations e.g. `ht`

## Files
`.h` and `.c` for C and `.hpp` and `.cpp` for C++.
Lowercase naming e.g. `filesystem.hpp`

## Classes & Structs
CamelCase e.g. `FileSystem`

### Order of variables and functions
```cpp
class Foo {
private:
    //private static variables
    
    //private variables
public:
    // public static variables

    //public variables
public:
    //public static functions

    //public functions
    
    //public inlines
private:
    //private functions    
}
```

## Variables
### Modifiers
- Global: `g_`
- Static: `s_`
- Member: `m_`
- Local: *none*
- Parameter: *none*

### Naming
Modifier + CamelCase e.g. `m_Count`

**Note**: Modifiers in variable naming are not present in structs.


## Macros
Macros are all upper case, prefixed with the abreviation of the project e.g. `HT_VERSION`

## Pointers
`int* m_Ids`
**Note**: For multiple pointers, I will put them on different lines:
```cpp
int* m_Ids;
int* m_Counts;
```

## Inlining
Inlining only happens if the function is shorter than 2 lines of code, I tend to put inline functions on the same line e.g.
```cpp
inline int GetID() { return m_ID; }
```

## Passing by const reference
Passing by const reference happens if the value is greater than 4 bytes and is not a primite type. (aka `long long`, `int`, `short`, etc)

