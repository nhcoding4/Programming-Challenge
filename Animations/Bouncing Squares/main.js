// --------------------------------------------------------------------------------------------------------------------
var Box = /** @class */ (function () {
    function Box(x, y, height, width, canvasWidth, canvasHeight, context, colour) {
        this.x = x;
        this.y = y;
        this.height = height;
        this.width = width;
        this.canvasHeight = canvasHeight;
        this.canvasWidth = canvasWidth;
        this.context = context;
        this.colour = colour;
        this.movementX = this.setSpeed();
        this.movementY = this.setSpeed();
        this.randomizeDirection();
    }
    // -----------------------------------------------------
    // Draw the asset on the canvas.
    Box.prototype.draw = function () {
        var _a;
        if (this.context != null) {
            this.context.fillStyle = this.colour;
        }
        (_a = this.context) === null || _a === void 0 ? void 0 : _a.fillRect(this.x, this.y, this.width, this.height);
    };
    // -----------------------------------------------------
    // Set the random direction for the object.
    Box.prototype.randomizeDirection = function () {
        var randomize = (function (direction) {
            var choice = Math.floor(Math.random() * 2);
            return (choice == 0) ? direction *= -1 : direction;
        });
        this.movementX = randomize(this.movementX);
        this.movementY = randomize(this.movementY);
    };
    // -----------------------------------------------------
    // Set the speed of the object.
    Box.prototype.setSpeed = function () {
        var i;
        i = Math.floor(Math.random() * 2 + 1);
        return i;
    };
    // -----------------------------------------------------
    // Updates the position to be drawn on the next frame.
    Box.prototype.update = function () {
        var objectXEdge = this.x + this.width;
        var objectYEdge = this.y + this.height;
        if (this.x <= 0 || objectXEdge >= this.canvasWidth) {
            if (this.movementX > 0) {
                this.movementX = this.setSpeed();
                this.movementX *= -1;
            }
            else {
                this.movementX = this.setSpeed();
            }
            if (this.x < 0) {
                this.x = 0;
            }
            if (this.x > this.canvasWidth) {
                this.x = this.canvasWidth;
            }
        }
        if (this.y <= 0 || objectYEdge >= this.canvasHeight) {
            if (this.movementY > 0) {
                this.movementY = this.setSpeed();
                this.movementY *= -1;
            }
            else {
                this.movementY = this.setSpeed();
            }
            if (this.y < 0) {
                this.y = 0;
            }
            if (this.y > this.canvasHeight) {
                this.y = this.canvasHeight;
            }
        }
        this.x += this.movementX;
        this.y += this.movementY;
    };
    return Box;
}());
// --------------------------------------------------------------------------------------------------------------------
var Game = /** @class */ (function () {
    function Game() {
        this.enemies = [];
        this.height = 1000;
        this.width = 500;
        this.totalBoxes = 20;
        this.createCanvas();
        this.createBox();
    }
    // -----------------------------------------------------
    // Animate assets.
    Game.prototype.animate = function () {
        var _this = this;
        var _a;
        (_a = this.context) === null || _a === void 0 ? void 0 : _a.clearRect(0, 0, this.width, this.height);
        for (var _i = 0, _b = this.enemies; _i < _b.length; _i++) {
            var object = _b[_i];
            object.draw();
            object.update();
        }
        requestAnimationFrame(function () {
            _this.animate();
        });
    };
    // -----------------------------------------------------
    // Canvas properties.
    Game.prototype.createCanvas = function () {
        var canvas = document.createElement("canvas");
        canvas.setAttribute("id", "canvas");
        canvas.height = this.height;
        canvas.width = this.width;
        canvas.style.border = "3px solid black";
        canvas.style.position = "absolute";
        canvas.style.top = "50%";
        canvas.style.left = "50%";
        canvas.style.transform = "translate(-50%, -50%)";
        canvas.style.height = "".concat(this.height, "px");
        canvas.style.width = "".concat(this.width, "px");
        this.context = canvas.getContext("2d");
        document.body.appendChild(canvas);
        return this.canvas = canvas;
    };
    // -----------------------------------------------------
    // Create an an enemy object.
    Game.prototype.createBox = function () {
        var xSize = 20;
        var ySize = 20;
        var xPos = Math.floor(Math.random() * this.width - xSize + 1);
        var yPos = Math.floor(Math.random() * this.height - ySize + 1);
        var colours = ["red", "blue", "green", "yellow", "purple", "pink", "black"];
        var colourSelection = colours[Math.floor(Math.random() * colours.length)];
        var newBox = new Box(xPos, yPos, ySize, xSize, this.width, this.height, this.context, colourSelection);
        this.enemies.push(newBox);
    };
    // -----------------------------------------------------
    // Mainloop.
    Game.prototype.run = function () {
        for (var i = 0; i < this.totalBoxes; i++) {
            this.createBox();
        }
        this.animate();
    };
    return Game;
}());
// --------------------------------------------------------------------------------------------------------------------
window.addEventListener("load", function () {
    var game = new Game();
    game.run();
});
