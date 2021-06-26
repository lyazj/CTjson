# CTjson

A C++ template library for JSON

## Convert C++ object to JSON string

Class `CTjson::ojsonstream`, derived from `std::ostream` protectedly, can convert any C++ object to JSON string conveniently, with `operator<<` well defined.

These are basic rules:

1. `nullptr` -> `null`
2. `(std::string)"STL-string"` -> `"STL-string"`
   `(const char *)"Cstyle-string"` -> `"Cstyle-string"`
   `(const char *)NULL` -> `null`
3. `(int)1` -> `1` (as well as any integer type)
4. `(double)1.0` -> `1.000000` (as well as any float type)
5. `(bool)true` -> `true` (as well as false)
6. `std::vector<int>{1, 2, 3}` -> `[1, 2, 3]` (as well as any `CTjson::ojsonstream` object `ojs` and any object `t` with `ojs << *std::begin(t)` defined)
7. 
       std::map<std::string, int>{{"a", 1}, {"b", 2}}

   ->

       {
           "a": 1,
           "b": 2
       }

   (as well as any `CTjson::ojsonstream` object `ojs` and any object `t` with both `std::string(std::begin(t)->first)` and `ojs << std::begin(t)->second` defined)

The last 2 rules are especially significant, depending on which a JSON string could be generated recursively. Note that C++ defines overloading function `std::begin` for most STL containers and built-in arrays, but without any pointer. So rule 6 works with built-in arrays but not with pointers, safely.

These are C++ types work with rule 6 conventionally, with suitable type `T`:

    T []
    std::array<T>
    std::vector<T>
    std::deque<T>
    std::list<T>
    std::forward_list<T>
    std::set<T>
    std::multiset<T>
    std::unordered_set<T>
    std::unordered_multiset<T>

These are C++ types work with rule 7 conventionally, with suitable type `T`:

    std::map<std::string, T>
    std::multimap<std::string, T>
    std::unordered_map<std::string, T>
    std::unordered_multimap<std::string, T>

`const char *` is accepted if not `std::string` as the first template argument, however not a sensible design in most cases.

**DO NOT** use `std::vector<std::pair<std::string, T>>`, etc., in case of semantic ambiguity.

### Create a stream object to output JSON string

`CTjson::ojsonstream` objects can only be created by providing a pointer to `std::basic_streambuf<char>` object. The only constructor is declared as:

    ojsonstream(std::basic_streambuf<char> *)

Use `rdbuf()` to get this pointer from an opened output stream is recommended, for example:

    ojsonstream ojs(cout.rdbuf());

To get a `std::string` object containing JSON string, use `std::ostringstream`, for example:

    std::ostringstream oss;
    ojsonstream ojs(oss.rdbuf());

### Get base reference for further manipulation

By default, `std::boolalpha`, `std::fixed`, `std::setprecision(6)` is used during construction. Use `ojsonstream::base()` to get reference to a `ojsonstream` object's base(`std::ostream`) object for further manipulation.

### Set indentation

By default, a `CTjson::endl` manipulation makes a break line and add 4 spaces of indentation. Use `ojsonstream::setindent()` to change this behavior. The function is declared as:

    setindent(char c, size_t cnt = (size_t)-1);

If argument `cnt` is not provided or equals to `(size_t)-1`, the value is set as:

* 4, if `c == ' '`
* 1, if `c == '\t'`
* 0, otherwise

To disable indentation for `CTjson::ojsonstream` object `ojs`, use:

    ojs.setindent(0);

### Convert your own C++ class

Use this function:

    template<class... Args>
    inline auto prt_obj(ojsonstream &ojs, Args &&...args)
      -> decltype(prt_pair(ojs, std::forward<Args>(args)...));

Return type deduction makes sure type of any argument is suitable and may avoid conflicting efficiently. Take an example of this [sample](CTjson_sam.cpp).
