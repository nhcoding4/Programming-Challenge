namespace main {

    export class Enemy {
        private offsetX: number
        private offsetY: number
        private width: number
        private height: number
        private currentFrame: number
        private lastUpdate: number
        private updateDelta: number

        constructor(
            private x: number,
            private y: number,
            private movementX: number,
            private movementY: number,
            private context: CanvasRenderingContext2D | null,
            private canvasWidth: number,
            private canvasHeight: number,
            private image: HTMLImageElement,
            private spriteWidth: number,
            private spriteHeight: number,
        ) {
            this.width = spriteWidth / 3
            this.height = spriteHeight / 3
            this.offsetX = this.x + this.width
            this.offsetY = this.y + this.height
            this.currentFrame = 0
            this.lastUpdate = new Date().getTime()
            this.updateDelta = Math.floor((Math.random() * 60) + 15) / 4

        }

        // ------------------------------------------------------------------------------------------------------------

        // Animates an enemy and updates the position for the next frame.

        public animate() {
            this.context?.drawImage(
                this.image,
                this.currentFrame * this.spriteWidth,
                0,
                this.spriteWidth,
                this.spriteHeight,
                this.x,
                this.y,
                this.width,
                this.height
            )
            this.update()
        }

        // ------------------------------------------------------------------------------------------------------------

        // Calculate the adjusted X and Y pos considering the object size.

        private calculateOffset() {
            this.offsetX = this.x + this.width
            this.offsetY = this.y + this.height
        }

        // ------------------------------------------------------------------------------------------------------------

        // Reverses the object direction if a collision with the edge of the canvas is detected.

        private edgeCollision() {
            if (this.offsetX <= 0 + this.width || this.offsetX >= this.canvasWidth) {
                this.movementX *= -1
            }

            if (this.offsetY <= 0 + this.height || this.offsetY >= this.canvasHeight) {
                this.movementY *= -1
            }
        }

        // ------------------------------------------------------------------------------------------------------------

        // Checks if the object is out of bounds of the canvas and moves it back within. 

        private outOfBounds() {
            if (this.offsetX < 0) {
                this.x = this.width
            }
            if (this.offsetX > this.canvasWidth) {
                this.x = this.canvasWidth - this.width
            }
            if (this.offsetY < 0) {
                this.y = this.height
            }
            if (this.offsetY > this.canvasHeight) {
                this.y = this.canvasHeight - this.height
            }
        }

        // ------------------------------------------------------------------------------------------------------------

        // Updates the position of the object on the canvas.

        private update() {
            this.calculateOffset()
            this.edgeCollision()
            this.outOfBounds()
            this.updateFlyingAnimation()

            this.x += this.movementX
            this.y += this.movementY

            this.lastUpdate = new Date().getTime()
        }

        // ------------------------------------------------------------------------------------------------------------

        // Checks to see if enough time has passed to update the flying animation.

        private updateFlyingAnimation() {
            let checkDelta = () => {
                let now = new Date().getTime()
                if (now - this.lastUpdate > this.updateDelta) {
                    return true
                }
                return false
            }

            if (checkDelta()) {
                this.currentFrame++
            }
            if (this.currentFrame > 4) {
                this.currentFrame = 0
            }
        }

        // ------------------------------------------------------------------------------------------------------------
    }
}