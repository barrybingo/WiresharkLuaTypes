require("wiresharktypes")

function typeof(obj)
    local mt = getmetatable(obj)
    return mt and mt.__typeof or obj.__typeof or type(obj)
end

require("int64")
require("struct")