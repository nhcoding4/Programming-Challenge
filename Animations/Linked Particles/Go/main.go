package main

import rl "github.com/gen2brain/raylib-go/raylib"

// ---------------------------------------------------------------------------------------------------------------------

func main() {
	game := Game{
		width:           1800,
		height:          1000,
		title:           "Particles",
		targetFPS:       144,
		backgroundColor: &rl.Black,
		totalParticles:  1500,
		mouseRadius:     750,
	}
	game.init()
	game.run()
}

// ---------------------------------------------------------------------------------------------------------------------
