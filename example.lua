--
-- Created by IntelliJ IDEA.
-- User: simon
-- Date: 28/10/2020
-- Time: 23:18
-- To change this template use File | Settings | File Templates.
--

window = engine.GlfwWindow("Simple timer", 800, 600)

application = Application:new()

timer = Component:new({elapsed_time = 0, total_elapsed_time = 0})

camera = engine.CameraComponent()

function timer:update(delta, input)
    self.elapsed_time = self.elapsed_time + delta
    self.total_elapsed_time = self.total_elapsed_time + delta
end

function timer:render(delta)
    if self.elapsed_time >= 3 then
        print("Elapsed time is " .. self.total_elapsed_time)
        self.elapsed_time = 0
    end
end

e = engine.Entity()

function application:initialise(input)
    e:add_component("my_timer", timer)
    --e:add_component("camera", camera)
    self.root:add_child("timer", e)
end

function application:update(delta, input)
    if input:is_key_pressed(32) then
        t = e:get_component("my_timer")
        print("Space bar", t:get("test"))
    end
end

engine = Engine:new(application, window, 60)
engine:start()

