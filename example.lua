--
-- Created by IntelliJ IDEA.
-- User: simon
-- Date: 28/10/2020
-- Time: 23:18
-- To change this template use File | Settings | File Templates.
--
--require("libexample-lib")
--angle = gem.angle.from_degrees(180)
--print(angle.degrees, angle.radians)
--print(example)

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

--v = gem.vector2i(17, 7)
--v3 = gem.vector3f(5, 6, 7)
--print(v)
--print(v3)
--print(v3.z, v3.y, v3.x)
--
--for a in v3 do
--    print('A is ', a)
--end

print(dump(gem))
print(gem.PI)