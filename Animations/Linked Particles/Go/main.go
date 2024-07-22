package main

import rl "github.com/gen2brain/raylib-go/raylib"

// ---------------------------------------------------------------------------------------------------------------------

func main() {
	game := Game{
		width:               1000,
		height:              1000,
		title:               "Particles",
		targetFPS:           144,
		backgroundColor:     &rl.Black,
		totalParticles:      1000,
		mouseRadius:         250,
		linkDistance:        200,
		powerPushMultiplier: 3.0,
	}
	game.init()
	game.run()
}

// ---------------------------------------------------------------------------------------------------------------------
