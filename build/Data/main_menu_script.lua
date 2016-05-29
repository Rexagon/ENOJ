-- require's go here
require 'test_object.lua'

scenes.main_menu = {
    on_init = function()
        print(objects.test_object.name)
    end,
    on_update = function(dt)
        
    end,
    on_draw = function(dt)
        
    end
}