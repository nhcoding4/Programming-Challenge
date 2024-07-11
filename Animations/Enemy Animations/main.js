var main;
(function (main) {
    var Enemy = /** @class */ (function () {
        function Enemy(x, y, movementX, movementY, context, canvasWidth, canvasHeight, image, spriteWidth, spriteHeight) {
            this.x = x;
            this.y = y;
            this.movementX = movementX;
            this.movementY = movementY;
            this.context = context;
            this.canvasWidth = canvasWidth;
            this.canvasHeight = canvasHeight;
            this.image = image;
            this.spriteWidth = spriteWidth;
            this.spriteHeight = spriteHeight;
            this.width = spriteWidth / 3;
            this.height = spriteHeight / 3;
            this.offsetX = this.x + this.width;
            this.offsetY = this.y + this.height;
            this.currentFrame = 0;
            this.lastUpdate = new Date().getTime();
            this.updateDelta = Math.floor((Math.random() * 60) + 15) / 4;
        }
        // ------------------------------------------------------------------------------------------------------------
        // Animates an enemy and updates the position for the next frame.
        Enemy.prototype.animate = function () {
            var _a;
            (_a = this.context) === null || _a === void 0 ? void 0 : _a.drawImage(this.image, this.currentFrame * this.spriteWidth, 0, this.spriteWidth, this.spriteHeight, this.x, this.y, this.width, this.height);
            this.update();
        };
        // ------------------------------------------------------------------------------------------------------------
        // Calculate the adjusted X and Y pos considering the object size.
        Enemy.prototype.calculateOffset = function () {
            this.offsetX = this.x + this.width;
            this.offsetY = this.y + this.height;
        };
        // ------------------------------------------------------------------------------------------------------------
        // Reverses the object direction if a collision with the edge of the canvas is detected.
        Enemy.prototype.edgeCollision = function () {
            if (this.offsetX <= 0 + this.width || this.offsetX >= this.canvasWidth) {
                this.movementX *= -1;
            }
            if (this.offsetY <= 0 + this.height || this.offsetY >= this.canvasHeight) {
                this.movementY *= -1;
            }
        };
        // ------------------------------------------------------------------------------------------------------------
        // Checks if the object is out of bounds of the canvas and moves it back within. 
        Enemy.prototype.outOfBounds = function () {
            if (this.offsetX < 0) {
                this.x = this.width;
            }
            if (this.offsetX > this.canvasWidth) {
                this.x = this.canvasWidth - this.width;
            }
            if (this.offsetY < 0) {
                this.y = this.height;
            }
            if (this.offsetY > this.canvasHeight) {
                this.y = this.canvasHeight - this.height;
            }
        };
        // ------------------------------------------------------------------------------------------------------------
        // Updates the position of the object on the canvas.
        Enemy.prototype.update = function () {
            this.calculateOffset();
            this.edgeCollision();
            this.outOfBounds();
            this.updateFlyingAnimation();
            this.x += this.movementX;
            this.y += this.movementY;
            this.lastUpdate = new Date().getTime();
        };
        // ------------------------------------------------------------------------------------------------------------
        // Checks to see if enough time has passed to update the flying animation.
        Enemy.prototype.updateFlyingAnimation = function () {
            var _this = this;
            var checkDelta = function () {
                var now = new Date().getTime();
                if (now - _this.lastUpdate > _this.updateDelta) {
                    return true;
                }
                return false;
            };
            if (checkDelta()) {
                this.currentFrame++;
            }
            if (this.currentFrame > 4) {
                this.currentFrame = 0;
            }
        };
        return Enemy;
    }());
    main.Enemy = Enemy;
})(main || (main = {}));
/// <reference path="enemy.ts" />
var main;
(function (main) {
    var Game = /** @class */ (function () {
        function Game() {
            this.enemies = [];
            this.images = [];
            this.canvasHeight = 1000;
            this.canvasWidth = 500;
            this.enemiesNumber = 10;
            this.targetFPS = 60;
            this.targetUpdateDelta = 1000 / this.targetFPS;
            this.createCanvas();
            this.createContext();
            this.loadImages();
            this.createEnemy();
            this.lastUpdate = new Date().getTime();
        }
        // ------------------------------------------------------------------------------------------------------------
        // Animates all the elements
        Game.prototype.animate = function () {
            var _this = this;
            var _a;
            if (this.updateFrame()) {
                (_a = this.context) === null || _a === void 0 ? void 0 : _a.clearRect(0, 0, this.canvasWidth, this.canvasHeight);
                for (var _i = 0, _b = this.enemies; _i < _b.length; _i++) {
                    var enemy = _b[_i];
                    enemy.animate();
                }
                this.lastUpdate = new Date().getTime();
            }
            requestAnimationFrame(function () {
                _this.animate();
            });
        };
        // ------------------------------------------------------------------------------------------------------------
        // Create a new canvas element to draw on.
        Game.prototype.createCanvas = function () {
            var newCanvas = document.createElement("canvas");
            newCanvas.width = this.canvasWidth;
            newCanvas.height = this.canvasHeight;
            newCanvas.style.border = "3px solid";
            newCanvas.style.position = "absolute";
            newCanvas.style.top = "50%";
            newCanvas.style.left = "50%";
            newCanvas.style.transform = "translate(-50%, -50%)";
            newCanvas.style.height = "".concat(this.canvasHeight, "px");
            newCanvas.style.width = "".concat(this.canvasWidth, "px");
            document.body.appendChild(newCanvas);
            return this.canvas = newCanvas;
        };
        // ------------------------------------------------------------------------------------------------------------
        // Get the canvas context.
        Game.prototype.createContext = function () {
            return this.context = this.canvas.getContext("2d");
        };
        // ------------------------------------------------------------------------------------------------------------
        // Creates a new enemy object.
        Game.prototype.createEnemy = function () {
            for (var i = 0; i < this.enemiesNumber; i++) {
                var spriteDimensions = [[293, 155]];
                var enemyWidth = 57;
                var enemyHeight = 30;
                var speedX = Math.floor(Math.random() * 5) - 5;
                var speedY = Math.floor(Math.random() * 5) - 5;
                var startX = Math.floor(Math.random() * this.canvasWidth - enemyWidth) + enemyWidth;
                var startY = Math.floor(Math.random() * this.canvasHeight - enemyHeight) + enemyHeight;
                var image = this.images[0];
                var spriteWidth = spriteDimensions[0][0];
                var spriteHeight = spriteDimensions[0][1];
                var newEnemy = new main.Enemy(startX, startY, speedX, speedY, this.context, this.canvasWidth, this.canvasHeight, image, spriteWidth, spriteHeight);
                this.enemies.push(newEnemy);
            }
        };
        // ------------------------------------------------------------------------------------------------------------
        // Loads images from file.
        Game.prototype.loadImages = function () {
            var prefix = "./enemies/";
            var paths = ["enemy1", "enemy2", "enemy3", "enemy4"];
            var suffix = ".png";
            for (var i = 0; i < paths.length; i++) {
                var enemyImage = new Image();
                enemyImage.src = "".concat(prefix).concat(paths[i]).concat(suffix);
                this.images.push(enemyImage);
            }
        };
        // ------------------------------------------------------------------------------------------------------------
        Game.prototype.updateFrame = function () {
            var now = new Date().getTime();
            var timeDelta = Math.abs(now - this.lastUpdate);
            if (timeDelta > this.targetUpdateDelta) {
                return true;
            }
            return false;
        };
        return Game;
    }());
    main.Game = Game;
})(main || (main = {}));
/// <reference path="game.ts" />
var main;
(function (main_1) {
    function main() {
        var game = new main_1.Game();
        game.animate();
    }
    main();
})(main || (main = {}));
