Wireshark Lua Types (Int64/UInt64/Struct) for LuaJIT
====================================================

Standalone Lua dll that implements [Int64/UInt64](https://www.wireshark.org/docs/wsdg_html_chunked/lua_module_Int64.html)
and [Struct](https://www.wireshark.org/docs/wsdg_html_chunked/lua_module_Struct.html)

Source from <https://github.com/wireshark/wireshark>

Build: VS2019 - x64 - LuaJIT 2.1.0-beta3       [Might work with other Lua; 6 ways to find out]

Usage:

    luajit  -lwiresharktypes

or

```lua
    require("wiresharktypes")

    local mynum = UInt64(0xDEADF007, 0x12345678)

    for i = 1, 16 do
      mynum = mynum:rol(8)
      print(mynum:tohex())
    end
```
