--
-- Created by IntelliJ IDEA.
-- User: simon
-- Date: 28/10/2020
-- Time: 23:18
-- To change this template use File | Settings | File Templates.
--

function dump(o)
    if type(o) == 'table' then
        local s = '{ '
        for k,v in pairs(o) do
            if type(k) ~= 'number' then k = '"'..k..'"' end
            s = s .. '['..k..'] = ' .. dump(v) .. ','
        end
        return s .. '} '
    else
        return tostring(o)
    end
end

print(dump(engine))