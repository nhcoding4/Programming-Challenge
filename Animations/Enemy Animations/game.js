/// <reference path="enemy.ts" />
var main;
(function (main) {
    var Game = /** @class */ (function () {
        function Game() {
            this.enemies = [];
            this.canvasHeight = 1000;
            this.canvasWidth = 500;
            this.createCanvas();
            this.createContext();
            this.createEnemy();
        }
        // ------------------------------------------------------------------------------------------------------------
        // Animates all the elements
        Game.prototype.animate = function () {
            var _this = this;
            var _a;
            (_a = this.context) === null || _a === void 0 ? void 0 : _a.clearRect(0, 0, this.canvasWidth, this.canvasHeight);
            for (var _i = 0, _b = this.enemies; _i < _b.length; _i++) {
                var enemy = _b[_i];
                enemy.animate();
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
            var newEnemy = new main.Enemy(0, 0, 50, 50, this.context);
            this.enemies.push(newEnemy);
        };
        return Game;
    }());
    main.Game = Game;
})(main || (main = {}));
