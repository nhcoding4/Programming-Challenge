var main;
(function (main) {
    var Enemy = /** @class */ (function () {
        function Enemy(x, y, width, height, context) {
            this.x = x;
            this.y = y;
            this.width = width;
            this.height = height;
            this.context = context;
        }
        // ------------------------------------------------------------------------------------------------------------
        // Animates an enemy.
        Enemy.prototype.animate = function () {
            var _a;
            (_a = this.context) === null || _a === void 0 ? void 0 : _a.fillRect(this.x, this.y, this.width, this.height);
        };
        return Enemy;
    }());
    main.Enemy = Enemy;
})(main || (main = {}));
