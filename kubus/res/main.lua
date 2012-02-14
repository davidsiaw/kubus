-- main script
-- this is where the top level game layout is implemented

-- game object
-- things prefixed with make return a thing you need to destroy
-- things prefixed with get return things you don't have to worry about
-- things prefixed with do block until the task is finished

img = game.getImage("misc/kubus.png")
img2 = game.getImage("misc/bunnybusiness.png")
img3 = game.getImage("misc/presents.png")

scene = game.makeIntermissionScene(img)
scene2 = game.makeIntermissionScene(img2)
scene3 = game.makeIntermissionScene(img3)

game.doScene(scene2)

game.doScene(scene3)

game.doScene(scene)


game.destroy(scene)
game.destroy(scene2)

game.doExit();
