package main

import (
	rl "github.com/gen2brain/raylib-go/raylib"
)

// --------------------------------------------------------------------------------------------------------------------

func main() {

	// -------------------------------

	// Create Window, cell size and set fps. Keep the aspect ratio 16:9 for correct fullscreen fill.
	const screen_width = 1920
	const screen_height = 1080
	const cells_size = 5
	const title = "Game of Life"
	target_fps := int32(60)
	rl.InitWindow(screen_width, screen_height, title)
	rl.SetTargetFPS(target_fps)

	// Create a simulation object. This controls the game.
	simulation := Simulation{cell_size: cells_size, height: screen_height, width: screen_width, run: false}
	simulation.Populate_Grid()

	// -------------------------------

	// Mainloop.

	for !rl.WindowShouldClose() {

		// -------------------------------
		// User Input.

		key := rl.GetKeyPressed()
		simulation.Input_Actions(key, &target_fps)

		if rl.IsMouseButtonDown(rl.MouseButtonLeft) {
			simulation.Mouse_Function()
		}

		// -------------------------------

		simulation.Update()

		// -------------------------------

		rl.BeginDrawing()

		rl.ClearBackground(rl.DarkGray)

		simulation.grid.Draw()

		rl.EndDrawing()

		// -------------------------------
	}

	rl.CloseWindow()
}

// --------------------------------------------------------------------------------------------------------------------
