/// <reference path="enemy.ts" />

namespace main {

    export class Game {
        private canvas: HTMLCanvasElement
        private context: CanvasRenderingContext2D | null
        private canvasHeight: number
        private canvasWidth: number
        private enemiesNumber: number
        private enemies: Enemy[] = []
        private images: HTMLImageElement[] = []
        private targetFPS: number
        private targetUpdateDelta: number
        private lastUpdate: number

        constructor() {
            this.canvasHeight = 1000
            this.canvasWidth = 500
            this.enemiesNumber = 10
            this.targetFPS = 60
            this.targetUpdateDelta = 1000 / this.targetFPS
            this.createCanvas()
            this.createContext()
            this.loadImages()
            this.createEnemy()
            this.lastUpdate = new Date().getTime()
        }

        // ------------------------------------------------------------------------------------------------------------

        // Animates all the elements

        animate() {
            if (this.updateFrame()) {
                this.context?.clearRect(0, 0, this.canvasWidth, this.canvasHeight)

                for (let enemy of this.enemies) {
                    enemy.animate()
                }

                this.lastUpdate = new Date().getTime()
            }

            requestAnimationFrame(() => {
                this.animate()
            })
        }

        // ------------------------------------------------------------------------------------------------------------

        // Create a new canvas element to draw on.

        private createCanvas(): HTMLCanvasElement {
            let newCanvas = document.createElement("canvas")

            newCanvas.width = this.canvasWidth
            newCanvas.height = this.canvasHeight

            newCanvas.style.border = "3px solid"
            newCanvas.style.position = "absolute"
            newCanvas.style.top = "50%"
            newCanvas.style.left = "50%"
            newCanvas.style.transform = "translate(-50%, -50%)"
            newCanvas.style.height = `${this.canvasHeight}px`
            newCanvas.style.width = `${this.canvasWidth}px`

            document.body.appendChild(newCanvas)

            return this.canvas = newCanvas
        }

        // ------------------------------------------------------------------------------------------------------------

        // Get the canvas context.

        private createContext(): CanvasRenderingContext2D | null {
            return this.context = this.canvas.getContext("2d")
        }

        // ------------------------------------------------------------------------------------------------------------

        // Creates a new enemy object.

        private createEnemy() {
            for (let i = 0; i < this.enemiesNumber; i++) {
                let spriteDimensions = [[293, 155]]

                let enemyWidth = 57
                let enemyHeight = 30
                let speedX = Math.floor(Math.random() * 5) - 5
                let speedY = Math.floor(Math.random() * 5) - 5
                let startX = Math.floor(Math.random() * this.canvasWidth - enemyWidth) + enemyWidth
                let startY = Math.floor(Math.random() * this.canvasHeight - enemyHeight) + enemyHeight
                let image = this.images[0]
                let spriteWidth = spriteDimensions[0][0]
                let spriteHeight = spriteDimensions[0][1]

                let newEnemy = new Enemy(
                    startX,
                    startY,
                    speedX,
                    speedY,
                    this.context,
                    this.canvasWidth,
                    this.canvasHeight,
                    image,
                    spriteWidth,
                    spriteHeight,
                )
                this.enemies.push(newEnemy)
            }
        }

        // ------------------------------------------------------------------------------------------------------------

        // Loads images from file.

        private loadImages() {
            let prefix = "./enemies/"
            let paths = ["enemy1", "enemy2", "enemy3", "enemy4"]
            let suffix = ".png"

            for (let i = 0; i < paths.length; i++) {
                const enemyImage = new Image()
                enemyImage.src = `${prefix}${paths[i]}${suffix}`
                this.images.push(enemyImage)
            }
        }

        // ------------------------------------------------------------------------------------------------------------


        private updateFrame(): boolean {
            let now = new Date().getTime()
            let timeDelta = Math.abs(now - this.lastUpdate)

            if (timeDelta > this.targetUpdateDelta) {
                return true
            }
            return false
        }


        // ------------------------------------------------------------------------------------------------------------
    }
}
