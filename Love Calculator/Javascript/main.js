"use strict";
const readline = require("readline-sync")

// --------------------------------------------------------------------------------------------------------------------

// Calculates a score based upon 2 names.

class LoveCalculator {

    // ----------------------------------------------------

    // Get 2 names from the user.

    get Name1() {
        return this.firstName = this.nameInput("Enter the name of the first person:")
    }
    get Name2() {
        return this.secondName = this.nameInput("Enter the name of the second person:")
    }

    // ----------------------------------------------------
    
    // Sum frequency of characters.

    get Record() {
        const letterRecord = {}
        const completedString = `${this.Name1}loves${this.Name2}`

        for (const letter of completedString) {
            if (!letterRecord[letter]) {
                letterRecord[letter] = 1
            } else {
                letterRecord[letter]++
            }
        }
        return this.letterRecord = letterRecord
    }

    // ----------------------------------------------------

    // Convert the record into an array of integers.

    get Numbers() {
        this.Record
        const numbers = []
        for (const letter in this.letterRecord) {
            numbers.push(this.letterRecord[letter])
        }
        return this.numbers = numbers.sort(function (a, b) { return a - b })
    }

    // ----------------------------------------------------

    // Scoring algorithm.

    get Score() {
        this.Numbers
        while (this.numbers.length > 2) {
            let i = 0
            while (i < this.numbers.length && this.numbers.length > 2) {
                this.numbers[i] += this.numbers[this.numbers.length - 1]
                this.numbers.length--
                i++
            }
        }

        return this.loveScore = `${this.numbers[0]}${this.numbers[1]}%`
    }

    // ----------------------------------------------------

    // Helper

    nameInput(prompt) {
        console.log(prompt)
        return String(readline.question())
    }
}

// --------------------------------------------------------------------------------------------------------------------

function main() {
    const game = new LoveCalculator()
    game.Score

    console.log(game.loveScore)

}

// --------------------------------------------------------------------------------------------------------------------

main()
