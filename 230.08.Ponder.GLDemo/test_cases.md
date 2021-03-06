Test Cases

Class under test: Velocity Input parameters Output
test_setDx_invalid          (‘string’)      ERROR: invalid
test_setDx_valid            (-100.00)       dx = -100.00
test_setDy_invalid          (‘string’)      ERROR: invalid
test_setDy_valid            (-100.00)       dy = -100.00
test_set_invalid            (‘string’, 100) ERROR: invalid
test_set_valid              (100, 100)      dx = 100, dy = 100
test_addDx_invalid          (‘string’)      ERROR: invalid
test_addDx_valid            (40)            dx += 40
test_addDy_invalid          (‘string’)      Error: invalid
test_addDy_valid            (-40)           dy += -40
test_add_invalid            (‘string’, 40)  ERROR: invalid
test_add_valid              (40, 40)        dx += 40, dy += 40
test_addMagnitude_invalid   (2, -100)       ERROR: invalid
test_addMagnitude_valid     (2, 100)        dx += 100cos(2), dy += 100sin(2)



Class under test: Artillery     Input parameters                        Output 
test_initialize_invalidPoint    point = (-1, 1)                         ERROR: invalid point
test_initialize_invalidVel      velocity = (1, 1)                       ERROR: starting velocity should be 0
test_initialize_invalidTime     time = 10                               ERROR: starting hang time should be 0
test_initialize_valid           ((150, 200), (800, 800), (0 , 0 ), 0)   point = (150, 200) ScreenTopRight = (800, 800) velocity = (0, 0) time = 0
test_getAltitude_invalidTime    at t = -1                               point.gety = 0
test_getAltitude_validTime      at t = 10                               point.gety >= 0
test_getSpeed_invalidTime       at t = -1                               velocity.getSpeed = 0
test_getSpeed_validTime         at t = 10                               velocity.getSpeed >= 0
test_getDistance_invalidTime    at t = -1                               point.getx = 0
test_getDistance_validTime      at t = 10                               point.getx >= 0 
test_getHangTime_invalidTime    at t = -1                               time = 0
test_getHangTime_validTime      at t = 10                               time >= 0


